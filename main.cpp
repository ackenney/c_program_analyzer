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
void createNumberTable(vector<string> in, string key[], vector<string>& out);
void getTokens(string key[], vector<string> ID, vector<string> num, vector<string> in, ofstream& outFile);


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

	// get input -> strip comments -> make ID table -> make number table -> make tokens table
	getInput(inputVector, inFile);
	removeComments(inputVector, keywordArray);
	createIDTable(inputVector, keywordArray, IDTableVector);
	createNumberTable(inputVector, keywordArray, numberTableVector);
	getTokens(keywordArray, IDTableVector, numberTableVector, inputVector, outFile);
	
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

void createNumberTable(vector<string> in, string key[], vector<string>& out)
{
	// Declaring variables
	vector<string> numVector;
	string tempString = "";
	char   tempChar;
	bool  numBool;

	// Looping until end of input
	for (unsigned int i = 0; i < in.size(); i++)
	{
		// Getting one string at at time
		tempString = in.at(i);

		for (unsigned int j = 0; j < tempString.size(); j++)
		{
			// Getting one char at at time
			tempChar = tempString[j];

			// If the char is a num it could be an id
			if (tempChar >= '0' && tempChar <= '9')
			{
				numBool = true;
			}
			else
			{
				// if any character is not a num then it can't be a num
				numBool = false;
				break;
			}

		}

		// Checking to make sure string is not a keyword
		for (int k = 0; k < KEYWORD_TABLE_LENGTH; k++)
		{
			if (tempString == key[k])
			{
				numBool = false;
			}
		}

		// Checking to make sure the string is not an already added num
		for (unsigned int i = 0; i < numVector.size(); i++)
		{
			if (tempString == numVector.at(i))
			{
				numBool = false;
			}
		}

		// Pushing num to vector if it is a num
		if (numBool == true)
		{
			numVector.push_back(tempString);
		}

	}

	out = numVector;  // Returning num table

	return;

} //End of number table function

void getTokens(string key[], vector<string> ID, vector<string> num, vector<string> in, ofstream& outFile)
{
	// Declaring variables
	string tempString;

	// Output header to console
	std::cout << "\n-------------------------------------\n"
		<< "Token Table\n"
		<< "-------------------------------------\n";
	std::cout << "Token\t class\t Index\n\n";

	// Output header to file
	outFile << "\n-------------------------------------\n"
		<< "Token Table\n"
		<< "-------------------------------------\n";
	outFile << "Token\t class\t Index\n\n";

	// Looping to check all input
	for (unsigned int i = 0; i < in.size(); i++)
	{
		// Temp holds value to be checked 
		tempString = in.at(i);

		// Checking table to see if value is an id
		for (unsigned int z = 0; z < ID.size(); z++)
		{
			if (tempString == ID.at(z))
			{
				// Output token to console
				std::cout << ID.at(z) << " \t id  \t " << z + 1 << std::endl;

				// Output token to file
				outFile << ID.at(z) << " \t id  \t " << z + 1 << std::endl;
			}
		}

		// Checking table to see if value is a keyword
		for (int j = 0; j < KEYWORD_TABLE_LENGTH; j++)
		{
			if (tempString == key[j])
			{
				// Output token to console
				std::cout << key[j] << " \t kw  \t " << j + 1 << std::endl;

				// Output token to file
				outFile << key[j] << " \t kw  \t " << j + 1 << std::endl;
			}
		}

		// Checking table to see if value is a num
		for (unsigned int p = 0; p < num.size(); p++)
		{
			if (tempString == num.at(p))
			{
				// Output token to console
				std::cout << num.at(p) << " \t num  \t " << p + 1 << std::endl;

				// Output token to file
				outFile << num.at(p) << " \t num  \t " << p + 1 << std::endl;
			}
		}
	}

	return;

} // End of getTokens function



