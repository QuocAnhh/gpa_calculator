#ifndef SEMESTER_H
#define SEMESTER_H

#include <vector>
#include <string>
#include "Course.h"

class Semester {
private:
    int id;
    std::string name;
    std::vector<Course> courses;
    double gpa;

public:
    Semester();
    Semester(int id, const std::string& name);
    Semester(const std::string& name); 
    
    int getId() const;
    std::string getName() const;
    const std::vector<Course>& getCourses() const;
    double getGPA() const;
    double getTotalCredits() const;
    double getTotalGradePoints() const;
    
    void setId(int id);
    void setName(const std::string& name);
    
    void addCourse(const Course& course);
    void updateCourse(int index, const Course& course);
    void removeCourse(int index);
    
    void calculateGPA();
    
    std::string serialize() const;
    static Semester deserialize(const std::string& data);
};

#endif // SEMESTER_H