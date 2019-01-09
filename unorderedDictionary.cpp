// CSCI 335 Steven Santana HP 3
#include<fstream>
#include<string>
#include<vector> // for collection of corrections.
#include<utility> // for std::pair
#include"unorderedDictionary.h"

unorderedDictionary::unorderedDictionary(std::string inputFile)
{
	initialParse(inputFile);	
}

unorderedDictionary::unorderedDictionary() { }

void unorderedDictionary::initialParse( std::string &inputFile)
{
	std::ifstream dictSrc(inputFile);
	std::string lineHolder;
	if (dictSrc.is_open())
	{
		while (dictSrc.good())
		{
			getline(dictSrc, lineHolder);
			dictionary.insert(lineHolder);
		}
		dictSrc.close();
	}
}


void unorderedDictionary::spellChecker(std::string inputFile)
{
	std::ifstream checkSrc(inputFile);
	std::string lineHolder;
	std::string wordHolder; 
	bool isNewFile = true; // Determines if append or overwrite.

	if (checkSrc.is_open())
	{
		while (checkSrc.good())
		{
			getline(checkSrc, lineHolder);

			for (auto lCharItr = lineHolder.begin(); lCharItr != lineHolder.end(); lCharItr++)
			{
				if (isLetter(*lCharItr)) wordHolder += *lCharItr;
				else  // Begin checking procedure.
				{
					if (dictionaryCheck(wordHolder)) { /** Do nothing if valid word.*/ }
					else
					{
						std::vector<std::string> correctionVec; // first elem always the incorrect word
						correctionVec.push_back(wordHolder);

						correctionChecker(correctionVec);
						
						printCorrections(correctionVec, isNewFile);
						isNewFile = false;
					}
					wordHolder.clear();
				}
			} 
		}
		checkSrc.close();
	}
}

bool unorderedDictionary::isLetter(char &c)
{
	if (c >= 'A' && c <= 'Z') {
		c += 32;
		return true;
	}
	else if (c >= 'a' && c <= 'z')
		return true;
	else if (c == (char)39)  // ASCII[39] == '
		return true; 

	else return false;
}

bool unorderedDictionary::dictionaryCheck(const std::string &word)
{
	if (dictionary.find(word) != dictionary.end()) return true;
	else return false;
}

void unorderedDictionary::correctionChecker(std::vector<std::string> &wordVec)
{
	if (missingLetterCheck(wordVec))
		return;
	else if (extraLetterCheck(wordVec))
		return;
	else if (singleTypoCheck(wordVec))
		return;
	else neighborSwapCheck(wordVec);
}

bool unorderedDictionary::missingLetterCheck(std::vector<std::string> &wordVec)
{
	// first is potential match, second is # of character mismatches.
	std::vector<std::pair<std::string, int>> possibleMatches;
	collectByLength(possibleMatches, wordVec[0].length() + 1);
	
	

	// later steps
	for (auto &x : possibleMatches)
	{
		unsigned int shift = 0; 
		for (int i = 0; i < wordVec[0].length() + 1; i++)
		{ 
			while (x.first[i + shift] != wordVec[0][i])
			{
				x.second++;
				shift++;
				if (shift > 1) break;
			}
			if (x.second > 1)
				break; // too many differences to be a possible match
			else if (i == x.first.length() - 1 && x.second == 1)
				wordVec.push_back(x.first); // add to corrections.
		}
	}

	if (wordVec.size() > 1) return true;
	else return false;
}

bool unorderedDictionary::extraLetterCheck(std::vector<std::string> &wordVec)
{
	// first is potential match, second is # of character mismatches.
	std::vector<std::pair<std::string, int>> possibleMatches;
	collectByLength(possibleMatches, wordVec[0].length() - 1);


	// later steps
	for (auto &x : possibleMatches)
	{
		unsigned int shift = 0;
		for (int i = 0; i < wordVec[0].length() - 1; i++)
		{
			while (x.first[i] != wordVec[0][i + shift])
			{
				x.second++;
				shift++;
				if (shift > 1) break;
			}
			if (x.second > 1)
				break; // to many differences to be a possible match
			else if (i == x.first.length() - 1 && x.second == 1)
				wordVec.push_back(x.first); // add to corrections.
		}
	}
	if (wordVec.size() > 1) return true;
	else return false;
}
bool unorderedDictionary::singleTypoCheck(std::vector<std::string> &wordVec)
{
	// first is potential match, second is # of character mismatches.
	std::vector<std::pair<std::string, int>> possibleMatches;
	collectByLength(possibleMatches, wordVec[0].length());

	// Combing possible matches for valid corrections.
	for (auto &x : possibleMatches)
	{
		for (int i = 0; i < wordVec[0].length(); i++)
		{
			if(x.first[i] != wordVec[0][i])
			{
				x.second++;
			}
			if (x.second > 1)
				break;
			else if (i == x.first.length() - 1 && x.second == 1)
				wordVec.push_back(x.first);
		}
	}
	if (wordVec.size() > 1) return true;
	else return false;
}

void unorderedDictionary::neighborSwapCheck(std::vector<std::string> &wordVec)
{
	// first is potential match, second is # of character mismatches.
	std::vector<std::pair<std::string, int>> possibleMatches; 

	collectByLength(possibleMatches, wordVec[0].length());

	// Later steps.
	for (auto &x : possibleMatches)
	{
		for (int i = 0; i < wordVec[0].length(); i++)
		{
			if (x.first[i] != wordVec[0][i])
			{
				if (x.first[i] == wordVec[0][i + 1] && x.first[i + 1] == wordVec[0][i])
					i++;
				else x.second = 2; // immediate disqualification
			}
			if (x.second > 1)
				break;
			else if (i == x.first.length() - 1)
			{
				wordVec.push_back(x.first);
				break;
			}
		}
	}
}

void unorderedDictionary::collectByLength(std::vector<std::pair<std::string, int>> &pM, int len) 
{
	for (auto i = dictionary.begin(); i != dictionary.end(); i++)
	{
		std::string candidate = *i;
		if (candidate.length() == len)
		{
			pM.push_back({ candidate, 0 });
		}
	}
}

void unorderedDictionary::printCorrections(const std::vector<std::string> &wordData, const bool newFile)
{
	const std::string fileName = "unorderedCorrections.txt";
	if (newFile)
	{
		std::ofstream corrOutput(fileName);
		printHelper(corrOutput, wordData);
		corrOutput.close();
	}
	else
	{
		std::ofstream corrOutput(fileName, std::ofstream::app);
		printHelper(corrOutput, wordData);
		corrOutput.close();
	}

}

void unorderedDictionary::printHelper(std::ofstream &corrOutput, const std::vector<std::string> &wordData)
{
	corrOutput << wordData[0] << ": ";
	for (int i = 1; i < wordData.size(); i++)
	{
		corrOutput << wordData[i] << " ";
	}
	corrOutput << "\n";
}