#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

// MSVC reports __cplusplus as 199711L unless /Zc:__cplusplus is set, so check _MSVC_LANG there.
#if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
#error "forward_list.h requires C++17 or newer"
#endif

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>

// Precondition checks (front, back and pop_front on an empty list).
// By default they use assert(), so they disappear in release builds (NDEBUG).
// Define FORWARD_LIST_ASSERT before including this header to use your own handler,
// or define it as ((void)0) to turn the checks off.
#ifndef FORWARD_LIST_ASSERT
#include <cassert>
#define FORWARD_LIST_ASSERT(condition) assert(condition)
#endif

namespace Forward {
    namespace Detail {
        template <typename T>
        class Node {
        public:
            template <typename... Args>
            explicit Node(Args&&... args) : _data(std::forward<Args>(args)...) {}

            Node(const Node&)            = delete;
            Node& operator=(const Node&) = delete;

            T& data() noexcept {
                return _data;
            }

            const T& data() const noexcept {
                return _data;
            }

            Node* next() const noexcept {
                return _next;
            }

            void set_next(Node* next) noexcept {
                _next = next;
            }

        private:
            T _data;
            Node* _next = nullptr;
        };

        template <typename T, bool IsConst>
        class ForwardListIterator {
        public:
            // These names are required by the standard library (std::iterator_traits),
            // so they keep their standard spelling.
            using iterator_category = std::forward_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = std::conditional_t<IsConst, const T*, T*>;
            using reference         = std::conditional_t<IsConst, const T&, T&>;

            ForwardListIterator() noexcept = default;

            explicit ForwardListIterator(Node<T>* node) noexcept : _node(node) {}

            // Allows Iterator -> ConstIterator, but not the other way around.
            template <bool OtherConst, std::enable_if_t<IsConst && !OtherConst, int> = 0>
            ForwardListIterator(const ForwardListIterator<T, OtherConst>& other) noexcept : _node(other._node) {}

            reference operator*() const {
                return _node->data();
            }

            // Note: a type that overloads unary operator& would need std::addressof (<memory>) here.
            pointer operator->() const {
                return &_node->data();
            }

            ForwardListIterator& operator++() {
                _node = _node->next();
                return *this;
            }

            ForwardListIterator operator++(int) {
                ForwardListIterator copy = *this;
                ++(*this);
                return copy;
            }

            friend bool operator==(const ForwardListIterator& lhs, const ForwardListIterator& rhs) noexcept {
                return lhs._node == rhs._node;
            }

            friend bool operator!=(const ForwardListIterator& lhs, const ForwardListIterator& rhs) noexcept {
                return !(lhs == rhs);
            }

        private:
            template <typename, bool>
            friend class ForwardListIterator;

            using NodePointer = std::conditional_t<IsConst, const Node<T>*, Node<T>*>;

            NodePointer _node = nullptr;
        };
    } // namespace Detail

    template <typename T>
    class ForwardList {
    public:
        using Iterator      = Detail::ForwardListIterator<T, false>;
        using ConstIterator = Detail::ForwardListIterator<T, true>;

        // ---- construction, destruction, assignment ----

        ForwardList() noexcept = default;

        explicit ForwardList(const T& value) : ForwardList() {
            push_back(value);
        }

        ForwardList(std::initializer_list<T> values) : ForwardList() {
            for (const T& value : values) {
                push_back(value);
            }
        }

        // Delegating to the default constructor makes the object "fully constructed"
        // before the loop starts, so if a push_back throws, the destructor still runs
        // and the nodes created so far are freed.
        ForwardList(const ForwardList& other) : ForwardList() {
            for (const T& value : other) {
                push_back(value);
            }
        }

        ForwardList(ForwardList&& other) noexcept
            : _head(std::exchange(other._head, nullptr)), _tail(std::exchange(other._tail, nullptr)),
              _size(std::exchange(other._size, 0)) {}

        ~ForwardList() {
            clear();
        }

        ForwardList& operator=(const ForwardList& other) {
            if (this != &other) {
                ForwardList copy(other);
                swap(copy);
            }
            return *this;
        }

        ForwardList& operator=(ForwardList&& other) noexcept {
            if (this != &other) {
                ForwardList moved(std::move(other));
                swap(moved);
            }
            return *this;
        }

        // ---- element access (precondition: list is not empty) ----

        T& front() {
            FORWARD_LIST_ASSERT(!empty() && "front() called on empty list");
            return _head->data();
        }

        const T& front() const {
            FORWARD_LIST_ASSERT(!empty() && "front() called on empty list");
            return _head->data();
        }

        T& back() {
            FORWARD_LIST_ASSERT(!empty() && "back() called on empty list");
            return _tail->data();
        }

        const T& back() const {
            FORWARD_LIST_ASSERT(!empty() && "back() called on empty list");
            return _tail->data();
        }

        // ---- iterators ----

        Iterator begin() noexcept {
            return Iterator(_head);
        }

        Iterator end() noexcept {
            return Iterator();
        }

        ConstIterator begin() const noexcept {
            return ConstIterator(_head);
        }

        ConstIterator end() const noexcept {
            return ConstIterator();
        }

        ConstIterator cbegin() const noexcept {
            return begin();
        }

        ConstIterator cend() const noexcept {
            return end();
        }

        // ---- capacity ----

        [[nodiscard]] std::size_t size() const noexcept {
            return _size;
        }

        [[nodiscard]] bool empty() const noexcept {
            return _size == 0;
        }

        // ---- modifiers ----

        void push_front(const T& value) {
            emplace_front(value);
        }

        void push_front(T&& value) {
            emplace_front(std::move(value));
        }

        template <typename... Args>
        T& emplace_front(Args&&... args) {
            Node* node = new Node(std::forward<Args>(args)...);
            node->set_next(_head);
            _head = node;
            if (_tail == nullptr) {
                _tail = node;
            }
            ++_size;
            return node->data();
        }

        void push_back(const T& value) {
            emplace_back(value);
        }

        void push_back(T&& value) {
            emplace_back(std::move(value));
        }

        template <typename... Args>
        T& emplace_back(Args&&... args) {
            Node* node = new Node(std::forward<Args>(args)...);
            if (_tail == nullptr) {
                _head = node;
            } else {
                _tail->set_next(node);
            }
            _tail = node;
            ++_size;
            return node->data();
        }

        // Precondition: list is not empty.
        void pop_front() {
            FORWARD_LIST_ASSERT(!empty() && "pop_front() called on empty list");
            _unlink(nullptr, _head);
        }

        // Removes the first element equal to value. Returns false if there was none.
        bool remove(const T& value) {
            auto [previous, node] = _find(value);
            if (node == nullptr) {
                return false;
            }

            _unlink(previous, node);
            return true;
        }

        void clear() noexcept {
            Node* current = _head;
            while (current != nullptr) {
                Node* next = current->next();
                delete current;
                current = next;
            }

            _head = nullptr;
            _tail = nullptr;
            _size = 0;
        }

        void reverse() noexcept {
            Node* previous = nullptr;
            Node* current  = _head;
            _tail          = _head;

            while (current != nullptr) {
                Node* next = current->next();
                current->set_next(previous);
                previous = current;
                current  = next;
            }

            _head = previous;
        }

        void swap(ForwardList& other) noexcept {
            std::swap(_head, other._head);
            std::swap(_tail, other._tail);
            std::swap(_size, other._size);
        }

        // ---- lookup ----

        [[nodiscard]] bool contains(const T& value) const {
            return _find(value).second != nullptr;
        }

        // ---- non-member operators (found through argument-dependent lookup) ----

        friend bool operator==(const ForwardList& lhs, const ForwardList& rhs) {
            if (lhs._size != rhs._size) {
                return false;
            }

            for (ConstIterator left = lhs.begin(), right = rhs.begin(); left != lhs.end(); ++left, ++right) {
                if (!(*left == *right)) {
                    return false;
                }
            }

            return true;
        }

        friend bool operator!=(const ForwardList& lhs, const ForwardList& rhs) {
            return !(lhs == rhs);
        }

        friend void swap(ForwardList& lhs, ForwardList& rhs) noexcept {
            lhs.swap(rhs);
        }

    private:
        using Node = Detail::Node<T>;

        // Returns { node before the match, the match }. The match is nullptr if not found.
        std::pair<Node*, Node*> _find(const T& value) const {
            Node* previous = nullptr;
            Node* current  = _head;

            while (current != nullptr && !(current->data() == value)) {
                previous = current;
                current  = current->next();
            }

            return {previous, current};
        }

        // Detaches node from the list and deletes it. previous is nullptr when node is the head.
        void _unlink(Node* previous, Node* node) noexcept {
            Node* next = node->next();

            if (previous == nullptr) {
                _head = next;
            } else {
                previous->set_next(next);
            }

            if (node == _tail) {
                _tail = previous;
            }

            delete node;
            --_size;
        }

        Node* _head       = nullptr;
        Node* _tail       = nullptr;
        std::size_t _size = 0;
    };
} // namespace Forward

#endif // FORWARD_LIST_H
