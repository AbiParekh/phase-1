
#include <iostream>
//#include "Map.h"
#include <string>
#include <regex>
#include <locale>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{

	string str{ "Hi, this is a test. Validating tokenization!" };
	string filename{ "MyMapReduce.txt" };
	int tokenStart{ 0 }, tokenEnd{ 0 }; //pointers to beginning and end of each token
	vector<string> tokenWords; //each word trimmed and indexed in a vector

	cout << "this is a test\n";

	for (int tokenStart = 0, tokenEnd = 0; tokenEnd < str.length(); tokenEnd++) //iterate through each char, check if end of work
	{
		if (ispunct(str[tokenEnd]) || str[tokenEnd] == ' ') //if char is punct 
			if (tokenStart != tokenEnd) //not first char in word
			{
				tokenWords.push_back(str.substr(tokenStart, tokenEnd - tokenStart));
				tokenStart = tokenEnd + 1;	// moves word start to next char
			}
			else if (tokenStart == tokenEnd) //first char in word is a punct
			{
				tokenStart = tokenEnd + 1; // moves word start to next char
			}
	}
	cout << "tokenization complete!";
}