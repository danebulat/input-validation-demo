#ifndef ValidationUtils
#define ValidationUtils

#include <algorithm>
#include <iostream>
#include <cctype>   // input validation functions
#include <limits>
#include <map>
#include <string>
#include <sstream>

namespace validation {

    // getAgeV1: 
    // - Extract input into a numeric type.
    // - Check the failbit to validate input.

    int getAgeV1() {
        int age{ 0 };

        // Loop until a valid age is extracted
        while (true) {
            std::cout << "Enter an age: ";
            std::cin >> age;

            // Check failbit (no extraction takes place if set)
            if (std::cin.fail()) {
                
                // Reset the state bits back to goodbit so we can use ignore()
                std::cin.clear();

                // Clear out the bad input from the stream until end of the line
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Try again
                continue;
            }
            
            // Try again if age is not positive
            if (age <= 0)
                continue;
            
            break;
        }

        return age;
    }

    // getAgeV2() 
    // - Read numeric input into a string.
    // - Process string and convert to numeric type if valid.

    int getAgeV2() {
        int age;

        while (true) {
            std::cout << "Enter an age: ";
            std::string input;
            std::cin >> input;

            // Check to make sure each character is a digit
            bool valid{ true };

            for (auto it = input.cbegin(); it != input.cend(); ++it) {
                if (!std::isdigit(*it)) {
                    valid = false;
                    break;
                }
            }

            // Ask for input again if validation fails
            if (!valid)
                continue;
            
            // Convert valid input into a number
            std::stringstream ss;
            ss << input;
            ss >> age;

            // Try again if age is not positive
            if (age <= 0)
                continue;
            
            break;
        }

        return age;
    }

    // getAgeV3() 
    // - Extract number from string. I.e. "27xzyv" will extract 27.
    // - Use gcount() to determine how many characters were ignored.

    int getAgeV3() {
        int age;

        while (true) {
            std::cout << "Enter your age: ";
            std::cin >> age;

            // Check failbit (no extraction takes place if set)
            if (std::cin.fail()) {

                // Reset state bits back to goodbit so we can use ignore()
                std::cin.clear();

                // Clear out bad input from stream
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Try again
                continue;
            }

            // Clear out any additional input from stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Try again if more than one character - '\n' - was cleared
            if (std::cin.gcount() > 1)
                continue;
            
            // Try again if age is not positive
            if (age <= 0)
                continue;
            
            break;
        }

        return age;
    }

    // getFullName()
    // - Validate first and second name
    // - Input must contain only letters and 1 space

    enum ErrorCode {
        NoSpace,
        NoLastName,
        NoFirstName,
        ContainsIllegalCharacters,
        TooManySpaces
    };

    static std::map<const ErrorCode, const char*> errorMessages {
        { NoSpace, "Name must include a space." },
        { NoLastName, "Please enter a last name." },
        { NoFirstName, "Please enter a first name" },
        { ContainsIllegalCharacters, "Name must contain only letters." },
        { TooManySpaces, "Name must contain one space character." }
    };

    std::string getFullName() {
        std::string input;
        
        while (true) {
            unsigned int spaces {0};
            bool         valid {true};
            bool         hasSpace {false};
            const char   spaceChar {' '};
            std::string  errorMessage {"\tError: "};

            // Get input
            std::cout << "Enter name: ";
            std::getline(std::cin, input);

            // Verify that a space was entered
            for (auto it = input.cbegin(); it != input.cend(); ++it) {
                if ((*it) == spaceChar) {
                    hasSpace = true;
                    break;
                }
            }

            if (!hasSpace) {
                errorMessage += errorMessages[NoSpace];
                valid = false;
            }
            
            // Verify that two names were entered
            if (valid) {
                auto spacePos = input.find(spaceChar);
                if (input.substr(spacePos).size() == 1) {
                    valid = false;
                    errorMessage += errorMessages[NoLastName];
                }
                else if (input.substr(0, spacePos).size() == 0) {
                    valid = false;
                    errorMessage += errorMessages[NoFirstName];
                }
            }

            // Verify letters and space count 
            if (valid) {
                for (auto it = input.cbegin(); it != input.cend(); ++it) {

                    // Check if character is a letter
                    if ((!isalpha(*it)) && ((*it) != spaceChar)) {
                        valid = false;
                        errorMessage += errorMessages[ContainsIllegalCharacters];
                        break;
                    }

                    // Check if character is a space
                    if ((*it) == spaceChar)
                        spaces += 1;
                }

                // Check space count
                if (spaces != 1 && valid) {
                    valid = false;
                    errorMessage += errorMessages[TooManySpaces];
                }
            }

            // Display any error messages
            if (!valid) {
                std::cerr << errorMessage << std::endl;
                continue;
            }

            break;
        }
        
        return input;
    }
}

#endif