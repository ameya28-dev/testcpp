#include <iostream>
#include <algorithm>

class Node
{
public:
    Node *next;
    int data;

    Node(int val)
    {
        this->data = val;
        this->next = nullptr;
    }
};

void insertNodeAtTail(Node *&head, int val)
{
    Node *n = new Node(val);

    if (head == nullptr)
    {
        head = n;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = n;
}

void insertNodeAtHead(Node *&head, int val)
{
    Node *newNode = new Node(val);
    // if(head == nullptr){
    //     head = newNode;
    //     return;
    // }
    newNode->next = head;
    head = newNode;
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

bool searchNode(Node *head, int key)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == key)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void deleteNode(Node *&head, int val)
{
    if (head == nullptr)
    {
        return;
    }

    if (head->data == val)
    {
        // if(head->next == nullptr){
        //     head = nullptr;
        //     return;
        // }
        // else{
        Node *todelete = head;
        head = head->next;
        delete todelete;
        return;
        // }
    }

    Node *temp = head;
    while (temp->next != nullptr && temp->next->data != val)
    {
        temp = temp->next;
    }
    if (temp->next != nullptr)
    {
        Node *todelete = temp->next;
        temp->next = temp->next->next;
        delete todelete;
    }
}

Node *reverseLinkedListIteratively(Node *head)
{
    Node *prevptr = nullptr;
    Node *currptr = head;
    Node *nextptr;

    while (currptr != nullptr)
    {
        nextptr = currptr->next;
        currptr->next = prevptr;
        prevptr = currptr;
        currptr = nextptr;
    }
    return prevptr;
}

Node *reverseLinkedListRecursively(Node *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    } // Make last node as head

    Node *newHead = reverseLinkedListRecursively(head->next);
    // now point next of head to null and next of next of head to null
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

Node *reverseKNodes(Node *head, int k)
{
    Node *currptr = head;
    Node *prevptr = nullptr;
    Node *nextptr;
    int count = 0;

    while (currptr != nullptr && count < k)
    {
        nextptr = currptr->next;
        currptr->next = prevptr;
        prevptr = currptr;
        currptr = nextptr;
        count++;
    }

    if (nextptr != nullptr)
    {
        head->next = reverseKNodes(nextptr, k);
    }

    return prevptr;
}

void makecycle(Node *&head, int pos)
{
    Node *temp = head;
    Node *startcycleposition;

    int count = 1;
    while (temp->next != nullptr)
    {
        if (count == pos)
        {
            startcycleposition = temp;
        }
        temp = temp->next;
        count++;
    }
    temp->next = startcycleposition;
}

bool detectcycle(Node *head)
{
    Node *fast = head, *slow = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow)
            return true;
    }

    return false;
}

void removecycle(Node *&head)
{
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
    {
        return;
    }

    Node *fast = head->next->next, *slow = head->next;

    while (fast != slow)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    fast = head;
    while (fast->next != slow->next)
    {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = nullptr;
}

int main()
{
    Node *head = nullptr;
    insertNodeAtHead(head, 0);
    insertNodeAtTail(head, 1);
    insertNodeAtTail(head, 2);
    insertNodeAtTail(head, 3);
    insertNodeAtTail(head, 4);
    std::cout << "Display original linked list:\t";
    display(head);

    std::cout << "If node 5 is present:\t" << searchNode(head, 5) << '\n';
    std::cout << "If node 3 is present:\t" << searchNode(head, 3) << '\n';

    deleteNode(head, 5);
    display(head);

    std::cout << "Reversing Linked List iteratively\n";
    Node *iterativelyreversed = reverseLinkedListIteratively(head);
    // reverseLinkedListIteratively(head);
    display(iterativelyreversed);

    std::cout << "Reversing Linked List recursively\n";
    Node *recursivelyreversed = reverseLinkedListRecursively(iterativelyreversed);
    display(recursivelyreversed);
    // display(head);

    std::cout << "Reversing k nodes of a Linked List\n";
    Node *knodesreversed = reverseKNodes(recursivelyreversed, 4);
    display(knodesreversed);

    Node *cyclehead = nullptr;
    insertNodeAtTail(cyclehead, 1);
    insertNodeAtTail(cyclehead, 2);
    insertNodeAtTail(cyclehead, 3);
    insertNodeAtTail(cyclehead, 4);
    insertNodeAtTail(cyclehead, 5);
    display(cyclehead);
    makecycle(cyclehead, 3);
    // display(cyclehead);

    std::cout << "Is there a cycle present?\t" << detectcycle(cyclehead) << '\n';
    std::cout << "Linked List after removing cycle:\t";
    removecycle(cyclehead);
    display(cyclehead);
    return 0;
}