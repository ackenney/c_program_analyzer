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
void removeComments(vector<string>& x, string key[]);
void createIDTable(vector<string> in, string key[], vector<string>& out);


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

	// get input -> strip comments -> make ID table
	getInput(inputVector, inFile);
	removeComments(inputVector, keywordArray);
	createIDTable(inputVector, keywordArray, IDTableVector);
	
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

void removeComments(vector<string> &x, string key[])
{
	// Declaring temp  vector
	vector<string> tempVector;

	for (unsigned int i = 0; i < x.size(); i++)
	{
		// loop	until you reach the opening comment
		if (x.at(i) == key[25]) // key[25] == "/*" from the keyword table
		{
			// loop	until you reach the end comment
			while (x.at(i) != key[26]) // key[26] == "*/" from the keyword table
			{
				i = i + 1; // Adding 1 to the index
			}
		}
		else 
		{
			// pushing the value to the temp vector
			tempVector.push_back(x.at(i));
		}
	}

	//Returning the vector with the input without comments
	x = tempVector;
} // End of removeComments function

void createIDTable(vector<string> in, string key[], vector<string>& out)
{
	// Declaring variables
	vector<string> idVector;
	string tempString = "";
	char   tempChar;
	bool  idBool;

	// Looping until end of input
	for (unsigned int i = 0; i < in.size(); i++)
	{
		// Getting one string at at time
		tempString = in.at(i);

		for (unsigned int j = 0; j < tempString.size(); j++)
		{
			// Reading one char from string
			tempChar = tempString[j];

			if ((tempChar >= 'a' && tempChar <= 'z'))
			{
				// if char is a letter then it is currently an id
				idBool = true;
			}
			else
			{
				// If char is not a letter it can't be an id
				idBool = false;
				break;
			}

		}

		// Checking if the string is a key word
		for (int k = 0; k < KEYWORD_TABLE_LENGTH; k++)
		{
			if (tempString == key[k])
			{
				// if string is a keyword then it can't be an id
				idBool = false;
			}
		}

		// Checking if it was an already added id
		for (unsigned int i = 0; i < idVector.size(); i++)
		{
			if (tempString == idVector.at(i))
			{
				idBool = false;
			}
		}

		// Pushing the string to the vector if the string is an id and not a keyword
		if (idBool == true)
		{
			idVector.push_back(tempString);
		}

	}

	out = idVector; // Returning keyword vector

	return;
}// End of createIDTable function