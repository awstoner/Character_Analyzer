// Alexander Stoner
// COP4530
// Project 6
// Due: 7/27/21

#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

// Fxn Prototypes: Each prints the top 10 characters, words, numbers respectively
void printChar(std::map<string, pair<int, int>> &map, int loopCount);  
void printWord(std::map<string, pair<int, int>> &map, int loopCount); 
void printNum(std::map<string, pair<int, int>> &map, int loopCount);  

int main(){

    // Ordered associative container "map" used to store the element in input file as well as # of times it is found
    // 3 separate maps for characters, words, numbers
	std::map<string, pair<int, int>> charMap; 
	std::map<string, pair<int, int>> wordMap; 
	std::map<string, pair<int, int>> numMap; 
	char char1; // temp variable to hold character read in via cin.get()
	string char2; // string variable to hold character via appending char1
	string word; // string variable to hold word read in
	string number; // string variable to hold number read in
	int charCount = 0; // counter of total # of characters
	int wordCount = 0; // counter of total # of words 
	int numCount = 0; // counter of total # of numbers
	
	while(!cin.eof())
	{ 
		cin.get(char1); 
		charCount++;	// increment counter of characters read
		char2 += char1; // append temp variabel char1 to char2

		if(isdigit(char1))	//check if character read in is a number
		{
            number += char1;        //add to var number
			if(word.size() >= 1){                   //if there are characters in var word (read in previously)
				if(wordMap.find(word) == wordMap.end())
                {
					wordMap.insert(make_pair(word, make_pair(1, charCount)));       //if word not found in map, insert it as first instance inserted
					wordCount++;        //increment total count of words
				}
				else
					++wordMap[word].first;      //if already found, increment number of instances of that word
				word = ""; //reset var word
			}
		}
		else if(isalpha(char1))     //check if character read in is a number
		{
			word += tolower(char1);     //convert all to lowercase to have same ascii val
			if(number.size() >= 1){             //if there is are characters in var number
				if(numMap.find(number) == numMap.end()){
					numMap.insert(make_pair(number, make_pair(1, charCount)));  //if number not found in map, insert it as first instance inserted
					numCount++;         //increment total count of numbers
				}
				else
					++numMap[number].first;     //if already found, increment number of instances of that number
				number = ""; 
			}
		}
		else        //if char read in is neither alpha or numeric, repeat above process to insert words or numbers
                    // into their respective maps
		{
			if(word.size() >= 1){
				if(wordMap.find(word) == wordMap.end()){
					wordMap.insert(make_pair(word, make_pair(1, charCount)));       //if char read in is neither alpha or numeric, repeat above process to insert words or numbers
					wordCount++;
				}
				else
					++wordMap[word].first;
				word = "";
			}
			else if(number.size() >= 1)
            {
				if(numMap.find(number) == numMap.end()){
					numMap.insert(make_pair(number, make_pair(1, charCount)));
					numCount++;
				}
				else
					++numMap[number].first;
				number = ""; 
			}
		}
		++charMap[char2].first;     //increment the number of characters read
		char2 = ""; 
	} 

    //Calling of print fxns
    printChar(charMap, charCount);      
    printWord(wordMap, wordCount);
	printNum(numMap, numCount);

	return 0;
}

void printChar(std::map<string, pair<int, int>> &map, int loopCount){
	int counter = 0;
    std::map<string, pair<int, int>>::iterator tempItr = map.begin();
	
	if(loopCount > 10){
		loopCount = 10;
    }

	
	if(loopCount > map.size())
    {
		loopCount = map.size();
    }

	cout << "Total "<< map.size() << " different characters, " << loopCount << " most used characters:" << endl;
	for(int i = 0; i < loopCount; i++)
    {
		int value = 0;

		for(std::map<string, pair<int, int>>::iterator it = map.begin(); it != map.end(); ++it){
			 if(it->second.first > value || (it->second.first == value && (it->second.second < tempItr->second.second))){
				value = it->second.first;
				tempItr = it;
				counter++;
			}
		}
		cout << "No. " << i << ": ";
		if(tempItr->first == "\t")
			cout << "\\t" << "		" << value << endl;
		else if(tempItr->first == "\n")
			cout << "\\n" << "		" << value << endl;
		else
			cout << tempItr->first << "		" << value << endl;
		map.erase(tempItr); 
	}
}				


void printWord(map<string, pair<int, int>> &map, int loopCount){
    int counter = 0;
	std::map<string, pair<int, int>>::iterator tempItr = map.begin();
	
	if(loopCount > 10)
		loopCount = 10;
	
	if(loopCount > map.size())
		loopCount = map.size();
	
	cout << endl << "Total "<< map.size() << " different words, " << loopCount << " most used words:" << endl;
	for(int i = 0; i < loopCount; i++){
		int value = 0; 

		for(std::map<string, pair<int, int>>::iterator it = map.begin(); it != map.end(); ++it){
			if(it->second.first > value || (it->second.first == value && (it->second.second < tempItr->second.second))){
				value = it->second.first;
				tempItr = it;
				counter++;
			}
		}
		cout << "No. " << i << ": " << tempItr->first << "		" << value << endl;
		map.erase(tempItr); 
	}
}					

void printNum(map<string, pair<int, int>> &map, int loopCount){
	int counter = 0;
	std::map<string, pair<int, int>>::iterator tempItr = map.begin();

	if(loopCount > 10)
		loopCount = 10;  
	
	if(loopCount > map.size())
		loopCount = map.size();
	
	cout << endl << "Total "<< map.size() << " different numbers, " << loopCount << " most used numbers:" << endl;
	for(int i = 0; i < loopCount; i++){
		int value = 0; 

		for(std::map<string, pair<int, int> >::iterator it = map.begin(); it != map.end(); ++it){
			if(it->second.first > value || (it->second.first == value && (it->second.second < tempItr->second.second))){
				value = it->second.first;
				tempItr = it;
				counter++;
			}
		}
		cout << "No. " << i << ": " << tempItr->first << "		" << value << endl;
		map.erase(tempItr); 
	}
}
