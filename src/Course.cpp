#include "../include/Course.h"
#include <sstream>
#include <vector>

Course::Course() : credits(0.0), gradePoints(0.0), semesterId(0) {}

Course::Course(const std::string& name, double credits, const std::string& grade, 
              double gradePoints, int semesterId) 
    : name(name), credits(credits), grade(grade), 
      gradePoints(gradePoints), semesterId(semesterId) {}

std::string Course::getName() const { return name; }
double Course::getCredits() const { return credits; }
std::string Course::getGrade() const { return grade; }
double Course::getGradePoints() const { return gradePoints; }
int Course::getSemesterId() const { return semesterId; }

void Course::setName(const std::string& name) { this->name = name; }
void Course::setCredits(double credits) { this->credits = credits; }
void Course::setGrade(const std::string& grade) { this->grade = grade; }
void Course::setGradePoints(double gradePoints) { this->gradePoints = gradePoints; }
void Course::setSemesterId(int semesterId) { this->semesterId = semesterId; }

std::string Course::serialize() const {
    std::stringstream ss;
    // Format: name|credits|grade|gradePoints|semesterId
    ss << name << "|" << credits << "|" << grade << "|" << gradePoints << "|" << semesterId;
    return ss.str();
}

Course Course::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string name, grade, token;
    double credits, gradePoints;
    int semesterId;
    
    // Parse name
    std::getline(ss, name, '|');
    
    // Parse credits
    std::getline(ss, token, '|');
    credits = std::stod(token);
    
    // Parse grade
    std::getline(ss, grade, '|');
    
    // Parse gradePoints
    std::getline(ss, token, '|');
    gradePoints = std::stod(token);
    
    // Parse semesterId
    std::getline(ss, token, '|');
    semesterId = std::stoi(token);
    
    return Course(name, credits, grade, gradePoints, semesterId);
}