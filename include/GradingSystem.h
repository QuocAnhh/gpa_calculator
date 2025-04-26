#ifndef GRADING_SYSTEM_H
#define GRADING_SYSTEM_H

#include <string>
#include <map>
#include <vector>

class GradingSystem {
private:
    std::map<std::string, double> gradeScale;
    std::string name;
    
public:
    // Predefined grading systems
    static GradingSystem createStandardFourPoint();
    static GradingSystem createFivePoint();
    static GradingSystem createTenPoint();
    
    // Custom grading system
    GradingSystem(const std::string& name);
    
    // Add a grade to the scale
    void addGrade(const std::string& grade, double points);
    
    // Remove a grade from the scale
    void removeGrade(const std::string& grade);
    
    // Get grade points for a given letter grade
    double getGradePoints(const std::string& grade) const;
    
    // Get all available grades
    std::vector<std::string> getAvailableGrades() const;
    
    // Get name of the grading system
    std::string getName() const;
    
    // Check if a grade is valid in this system
    bool isValidGrade(const std::string& grade) const;
    
    // For file I/O
    std::string serialize() const;
    static GradingSystem deserialize(const std::string& data);
};

#endif // GRADING_SYSTEM_H