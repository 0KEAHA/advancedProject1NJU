#include "General.h"

stack<double> num;
stack<char> op;

void eval()
{
    auto b = num.top(); num.pop();//注意b、a的顺序，越靠近栈顶说明后放入，说明在表达式右边，这意味着从栈先拿出来的数字是加减乘除数，【后拿出来】的是【被】加减乘除数。
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

    //初始化,清空
    unordered_map<char, int> pr{ {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    while (num.size()) num.pop();
    while (op.size()) op.pop();

    int last_op = 3, cnt = 0;//cnt记录括号数量是否合法
    /*
    记录上一个字符的状态
    1：数字，2：操作符，3：前括号或无前置字符
    */
    for (int i = 0; i < str.size(); i++)
    {
        auto c = str[i];
        if (c == ' ') continue;
        else if (isdigit(c) || (last_op == 3 && c == '-'))//是数字或者前一位是（并且本位是负号
        {
            last_op = 1;

            double x = 0;
            if (c == '-')
            {
                i++;
                if (!isdigit(str[i]))
                {
                    res += "多余的操作符,位置:" + to_string(i);
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

                if (str[j] == '.' || str[j - 1] == '.')//一个数字两个小数点，或小数点后没有数字直接是运算符
                {
                    res += "错误的小数,位置:" + to_string(j + 1);
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
                res += "缺少操作符,位置:" + to_string(i + 1);
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
                res += "括号数量错误,位置:" + to_string(i + 1);
                state = false; break;
            }
            else if (last_op == 3)
            {
                res += "括号内表达式为空,位置:" + to_string(i + 1);
                state = false; break;
            }
            cnt--;

            while (op.top() != '(') eval();
            op.pop();
        }
        else
        {
            if (last_op != 1)//连用操作符
            {
                res += "多余操作符,位置:" + to_string(i + 1);
                state = false; break;
            }
            last_op = 2;

            if (c != '+' && c != '-' && c != '*' && c != '/')
            {
                res += "操作符未定义,位置:" + to_string(i + 1);
                state = false; break;
            }
            while (op.size() && op.top() != '(' && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    if (state && cnt)
    {
        res += "括号数量错误,后括号数量不足";
        state = false;
    }
    else if (state && last_op == 2)
    {
        res += "计算式不完整";
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
