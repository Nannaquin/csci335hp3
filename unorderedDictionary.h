// CSCI 335 Steven Santana HP3


#ifndef UNORDERED_DICTIONARY
#define UNORDERED_DICTIONARY

#include<string>
#include<unordered_set>
#include<vector>

class unorderedDictionary 
{
	protected:
		
		std::unordered_set<std::string> dictionary;
		
		/** Constructor helper to populate the collection of words.
		@pre  Input file has only one word per line.
		@post  dictionary member will be populated.
		@param  inputFile  The file to source the words from. */
		void initialParse(std::string &inputFile);

		/** ******************** **
		 ** Spellchecker Helpers **
		 ** ******************** **/

		/** Determines if given char is a member of the english alphabet, or an apostraphe.
			Additionally, converts uppercase letters their lowercase counterparts.
		@post If a given letter is of the uppercase variety, it will be put into
			lowercase form.
		@param  c  The character to be checked.
		@return  True if letter is between [A,Z],[a,z] or is an apostrophe, otherwise false */
		bool isLetter(char &c);

		/** Checks if word is actually in dictionary.
		@pre  Word given only consists of english alphabet characters.
		@param  word  The word to be checked.
		@return  True if included in dictionary, otherwise false */
		bool dictionaryCheck(const std::string &word);

		/** Calls checking functions.
		@pre  Incorrect word detected.
		@post  Program will have data to print into an output file.
		@param  wordVec  The container for the incorrect word, and its 
			corrections.*/
		void correctionChecker(std::vector<std::string> &wordVec);

		/** Checks for similar words with an additional letter.
		@pre  An incorrect word has been uncovered.
		@post Similar words with an additional letter will be added to
			the corrections.
		@param  wordVec  The word to check, and space to hold its corrections. 
		@return  True if corrections found, otherwise false. */
		bool missingLetterCheck(std::vector<std::string> &wordVec);

		/** Checks for similar words with shorter by one character.
		@pre  Incorrect word isolated.
		@post Similar words, only a character shorter, will be added to 
			the corrections. 
		@param  wordVec  The word to check, and space to hold its correcitons.
		@return  True if corrections found, otherwise false. */
		bool extraLetterCheck(std::vector<std::string> &wordVec);

		/** Checks for matches off by a single (incorrect) character. 
		@pre  Incorrect word has been found.
		@post  Similar words off by one character will be added to corrections.
		@param  wordVec  The word to check, and space to hold its corrections.
		@return  True if corrections found, otherwise false. */
		bool singleTypoCheck(std::vector<std::string> &wordVec);

		/** Checks for matches of the incorrect word with two of its characters switched.
		@pre  An incorrect word has been discovered.
		@post  Possible entrie will be added to the correction collection.
		@param  wordVec  The word to check, with space to hold its corrections.*/
		void neighborSwapCheck(std::vector<std::string> &wordVec);

		/** Creates a subset of the dictionary based upon a specified length.
		@pre  One of the four mistake checking functions has been called.
		@post  A subset of dictionary member container will be made.
		@param  pM  A ref to a container for possible matches.
				len  The specified length used to create the subset.*/
		void collectByLength(std::vector<std::pair<std::string, int>> &pM, int len);


		/** Creates new correction file or appends existing one for current text.
		@pre  An incorrect word has been located, with or without corrections.
		@post  The incorrect word will be added to a text file (with or without corrections).
		@param  wordData  A vector of strings, holding the incorrect word and any potential
			corrections found.
				newFile  If true, overwrite previous file, otherwise append existing file. */
		void printCorrections(const std::vector<std::string> &wordData, const bool newFile);

		/** output file helper function. Handles actual output procedures.
		@post Data will be loaded into a plain text file.
		@param  corrOutput  The means of outputting the data.
				wordData  Holds the given incorrect word and its respective corrections (if any). */
		void printHelper(std::ofstream &corrOutput, const std::vector<std::string> &wordData);
	
	public:
	
		/** Constructor that calls a parsing function for the given input file.
		@pre  The input file has one word per line, with no punctuation marks
		@post  Dictionary will be loaded with words.
		@param  inputFile  Name of the file to be parsed.*/
		unorderedDictionary(std::string inputFile);

		unorderedDictionary();
	
		/** Checks words in the given text against the dictionary
		for typographical errors. 
		@pre  The dictionary is populated.
		@post  An output file will be created with incorrect
			words and their respective suggested resolutions.
		@param  inputFile  The file to be inspected. */
		void spellChecker(std::string inputFile);
	
};

#endif