/**
 * CSC450_CT5_mod5.cpp
 *
 * Module 5 Critical Thinking Assignment - User Input Program
 * CSC450 - C++ Programming
 *
 * Prompts the user for a line of text, appends it to the provided
 * CSC450_CT5_mod5.txt file without disturbing the existing content,
 * then reverses the entire contents of that file and writes the
 * result to CSC450-mod5-reverse.txt.
 *
 * @author Connor Colvin (Lightbearer77)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

namespace {
    const std::string INPUT_FILE_NAME = "CSC450_CT5_mod5.txt";
    const std::string REVERSE_FILE_NAME = "CSC450-mod5-reverse.txt";
    const std::size_t MAX_INPUT_LENGTH = 500;
}

/**
 * Prompts the user for a single line of input and returns it.
 * Bounds the read length to guard against unbounded buffer growth.
 */
std::string promptForUserInput();

/**
 * Appends a single line of text to the target file. Opens the stream
 * in append mode specifically so pre-existing content is preserved.
 * Returns true on success, false if the file could not be opened.
 */
bool appendLineToFile(const std::string& fileName, const std::string& line);

/**
 * Reads the entire contents of a file into a single string.
 * Returns true on success, false if the file could not be opened.
 */
bool readEntireFile(const std::string& fileName, std::string& contents);

/**
 * Writes a string to a file, overwriting any existing content.
 * Returns true on success, false if the file could not be opened.
 */
bool writeEntireFile(const std::string& fileName, const std::string& contents);

/**
 * Reads sourceFile, reverses every character in its contents (including
 * whitespace and newlines), and writes the reversed text to destFile.
 * Returns true if both the read and the write succeeded.
 */
bool reverseFileContents(const std::string& sourceFile, const std::string& destFile);

/**
 * Prints a labeled separator line to organize console output.
 */
void printSeparator(const std::string& label);

int main() {
    printSeparator("CSC450 Module 5 - User Input Program");

    std::string userInput = promptForUserInput();

    if (!appendLineToFile(INPUT_FILE_NAME, userInput)) {
        std::cerr << "Error: could not open " << INPUT_FILE_NAME
                  << " for appending." << std::endl;
        return 1;
    }
    std::cout << "\nYour input was appended to " << INPUT_FILE_NAME << "." << std::endl;

    if (!reverseFileContents(INPUT_FILE_NAME, REVERSE_FILE_NAME)) {
        std::cerr << "Error: could not reverse contents into "
                  << REVERSE_FILE_NAME << "." << std::endl;
        return 1;
    }
    std::cout << "Reversed contents written to " << REVERSE_FILE_NAME << "." << std::endl;

    printSeparator("Final file contents");

    std::string finalContents;
    if (readEntireFile(INPUT_FILE_NAME, finalContents)) {
        std::cout << "\n--- " << INPUT_FILE_NAME << " ---\n" << finalContents << std::endl;
    }

    std::string reversedContents;
    if (readEntireFile(REVERSE_FILE_NAME, reversedContents)) {
        std::cout << "\n--- " << REVERSE_FILE_NAME << " ---\n" << reversedContents << std::endl;
    }

    return 0;
}

std::string promptForUserInput() {
    std::cout << "Enter a line of text to append to " << INPUT_FILE_NAME << ":\n> ";

    std::string line;
    std::getline(std::cin, line);

    if (line.size() > MAX_INPUT_LENGTH) {
        std::cout << "Input truncated to " << MAX_INPUT_LENGTH << " characters." << std::endl;
        line.resize(MAX_INPUT_LENGTH);
    }

    return line;
}

bool appendLineToFile(const std::string& fileName, const std::string& line) {
    std::ofstream outFile(fileName, std::ios::app);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << line << std::endl;
    outFile.close();
    return true;
}

bool readEntireFile(const std::string& fileName, std::string& contents) {
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile.is_open()) {
        return false;
    }
    std::ostringstream buffer;
    buffer << inFile.rdbuf();
    contents = buffer.str();
    inFile.close();
    return true;
}

bool writeEntireFile(const std::string& fileName, const std::string& contents) {
    std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << contents;
    outFile.close();
    return true;
}

bool reverseFileContents(const std::string& sourceFile, const std::string& destFile) {
    std::string contents;
    if (!readEntireFile(sourceFile, contents)) {
        return false;
    }

    std::reverse(contents.begin(), contents.end());

    return writeEntireFile(destFile, contents);
}

void printSeparator(const std::string& label) {
    std::string bar(label.size() + 4, '=');
    std::cout << bar << "\n= " << label << " =\n" << bar << std::endl;
}
