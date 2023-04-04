//c_program_analyzer

#include<iostream>
#include <fstream>
#include <string> 
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


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
	
	// Closing i/o files files
	inFile.close();
	outFile.close();

	return 0;
}//End of Main