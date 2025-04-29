#include <iostream>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

bool isVowel(char c)
{
	c = tolower(c);
	if (c == 'а' || c == 'е' || c == 'є' || c == 'и' || c == 'і' ||
		c == 'ї' || c == 'о' || c == 'у' || c == 'ю' || c == 'я')
	{
		return true;
	}

	return false;
}

int countVowels(const string& text)
{
	int count = 0;
	for (char c : text)
	{
		if (isVowel(c)) count++;
	}

	return count;
}

int numberWordsInText(const string& text)
{
	int words = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (i == 0 && text[i] != ' ')
		{
			words++;
		}
		if (i != 0 && text[i] != ' ' && text[i - 1] == ' ')
		{
			words++;
		}
	}

	return words;
}

void mostVowels(const string& text)
{
	string maxVowelWord;
	string currentWord;
	int vowelCount = 0;
	int maxVowels = 0;

	for (int i = 0; i < text.length(); i++)
	{
		while (i < text.length() && text[i] == ' ')
		{
			i++;
		}

		currentWord.clear();
		while (i < text.length() && text[i] != ' ')
		{
			currentWord += text[i];
			i++;
		}

		if (!currentWord.empty())
		{
			vowelCount = countVowels(currentWord);

			if (vowelCount > maxVowels)
			{
				maxVowels = vowelCount;
				maxVowelWord = currentWord;
			}
		}
	}

	if (maxVowels > 0)
	{
		cout << "Слово з найбільшою кількістю голосних: " << maxVowelWord
			<< " ( " << maxVowels << " голосних )" << endl;
	}
}

string dateToText(const string& date)
{
	map<string, string> months = {
		{"01", "січня"}, {"02", "лютого"}, {"03", "березня"},
		{"04", "квітня"}, {"05", "травня"}, {"06", "червня"},
		{"07", "липня"}, {"08", "серпня"}, {"09", "вересня"},
		{"10", "жовтня"}, {"11", "листопада"}, {"12", "грудня"}
	};

	map<string, string> days = {
		{"01", "перше"}, {"02", "друге"}, {"03", "третє"}, {"04", "четверте"},
		{"05", "п'яте"}, {"06", "шосте"}, {"07", "сьоме"}, {"08", "восьме"},
		{"09", "дев'яте"}, {"10", "десяте"}, {"11", "одинадцяте"}, {"12", "дванадцяте"},
		{"13", "тринадцяте"}, {"14", "чотирнадцяте"}, {"15", "п'ятнадцяте"}, {"16", "шістнадцяте"},
		{"17", "сімнадцяте"}, {"18", "вісімнадцяте"}, {"19", "дев'ятнадцяте"}, {"20", "двадцяте"},
		{"21", "двадцять перше"}, {"22", "двадцять друге"}, {"23", "двадцять третє"}, {"24", "двадцять четверте"},
		{"25", "двадцять п'яте"}, {"26", "двадцять шосте"}, {"27", "двадцять сьоме"}, {"28", "двадцять восьме"},
		{"29", "двадцять дев'яте"}, {"30", "тридцяте"}, {"31", "тридцять перше"}
	};

	int colon = date.find(":");
	if (colon == string::npos || colon != 2 || date.size() != 5)
	{
		return "Невірний формат дати";
	}

	string day = date.substr(0, 2);
	string month = date.substr(3, 2);
	if (days.find(day) == days.end() || months.find(month) == months.end())
	{
		return "Невірна дата";
	}

	return days[day] + " " + months[month];
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int var = 0;
	cout << "Виберіть пункт завдання\n"
		<< "1. Текстовий рядок вводиться з клавіатури, виводить кількість слів у тексті та слов, що містить найбільшу кількість голосних\n"
		<< "2. Вводиться з клавіатури дата (день, місяць 25:05), виводить дату текстом\n";
	cin >> var;

	string text;
	string result;
	switch (var)
	{
	case 1:
		cout << "Введіть текстовий рядок: ";
		getline(cin >> ws, text);

		mostVowels(text);
		cout << "Кількість слів в тексті: " << numberWordsInText(text) << endl;
		break;
	case 2:
		cout << "Введіть дату (день, місяць, 15:03):";
		getline(cin >> ws, text);

		result = dateToText(text);
		cout << "Дата текстом: " << result << endl;
		break;
	default:
		cout << "Неправильний пункт завдання\n";
		break;
	}

}