#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <stack>
#include <queue>

#define n 20

using namespace std;

class QueueUsingArray{
    int arr[n];
    int front;
    int back; 

    public:
        QueueUsingArray(){
            front = -1;
            back = -1;
        }

        void enqueue(int x){
            if(back == n-1){
                cout << "Queue Overflow\n";
                return;
            }

            back++;
            arr[back] = x;

            if(front == -1){
                front++;
            }
        }

        void dequeue(){
            if(front == -1 || front > back){
                cout << "No element in the Queue\n";
                return;
            }
            front++;
        }

        int peek(){
            if(front == -1 || front > back){
                cout << "No element in the Queue\n";
                return -1;
            }
            return arr[front];
        }

        bool empty(){
            if(front == -1 || front > back){
                return true;
            }
            return false;
        }

};

class Node{
    public:
        int data;
        Node* next;

        Node(int x){
            data = x;
            next = NULL;
        }
};

class QueueUsingLinkedList{
    Node* front;
    Node* back;

    public:
        QueueUsingLinkedList(){
            front = NULL;
            back = NULL;
        }

        void enqueue(int x){
            Node* node = new Node(x);

            if(front == NULL){
                front = node;
                back = node;
                return;
            }
            back->next = node;
            back = node;
        }

        void dequeue(){
            Node* todelete = front;

            if(front == NULL){
                cout << "Queue Underflow\n";
                return;
            }
            front = front->next;
            delete todelete;
        }

        int peek(){
            if(front == NULL){
                cout << "Queue Underflow\n";
                return -10.0315103284651;
            }
            return front->data;
        }

        bool empty(){
            return front == NULL;
        }

};

class QueueUsingStacks1{
    stack<int> st1;
    stack<int> st2;

    public:
        void push(int x){
            st1.push(x);
            return;
        }

        int pop(){
            if(st1.empty() && st2.empty()){
                return -1;
            }
            if(st2.empty()){
                while(!st1.empty()){
                    st2.push(st1.top());
                    st1.pop();
                }
            }
            int topval = st2.top();
            st2.pop();
            return topval;
        }

        bool empty(){
            return st1.empty() && st2.empty();
        }
};

class QueueUsingStacks2{
    stack<int> st;

    public:
        void push(int x){
            st.push(x);
            return;
        }

        int pop(){
            if(st.empty()){
                return -1;
            }
            
            int val = st.top();
            st.pop();
            if(st.empty()) return val;

            int res = pop();
            st.push(val);
            return res;
        }

        bool empty(){
            return st.empty();
        }
};

class StacksUsingQueues1{
    int N;
    queue<int> q1;
    queue<int> q2;

    public:
        StacksUsingQueues1(){
            N = 0;
        }

        void push(int x){
            q2.push(x);

            while(!q1.empty()){
                q2.push(q1.front());
                q1.pop();    
            }

            queue<int> temp = q1;
            q1 = q2;
            q2 = temp;

            N++;
        }

        void pop(){
            q1.pop();
            N--;
        }

        int top(){
            return q1.front();
        }

        int size(){
            return N;
        }
};

class StacksUsingQueues2{
    int N;
    queue<int> q1;
    queue<int> q2;

    public:
        StacksUsingQueues2(){
            N = 0;
        }

        void push(int x){
            q1.push(x);
            N++;
        }

        void pop(){
            if(q1.empty()) return;

            while(q1.size() != 1){
                q2.push(q1.front());
                q1.pop();
            }

            q1.pop();

            queue<int> temp = q1;
            q1 = q2;
            q2 = temp;

            N++;       
        }

        int top(){
            if(q1.empty()) return -1;

            while(q1.size() != 1){
                q2.push(q1.front());
                q1.pop();
            }

            int val = q1.front();
            q2.push(val);

            queue<int> temp = q1;
            q1 = q2;
            q2 = temp;

            return val;
        }

        int size(){
            return N;
        }
};

int main(){
    cout << "Queues using Arrays:\n";
    QueueUsingArray qa = QueueUsingArray();
    qa.enqueue(1);
    qa.enqueue(2);
    qa.enqueue(3);
    qa.enqueue(4);
    qa.dequeue();
    cout << "Is this queue empty: "<< qa.empty() <<"\n";
    cout << "First element: "<< qa.peek() <<"\n";
    cout << "\n";

    cout << "Queues using Linked List:\n";
    QueueUsingLinkedList ql = QueueUsingLinkedList();
    ql.enqueue(1);
    ql.enqueue(2);
    ql.enqueue(3);
    ql.enqueue(4);

    cout << ql.peek() <<"\n";
    ql.dequeue();
    cout << ql.peek() <<"\n";
    ql.dequeue();
    cout << ql.peek() <<"\n";
    ql.dequeue();
    cout << ql.peek() <<"\n";
    ql.dequeue();

    cout << ql.empty() <<"\n";
    cout << "\n";

    cout << "Queues using Stacks - Approach 1:\n";
    QueueUsingStacks1 qs1;
    qs1.push(1);
    qs1.push(2);
    qs1.push(3); 
    cout << qs1.pop() << "\n";
    cout << qs1.pop() << "\n";
    cout << qs1.pop() << "\n";
    cout << qs1.pop() << "\n";
    cout << "Is the queue empty??: " << qs1.empty() << "\n\n";

    cout << "Queues using Stacks - Approach 2:\n";
    QueueUsingStacks2 qs2;
    qs2.push(1);
    qs2.push(2);
    qs2.push(3); 
    cout << qs2.pop() << "\n";
    cout << qs2.pop() << "\n";
    cout << qs2.pop() << "\n";
    cout << qs2.pop() << "\n";
    cout << "Is the queue empty??: " << qs2.empty() << "\n\n";

    cout << "Stacks using Queues  - Approach 1:\n";
    StacksUsingQueues1 sq1;
    sq1.push(1);
    sq1.push(2);
    sq1.push(3);
    cout << sq1.size() << "\n";
    cout << sq1.top() << "\n";
    sq1.pop();
    cout << sq1.size() << "\n";
    cout << sq1.top() << "\n";
    sq1.pop();
    cout << sq1.size() << "\n";
    cout << sq1.top() << "\n\n";
    sq1.pop();

    cout << "Stacks using Queues  - Approach 2:\n";
    StacksUsingQueues1 sq2;
    sq2.push(1);
    sq2.push(2);
    sq2.push(3);
    cout << sq2.size() << "\n";
    cout << sq2.top() << "\n";
    sq2.pop();
    cout << sq2.size() << "\n";
    cout << sq2.top() << "\n";
    sq2.pop();
    cout << sq2.size() << "\n";
    cout << sq2.top() << "\n";
    sq2.pop();


    return 0;
}