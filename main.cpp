#include <iostream>
#include <string>
using namespace std;

class Stack
{
    int top = -1;
    int size = 20;   //Max size of the stack
    string* stackList = new string[size];   //Array is used as container for stack

public:
    bool isEmpty()
    {
        return (top < 0);
    }

    bool isFull()
    {
        return (top == size - 1);
    }

    void Clear()
    {
        delete[]stackList;
        stackList = new string[size];
    }

    void Push(char element)
    {
        if (top < size)
        {
            stackList[top + 1] = element;
            top++;
        }
        else
        {
            cout << "Full!!" << endl;
        }
    }

    string Pop()
    {
        if (top >= 0)
        {
            string value = stackList[top];
            top--;
            return value;
        }
        else
        {
            return "000";
        }
    }

    string Top()
    {
        return stackList[top];
    }

    void Peak()
    {
        cout << "The element on the top of the stack is: " << stackList[top] << endl;
    }
};

class ExpressionADT
{
    int precedence(char c) {
        if (c == '^')
            return 3;
        else if (c == '/' || c == '*')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return -1;
    }

public:
    string infix_to_postfix(string expr)
    {
        Stack stk;
        string postfixExpr = "";

        for (int i = 0; i < expr.length(); i++)
        {
            if (isdigit(expr[i]))
            {
                postfixExpr += expr[i];
            }
            else if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
            {
                stk.Push(expr[i]);
            }
            else if (expr[i] == ')')
            {
                while (stk.Top() != "(")
                {
                    postfixExpr += stk.Top();
                    stk.Pop();
                }
                stk.Pop();
            }
            else if (expr[i] == '}')
            {
                while (stk.Top() != "{")
                {
                    postfixExpr += stk.Top();
                    stk.Pop();
                }
                stk.Pop();
            }
            else if (expr[i] == ']')
            {
                while (stk.Top() != "[")
                {
                    postfixExpr += stk.Top();
                    stk.Pop();
                }
                stk.Pop();
            }
            else
            {
                while (!stk.isEmpty() && precedence(expr[i]) <= precedence(stk.Top().at(0)))
                {
                    postfixExpr += stk.Top();
                    stk.Pop();
                }
                stk.Push(expr[i]);
                postfixExpr += ' ';
            }
        }
        while (!stk.isEmpty())
        {
            postfixExpr += stk.Top();
            stk.Pop();
        }
        return postfixExpr;
    }
};

bool bracketsValidity(string expr)
{
    Stack stk;
    for (int i = 0; i < expr.length(); i++)
    {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
        {
            stk.Push(expr[i]);
        }
        else if (expr[i] == ')' && stk.Top() == "(")
        {
            stk.Pop();
        }
        else if (expr[i] == '}' && stk.Top() == "{")
        {
            stk.Pop();
        }
        else if (expr[i] == ']' && stk.Top() == "[")
        {
            stk.Pop();
        }
    }
    return stk.isEmpty();
}

bool operatorValidity(string expr)
{
    if (expr.at(0) == '+' || expr.at(0) == '-' || expr.at(0) == '*' || expr.at(0) == '/' || expr.at(0) == '^')
    {
        return false;
    }
    Stack stk;

    for (int i = 0; i < expr.length(); i++)
    {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^')
        {
            if (stk.Top() == "+" || stk.Top() == "-" || stk.Top() == "*" || stk.Top() == "/" || stk.Top() == "^")
            {
                return false;
            }
            else
            {
                stk.Push(expr[i]);
            }
        }
        else if (!stk.isEmpty())
        {
            stk.Pop();
        }
    }
}

bool infixValidiy(string expression)
{
    return bracketsValidity(expression) && operatorValidity(expression);
}


int main()
{
    ExpressionADT exp;
    cout << exp.infix_to_postfix("11+12*(13^14-15)^(16+17*18)-19");
}