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
