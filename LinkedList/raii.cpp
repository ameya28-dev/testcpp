#include <exception>
#include <iostream>
#include <sstream>

template <typename T>
class Node {
   public:
    Node() = delete;
    Node(const T& data) : data(data), next(nullptr) {}
    Node(const T& data, const Node<T>* next) : data(data), next(next) {}

    T get_data() { return data; }
    const T& get_data() const { return data; }

    Node<T>* get_next() { return next; }
    const Node<T>* get_next() const { return next; }
    void set_next(Node<T>* ptr) { next = ptr; }

   private:
    T data;
    Node<T>* next;
};

template <typename T>
class LinkedList {
   public:
    LinkedList() : head(nullptr), last(nullptr), length(0) {}

    LinkedList(const T& data) {
        create_head(data);
    }

    ~LinkedList() {
        clear();
    }

    void insert_back(const T& data) {
        if (head == nullptr) {
            create_head(data);
            return;
        }

        Node<T>* ptr = new Node<T>(data);
        last->set_next(ptr);
        last = ptr;
        length++;
        ptr = nullptr;
    }

    void insert_front(const T& data) {
        if (head == nullptr) {
            create_head(data);
            return;
        }

        Node<T>* ptr = head;
        head = new Node<T>(data);
        head->set_next(ptr);
        length++;
    }

    std::size_t size() { return length; }

    bool empty() { return length <= 0; }

    bool contains(const T& data) {
        Node<T>* ptr = head;
        while (ptr) {
            if (ptr->get_data() == data) {
                return true;
            }
            ptr = ptr->get_next();
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& instream, const LinkedList<T>& ll) {
        instream << "linked list: ";
        auto temp = ll.head;
        while (temp) {
            instream << temp->get_data() << "->";
            temp = temp->get_next();
        }

        instream << "nullptr";
        return instream;
    }

    void remove(const T& val) {
        if (head == nullptr) {
            throw std::domain_error("Trying to remove item from an empty list");
        }

        Node<T>* curr = head;
        Node<T>* prev = nullptr;
        while (curr) {
            if (curr->get_data() != val) {
                prev = curr;
                curr = curr->get_next();
                continue;
            }

            if (prev == nullptr) {
                if (curr->get_next() == nullptr) {
                    delete head;
                    head = nullptr;
                    last = nullptr;
                    length--;
                    return;
                }

                prev = head;
                head = curr->get_next();
                prev->set_next(nullptr);
                curr = nullptr;
                delete prev;
                length--;
                return;
            }

            if (curr->get_next() == nullptr) {
                last = prev;
            }
            prev->set_next(curr->get_next());
            length--;
            delete curr;
            curr = nullptr;
            return;
        }

        throw std::domain_error("Trying to remove item not in the list");
    }

    void clear() {
        if (head == nullptr) return;

        if (head->get_next() == nullptr) {
            delete head;
            head = nullptr;
            last = nullptr;
            length = 0;
            return;
        }

        Node<T>* prev = head;
        Node<T>* curr = head->get_next();
        while (curr != nullptr) {
            delete prev;
            prev = curr;
            curr = curr->get_next();
        }

        head = nullptr;
        last = nullptr;
        length = 0;
    }

   private:
    Node<T>* head;
    Node<T>* last;
    std::size_t length = 0;

    void create_head(const T& data) {
        head = new Node<T>(data);
        last = head;
        length++;
    }
};

int main() {
    LinkedList<int> l;

    l.insert_back(1);
    l.remove(1);
    l.insert_back(2);
    l.insert_back(3);
    l.remove(2);
    l.insert_front(0);
    l.insert_back(4);
    l.remove(4);
    // l.insert_front(6);
    l.insert_back(7);
    l.remove(0);
    l.insert_back(8);
    l.insert_front(5);
    l.clear();
    l.insert_back(11);

    std::cout << std::boolalpha;
    std::cout << l << std::endl;
    std::cout << "Size: " << l.size() << std::endl;
    std::cout << "l contains 10: " << l.contains(10) << '\n';
    std::cout << "l contains 1: " << l.contains(1) << '\n';
}