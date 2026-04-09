#include <iostream>
#include <string>

static int ID = 1;

class Move {
    int id;
    std::string name;
    int* list;

   public:
    Move() = delete;

    Move(const std::string& name) : name(name) {
        id = ID++;
        list = new int[5];
        for (int i = 0; i < 5; i++) {
            list[i] = i;
        }
    }

    Move(const Move&& other) {
        id = other.id;
        name = std::move(other.name);
        list = std::move(other.list);
    }

    void display() {
        std::cout << "Move{id: " << id << ", name: " << name << ", list = [" << list[0];
        for (int i = 1; i < 5; i++) {
            std::cout << ", " << list[i];
        }
        std::cout << "]}\n";
    }
};

int main() {
    Move m1 = Move("Ameya");
    m1.display();

    Move m2 = std::move(m1);
    m1.display();
    m2.display();
}
