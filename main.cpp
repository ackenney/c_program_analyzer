//c_program_analyzer

#include<iostream>
#include <fstream>
#include <string> 
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

// Constant variables
const int KEYWORD_TABLE_LENGTH = 27;

//Prototypes
void getInput(vector<string>& x, ifstream& inFile);

int main()
{
	string fileName;

	// Declaring vectors that will hold the input 
	vector<string> inputVector;
	vector<string> numberTableVector;
	vector<string> IDTableVector;
	vector<string> tokenTable;

	//file stream variable
	ifstream inFile;
	ofstream outFile;

	// Declaring keyword table
	std::string keywordArray[] = { "else" , "if" , "int" , "return" , "void" , "while", "+" , "-",
							  "*" , "/" , "<" , "<=" , ">" , ">=" , "==", "!=", "=", ";" , ",",
							  "(", ")" , "[" , "]" , "{" , "}" , "/*" , "*/" };

	
	std::cout << "Enter file name: "; std::cin >> fileName;
	
	// Opening files
	inFile.open(fileName);
	outFile.open("output.txt");

	// Checking if the files opened
	if (!inFile.good() && !outFile.good())
	{
		std::cout << "Error opening file:\n";
	}

	// get input
	getInput(inputVector, inFile);
	
	// Closing i/o files files
	inFile.close();
	outFile.close();

	return 0;
}//End of Main

// get c program input
void getInput(vector<string>& x, ifstream& inFile)
{
	// Declaring variables
	vector<char> vectorChars; //Vector hold input char by char
	string tempString = ""; // temp var

	// Puting each character from file into a char vector
	while (!inFile.eof())
	{
		// Getting char
		vectorChars.push_back(inFile.get()); // 
	}

	// Making each letter into a word
	// looping until the end of the input
	for (unsigned int i = 0; i < vectorChars.size(); i++)
	{
		// if the chars is not a new line or a space it gets added to the temp string
		if (vectorChars.at(i) != '\n' && vectorChars.at(i) != ' ')
		{
			tempString += vectorChars.at(i);

		}

		// If char is a space or new line it gets added and the string gets pushed to the vector
		if (vectorChars.at(i) == ' ')
		{
			if (tempString != "")
			{
				x.push_back(tempString); // Pushing string
				tempString = ""; // Reset string
			}
			x.push_back(" "); // Pushing space
		}
		if (vectorChars.at(i) == '\n')
		{
			if (tempString != "")
			{
				x.push_back(tempString); // Pushing string
				tempString = ""; // Reset string
			}
			x.push_back("\n"); // Pushing new line
		}

		// adding last string
		if (i == vectorChars.size() - 1)
		{
			tempString = vectorChars.at(vectorChars.size() - 2);
			x.push_back(tempString);
		}

	}

}//End of gitInput