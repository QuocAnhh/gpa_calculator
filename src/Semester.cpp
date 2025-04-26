#include "../include/Semester.h"
#include <sstream>
#include <numeric>

Semester::Semester() : id(0), gpa(0.0) {}

Semester::Semester(int id, const std::string& name) : id(id), name(name), gpa(0.0) {}

int Semester::getId() const { return id; }
std::string Semester::getName() const { return name; }
const std::vector<Course>& Semester::getCourses() const { return courses; }
double Semester::getGPA() const { return gpa; }

double Semester::getTotalCredits() const {
    double total = 0.0;
    for (const auto& course : courses) {
        total += course.getCredits();
    }
    return total;
}

double Semester::getTotalGradePoints() const {
    double total = 0.0;
    for (const auto& course : courses) {
        total += course.getCredits() * course.getGradePoints();
    }
    return total;
}

void Semester::setId(int id) { this->id = id; }
void Semester::setName(const std::string& name) { this->name = name; }

void Semester::addCourse(const Course& course) {
    courses.push_back(course);
    calculateGPA();
}

void Semester::updateCourse(int index, const Course& course) {
    if (index >= 0 && index < static_cast<int>(courses.size())) {
        courses[index] = course;
        calculateGPA();
    }
}

void Semester::removeCourse(int index) {
    if (index >= 0 && index < static_cast<int>(courses.size())) {
        courses.erase(courses.begin() + index);
        calculateGPA();
    }
}

void Semester::calculateGPA() {
    double totalCredits = getTotalCredits();
    double totalGradePoints = getTotalGradePoints();
    
    gpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;
}

std::string Semester::serialize() const {
    std::stringstream ss;
    ss << id << "|" << name << "|" << courses.size();
    
    for (const auto& course : courses) {
        ss << "|" << course.serialize();
    }
    
    return ss.str();
}

Semester Semester::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string token, name;
    int id, courseCount;
    
    // Parse id
    std::getline(ss, token, '|');
    id = std::stoi(token);
    
    // Parse name
    std::getline(ss, name, '|');
    
    // Parse course count
    std::getline(ss, token, '|');
    courseCount = std::stoi(token);
    
    Semester semester(id, name);
    
    // Parse courses
    for (int i = 0; i < courseCount; i++) {
        std::string courseData;
        std::getline(ss, courseData, '|');
        Course course = Course::deserialize(courseData);
        semester.addCourse(course);
    }
    
    return semester;
}