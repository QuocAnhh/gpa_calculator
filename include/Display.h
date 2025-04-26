#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
#include "Student.h"
#include "Semester.h"
#include "Course.h"

class Display {
public:
    // Main display functions
    static void showMainMenu();
    static void showStudentMenu();
    static void showSemesterMenu();
    static void showCourseMenu();
    static void showGradingSystemMenu();
    static void showTargetCGPAMenu();
    static void showFileMenu();
    
    // Student information display
    static void displayStudentInfo(const Student& student);
    
    // Semester information display
    static void displaySemesterList(const std::vector<Semester>& semesters);
    static void displaySemesterInfo(const Semester& semester);
    
    // Course information display
    static void displayCourseList(const std::vector<Course>& courses);
    static void displayCourseInfo(const Course& course);
    
    // CGPA and GPA displays
    static void displayCGPA(const Student& student);
    static void displayGPA(const Semester& semester);
    static void displayTargetCGPAInfo(double currentCGPA, double targetCGPA, 
                                     double requiredGPA, double futureCredits);
    
    // File listings
    static void displayFileList(const std::vector<std::string>& files, const std::string& fileType);
    
    // Grading System display
    static void displayGradingSystem(const GradingSystem& system);
    static void displayAllGradingSystems();
    
    // Utility display functions
    static void showHeader(const std::string& title);
    static void showFooter();
    static void showError(const std::string& message);
    static void showSuccess(const std::string& message);
    static void clearScreen();
    static void pressEnterToContinue();
};

#endif // DISPLAY_H