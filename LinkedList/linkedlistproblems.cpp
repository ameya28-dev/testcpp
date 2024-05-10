#include <iostream>

class Node
{
public:
    int data;
    Node *next;

    Node(int val)
    {
        data = val;
        next = nullptr;
    }
};

void insertNodeAtTail(Node *&head, int val)
{
    Node *newnode = new Node(val);

    if (head == nullptr)
    {
        head = newnode;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newnode;
}

void display(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << "->";
        temp = temp->next;
    }
    std::cout << "NULL\n";
}

int findLengthOfLinkedList(Node *head)
{
    Node *temp = head;
    int count = 0;
    while (temp != nullptr)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

Node *appendLastKNodes(Node *head, int k)
{
    int l = findLengthOfLinkedList(head);
    Node *newhead;
    Node *newtail;
    Node *last = head;
    k = k % l;
    int count = 1;

    while (last->next != nullptr)
    {
        if (count == l - k)
        {
            newtail = last;
        }
        if (count == l - k + 1)
        {
            newhead = last;
        }
        last = last->next;
        count++;
    }
    last->next = head;
    newtail->next = nullptr;

    return newhead;
}

void intersectLinkedLists(Node *&head1, Node *&head2, int pos)
{
    Node *temp1 = head1;
    pos--;
    while (pos)
    {
        temp1 = temp1->next;
        pos--;
    }

    Node *temp2 = head2;
    while (temp2->next != nullptr)
    {
        temp2 = temp2->next;
    }
    temp2->next = temp1;
}

int findDataAtIntersectionPoint(Node *&head1, Node *&head2)
{
    int l1 = findLengthOfLinkedList(head1);
    int l2 = findLengthOfLinkedList(head2);

    int d;
    Node *ptr1, *ptr2;
    if (l1 > l2)
    {
        d = l1 - l2;
        ptr1 = head1;
        ptr2 = head2;
    }
    else
    {
        d = l2 - l1;
        ptr1 = head2;
        ptr2 = head1;
    }

    while (d)
    {
        ptr1 = ptr1->next;
        if (ptr1 == nullptr)
            return -1;
        d--;
    }

    while (ptr1 != nullptr && ptr2 != nullptr)
    {
        if (ptr1 == ptr2)
            return ptr1->data;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return -1;
}

Node *mergeLinkedListsIteratively(Node *head1, Node *head2)
{
    Node *ptr1 = head1, *ptr2 = head2;
    Node *dummyhead = new Node(0);
    Node *ptr3 = dummyhead;

    while (ptr1 != nullptr && ptr2 != nullptr)
    {
        if (ptr1->data < ptr2->data)
        {
            ptr3->next = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            ptr3->next = ptr2;
            ptr2 = ptr2->next;
        }
        ptr3 = ptr3->next;
    }

    if (ptr1 != nullptr)
        ptr3->next = ptr1;
    if (ptr2 != nullptr)
        ptr3->next = ptr2;

    return dummyhead->next;
}

Node* mergeLinkedListsRecursively(Node* head1, Node* head2){
    if(head1 == nullptr) return head2;
    if(head2 == nullptr) return head1;

    Node* result;
    if(head1->data < head2->data){
        result = head1;
        result->next = mergeLinkedListsRecursively(head1->next, head2);
    }
    else{
        result = head2;
        result->next = mergeLinkedListsRecursively(head1, head2->next);
    }

    return result;
}

void evenAfterOdd(Node* &head){
    Node *odd = head;
    if(head==nullptr || head->next == nullptr){
        return;
    }

    Node *even = head->next;
    Node *evenStart = head->next;

    while(odd->next != nullptr && even->next !=nullptr){
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenStart;
    if(odd->next == nullptr){
        even->next = nullptr;
    }
}

int main()
{
    std::cout << "Append last k nodes of a linked list to its start" << '\n';
    Node *head = nullptr;
    for (int i = 1; i < 7; i++)
    {
        insertNodeAtTail(head, i);
    }
    display(head);
    auto newhead = appendLastKNodes(head, 5);
    display(newhead);

    std::cout << "Find Intersection in a Linked List:\n";
    Node *head1 = nullptr;
    Node *head2 = nullptr;
    for (int i = 0; i < 6; i++)
        insertNodeAtTail(head1, i + 1);
    insertNodeAtTail(head2, 9);
    insertNodeAtTail(head2, 10);
    intersectLinkedLists(head1, head2, 5);
    display(head1);
    display(head2);
    std::cout << "Data at intersection point: " << findDataAtIntersectionPoint(head1, head2) << '\n';

    std::cout << "Merge 2 sorted Linked Lists: "
              << "\n";
    Node *sortedhead1 = NULL;
    Node *sortedhead2 = NULL;
    int arr1[] = {1, 4, 5, 7};
    int arr2[] = {2, 3, 6, 8, 9, 10};
    for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
        insertNodeAtTail(sortedhead1, arr1[i]);
    for (int i = 0; i < sizeof(arr2) / sizeof(int); i++)
        insertNodeAtTail(sortedhead2, arr2[i]);
    display(sortedhead1);
    display(sortedhead2);

    std::cout << "Sorted iteratively:\n";
    Node *iterativelyMerged = mergeLinkedListsIteratively(sortedhead1, sortedhead2);
    display(iterativelyMerged);
  
    Node* rsortedhead1 = nullptr;
    Node* rsortedhead2 = nullptr;
    for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
        insertNodeAtTail(rsortedhead1, arr1[i]);
    for (int i = 0; i < sizeof(arr2) / sizeof(int); i++)
        insertNodeAtTail(rsortedhead2, arr2[i]);

    std::cout << "Sorted recursively:\n";
    Node *resursivelyMerged = mergeLinkedListsRecursively(rsortedhead1, rsortedhead2);
    display(resursivelyMerged);

    std::cout << "Even After Odd: " << "\n";
    Node* headeo = NULL;
    int arreo[] = {1,2,3,4,5,6,7};
    for(int i=0;i <7;i++) insertNodeAtTail(headeo,arreo[i]);
    display(headeo);
    evenAfterOdd(headeo);
    display(headeo);
    std::cout << "\n";

    return 0;
}