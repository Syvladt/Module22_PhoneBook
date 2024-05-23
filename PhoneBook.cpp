// PhoneBook.cpp: определяет точку входа для приложения.
//

#include "PhoneBook.h"
#include <map>
#include <string>
#include <conio.h>

std::string addRecord(std::map<std::string, std::string>& phonebook)
{	// Функция ввода данных
	std::string phone, name, message;
	bool fail;
	// Вводим фамилию и проверяем на корректность. Допускаются только буквы и "-",
	// например Petrov-Vodkin или Rimskii-Korsakov ... Правильно было бы добавить
	// Проверку на наличие "-" в начале и конце и наличие подряд нескольких "-", чтобы 
	// не получилось "-Shtyrtskober" или "Pokh-" или "K---im", но задача не в этом.
	std::cout << "\nEnter LAST NAME of contact: ";
	do
	{
		fail = false;
		std::cin >> name;
		for (int i = 0; !fail && i < name.length(); ++i)
			if (!isalpha(name[i]) && name[i] != '-')
			{
				fail = true;
				std::cout << "An incorrect LAST NAME was entered. Repeat, please.\n";
			}
	} while (fail);
	// Вводим номер телефона и тоже проверяем на корректность.
	// Допускаются только цифры и "+" в начале.
	std::cout << "Enter PHONE NUMBER of contact (+71234567890): ";
	do
	{
		fail = false;
		std::cin >> phone;
		if (phone.length() == 12)
		{
			for (int i = 0; !fail && i < 12; ++i)
				if (!isdigit(phone[i]))
				{
					if(i != 0 && phone[i] == '+')
					{
						fail = true;
						std::cout << "An incorrect PHONE NUMBER was entered. Repeat, please.\n";
					}
				}
		}
		else
		{
			fail = true;
			std::cout << "An incorrect PHONE NUMBER was entered. Repeat, please.\n";
		}
	} while (fail);
	phonebook.insert({ name, phone });
	// Так как оба элемента - строки, то их можно поменять местами
	// И тогда в поле name будут и телефоны.
	// Избыточно - ДА, но работает.
	phonebook.insert({ phone, name });

	return message;
}

std::string generateRecord(std::map<std::string, std::string>& phonebook)
{
	int len, ch, numRecords;
	std::string name, phone, message;
	// Генерация длины фамилии. Будем считать, что минимальная длина фамилии = 3
	len = std::rand() % 18 + 3;
	// Генерация количество записей в справочнике
	numRecords = std::rand() % 15 + 1;
	for(int i=0; i < numRecords; ++i)
	{	// Генерация фамилий контактов
		name = "";
		for (int j = 0; j < len; ++j)
		{
			if (j == 0)
				name += char(std::rand() % 26 + 65);
			else
				name += char(std::rand() % 26 + 97);
		}
		// Генерация телефонов контактов
		phone = "+";
		for (int j = 0; j < 12; ++j)
			phone += char(std::rand() % 10 + 48);
		phonebook.insert({ name, phone });
		phonebook.insert({ phone, name });
	}
	message = "Generation was successfully.";
	return message;
}

void showPhonebook(std::map<std::string, std::string>& phonebook)
{	// Функция отображения справочника.
	std::cout << "\x1B[2J\x1B[H";
	for (std::map<std::string, std::string>::iterator it = phonebook.begin(); it != phonebook.end(); ++it)
		std::cout << it->first << " " << it->second << '\n';
	std::cout << "\nPress any key ...";
	while (!kbhit()){}
}

int main()
{	// Главвная функция. Отображает главное меню и обрабатывает
	// нажатие клавиш.
	std::string message = " ", temp;
	std::map<std::string, std::string> phonebook;
	int ch = 0;
	bool success;
		
	while(ch != 68)
	{
		std::cout << "Main menu:\nA - Add data to phonebook.\nG - Generate data for phonebook.\n" << \
			"S - Show phonebook.\nF2 - Find phonenumber by last name.\nF3 - Find last name by phonenumber,\n" << \
			"F10 - Exit from phonebook.\n\n" << message << "\nMake your choice: ";
		ch = _getch();
		// Если нажата клавиша на дополнительной раскладке или сочетание клавиш
		// То считываем второй код.
		if ((ch > 200) || ch == 0)
		{
			ch = _getch();
		}
		if (ch == 132 || ch == 97) // A
		{
			message = addRecord(phonebook);
		}
		else if (ch == 191 || ch == 103) // G
		{
			message = generateRecord(phonebook);
		}
		else if (ch == 115 || ch == 139) // S
		{
			showPhonebook(phonebook);
		}
		else if (ch == 59) // F1
		{
			message = "You press key - <F1>";
		}
		else if (ch == 60)  // F2
		{
			std::cout << "\nEnter last name for search: ";
			// Что бы не заводить новую переменную - используем message.
			std::cin >> message;
			if(phonebook.count(message) > 0)
				message = "For last name " + message + " found phone number: " + phonebook.at(message);
			else
				message = "For last name " + message + " phone number not found.";
		}
		else if (ch == 61) // F3
		{
			// Ищем фамилию по номеру телефона. как я понял в multimap тоже
			// избыточная информация.
			std::cout << "\nEnter phone number for search: ";
			std::cin >> message;
			if (phonebook.count(message) > 0)
				message = "For phone number " + message + " found last name: " + phonebook.at(message);
			else
				message = "For phone number " + message + " last name not found.";
		}
		else
			message = "Undefined command. Code - " + std::to_string(ch);
		std::cout << "\x1B[2J\x1B[H";
	}
	std::cout << "\nBye bye. Thank you for use my program.\n";
	return 0;
}
