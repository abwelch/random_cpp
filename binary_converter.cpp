#include <iostream>
#include <fstream>
#include <string>
#include <exception>

void ValidateFile(std::ifstream&);
bool Spaces();
void Convert(std::ifstream &);
void ConvertWithSpaces(std::ifstream &);

int main()
{
	std::cout << "*** Binary to ASCII converter ***\n\n";
	std::ifstream input_file;
	ValidateFile(input_file);
	std::cin.ignore();
	if (Spaces())
	{
		ConvertWithSpaces(input_file);
	}
	else
	{
		Convert(input_file);
	}
	input_file.close();
	return 0;
}

void ValidateFile(std::ifstream& input_file)
{
	bool first_pass = true;
	bool file_opened = true;
	std::string filename = "";
	do
	{
		if (!first_pass)
		{
			std::cout << "ERROR: Unable to open file with name: " 
					  << filename << std::endl << std::endl;
		}
		std::cout << "Enter the filename you wish to process: ";
		std::cin >> filename;
		input_file.open(filename);
		file_opened = input_file.is_open();
		if (!file_opened)
		{
			first_pass = false;
		}
	} while (!file_opened);
}

bool Spaces()
{
	const char yes = 'Y';
	const char no = 'N';
	const char quit = 'X';
	std::string input = "";
	bool first_pass = true;
	bool invalid_input = false;
	do
	{
		if (!first_pass)
		{
			std::cout << "ERROR: A valid option was not inputted!\n\n";
		}
		std::cout << "Spaces? (Y/N or X to quit):  ";
		std::getline(std::cin, input);
		invalid_input = (input[0] != yes && input[0] != no && input[0] != quit);
		if (first_pass && invalid_input)
		{
			first_pass = false;
		}
	} while (invalid_input);
	if (input[0] == yes)
	{
		return true;
	}
	return false;
}

void Convert(std::ifstream& file)
{
	std::string wholeFile = "";
	std::string byte = "";
	short binaryTotal = 0;
	char asciiValue;
	std::ofstream convertedFile;
	convertedFile.open("converted.txt");
	std::getline(file, wholeFile);
	for (int i = 0; wholeFile[i] != '\0'; i += 8)
	{
		try 
		{
			byte = wholeFile.substr(i, 8);
		}
		catch (std::exception e) 
		{
			std::cout << "ERROR: file is invalid!\n";
			convertedFile.close();
			return;
		}

		for (int i = 0; i < 8; ++i)
		{
			if (byte[i] != '0')
			{
				switch (i)
				{
					case 0:
						binaryTotal += 128;
						break;
					case 1:
						binaryTotal += 64;
						break;
					case 2:
						binaryTotal += 32;
						break;
					case 3:
						binaryTotal += 16;
						break;
					case 4:
						binaryTotal += 8;
						break;
					case 5:
						binaryTotal += 4;
						break;
					case 6:
						binaryTotal += 2;
						break;
					case 7:
						binaryTotal += 1;
						break;
				}
			}
		}
		asciiValue = binaryTotal;
		convertedFile << asciiValue;
		binaryTotal = 0;
	}
	convertedFile.close();
}

void ConvertWithSpaces(std::ifstream& file)
{
	std::string byte = "";
	short binaryTotal = 0;
	char asciiValue;
	std::ofstream convertedFile;
	convertedFile.open("converted.txt");
	while (file >> byte)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (byte[i] != '0')
			{
				switch (i)
				{
					case 0:
						binaryTotal += 128;
						break;
					case 1:
						binaryTotal += 64;
						break;
					case 2:
						binaryTotal += 32;
						break;
					case 3:
						binaryTotal += 16;
						break;
					case 4:
						binaryTotal += 8;
						break;
					case 5:
						binaryTotal += 4;
						break;
					case 6:
						binaryTotal += 2;
						break;
					case 7:
						binaryTotal += 1;
						break;
				}
			}
		}
		asciiValue = binaryTotal;
		convertedFile << asciiValue;
		binaryTotal = 0;
	}
	convertedFile.close();
}