#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Worker
{
private:
    string name;
    string workPosition; //Посада
    int year; //Рік надходження на роботу
    double salary;
public:
    Worker(const string& newName="noname", const string& newPosition="none", int newYear=2025, double newSalary=0)
        : name(newName), workPosition(newPosition), year(newYear), salary(newSalary) {}

    Worker(const Worker& other): name(other.name), workPosition(other.workPosition),
                                 year(other.year), salary(other.salary) {}

    ~Worker() = default;

    static void saveToFile(const Worker workers[], int size, const string& file)
    {
        ofstream outFile(file + ".txt");
        if (!outFile.is_open())
        {
            throw runtime_error("Couldn't open file to write.");
        }

        try
        {
            for (int i = 0; i < size; i++)
            {
                outFile << workers[i];
                outFile << endl;
                if (outFile.fail()) throw runtime_error("Error to write to file");
            }
        }
        catch (const runtime_error e)
        {
            outFile.close();
            cout << e.what();
        }

        outFile.close();
    }

    static void loadFromFile(Worker workers[], int size, const string& file)
    {
        ifstream inFile(file + ".txt");
        if (!inFile.is_open())
        {
            throw runtime_error("Couldn't open file to write.");
        }

        try
        {
            for (int i = 0; i < size && !inFile.eof(); i++)
            {
                Worker temp;
                inFile >> temp.name;
                inFile >> temp.workPosition;
                inFile >> temp.year;
                inFile >> temp.salary;
                if (inFile.fail() && !inFile.eof()) throw runtime_error("");

                workers[i] = temp;
            }
        }
        catch (const runtime_error e)
        {
            inFile.close();
            cout << e.what();
        }

        inFile.close();
    }

    string getName() const { return name; }
    string getWorkPosition() const { return workPosition; }
    int getYear() const { return year; }
    double getSalary() const { return salary; }

    void setName(const string& newName) { name = newName; }
    void setWorkPosition(const string& newPosition) { workPosition = newPosition; }
    void setYear(int newYear) { year = newYear; }
    void setSalary(double newSalary) { salary = newSalary; }

    friend ostream& operator<<(ostream& out, const Worker work)
    {
        out << "Name: " << work.name
            << "\nPosition in work:" << work.workPosition
            << "\nYear of employment: " << work.year
            << "\nSalary: " << work.salary << endl;

        return out;
    }

    friend istream& operator>>(istream& is, Worker& work)
    {
        cout << "Enter name: ";
        getline(is >> ws, work.name);

        cout << "Enter postion in work: ";
        getline(is >> ws, work.workPosition);

        cout << "Enter year of employement: ";
        is >> work.year;

        cout << "Enter salary: ";
        is >> work.salary;
        cout << endl;

        return is;
    }
};

int main()
{
    int n = 0;
    cout << "Enter size of array: ";
    cin >> n;

    Worker* workers = new Worker[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Worker " << i + 1 << endl;
        cin >> workers[i];
    }
    Worker::saveToFile(workers, n, "outFile");
    cout << "Data from array are saved to file: 'outFile'" << endl;

    delete[] workers;

    cout << "Enter new size of array: ";
    cin >> n;
    workers = new Worker[n];

    Worker::loadFromFile(workers, n, "inFile");
    cout << "Data from file: 'inFile' are loaded" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Worker " << i + 1 << endl << workers[i] << endl;
    }

    delete[] workers;
}