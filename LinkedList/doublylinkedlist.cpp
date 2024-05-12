#include <iostream>

class Node
{
public:
    int data;
    Node *prev, *next;

    Node(int val)
    {
        this->data = val;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

void insertNodeAtHead(Node *&head, int val)
{
    Node *newnode = new Node(val);
    newnode->next = head;
    if (head != nullptr)
        head->prev = nullptr;
    head = newnode;
}

void insertNodeAtTail(Node *&head, int val)
{
    if (head == nullptr)
    {
        insertNodeAtHead(head, val);
        return;
    }

    Node *newnode = new Node(val);
    Node *temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->prev = temp;
}

void display(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << "->";
        temp = temp->next;
    }
    std::cout << "NULL" << '\n';
}

void deleteAtHead(Node *&head)
{
    if (head == nullptr)
        return;

    Node *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;
}

void deleteNode(Node *&head, int pos)
{
    if (head == nullptr)
        return;

    if (pos == 1)
    {
        deleteAtHead(head);
        return;
    }

    Node *temp = head;
    int count = 1;

    while (temp != nullptr && count != pos)
    {
        temp = temp->next;
        count++;
    }

    if(temp == nullptr) return;
    if(temp->next != nullptr) temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    delete temp;
}

int main()
{
    Node *head = nullptr;
    insertNodeAtTail(head, 1);
    insertNodeAtTail(head, 2);
    insertNodeAtTail(head, 3);
    insertNodeAtHead(head, 0);
    insertNodeAtHead(head, 4);
    display(head);
    deleteAtHead(head);
    display(head);
    insertNodeAtTail(head, 5);
    insertNodeAtTail(head, 4);
    display(head);
    deleteNode(head, 5);
    display(head);
    deleteNode(head, 8);
    display(head);
    return 0;
}
