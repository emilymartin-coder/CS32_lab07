// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY; i++) {
		for(const auto& x : table[i]) {
			count += x.second;
		}
	}
	return count;
}

int WordCount::getNumUniqueWords() const {
	int count = 0;
	for(size_t i = 0; i < CAPACITY; i++) {
		count += table[i].size();
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word);
	size_t index = hash(word);

	//word in table
	for(const auto& x : table[index]) {
		if(x.first == word) {
			return x.second;
		}
		
	}

	//word not in table
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);
	if(word.empty()) {
		return 0;
	}
	size_t index = hash(word);

	//word in table
	for(auto& x : table[index]) {
		if(x.first == word) {
			x.second++;
			return x.second;
		}
	}
	
	//word not in table
	table[index].push_back({word, 1});
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
	size_t index = hash(word);

	//word in table
	for (auto it = table[index].begin(); it != table[index].end(); it++) {
		if(it->first == word) {
			if(it->second > 1){
				it->second = it->second - 1;
				return it->second;
			} else {
				table[index].erase(it);
				return 0;
			}
		}
		
	}
// not in table
	return -1;
 }


bool WordCount::isWordChar(char c) {
	if(isalpha(c) != 0){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string valid = "";

	for(char c : word) {
		if(isWordChar(c) || c == '\'' || c == '-') {
			valid += tolower(c);
		}
	}

	while (!valid.empty() && (valid.front() == '\'' || valid.front() == '-')) {
        valid.erase(0, 1);
    }
	
    while (!valid.empty() && (valid.back() == '\'' || valid.back() == '-')) {
        valid.pop_back();
    }

	return valid;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	vector<pair<string, int>> allWords;

	for(size_t i = 0; i < CAPACITY; i++) {
		for(const auto& pair : table[i]) {
			allWords.push_back(pair);
		}
	}

	sort(allWords.begin(), allWords.end(), 
    	[](const pair<string, int>& a, const pair<string, int>& b) {
            return a.first > b.first; 
        });

	for (const auto& pair : allWords) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	vector<pair<string, int>> allWords;
    
    for (size_t i = 0; i < CAPACITY; i++) {
        for (const auto& pair : table[i]) {
            allWords.push_back(pair);
        }
    }
    
    sort(allWords.begin(), allWords.end(), 
        [](const pair<string, int>& a, const pair<string, int>& b) {

			if (a.second != b.second) {
                return a.second < b.second;
            }

			return a.first < b.first;
        });

		for (const auto& pair : allWords) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
	if (text.empty()) {
        return;
    }
    
    size_t start = 0;
    size_t end = 0;
    
	while (end < text.length()) {

		if (text[end] == ' ' || text[end] == '\n' || text[end] == '\t') {

			if (start < end) {
                std::string word = text.substr(start, end - start);
                incrWordCount(word);  
            }
            start = end + 1;
        }
        end++;
    }

	if (start < end) {
        std::string word = text.substr(start, end - start);
        incrWordCount(word);
    }
}
