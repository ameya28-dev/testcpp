#include <vector>
#include <string>
class Node
{
public:
	std::string name;
	int age;

	Node()
	{
		this->name = "mason";
		this->age = 0;
	}

	Node(std::string name, int age)
	{
		this->name = name;
		this->age = age;
	}
};

Node createNode(std::string name, int age)
{
	return Node(name, age);
}

Node* createHeapNode(std::string name, int age)
{
	Node* node = new Node(name, age);
	return node;
}

int main()
{

	std::vector<int> v{};

	int *ptr = new int[5];
	delete[] ptr;
	ptr = nullptr;

	createNode("mason", 15);
	Node* n = createHeapNode("mason", 15);
	delete n;
	return 0;
}
