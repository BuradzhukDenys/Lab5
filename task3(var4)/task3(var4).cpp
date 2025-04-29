#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Stack
{
private:
	struct Node
	{
		char data;
		Node* next;
	};

	Node* top;
	int size;
public:
	Stack() : top(nullptr), size(0) {}
	Stack(char value) : size(1)
	{
		top = new Node{ value, nullptr };
	}

	~Stack()
	{
		while (!isEmpty())
		{
			pop();
		}
	}

	void push(const char& value)
	{
		Node* newNode = new Node{ value, top };
		top = newNode;
		size++;
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "Size is empty";
			return;
		}
		else {
			Node* temp = top;
			top = top->next;
			delete temp;
			size--;
		}
	}

	char Top() const
	{
		if (isEmpty())
		{
			cout << "Stack is empty\n";
			return '\0';
		}
		return top->data;
	}

	bool isEmpty() const
	{
		return size == 0;
	}

	int Size() const
	{
		return size;
	}

	bool isBalanced(const string& text)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == '(' || text[i] == '[' || text[i] == '{')
			{
				push(text[i]);
			}
			else if (text[i] == ')' || text[i] == ']' || text[i] == '}') {
				if (isEmpty()) return false;

				char topChar = Top();
				pop();

				if ((text[i] == ')' && topChar != '(') ||
					(text[i] == ']' && topChar != '[') ||
					(text[i] == '}' && topChar != '{')) {
					return false;
				}
			}
		}

		return isEmpty();
	}

	string readFromFile(const string& filename)
	{
		ifstream inFile(filename);
		string line;

		if (!inFile.is_open())
		{
			throw runtime_error("Couldn't open file to read.");
		}
		else {
			getline(inFile, line);
		}

		return line;
		inFile.close();
	}

	void writeToFile(const string& text, const string& filename)
	{
		ofstream outFile(filename);

		if (!outFile.is_open())
		{
			throw runtime_error("Couldn't open file to write.");
		}

		try
		{
			if (isBalanced(text))
			{
				outFile << text << " - brackets are balanced\n";
			}
			else {
				outFile << text << " - brackets are not balanced\n";
			}
		}
		catch (const exception& e)
		{
			outFile.close();
		}

		outFile.close();
	}
};

int main()
{
	cout << "Select method:\n"
		<< "1. Read from keyboard, write to console.\n"
		<< "2. Read from keyboard, write to file.\n"
		<< "3. Read from file, write to console.\n"
		<< "4. Read from file, write to file.\n";
	int method;
	cin >> method;
	cin.ignore();
	switch (method)
	{
	case 1:
	{
		system("cls");
		Stack stack;

		cout << "Enter text:\n";
		string text;
		getline(cin, text);
		if (stack.isBalanced(text))
		{
			cout << "Brackets are balanced\n";
		}
		else {
			cout << "Brackets are not balanced\n";
		}
		break;
	}
	case 2:
	{
		system("cls");
		Stack stack;

		cout << "Enter text:\n";
		string text;
		getline(cin, text);
		stack.writeToFile(text, "Out file1.txt");
		break;
	}
	case 3:
	{
		system("cls");
		Stack stack;

		string text = "";
		try
		{
			text = stack.readFromFile("In file.txt");
		}
		catch (const exception& e)
		{
			cerr << e.what();
		}

		cout << "Text from file: " << text << endl;
		if (stack.isBalanced(text))
		{
			cout << "Brackets are balanced\n";
		}
		else {
			cout << "Brackets are not balanced\n";
		}
		break;
	}
	case 4:
	{
		system("cls");
		Stack stack;

		string text = "";
		try
		{
			text = stack.readFromFile("In file.txt");
		}
		catch (const exception& e)
		{
			cerr << e.what();
		}

		stack.writeToFile(text, "Out file2.txt");
		break;
	}
	default:
		cout << "Invalid option\n";
		break;
	}
}