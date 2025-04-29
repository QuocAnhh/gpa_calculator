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
    static GradingSystem createStandardFourPoint();
    static GradingSystem createFivePoint();
    static GradingSystem createTenPoint();
    
    GradingSystem(const std::string& name);
    
    void addGrade(const std::string& grade, double points);
    
    void removeGrade(const std::string& grade);
    
    double getGradePoints(const std::string& grade) const;
    
    std::vector<std::string> getAvailableGrades() const;
    
    std::string getName() const;
    
    bool isValidGrade(const std::string& grade) const;
    
    // For file I/O
    std::string serialize() const;
    static GradingSystem deserialize(const std::string& data);
};

#endif // GRADING_SYSTEM_H