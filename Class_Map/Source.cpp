
//#include "Source.h"

int main()
{

	string str1{ "HI, I WAS ALL CAPS!!!" };
	string str2{ "Hi, this is a test. Validating tokenization 1000!" };
	string str3{ "comma,ellipse...space tab\t hyphon-underscore_!!\nnewline!apostrophy's" };
	string filename{ "MyMapReduce.txt" };
	
	int tokenStart{ 0 }, tokenEnd{ 0 }; //pointers to beginning and end of each token
	 //each word trimmed and indexed in a vector
	Map myBook{10};

	myBook.map(filename, str1);
	myBook.map(filename, str2);
	myBook.map(filename, str3);
	myBook.emptyCache();

}