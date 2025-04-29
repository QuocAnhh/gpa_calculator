#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "GradingSystem.h"

class Utils {
public:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    
    static bool isValidNumber(const std::string& str);
    static bool isValidGrade(const std::string& grade, const GradingSystem& system);
    
    static int getIntInput(const std::string& prompt, int min, int max);
    static double getDoubleInput(const std::string& prompt, double min, double max);
    static std::string getStringInput(const std::string& prompt);
    static std::string getGradeInput(const std::string& prompt, const GradingSystem& system);
    
    static int generateUniqueId();
    static std::string getCurrentDateTime();
};

#endif // UTILS_H