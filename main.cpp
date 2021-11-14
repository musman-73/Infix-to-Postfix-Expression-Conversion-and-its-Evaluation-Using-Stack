#include <iostream>
#include <string>
using namespace std;

//Class of stack to store string data type
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
            return "0_0";
        }
    }

    string Top()
    {
        if (!isEmpty())
        {
            return stackList[top];
        }
        else
            return "0_0";
    }

    void Peak()
    {
        cout << "The element on the top of the stack is: " << stackList[top] << endl;
    }
};

//Class of stack to store integer data type
class intStack
{
    int top = -1;
    int size = 20;   //Max size of the stack
    int* stackList = new int[size];   //Array is used as container for stack

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
        stackList = new int[size];
    }

    void Push(int element)
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

    int Pop()
    {
        if (top >= 0)
        {
            int value = stackList[top];
            top--;
            return value;
        }
        else
        {
            return 0;
        }
    }

    int Top()
    {
        if (!isEmpty())
        {
            return stackList[top];
        }
        else
        {
            return 0;
        }
    }

    void Peak()
    {
        cout << "The element on the top of the stack is: " << stackList[top] << endl;
    }
};

class ExpressionADT
{
    // This function is used to solve exponents
    int exponentiation(int num, int pow)
    {
        int result = 1;
        for (int i = 0; i < pow; i++)
        {
            result *= num;
        }
        return result;
    }

    //This function defines the precedence of the operators
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

    //This function tells if a character is operator or not
    bool isOperator(char opr)
    {
        if (opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '^')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    //This will take infix expression and return its postfix expression
    string infix_to_postfix(string expr)
    {
        Stack stk;  //Stack to store operators and brackets
        string postfixExpr = "";

        for (int i = 0; i < expr.length(); i++)
        {
            //if a digit is found we add it to the final expression
            if (isdigit(expr[i]))
            {
                postfixExpr += expr[i];
            }

            //if opening bracket is found we push it in the stack
            else if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
            {
                stk.Push(expr[i]);
            }

            //if a closing bracket is found, we start to pop the
            //elements from the stack and add them to the expression
            //until corresponding opening bracket is at the top of
            //the stack. Then we pop and discard the openeing bracket.
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

            //if an operator is found, we push it to the stack if the top
            //of the stack has lower precedence than the operator found
            //otherwise we start to pop the operators and add them to the
            //final expression until said condtition is satisfied or an
            //opening brackets comes at the top of the stack
            else
            {
                while (!stk.isEmpty() && precedence(expr[i]) <= precedence(stk.Top().at(0)))
                {
                    postfixExpr += stk.Top();
                    stk.Pop();
                }
                stk.Push(expr[i]);
                postfixExpr += ' '; //THIS SPACE WILL WORK AS A DELIMETER
            }
        }

        //Finally we pop all remaining operators and push them in the stack.
        while (!stk.isEmpty())
        {
            postfixExpr += stk.Top();
            stk.Pop();
        }
        return postfixExpr;
    }

    int postfixEval(string expr)
    {
        intStack stk;   //stack to store integers
        int temp = 0;   //variable to store number with multiple digits
        int prevOperator = 0;   //0 in this variable shows that previous finding was not an operator.
        for (int i = 0; i < expr.length(); i++)
        {
            //If the found character is a digit, we make it our temp number
            //This number can have multiple digits if digits are found
            //consecutively with no delimeter in between. Top of stack is
            //set to zero when stack is empty.
            if (isdigit(expr[i]))
            {
                prevOperator = 0;
                char c = expr[i];
                temp = (10 * temp) + (int)(c - '0');
            }

            //If delimeter is found and previous finding was a digit too,
            //we push the temporary number in the stack and reset the
            //temporary number.
            else if (expr[i] == ' ' && prevOperator == 0)    // ' ' is a delimeter
            {
                stk.Push(temp);
                temp = 0;
            }

            //If an operator is found, we pop two numbers from the stack,
            //perform the corresponding operation on them in such a way
            //that the first popped number is at right and second popped
            //is at left, finally we push the result back into the stack.
            else if (isOperator(expr[i]))
            {
                if (prevOperator == 0)
                {
                    stk.Push(temp);
                    temp = 0;
                }
                prevOperator = 1;

                int first = stk.Top();
                stk.Pop();
                int second = stk.Top();
                stk.Pop();
                if (expr[i] == '+')
                {
                    stk.Push(second + first);
                }
                else if (expr[i] == '-')
                {
                    stk.Push(second - first);
                }
                else if (expr[i] == '*')
                {
                    stk.Push(second * first);
                }
                else if (expr[i] == '/')
                {
                    stk.Push(second / first);
                }
                else if (expr[i] == '^')
                {
                    stk.Push(exponentiation(second, first));
                }
            }
        }
        return stk.Top();
    }
};


//This function checks if the brackets in expression are valid
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

//This function checks if the operators are valid in an expression
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


int main()
{
    ExpressionADT obj;
    string expr;
    cout << "Enter the expression: ";
    getline(cin, expr);

    if (bracketsValidity(expr) && operatorValidity(expr))
    {
        string postfix = obj.infix_to_postfix(expr);
        int result = obj.postfixEval(postfix);
        cout << "Postfix Expression:\t" << postfix << endl;
        cout << "Result:\t" << result << endl;
    }
}