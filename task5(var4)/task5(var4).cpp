#include <iostream>
#include <list>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile("inFile.txt");
    if (!inFile.is_open())
    {
        cerr << "Couldn't open file to read.";
        return 1;
    }

    double number = 0;
    list<double> numbers;

    while (inFile >> number)
    {
        numbers.push_back(number);
    }
    inFile.close();

    if (numbers.size() < 10)
    {
        cerr << "File contain less than 10 numbers." << endl;
        return 1;
    }

    cout << "List: ";
    for (double num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    numbers.sort();
    numbers.reverse();

    double sum = 0;
    list<double> top10;
    auto it = numbers.begin();
    for (int i = 0; i < 10 && it != numbers.end(); i++, it++)
    {
        sum += *it;
        top10.push_back(*it);
    }
    double avarage = sum / 10;

    cout << "Sorted list: ";
    for (double num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "10 maxnumbers: ";
    for (double num : top10)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "Avarage of 10 max numbers: " << avarage << endl;
}