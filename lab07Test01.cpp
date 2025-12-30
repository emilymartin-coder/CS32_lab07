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
