/**
	--- AoC 2017 ---
	--- Day 4: High-Entropy Passphrases ---
	http://adventofcode.com/2017/day/4
-------------------------------------------------------------------------------------------------------------
Part 1:
A new system policy has been put in place that requires all accounts to use a passphrase instead of simply a password. 
A passphrase consists of a series of words (lowercase letters) separated by spaces.

To ensure security, a valid passphrase must contain no duplicate words.

For example:

    aa bb cc dd ee is valid.
    aa bb cc dd aa is not valid - the word aa appears more than once.
    aa bb cc dd aaa is valid - aa and aaa count as different words.

The system's full passphrase list is available as your puzzle input. How many passphrases are valid?

-------------------------------------------------------------------------------------------------------------
Part 2:

For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words 
that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any 
other word in the passphrase.

For example:

    abcde fghij is a valid passphrase.
    abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
    a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
    iiii oiii ooii oooi oooo is valid.
    oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.

Under this new system policy, how many passphrases are valid?

*/
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <sstream>
#include <algorithm>
#include <map>

bool isAnagram(const std::string a, const std::string b)
{
	if(a.size() != b.size()) return false;

	unsigned matchedChars = 0;
	for(unsigned i=0; i<a.size(); ++i)
	{
		const char C = a[i];
		if(std::find(b.begin(), b.end(), C) == b.end())
		{
			return false;
		}
	}
	return true;
}

void day4()
{
	std::vector<std::string> input;

	// Read the input from file.
	{	
		std::ifstream ifs("input_day4.txt");
		std::string str;
		while(!ifs.eof())
		{
			char c = ifs.get();
			if(c != '\n') 
				str += c;
			else
			{
				input.push_back(str);
				str = "";
			}
		}	

		/*for(unsigned i=0; i<input.size(); ++i)
		{
			std::cout << input[i] << std::endl;
		}*/
	}
	
// == Part 1 ==================================================================================
{
	unsigned totalValidPhrases = input.size();
	for(unsigned i=0; i<input.size(); ++i)
	{
		std::map<std::string, unsigned> resultMap;

		std::stringstream ss(input[i]);
		std::string str; 
		while(ss >> str)
		{
			++resultMap[str];
			if(resultMap[str] > 1)
			{
				//std::cout << input[i] << " is invalid because of multiple " << str << std::endl;
				--totalValidPhrases;
				break;
			}
		}
	}

	std::cout << "Number of valid passphrases: " << totalValidPhrases << std::endl;
}
// == Part 2 ==================================================================================
{
	unsigned totalValidPhrases = input.size();
	for(unsigned i=0; i<input.size(); ++i)
	{
		std::vector<std::string> wordList;

		// Read all words from this line.
		{
			std::stringstream ss(input[i]);
			std::string str; 
			while(ss >> str) wordList.push_back(str);
		}
		
		// Loop through each word.
		for(unsigned j=0; j<wordList.size()-1; ++j)
		{
			std::string& word = wordList[j];
			bool foundAnagram = false;

			// Now check with every following word for anagrams.
			for(unsigned jj=j+1; jj<wordList.size(); ++jj)
			{
				if(isAnagram(word, wordList[jj]))
				{
					--totalValidPhrases;
					foundAnagram = true;
					break;
				}	
			}
			// If an anagram was found skip to next line.
			if(foundAnagram) break;	
		}
	}

	std::cout << "Number of valid passphrases: " << totalValidPhrases << std::endl;
}
}
