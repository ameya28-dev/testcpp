#include <iostream>
#include <memory>
#include <string>

class Autodelete {
private:
  std::string name;

public:
  Autodelete(std::string name);
  ~Autodelete();

  void showName() { std::cout << this->name << std::endl; }
};

Autodelete::Autodelete(std::string name) { this->name = name; }

Autodelete::~Autodelete() { std::cout << "Class deleted" << name << std::endl; }

void testFunction(std::string name) {
  Autodelete a = Autodelete(name);
  a.showName();
}

int main() {
  std::string name = "Ameya";
  std::cin >> name;
  testFunction(name);
  std::unique_ptr<int> ptr = std::make_unique<int>();

  return 0;
}
