#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string name;
    double credits;
    std::string grade;
    double gradePoints;
    int semesterId;  // Helps identify which semester this course belongs to

public:
    // Constructors
    Course();
    Course(const std::string& name, double credits, const std::string& grade, double gradePoints, int semesterId);
    
    // Getters
    std::string getName() const;
    double getCredits() const;
    std::string getGrade() const;
    double getGradePoints() const;
    int getSemesterId() const;
    
    // Setters
    void setName(const std::string& name);
    void setCredits(double credits);
    void setGrade(const std::string& grade);
    void setGradePoints(double gradePoints);
    void setSemesterId(int semesterId);
    
    // For file I/O
    std::string serialize() const;
    static Course deserialize(const std::string& data);
};

#endif // COURSE_H