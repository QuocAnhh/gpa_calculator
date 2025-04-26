#ifndef CGPA_CALCULATOR_H
#define CGPA_CALCULATOR_H

#include <string>
#include <vector>

struct Course {
    std::string name;
    std::string code;
    double credits;
    std::string grade;
    double gradePoints;
};

class GPACalculator {
public:
    GPACalculator();
    ~GPACalculator();

    void addCourse(const Course& course);
    void removeCourse(const std::string& courseCode);
    double calculateGPA() const;
    double calculateCGPA() const;
    
private:
    std::vector<Course> courses;
    double getGradePoints(const std::string& grade) const;
};

#endif // CGPA_CALCULATOR_H
