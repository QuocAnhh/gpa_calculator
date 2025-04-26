#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Semester.h"
#include "GradingSystem.h"

class Student {
private:
    std::string name;
    std::string id;
    std::vector<Semester> semesters;
    double cgpa;
    GradingSystem gradingSystem;

public:
    // Constructors
    Student();
    Student(const std::string& name, const std::string& id, const GradingSystem& gradingSystem);
    
    // Getters
    std::string getName() const;
    std::string getId() const;
    const std::vector<Semester>& getSemesters() const;
    double getCGPA() const;
    const GradingSystem& getGradingSystem() const;
    double getTotalCredits() const;
    double getTotalGradePoints() const;
    
    // Setters
    void setName(const std::string& name);
    void setId(const std::string& id);
    void setGradingSystem(const GradingSystem& gradingSystem);
    
    // Semester management
    void addSemester(const Semester& semester);
    void updateSemester(int index, const Semester& semester);
    void removeSemester(int index);
    Semester* getSemester(int semesterId);
    Semester* getSemesterByIndex(int index) {
        if (index >= 0 && index < semesters.size()) {
            return &semesters[index];
        }
        return nullptr;
    }
    
    // CGPA calculation
    void calculateCGPA();
    
    // Target CGPA calculations
    double calculateRequiredGPA(double targetCGPA, double futureCredits) const;
    
    // Academic standing
    std::string getAcademicStanding() const;
    
    // For file I/O
    std::string serialize() const;
    static Student deserialize(const std::string& data);
};

#endif // STUDENT_H