#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>

#define n 20
#define emptyqueue "Queue is empty\t"

class QueueUsingArrays
{
    int arr[n];
    int front;
    int back;

public:
    QueueUsingArrays()
    {
        front = -1;
        back = -1;
    }

    void enqueue(int x)
    {
        if (back == n - 1)
        {
            std::cout << "Queue overflow\n";
            return;
        }

        back++;
        arr[back] = x;

        if (front == -1)
        {
            front++;
        }
    }

    void dequeue()
    {
        if (front == -1 || front > back)
        {
            std::cout << "No element in queue\n";
        }
        front++;
    }

    int peek()
    {
        if (front == -1 || front > back)
        {
            std::cout << "No element in queue\n";
            return -1;
        }
        return arr[front];
    }

    bool empty()
    {
        return front == -1 || front > back;
    }
};

class QueueUsingVectors
{
    std::vector<int> v;

public:
    QueueUsingVectors()
    {
        v = {};
    }

    void enqueue(int x)
    {
        v.push_back(x);
    }

    void dequeue()
    {
        v.erase(v.begin());
    }

    bool empty()
    {
        return v.empty();
    }

    int peek()
    {
        if (empty())
        {
            std::cout << "No element in queue:\t";
            return -1;
        }
        else
            return *(v.begin());
    }
};

class Node
{
public:
    int data;
    Node *next;

    Node(int x)
    {
        data = x;
        next = nullptr;
    }
};

class QueueUsingLinkedList
{
    Node *front;
    Node *back;

public:
    QueueUsingLinkedList()
    {
        front = nullptr;
        back = nullptr;
    }

    void enqueue(int x)
    {
        Node *node = new Node(x);
        if (front == nullptr)
        {
            front = node;
            back = node;
            return;
        }

        back->next = node;
        back = node;
    }

    void dequeue()
    {
        if (front == nullptr)
        {
            std::cout << "Queue is empty\n";
            return;
        }
        Node *todelete = front;
        front = front->next;
        delete todelete;
    }

    bool empty()
    {
        return front == nullptr;
    }

    int peek()
    {
        if (empty())
        {
            std::cout << "Queue is empty\t";
            return -1;
        }
        return front->data;
    }
};

class QueueUsingTwoStacks
{
    std::stack<int> st1;
    std::stack<int> st2;

public:
    void push(int x)
    {
        st1.push(x);
    }

    int pop()
    {
        if (st1.empty() && st2.empty())
        {
            std::cout << emptyqueue;
            return -1;
        }
        if (st2.empty())
        {
            while (!st1.empty())
            {
                st2.push(st1.top());
                st1.pop();
            }
        }
        int first = st2.top();
        st2.pop();
        return first;
    }

    int empty()
    {
        return st1.empty() && st2.empty();
    }
};

class QueueUsingOneStack
{
    std::stack<int> st;

public:
    void push(int x)
    {
        st.push(x);
    }

    bool empty()
    {
        return st.empty();
    }

    int pop()
    {
        if (empty())
        {
            std::cout << emptyqueue;
            return -1;
        }

        int val = st.top();
        st.pop();
        if (st.empty())
            return val;

        int res = pop();
        st.push(val);
        return res;
    }
};

int main()
{
    std::cout << "Queue using array\n";
    QueueUsingArrays qarray;
    for (int i = 1; i <= 19; i++)
    {
        qarray.enqueue(i);
    }
    // for(int i = 1; i<=19;i++){
    //     qarray.dequeue();
    // }
    qarray.enqueue(1);
    qarray.enqueue(1);
    qarray.enqueue(1);
    std::cout << qarray.peek() << '\n';

    std::cout << "Queues using vectors\n";
    QueueUsingVectors qv;
    // std::cout << qv.peek() << '\n';
    qv.enqueue(100);
    // qv.enqueue(20);
    // std::cout << qv.peek() << '\n';
    qv.dequeue();
    std::cout << qv.empty() << '\n';
    std::cout << qv.peek() << '\n';
    // qv.dequeue();

    std::vector<int> v{1, 2, 3, 4, 5};
    v.erase(v.begin(), v.end());
    std::cout << *v.begin() << '\n';

    std::cout << "Queues using Linked list\n";
    QueueUsingLinkedList ql;
    ql.enqueue(10);
    std::cout << ql.peek() << '\n';
    ql.dequeue();
    std::cout << ql.peek() << '\n';
    std::cout << ql.empty() << '\n';

    std::cout << "Queues using Two Stacks\n";
    QueueUsingTwoStacks q2s;
    std::cout << "Is queue empty:\t" << q2s.empty() << '\n';
    std::cout << "First element:\t" << q2s.pop() << '\n';
    q2s.push(5);
    std::cout << "First element:\t" << q2s.pop() << '\n';
    std::cout << "Is queue empty:\t" << q2s.empty() << '\n';

    std::cout << "Queues using One Stack\n";
    QueueUsingOneStack q1s;
    std::cout << "Is queue empty:\t" << q1s.empty() << '\n';
    std::cout << "First element:\t" << q1s.pop() << '\n';
    q1s.push(5);
    q1s.push(6);
    q1s.push(7);
    std::cout << "First element:\t" << q1s.pop() << '\n';
    std::cout << "Is queue empty:\t" << q1s.empty() << '\n';
    std::cout << "First element:\t" << q1s.pop() << '\n';
    std::cout << "Is queue empty:\t" << q1s.empty() << '\n';
    std::cout << "First element:\t" << q1s.pop() << '\n';
    std::cout << "Is queue empty:\t" << q1s.empty() << '\n';
    std::cout << "First element:\t" << q1s.pop() << '\n';
    std::cout << "Is queue empty:\t" << q1s.empty() << '\n';


    return 0;
}