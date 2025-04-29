#include "../include/Student.h"
#include <sstream>
#include <algorithm>

Student::Student() : cgpa(0.0), gradingSystem(GradingSystem::createStandardFourPoint()) {}

Student::Student(const std::string& name, const std::string& id, const GradingSystem& gradingSystem)
    : name(name), id(id), cgpa(0.0), gradingSystem(gradingSystem) {}

std::string Student::getName() const { return name; }
std::string Student::getId() const { return id; }
const std::vector<Semester>& Student::getSemesters() const { return semesters; }
double Student::getCGPA() const { return cgpa; }
const GradingSystem& Student::getGradingSystem() const { return gradingSystem; }

double Student::getTotalCredits() const {
    double total = 0.0;
    for (const auto& semester : semesters) {
        total += semester.getTotalCredits();
    }
    return total;
}

double Student::getTotalGradePoints() const {
    double total = 0.0;
    for (const auto& semester : semesters) {
        total += semester.getTotalGradePoints();
    }
    return total;
}

void Student::setName(const std::string& name) { this->name = name; }
void Student::setId(const std::string& id) { this->id = id; }
void Student::setGradingSystem(const GradingSystem& gradingSystem) { this->gradingSystem = gradingSystem; }

void Student::addSemester(const Semester& semester) {
    semesters.push_back(semester);
    calculateCGPA();
}

void Student::updateSemester(int index, const Semester& semester) {
    if (index >= 0 && index < static_cast<int>(semesters.size())) {
        semesters[index] = semester;
        calculateCGPA();
    }
}

void Student::removeSemester(int index) {
    if (index >= 0 && index < static_cast<int>(semesters.size())) {
        semesters.erase(semesters.begin() + index);
        calculateCGPA();
    }
}

Semester* Student::getSemester(int semesterId) {
    for (auto& semester : semesters) {
        if (semester.getId() == semesterId) {
            return &semester;
        }
    }
    return nullptr;
}

void Student::calculateCGPA() {
    double totalCredits = getTotalCredits();
    double totalGradePoints = getTotalGradePoints();
    
    cgpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;
}

double Student::calculateRequiredGPA(double targetCGPA, double futureCredits) const {
    // Calculate the GPA needed in future courses to achieve the target CGPA
    double currentCredits = getTotalCredits();
    double currentPoints = getTotalGradePoints();
    
    // Total points needed to achieve target CGPA
    double totalPointsNeeded = (currentCredits + futureCredits) * targetCGPA;
    
    // Points needed from future courses
    double futurePointsNeeded = totalPointsNeeded - currentPoints;
    
    // Required GPA for future courses
    return (futureCredits > 0) ? (futurePointsNeeded / futureCredits) : 0.0;
}

std::string Student::getAcademicStanding() const {
    if (cgpa >= 3.5) {
        return "Excellent (Dean's List)";
    } else if (cgpa >= 3.0) {
        return "Very Good";
    } else if (cgpa >= 2.5) {
        return "Good";
    } else if (cgpa >= 2.0) {
        return "Satisfactory";
    } else if (cgpa >= 1.0) {
        return "Warning (Academic Probation)";
    } else {
        return "Unsatisfactory (Academic Dismissal)";
    }
}

std::string Student::serialize() const {
    std::stringstream ss;
    ss << name << "|" << id << "|" << semesters.size() << "|" << gradingSystem.serialize();
    
    for (const auto& semester : semesters) {
        ss << "|" << semester.serialize();
    }
    
    return ss.str();
}

Student Student::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string name, id, token, gradingSystemData;
    int semesterCount;
    
    std::getline(ss, name, '|');
    
    std::getline(ss, id, '|');
    
    std::getline(ss, token, '|');
    semesterCount = std::stoi(token);
    
    std::getline(ss, gradingSystemData, '|');
    GradingSystem gradingSystem = GradingSystem::deserialize(gradingSystemData);
    
    Student student(name, id, gradingSystem);
    
    for (int i = 0; i < semesterCount; i++) {
        std::string semesterData;
        std::getline(ss, semesterData, '|');
        Semester semester = Semester::deserialize(semesterData);
        student.addSemester(semester);
    }
    
    return student;
}