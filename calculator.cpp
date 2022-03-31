#include "General.h"

stack<double> num;
stack<char> op;

void eval()
{
    auto b = num.top(); num.pop();//ע��b��a��˳��Խ����ջ��˵������룬˵���ڱ��ʽ�ұߣ�����ζ�Ŵ�ջ���ó����������ǼӼ��˳����������ó��������ǡ������Ӽ��˳�����
    auto a = num.top(); num.pop();
    auto c = op.top(); op.pop();
    double x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else if (c == '/') x = a / b;
    num.push(x);
}

string calculator(string str)
{
    bool state = true;
    string res;

    //��ʼ��,���
    unordered_map<char, int> pr{ {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    while (num.size()) num.pop();
    while (op.size()) op.pop();

    int last_op = 3, cnt = 0;//cnt��¼���������Ƿ�Ϸ�
    /*
    ��¼��һ���ַ���״̬
    1�����֣�2����������3��ǰ���Ż���ǰ���ַ�
    */
    for (int i = 0; i < str.size(); i++)
    {
        auto c = str[i];
        if (c == ' ') continue;
        else if (isdigit(c) || (last_op == 3 && c == '-'))//�����ֻ���ǰһλ�ǣ����ұ�λ�Ǹ���
        {
            last_op = 1;
            double x = 0;
            if (c == '-')
            {
                i++;
                if (!isdigit(str[i]))
                {
                    res += "����Ĳ�����,λ��:" + to_string(i);
                    state = false; break;
                }
            }
            int j = i;
            while (j < str.size() && isdigit(str[j]))
                x = x * 10 + str[j++] - '0';
            if (str[j] == '.')
            {
                int t = 0;
                j++;
                while (j < str.size() && isdigit(str[j]))
                {
                    x = x * 10 + str[j++] - '0';
                    t++;
                }

                if (str[j] == '.' || str[j - 1] == '.')//һ����������С���㣬��С�����û������ֱ���������
                {
                    res += "�����С��,λ��:" + to_string(j + 1);
                    state = false; break;
                }

                while (t--) x *= 0.1;
            }
            i = j - 1;

            if (c == '-') x = -x;
            num.push(x);
        }
        else if (c == '(')
        {
            if (last_op == 1)
            {
                res += "ȱ�ٲ�����,λ��:" + to_string(i + 1);
                state = false; break;
            }
            last_op = 3;

            op.push(c);
            cnt++;
        }
        else if (c == ')')
        {
            if (cnt <= 0)
            {
                res += "������������,λ��:" + to_string(i + 1);
                state = false; break;
            }
            else if (last_op == 3)
            {
                res += "�����ڱ��ʽΪ��,λ��:" + to_string(i + 1);
                state = false; break;
            }
            cnt--;

            while (op.top() != '(') eval();
            op.pop();
        }
        else
        {
            if (last_op != 1)//���ò�����
            {
                res += "���������,λ��:" + to_string(i + 1);
                state = false; break;
            }
            last_op = 2;

            if (c != '+' && c != '-' && c != '*' && c != '/')
            {
                res += "������δ����,λ��:" + to_string(i + 1);
                state = false; break;
            }
            while (op.size() && op.top() != '(' && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    if (state && cnt)
    {
        res += "������������,��������������";
        state = false;
    }
    else if (state && last_op == 2)
    {
        res += "����ʽ������";
        state = false;
    }

    if (state)
    {
        while (op.size()) eval();

        string ans = to_string(num.top());
        for (int i = 0; i < ans.size(); i++)
        {
            if (ans[i] == '.')
            {
                res += '.';
                res += ans[i + 2] <= '4' ? ans[i + 1] : ans[i + 1] + 1;
                break;
            }
            else res += ans[i];
        }
    }

    return res;
}
