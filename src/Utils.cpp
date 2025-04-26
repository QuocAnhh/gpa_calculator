#include "../include/Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <random>
#include <chrono>
#include <iomanip>

std::string Utils::trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
        return std::isspace(c);
    }).base();
    
    return (start < end) ? std::string(start, end) : std::string();
}

std::vector<std::string> Utils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool Utils::isValidNumber(const std::string& str) {
    if (str.empty()) return false;
    
    bool hasDecimal = false;
    bool hasDigit = false;
    
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        
        if (i == 0 && c == '-') {
            // Negative number
            continue;
        } else if (c == '.' && !hasDecimal) {
            // First decimal point
            hasDecimal = true;
        } else if (!std::isdigit(c)) {
            // Not a digit and not the first '-' or first '.'
            return false;
        } else {
            // It's a digit
            hasDigit = true;
        }
    }
    
    return hasDigit;
}

bool Utils::isValidGrade(const std::string& grade, const GradingSystem& system) {
    return system.isValidGrade(grade);
}

int Utils::getIntInput(const std::string& prompt, int min, int max) {
    std::string input;
    int value;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (!isValidNumber(input)) {
            std::cout << "Error: Invalid input. Please enter a number.\n";
            continue;
        }
        
        try {
            value = std::stoi(input);
            if (value < min || value > max) {
                std::cout << "Error: Please enter a number between " << min << " and " << max << ".\n";
                continue;
            }
            break;
        } catch (const std::exception& e) {
            std::cout << "Error: Invalid input. Please enter a valid integer.\n";
        }
    }
    
    return value;
}

double Utils::getDoubleInput(const std::string& prompt, double min, double max) {
    std::string input;
    double value;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (!isValidNumber(input)) {
            std::cout << "Error: Invalid input. Please enter a number.\n";
            continue;
        }
        
        try {
            value = std::stod(input);
            if (value < min || value > max) {
                std::cout << "Error: Please enter a number between " << min << " and " << max << ".\n";
                continue;
            }
            break;
        } catch (const std::exception& e) {
            std::cout << "Error: Invalid input. Please enter a valid number.\n";
        }
    }
    
    return value;
}

std::string Utils::getStringInput(const std::string& prompt) {
    std::string input;
    
    do {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "Error: Input cannot be empty.\n";
        }
    } while (input.empty());
    
    return input;
}

std::string Utils::getGradeInput(const std::string& prompt, const GradingSystem& system) {
    std::string input;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (isValidGrade(input, system)) {
            break;
        } else {
            std::cout << "Error: Invalid grade. Please enter a valid grade.\n";
            std::cout << "Available grades: ";
            
            auto grades = system.getAvailableGrades();
            for (size_t i = 0; i < grades.size(); i++) {
                std::cout << grades[i];
                if (i < grades.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    return input;
}

int Utils::generateUniqueId() {
    // Use current time and random number to generate a unique ID
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1000, 9999);
    return dist(gen);
}

std::string Utils::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    struct tm timeinfo;
    
    #ifdef _WIN32
    localtime_s(&timeinfo, &in_time_t);
    #else
    localtime_r(&in_time_t, &timeinfo);
    #endif
    
    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}