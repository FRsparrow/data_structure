#include <iostream>
#include <stack>
#include <unordered_map>

#define MAX_EXPRESSION_LENGTH 100

using namespace std;

unordered_map<char, int> in_stack_priority = {{';', 0}, {'(', 1}, {'*', 5}, {'/', 5}, {'%', 5}, {'+', 3}, {'-', 3}, {')', 6}};
unordered_map<char, int> in_coming_priority = {{';', 0}, {'(', 6}, {'*', 4}, {'/', 4}, {'%', 4}, {'+', 2}, {'-', 2}, {')', 1}};

bool is_letter(char ch)
 {
     return (ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <= 'z');
//     return ch >= '0' && ch <= '9';
 }

/*
操作符栈初始化，将结束符‘;’进栈。然后读入中缀表达式字符流的首字符ch。
重复执行以下步骤，直到ch = ‘;’，同时栈顶的操作符也是‘;’，停止循环。
    若ch是操作数直接输出，读入下一个字符ch。
    若ch是操作符，判断ch的优先级icp和位于栈顶的操作符op的优先级isp：
        若 icp(ch) > isp(op)，令ch进栈，读入下一个字符ch。
        若 icp(ch) < isp(op)，退栈并输出。
        若 icp(ch) == isp(op)，退栈但不输出，若退出的是“(”号读入下一个字符ch。
算法结束，输出序列即为所需的后缀表达式。
 */
int infix2postfix(char infix[], char postfix[])
{
    stack<char> stack;

//    cout << in_stack_priority.at('(');
    int in_index = 0, post_index = 0;
    stack.push(';');
    while(stack.top() != ';' || infix[in_index] != ';')
    {
//        cout << in_index;
        if (is_letter(infix[in_index]))
        {
            postfix[post_index++] = infix[in_index++];
        }
        else
        {
            int icp = in_coming_priority.at(infix[in_index]);
            int isp = in_stack_priority.at(stack.top());
            if (icp > isp)
            {
                stack.push(infix[in_index++]);
            }
            else if (icp < isp)
            {
                postfix[post_index++] = stack.top();
                stack.pop();
            }
            else
            {
                if (stack.top() == '(')
                {
                    ++in_index;
                }
                stack.pop();
            }

        }
    }

    return post_index;
}

int op(int a1, int a2, char op)
{
    switch(op)
    {
        case '+':
            return a1 + a2;
        case '-':
            return a1 - a2;
        case '/':
            return a1 / a2;
        case '*':
            return a1 * a2;
        default:
            return 0;
    }
}

int compute_infix(char infix[]){
    int index = 0;
    stack<char> optr_stack;
    stack<int> opnd_stack;
    optr_stack.push(';');

    while(optr_stack.top() != ';' || infix[index] != ';')
    {
        if (isdigit(infix[index]))
        {
            opnd_stack.push(infix[index++] - '0');
        }
        else {
            int icp = in_coming_priority.at(infix[index]);
            int isp = in_stack_priority.at(optr_stack.top());
            if (icp > isp) {
                optr_stack.push(infix[index++]);
            } else if (icp < isp) {
                int a2 = opnd_stack.top();
                opnd_stack.pop();
                int a1 = opnd_stack.top();
                opnd_stack.pop();
                opnd_stack.push(op(a1, a2, optr_stack.top()));
                optr_stack.pop();
            } else {
                if (optr_stack.top() == '(') {
                    optr_stack.pop();
                    ++index;
                }

            }
        }
    }

    return opnd_stack.top();
}

// 读入中缀表达式
void read_infix(char infix[]){
    char ch;
    int count = 0;
    printf("请输入中缀表达式：\n");
    while((ch = getchar()) != '\n')
    {
        infix[count++] = ch;
    }
    infix[count] = ';';
}

int main()
{
    char infix[MAX_EXPRESSION_LENGTH], postfix[MAX_EXPRESSION_LENGTH];

    read_infix(infix);

//    infix2postfix(infix, postfix);
//
//    printf("%s", postfix);

    printf("结果=%d\n", compute_infix(infix));

    system("pause");
    return 0;
}
