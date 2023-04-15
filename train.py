from torch.optim import AdamW

import csv
from config import Config
# from transformers import AutoTokenizer
import os


from models import BartTranslation
import torch

from dataset import TranslationDataset
from torch.utils.data import DataLoader
from tqdm import tqdm
from evaluate import CiderD
from tools import FGM
# from tools import EMA

def seq_to_str(seq):
    ignore_tokens = {0, 101, 102}  # Add other token IDs if needed
    string_list = [str(token_id.item()) for token_id in seq if token_id.item() not in ignore_tokens]
    output_string = ' '.join(string_list)
    return output_string


def evaluate(model, loader):
    device = torch.device('cuda:0') if torch.cuda.is_available() else torch.device('cpu')

    res, gts = [], {}
    tot = 0
    for batch in tqdm(loader):
        input_ids = batch['description_encodings']['input_ids'].to(device)
        attention_mask = batch['description_encodings']['attention_mask'].to(device)
        output_ids = batch['diagnosis_encodings']['input_ids']
        result = model.generate(input_ids, attention_mask=attention_mask)
        result = result.cpu().numpy()
        for i in range(output_ids.shape[0]):
            # res.append({'image_id': tot, 'caption': [tokenizer.decode(result[i], skip_special_tokens=True)]})
            # gts[tot] = [tokenizer.decode(output_ids[i], skip_special_tokens=True)]
            res.append({'image_id': tot, 'caption': [seq_to_str(result[i])]})
            gts[tot] = [seq_to_str(output_ids[i])]
            tot += 1

    CiderD_scorer = CiderD(df='corpus', sigma=15)
    cider_score, cider_scores = CiderD_scorer.compute_score(gts, res)
    return cider_score


def train():
    # tokenizer = AutoTokenizer.from_pretrained("fnlp/bart-base-chinese")
    device = torch.device('cuda:0') if torch.cuda.is_available() else torch.device('cpu')

    # 加载模型
    model = BartTranslation(pretrain_model_path)
    model = model.to(device)
    model.train()

    # 加载数据
    train_dataset = TranslationDataset(conf['train_file'], max_length=conf['max_length'])
    train_loader = DataLoader(train_dataset, batch_size=conf['batch'], shuffle=True, drop_last=False)

    valid_dataset = TranslationDataset(conf['valid_file'], max_length=conf['max_length'])
    valid_loader = DataLoader(valid_dataset, batch_size=conf['batch'], shuffle=True, drop_last=False)

    # 初始化FGM
    fgm = FGM(model)

    # # 在训练循环之前实例化 EMA
    # ema = EMA(model, decay=0.999)

    # 定义分层学习率
    encoder_lr = 1e-5
    decoder_lr = 5e-5

    # 根据参数名称为编码器和解码器设置不同的学习率
    param_optimizer = list(model.named_parameters())
    no_decay = ["bias", "LayerNorm.bias", "LayerNorm.weight"]
    optimizer_grouped_parameters = [
        {
            "params": [p for n, p in param_optimizer if
                       "bart.model.encoder" in n and not any(nd in n for nd in no_decay)],
            "lr": encoder_lr,
            "weight_decay": 0.01,
        },
        {
            "params": [p for n, p in param_optimizer if "bart.model.encoder" in n and any(nd in n for nd in no_decay)],
            "lr": encoder_lr,
            "weight_decay": 0.0,
        },
        {
            "params": [p for n, p in param_optimizer if
                       "bart.model.decoder" in n and not any(nd in n for nd in no_decay)],
            "lr": decoder_lr,
            "weight_decay": 0.01,
        },
        {
            "params": [p for n, p in param_optimizer if "bart.model.decoder" in n and any(nd in n for nd in no_decay)],
            "lr": decoder_lr,
            "weight_decay": 0.0,
        },
    ]

    optim = AdamW(optimizer_grouped_parameters)

    log = conf['model_dir'] + '/output.txt'

    # loss_function = CrossEntropyLoss(ignore_index=-100)

    for epoch in range(conf['n_epoch']):
        for i, batch in enumerate(train_loader):
            input_ids = batch['description_encodings']['input_ids'].to(device)
            input_attention_mask = batch['description_encodings']['attention_mask'].to(device)
            output_ids = batch['diagnosis_encodings']['input_ids'].to(device)
            output_attention_mask = batch['diagnosis_encodings']['attention_mask'].to(device)

            output_ids[output_attention_mask == 0] = -100

            optim.zero_grad()

            loss = model(input_ids=input_ids, attention_mask=input_attention_mask, labels=output_ids).loss

            if epoch >= conf['warm_up_epochs']:
                # 使用FGM进行对抗训练
                loss.backward()  # 计算原始梯度
                fgm.attack()  # 在embedding上添加扰动
                loss_adv = model(input_ids=input_ids, attention_mask=input_attention_mask, labels=output_ids).loss
                loss_adv.backward()  # 计算对抗梯度
                fgm.restore()  # 恢复embedding参数
            else:
                loss.backward()  # 如果在热身轮内，只计算原始梯度

            # 更新参数
            optim.step()

            # # 更新 EMA 的影子权重
            # ema.update()

            if i % 50 == 0:
                print("Epoch: ", epoch, " , step: ", i)
                print("training loss: ", loss.item())
                with open(log, "a", encoding="utf-8") as file:
                    file.write(f"Epoch: {epoch} , step: {i}\n")
                    file.write(f"training loss: {loss.item()}\n")

        if epoch >= 0:
            # # 在评估之前将影子模型的权重加载到原始模型中
            # state_dict = model.state_dict()
            # for name, param in state_dict.items():
            #     if name in ema.shadow:
            #         state_dict[name].copy_(ema.shadow[name])
            # model.load_state_dict(state_dict)

            # 测试
            model.eval()
            cider_score = evaluate(model, valid_loader)
            print("Epoch: ", epoch, " , cider_score: ", cider_score)
            with open(log, "a", encoding="utf-8") as file:
                file.write(f"Epoch: {epoch} , cider_score: {cider_score}\n")
            model.train()

            if cider_score >= 2.5:
                # 保存模型和优化器状态
                checkpoint = {
                    'model': model.state_dict(),
                    'optimizer': optim.state_dict(),
                    'epoch': epoch
                }
                torch.save(checkpoint, conf['model_dir'] + '/model_%d.pt' % epoch)

                # # 保存词表
                # tokenizer_path = conf['model_dir'] + '/model_%d_tokenizer' % epoch
                # if not os.path.exists(tokenizer_path):
                #     os.mkdir(tokenizer_path)
                # tokenizer.save_pretrained(tokenizer_path)


def inference(epoch):
    # 参数epoch表示用第几轮epoch结果进行预测

    checkpoint = torch.load(conf['model_dir'] + '/model_%d.pt' % epoch)
    device = torch.device('cuda:0') if torch.cuda.is_available() else torch.device('cpu')

    # 加载模型
    model = BartTranslation(pretrain_model_path)
    model = model.to(device)
    model.load_state_dict(checkpoint['model'])

    # optim = AdamW(model.parameters(), lr=5e-5)
    # optim.load_state_dict(checkpoint['optimizer'])

    model.eval()

    # # 加载tokenizer
    # tokenizer_path = conf['model_dir'] + '/model_%d_tokenizer' % epoch
    # tokenizer = AutoTokenizer.from_pretrained(tokenizer_path)

    test_dataset = TranslationDataset(conf['test_file'], train=False, max_length=conf['max_length'])
    test_loader = DataLoader(test_dataset, batch_size=conf['batch'], shuffle=False, drop_last=False)

    fp = open('pred.csv', 'w', newline='')
    writer = csv.writer(fp)
    tot = 0

    for batch in tqdm(test_loader):
        input_ids = batch['description_encodings']['input_ids'].to(device)
        attention_mask = batch['description_encodings']['attention_mask'].to(device)
        result = model.generate(input_ids, attention_mask=attention_mask)
        result = result.cpu().numpy()
        for i in range(result.shape[0]):
            writer.writerow([tot, seq_to_str(result[i])])
            tot += 1

    fp.close()


version = 1
conf = Config(version)

print('batch size: ')
print(conf['batch'])
print('max_length: ')
print(conf['max_length'])
print('warm_up_epoch: ')
print(conf['warm_up_epoch'])

# root = os.getcwd()
if not os.path.exists(conf['model_dir']):
    os.mkdir(conf['model_dir'])

pretrain_model_path = "/hy-tmp/baseline/pretrain/checkpoint-19300"

train()
# inference()
