// WordCount.h

#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class WordCount {
public:
  WordCount();
  // Default Constructor

  int getTotalWords() const;
  // Return total number of word occurrences (for all words) in the
  // hash table.

  int getNumUniqueWords() const;
  // Return total number of unique words that exist in the hash table.
  // Note that multiple occurrences of a word is considered one unique
  // word.

  int getWordCount(std::string word) const;
  // Return the number of occurences for a specific word.
  // You may not assume the parameter is a valid word and must
  // strip / convert to lower case before looking in the hash table.
  // If the word does not exist in the table, return 0

  int incrWordCount(std::string word);
  // Update the hash table by incrementing the number of occurences for
  // the word. You MAY NOT assume the parameter word is a valid word.
  // Words must be hashed and stored containing all lower case
  // characters.
  // * If the word is not in the table, then add it with the number
  // of occurences equal to 1.
  // * If the word was added, this method updates the number of occurences
  // of the word in the hash table, and returns the current number of
  // occurences of the word after it was added.

  int decrWordCount(std::string word);
  // Update the hash table by decrementing the number of occurences for
  // the word. You MAY NOT assume the parameter word is a valid word.
  // The word must be converted to a valid word containing all
  // lower case characters to be searched through the hash table.
  // * If an entry for the word exists and the number of occurences is > 1,
  // then the number of occurences for this word entry is updated and this
  // method returns the updated number of occurences.
  // * If the number of occurences for the word is 1, then the key / value
  // pair entry in the hash table is removed from the vector and 0 is
  // returned.
  // * If the word does not exist, then this method returns -1.

  static bool isWordChar(char c);
  // Useful as a helper method in your code.
  // Returns true if c is a valid word character defined as either
  // a lower-case or upper-case alpha char.

  static std::string makeValidWord(std::string word);
  // Words cannot contain any digits, or special characters EXCEPT for
  // hyphens (-) and apostrophes (') that occur in the middle of a
  // valid word (the first and last characters of a word must be an alpha
  // character). All upper case characters in the word should be convertd
  // to lower case.
  // For example, "can't" and "good-hearted" are considered valid words.
  // "12mOnkEYs-$" will be converted to "monkeys".
  // "Pa55ive" will be converted to "paive".
  // "$money!" will be converted to "money"
  // "C++" will be converted to "c"
  // "$1wo,rd-%#" will be converted to "word"
  // "'nuff-said-" will be converted to "nuff-said".


////// NEW FUNCTIONS FOR LAB07a //////
  void dumpWordsSortedByWord(std::ostream &out) const;
  // dump each word,count pair as CSV to std::ostream, sorted by word in
  // descending lexicographical order based on ASCII values. Each word,count
  // pair will be in its own line with as: word,numOccurence\n
  // For example: "Sentence is a sentence" will be:
  // sentence,2
  // is,1
  // a,1

  void dumpWordsSortedByOccurence(std::ostream &out) const;
  // dump each word,count pair as CSV to std::ostream, sorted by occurence in
  // ascending order. In the event of a tie, ordering is defined by the
  // ascending lexicographical order of the word key based on ASCII value.
  // Each word count pair will be in its own line with as word,numOccurence\n
  // For example, "Sentence is a fun fun sentence" will be:
  // a,1
  // is,1
  // fun,2
  // sentence,2

  void addAllWords(std::string text);
  // parse out string text into individual words, and add each word
  // to the hash table. You may assume that words are always
  // separated by whitespace characters (' ','\n','\t') within the
  // string text.

private:
  const static size_t CAPACITY = 100;
  // capacity for the hash table array

  std::vector<std::pair<std::string, int> > table[CAPACITY];
  // hash table array of vectors. Each index in the array will contain
  // a vector. Each element in the vector contains a <string, int>
  // pair where the string value represents a unique word and the int
  // value represents the number of occurences for that word.

  size_t hash(std::string word) const;
  // Hash function that will return an index for the hash table.
};

#endif // WORDCOUNT_H

// lab07Test01.cpp - Basic functionality tests for WordCount Lab07
#include <iostream>
#include <sstream>
#include "WordCount.h"

void testAddAllWords() {
    std::cout << "=== Test 1: addAllWords Basic Functionality ===" << std::endl;
    WordCount wc;
    
    // Test basic sentence
    wc.addAllWords("Hello world this is a test");
    if (wc.getNumUniqueWords() == 6) {
        std::cout << "PASS: addAllWords - basic sentence" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - basic sentence. Expected 6, got " 
                  << wc.getNumUniqueWords() << std::endl;
    }
    
    // Test with punctuation
    WordCount wc2;
    wc2.addAllWords("Hello! World! This, is. a; test:");
    if (wc2.getNumUniqueWords() == 6) {
        std::cout << "PASS: addAllWords - punctuation handling" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - punctuation handling. Expected 6, got " 
                  << wc2.getNumUniqueWords() << std::endl;
    }
    
    // Test with repeated words
    WordCount wc3;
    wc3.addAllWords("test test test repeated repeated");
    if (wc3.getWordCount("test") == 3 && wc3.getWordCount("repeated") == 2) {
        std::cout << "PASS: addAllWords - repeated words counting" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - repeated words counting" << std::endl;
    }
}

void testDumpByWord() {
    std::cout << "\n=== Test 2: dumpWordsSortedByWord ===" << std::endl;
    WordCount wc;
    wc.addAllWords("apple zebra cherry banana");
    
    std::stringstream ss;
    wc.dumpWordsSortedByWord(ss);
    std::string output = ss.str();
    
    // Check if output is in descending alphabetical order
    if (output.find("zebra") < output.find("cherry") &&
        output.find("cherry") < output.find("banana") &&
        output.find("banana") < output.find("apple")) {
        std::cout << "PASS: dumpWordsSortedByWord - descending order" << std::endl;
    } else {
        std::cout << "FAIL: dumpWordsSortedByWord - descending order" << std::endl;
        std::cout << "Output: " << output << std::endl;
    }
    
    // Check CSV format
    if (output.find("apple,1") != std::string::npos &&
        output.find("zebra,1") != std::string::npos) {
        std::cout << "PASS: dumpWordsSortedByWord - CSV format" << std::endl;
    } else {
        std::cout << "FAIL: dumpWordsSortedByWord - CSV format" << std::endl;
    }
}

int main() {
    std::cout << "Running Lab07 Test01 - Basic Functionality Tests" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    testAddAllWords();
    testDumpByWord();
    
    std::cout << "\nAll Test01 tests completed!" << std::endl;
    return 0;
}
// lab07Test02.cpp - Advanced functionality tests for WordCount Lab07
#include <iostream>
#include <sstream>
#include "WordCount.h"

void testDumpByOccurrence() {
    std::cout << "=== Test 1: dumpWordsSortedByOccurence ===" << std::endl;
    WordCount wc;
    wc.addAllWords("a b b c c c d d d d");
    
    std::stringstream ss;
    wc.dumpWordsSortedByOccurence(ss);
    std::string output = ss.str();
    
    // Check ascending order by count
    size_t pos_a = output.find("a,1");
    size_t pos_b = output.find("b,2");
    size_t pos_c = output.find("c,3");
    size_t pos_d = output.find("d,4");
    
    if (pos_a < pos_b && pos_b < pos_c && pos_c < pos_d) {
        std::cout << "PASS: dumpWordsSortedByOccurence - ascending count order" << std::endl;
    } else {
        std::cout << "FAIL: dumpWordsSortedByOccurence - ascending count order" << std::endl;
        std::cout << "Output: " << output << std::endl;
    }
    
    // Test tie-breaking with alphabetical order
    WordCount wc2;
    wc2.addAllWords("zebra apple cherry apple cherry");
    
    std::stringstream ss2;
    wc2.dumpWordsSortedByOccurence(ss2);
    std::string output2 = ss2.str();
    
    // Both apple and cherry have count 2, should be sorted alphabetically
    size_t pos_apple = output2.find("apple,2");
    size_t pos_cherry = output2.find("cherry,2");
    size_t pos_zebra = output2.find("zebra,1");
    
    if (pos_zebra < pos_apple && pos_apple < pos_cherry) {
        std::cout << "PASS: dumpWordsSortedByOccurence - tie breaking alphabetical" << std::endl;
    } else {
        std::cout << "FAIL: dumpWordsSortedByOccurence - tie breaking alphabetical" << std::endl;
        std::cout << "Output: " << output2 << std::endl;
    }
}

void testComplexAddAllWords() {
    std::cout << "\n=== Test 2: Complex addAllWords Scenarios ===" << std::endl;
    
    // Test with multiple whitespace characters
    WordCount wc;
    wc.addAllWords("  multiple   spaces\nand\ttabs   ");
    
    if (wc.getWordCount("multiple") == 1 &&
        wc.getWordCount("spaces") == 1 &&
        wc.getWordCount("and") == 1 &&
        wc.getWordCount("tabs") == 1) {
        std::cout << "PASS: addAllWords - multiple whitespace handling" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - multiple whitespace handling" << std::endl;
    }
    
    // Test with mixed case and punctuation
    WordCount wc2;
    wc2.addAllWords("Hello! World! HELLO! world! hElLo!");
    
    if (wc2.getWordCount("hello") == 3 && wc2.getWordCount("world") == 2) {
        std::cout << "PASS: addAllWords - case insensitivity and punctuation" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - case insensitivity and punctuation" << std::endl;
        std::cout << "hello count: " << wc2.getWordCount("hello") 
                  << ", world count: " << wc2.getWordCount("world") << std::endl;
    }
}

void testEdgeCases() {
    std::cout << "\n=== Test 3: Edge Cases ===" << std::endl;
    
    // Test empty string
    WordCount wc;
    wc.addAllWords("");
    if (wc.getTotalWords() == 0 && wc.getNumUniqueWords() == 0) {
        std::cout << "PASS: addAllWords - empty string" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - empty string" << std::endl;
    }
    
    // Test only whitespace
    WordCount wc2;
    wc2.addAllWords("   \n\t   ");
    if (wc2.getTotalWords() == 0 && wc2.getNumUniqueWords() == 0) {
        std::cout << "PASS: addAllWords - only whitespace" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - only whitespace" << std::endl;
    }
    
    // Test single word
    WordCount wc3;
    wc3.addAllWords("single");
    if (wc3.getTotalWords() == 1 && wc3.getNumUniqueWords() == 1 && 
        wc3.getWordCount("single") == 1) {
        std::cout << "PASS: addAllWords - single word" << std::endl;
    } else {
        std::cout << "FAIL: addAllWords - single word" << std::endl;
    }
}

int main() {
    std::cout << "Running Lab07 Test02 - Advanced Functionality Tests" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    testDumpByOccurrence();
    testComplexAddAllWords();
    testEdgeCases();
    
    std::cout << "\nAll Test02 tests completed!" << std::endl;
    return 0;
}
CXX=clang++

CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES=lab07Test01 lab07Test02

all: ${BINARIES}

lab07Test01: lab07Test01.o WordCount.o
	${CXX} $^ -o $@

lab07Test02: lab07Test02.o WordCount.o
	${CXX} $^ -o $@

tests: ${BINARIES}
	./lab07Test01
	./lab07Test02

clean:
	/bin/rm -f ${BINARIES} *.o
#include "tddFuncs.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

std::string convertLineNumber(int lineNumber) {
  std::string retVal="";
  if (lineNumber > 0) 
    retVal += " line: " + std::to_string(lineNumber);
  return retVal;
}

void assertEquals(const char * const expected, 
		  const char * const actual, 
		  std::string message,
		  int lineNumber) {
  std::string line = convertLineNumber(lineNumber);
  if ( !strcmp(expected,actual) ) {  // if they are equal
    cout << "PASSED: " << message << line <<  endl;;
  } else {
    cout << "   FAILED: " << message << line << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}

void assertEquals(const char * const expected, 
		  std::string actual, 
		  std::string message,
		  int lineNumber) {
  assertEquals(std::string(expected),actual,message,lineNumber);
}

void assertTrue(bool expression,
		std::string message,
		int lineNumber) {
  std::string line = convertLineNumber(lineNumber);
  if (expression) {
    cout << "PASSED: " << message << line << endl;;
  } else {
    cout << "   FAILED: " << message << line << endl 
	 << "     Expected true, but was false " << endl;
  }
}


#ifndef TDDFUNCS_H
#define TDDFUNCS_H

#include <string>
#include <iostream>

std::string convertLineNumber(int lineNumber);

// template requires == and << 

template<typename T> void assertEquals(T expected, 
				       T actual, 
				       std::string message,
				       int lineNumber) {
  std::string line=convertLineNumber(lineNumber);
  if (expected==actual) {
    std::cout << "PASSED: " << message << line << std::endl;;
  } else {
    std::cout << "   FAILED: " << message << line << std::endl
	      << "     Expected: "  << expected << " Actual: " << actual << std::endl; 
  }
}

// specialized because char * doesn't work properly on ==
void assertEquals(const char * const expected, 
		  const char * const actual, 
		  std::string message,
		  int lineNumber=-1);

// specialized for the same reason, and because expected is often a string literal
void assertEquals(const char * const expected, 
		  std::string actual, 
		  std::string message,
		  int lineNumber=-1);

#define ASSERT_EQUALS(expected,actual) \
  assertEquals(expected,actual,#actual " at " __FILE__ ,  __LINE__ )


void assertTrue(bool expression, std::string message="", int lineNumber=-1);

#define ASSERT_TRUE(expression) \
  assertTrue(expression,#expression " at " __FILE__, __LINE__)

#endif // TDDFUNCS_H
