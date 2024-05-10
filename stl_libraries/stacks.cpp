#include <iostream>
#include <stack>

#define n 100

class Stack
{
    int arr[n];
    int top;

public:
    Stack()
    {
        arr[n] = {};
        top = -1;
    }

    void push(int x)
    {
        if (top == n - 1)
        {
            std::cout << "Stack Overflow" << '\n';
            return;
        }

        top++;
        arr[top] = x;
    }

    void pop()
    {
        if (top == -1)
        {
            std::cout << "Stack is empty\n";
            return;
        }
        top--;
    }

    int Top()
    {
        if (top == -1)
        {
            std::cout << "No top element in the stack\n";
            return -1;
        }
        return arr[top];
    }

    bool empty()
    {
        return top == -1;
    }
};

void reversesentence(std::string s)
{
    std::stack<std::string> st;

    for (int i = 0; i < s.length(); i++)
    {
        std::string word = "";

        while (s[i] != ' ' && i < s.length())
        {
            word += s[i];
            i++;
        }
        st.push(word);
    }

    while (!st.empty())
    {
        std::cout << st.top() << " ";
        st.pop();
    }

    std::cout << '\n';
}

void insertAtBottom(std::stack<int> &st, int topElement)
{
    if (st.empty())
    {
        st.push(topElement);
        return;
    }

    int top = st.top();
    st.pop();
    insertAtBottom(st, top);
}

void reverseStack(std::stack<int> st)
{
    if (st.empty())
        return;

    int element = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, element);
}

int main()
{
    Stack st = Stack();
    std::cout << st.empty() << '\n';
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    std::cout << st.Top() << '\n';
    st.pop();
    st.pop();
    std::cout << st.Top() << '\n';

    std::string s = "Hey, how are you doing?";
    reversesentence(s);

    std::stack<int> reversestack;
    reversestack.push(1);
    reversestack.push(2);
    reversestack.push(3);
    reversestack.push(4);
    reverseStack(reversestack);

    while (!reversestack.empty())
    {
        std::cout << reversestack.top() << '\t';
        reversestack.pop();
    }

    return 0;
}