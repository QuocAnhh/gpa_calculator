#include "../include/GradingSystem.h"
#include <sstream>

GradingSystem GradingSystem::createStandardFourPoint() {
    GradingSystem system("Standard 4.0 Scale");
    system.addGrade("A", 4.0);
    system.addGrade("A-", 3.7);
    system.addGrade("B+", 3.3);
    system.addGrade("B", 3.0);
    system.addGrade("B-", 2.7);
    system.addGrade("C+", 2.3);
    system.addGrade("C", 2.0);
    system.addGrade("C-", 1.7);
    system.addGrade("D+", 1.3);
    system.addGrade("D", 1.0);
    system.addGrade("F", 0.0);
    return system;
}

GradingSystem GradingSystem::createFivePoint() {
    GradingSystem system("5.0 Scale");
    system.addGrade("A+", 5.0);
    system.addGrade("A", 4.5);
    system.addGrade("B+", 4.0);
    system.addGrade("B", 3.5);
    system.addGrade("C+", 3.0);
    system.addGrade("C", 2.5);
    system.addGrade("D+", 2.0);
    system.addGrade("D", 1.5);
    system.addGrade("E", 1.0);
    system.addGrade("F", 0.0);
    return system;
}

GradingSystem GradingSystem::createTenPoint() {
    GradingSystem system("10.0 Scale");
    system.addGrade("10", 10.0);
    system.addGrade("9", 9.0);
    system.addGrade("8", 8.0);
    system.addGrade("7", 7.0);
    system.addGrade("6", 6.0);
    system.addGrade("5", 5.0);
    system.addGrade("4", 4.0);
    system.addGrade("3", 3.0);
    system.addGrade("2", 2.0);
    system.addGrade("1", 1.0);
    system.addGrade("0", 0.0);
    return system;
}

GradingSystem::GradingSystem(const std::string& name) : name(name) {}

void GradingSystem::addGrade(const std::string& grade, double points) {
    gradeScale[grade] = points;
}

double GradingSystem::getGradePoints(const std::string& grade) const {
    std::string upperGrade = grade;
    // Convert to uppercase for case-insensitive comparison
    for (char& c : upperGrade) {
        c = std::toupper(c);
    }
    
    auto it = gradeScale.find(upperGrade);
    if (it != gradeScale.end()) {
        return it->second;
    }
    
    // Check for case-insensitive match
    for (const auto& pair : gradeScale) {
        std::string upper = pair.first;
        for (char& c : upper) {
            c = std::toupper(c);
        }
        
        if (upper == upperGrade) {
            return pair.second;
        }
    }
    
    return 0.0; // Default value for unrecognized grades
}

std::vector<std::string> GradingSystem::getAvailableGrades() const {
    std::vector<std::string> grades;
    for (const auto& pair : gradeScale) {
        grades.push_back(pair.first);
    }
    return grades;
}

std::string GradingSystem::getName() const {
    return name;
}

bool GradingSystem::isValidGrade(const std::string& grade) const {
    std::string upperGrade = grade;
    for (char& c : upperGrade) {
        c = std::toupper(c);
    }
    
    for (const auto& pair : gradeScale) {
        std::string upper = pair.first;
        for (char& c : upper) {
            c = std::toupper(c);
        }
        
        if (upper == upperGrade) {
            return true;
        }
    }
    
    return false;
}

std::string GradingSystem::serialize() const {
    std::stringstream ss;
    ss << name << "|" << gradeScale.size();
    
    for (const auto& pair : gradeScale) {
        ss << "|" << pair.first << "," << pair.second;
    }
    
    return ss.str();
}

GradingSystem GradingSystem::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string name, token, grade, points;
    int scaleSize;
    
    // Parse name
    std::getline(ss, name, '|');
    
    // Parse size
    std::getline(ss, token, '|');
    scaleSize = std::stoi(token);
    
    GradingSystem system(name);
    
    // Parse grade scale
    for (int i = 0; i < scaleSize; i++) {
        std::getline(ss, token, '|');
        std::stringstream gradeData(token);
        
        std::getline(gradeData, grade, ',');
        std::getline(gradeData, points);
        
        system.addGrade(grade, std::stod(points));
    }
    
    return system;
}