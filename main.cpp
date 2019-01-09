// Steven Santana CSCI 335 Home Project the Third
#include<iostream> // perhaps
#include<chrono>
#include"unorderedDictionary.h"
#include"orderedDictionary.h"

void unorderedTest(std::string dictionarySource, std::string checkSource);
void orderedTest(std::string dictionarySource, std::string checkSource);



int main(int argc, char* argv[])
{
	if (argc > 3) {
		std::cout << "[" << argv[0] << "] [" << argv[1] << "] [" << argv[2] << "]" << std::endl;
		std::cout << argc << std::endl;
		std::cout << "first input dictionary file name, then name of file to be checked. \n"; 
		return 0;
	}
	else
	{
		std::cout << "Measurements (in Milliseconds)\n";
		/** Unordered Test **/
		unorderedTest(argv[2], argv[1]);

		/** Ordered Test **/
		orderedTest(argv[2], argv[1]);

	}	
}

void unorderedTest(std::string dictionarySource, std::string checkSource)
{
	std::chrono::steady_clock::time_point t1 =
		std::chrono::steady_clock::now();

	unorderedDictionary unDict(dictionarySource);
	unDict.spellChecker(checkSource);

	std::chrono::steady_clock::time_point t2 =
		std::chrono::steady_clock::now();

	auto unorderedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::cout << "Unordered Dictionary: " << unorderedTime.count() << std::endl;
}

void orderedTest(std::string dictionarySource, std::string checkSource)
{
	std::chrono::steady_clock::time_point t1 = 
		std::chrono::steady_clock::now();

	orderedDictionary ordDict(dictionarySource);
	ordDict.spellChecker(checkSource);

	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	auto orderedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	std::cout << "  Ordered Dictionary: " << orderedTime.count() << std::endl;
}