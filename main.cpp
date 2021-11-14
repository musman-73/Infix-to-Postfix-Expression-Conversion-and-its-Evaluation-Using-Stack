#include <iostream>
#include <string>
using namespace std;

class stack
{
    int top = -1;
    int size = 20;   //Max size of the stack
    string* stackList = new string[size];   //Array is used as container for stack

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
            cout << "Empty!!" << endl;
        }
    }

    void Peak()
    {
        cout << "The element on the top of the stack is: " << stackList[top] << endl;
    }
};

int main()
{
    cout << "Assalamu Alikum Duniya!" << endl;
}