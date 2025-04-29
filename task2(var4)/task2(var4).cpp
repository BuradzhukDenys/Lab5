#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Matrix
{
private:
	double** data;
	int size;
public:
	Matrix() : size(3)
	{
		data = new double* [size];
		for (int i = 0; i < size; i++)
		{
			data[i] = new double[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				data[i][j] = 0;
			}
		}
	}

	Matrix(int n, double value = 0) : size(n)
	{
		if (size > 0)
		{
			data = new double* [size];
			for (int i = 0; i < size; i++)
			{
				data[i] = new double[size];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				data[i][j] = value;
			}
		}
	}

	Matrix(const Matrix& other) : size(other.size)
	{
		if (size > 0)
		{
			data = new double* [size];
			for (int i = 0; i < size; i++)
			{
				data[i] = new double[size];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				data[i][j] = other.data[i][j];
			}
		}
	}

	~Matrix()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	void ShowMatrix()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}

	double norm() const
	{
		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				sum += data[i][j] * data[i][j];
			}
		}
		return sqrt(sum);
	}

	static void saveToFile(const Matrix& matrix, const string& file)
	{
		ofstream outFile(file + ".txt", ios::app);
		outFile.clear();

		if (!outFile.is_open())
		{
			throw runtime_error("Couldn't open file to write.");
		}

		try
		{
			outFile << matrix;
			if (outFile.fail()) throw runtime_error("Error to write to file");
		}
		catch (const runtime_error e)
		{
			outFile.close();
		}

		outFile.close();
	}

	static Matrix loadFromFile(const string& file)
	{
		ifstream inFile(file + ".txt");
		if (!inFile.is_open())
		{
			throw runtime_error("Couldn't open file to write.");
		}

		string line;
		getline(inFile, line);

		if (line.find("Size: ") == string::npos)
		{
			inFile.close();
			throw runtime_error("Format for size - 'Size: N'");
		}

		int fileSize = 0;
		try
		{
			if (line.size() == 7)
			{
				fileSize = stoi(line.substr(6));
			}
		}
		catch (...)
		{
			inFile.close();
			throw runtime_error("Invalid size");
		}

		if (fileSize <= 0)
		{
			inFile.close();
			throw runtime_error("Size must be greater than zero");
		}
		Matrix result(fileSize);

		try
		{
			for (int i = 0; i < fileSize; i++)
			{
				for (int j = 0; j < fileSize; j++)
				{
					inFile >> result.data[i][j];
					if (inFile.fail() && !inFile.eof())
						throw runtime_error("Invalid matrix data");
				}
			}
		}
		catch (const exception e)
		{
			inFile.close();
		}

		inFile.close();
		return result;
	}

	Matrix operator+(const Matrix& other) const
	{
		Matrix result(size);
		if (size == other.size)
		{
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					result.data[i][j] = this->data[i][j] + other.data[i][j];
				}
			}
		}
		else cout << "Sizes must be same.\n";
		return result;
	}

	Matrix operator-(const Matrix& other) const
	{
		Matrix result(size);
		if (size == other.size)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					result.data[i][j] = this->data[i][j] - other.data[i][j];
				}
			}
		}
		else cout << "Sizes must be same.\n";
		return result;
	}

	Matrix operator*(const Matrix& other)
	{
		Matrix result(size);
		if (size == other.size)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					result.data[i][j] += this->data[i][j] * other.data[i][j];
				}
			}
		}
		else cout << "Sizes must be same.\n";
		return result;
	}

	Matrix& operator=(const Matrix& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < size; i++)
			{
				delete[] data[i];
			}
			delete[] data;
			size = other.size;

			data = new double* [size];
			for (int i = 0; i < size; i++)
			{
				data[i] = new double[size];
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Matrix& matrix)
	{
		out << "Size: " << matrix.size << endl;
		for (int i = 0; i < matrix.size; i++)
		{
			for (int j = 0; j < matrix.size; j++)
			{
				out << matrix.data[i][j] << " ";
			}
			out << endl;
		}

		return out;
	}

	friend istream& operator>>(istream& is, Matrix& matrix)
	{
		cout << "Enter size: ";
		is >> matrix.size;

		cout << "Fill matrix: ";
		for (int i = 0; i < matrix.size; i++)
		{
			for (int j = 0; j < matrix.size; j++)
			{
				is >> matrix.data[i][j];
			}
		}

		return is;
	}
};

int main()
{
	Matrix m1;
	Matrix m2(5);
	Matrix m3(3, 2);

	cout << "Matrix 1:\n";
	m1.ShowMatrix();
	cout << "Matrix 2:\n";
	m2.ShowMatrix();
	cout << "Matrix 3:\n";
	m3.ShowMatrix();

	Matrix m4(m2);
	cout << "Matrix 4:\n";
	m4.ShowMatrix();

	Matrix m5 = m1 + m3;
	cout << "Matrix 5:\n";
	m5.ShowMatrix();
	Matrix m6 = m5 - m1;
	cout << "Matrix 6:\n";
	m6.ShowMatrix();
	Matrix m7 = m5 * m3;
	cout << "Matrix 7:\n";
	m7.ShowMatrix();

	m1 = m3;
	cout << "Matrix 1:\n";
	m1.ShowMatrix();


	try
	{
		const int size = 3;
		Matrix matrices[size] = {
			Matrix(2, 1.0),
			Matrix(3, 2.0),
			Matrix(4, 3.0)
		};

		for (int i = 0; i < size; i++)
		{
			cout << matrices[i] << endl;
		}

		for (int i = 0; i < size; i++)
		{
			Matrix::saveToFile(matrices[i], "OutFile");
			cout << "Data from array are saved to file: 'outFile'" << endl;
		}
	}
	catch (const exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	try
	{
		Matrix matrix = Matrix::loadFromFile("inFile");
		cout << "Data from file: 'inFile' are loaded" << endl;
		cout << matrix << endl;
	}
	catch (const exception& e)
	{
		cerr << "Error: " << e.what();
		return 1;
	}
}