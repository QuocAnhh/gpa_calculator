#include "../include/Display.h"
#include <iostream>
#include <iomanip>  // Make sure this is included for std::setprecision
#include <algorithm>
#include <limits>

void Display::showMainMenu() {
    clearScreen();
    showHeader("CGPA CALCULATOR - MAIN MENU");
    
    std::cout << "1. Create New Student Profile\n";
    std::cout << "2. Load Existing Student Profile\n";
    std::cout << "3. Manage Grading Systems\n";
    std::cout << "4. Exit\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::showStudentMenu() {
    clearScreen();
    showHeader("STUDENT PROFILE MENU");
    
    std::cout << "1. View Student Information\n";
    std::cout << "2. Edit Student Information\n";
    std::cout << "3. Add Semester\n";
    std::cout << "4. View/Edit Semester\n";
    std::cout << "5. Calculate Target CGPA\n";
    std::cout << "6. Change Grading System\n";
    std::cout << "7. Save Student Profile\n";
    std::cout << "8. Return to Main Menu\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::showSemesterMenu() {
    clearScreen();
    showHeader("SEMESTER MENU");
    
    std::cout << "1. View Semester Details\n";
    std::cout << "2. Edit Semester Name\n";
    std::cout << "3. Add Course\n";
    std::cout << "4. View/Edit Course\n";
    std::cout << "5. Delete Course\n";
    std::cout << "6. Return to Student Menu\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::showCourseMenu() {
    clearScreen();
    showHeader("COURSE MENU");
    
    std::cout << "1. View Course Details\n";
    std::cout << "2. Edit Course Name\n";
    std::cout << "3. Edit Course Credits\n";
    std::cout << "4. Edit Course Grade\n";
    std::cout << "5. Return to Semester Menu\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::showGradingSystemMenu() {
    clearScreen();
    showHeader("GRADING SYSTEM MENU");
    
    std::cout << "1. View Standard Grading Systems\n";
    std::cout << "2. Create Custom Grading System\n";
    std::cout << "3. Load Custom Grading System\n";
    std::cout << "4. Save Grading System\n";
    std::cout << "5. Return to Main Menu\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::showTargetCGPAMenu() {
    clearScreen();
    showHeader("TARGET CGPA CALCULATOR");
    
    std::cout << "This tool helps you determine what GPA you need in future courses\n";
    std::cout << "to achieve your target CGPA.\n\n";
}

void Display::showFileMenu() {
    clearScreen();
    showHeader("FILE OPERATIONS");
    
    std::cout << "1. Save Current Profile\n";
    std::cout << "2. Load Profile\n";
    std::cout << "3. Delete Profile\n";
    std::cout << "4. Return to Main Menu\n\n";
    
    std::cout << "Enter your choice: ";
}

void Display::displayStudentInfo(const Student& student) {
    clearScreen();
    showHeader("STUDENT INFORMATION");
    
    std::cout << "Name: " << student.getName() << std::endl;
    std::cout << "ID: " << student.getId() << std::endl;
    std::cout << "Grading System: " << student.getGradingSystem().getName() << std::endl;
    std::cout << "Total Credits: " << student.getTotalCredits() << std::endl;
    std::cout << "CGPA: " << std::fixed << std::setprecision(2) << student.getCGPA() << std::endl;
    std::cout << "Academic Standing: " << student.getAcademicStanding() << std::endl;
    std::cout << "\nNumber of Semesters: " << student.getSemesters().size() << std::endl;
    
    if (!student.getSemesters().empty()) {
        std::cout << "\nSemester Overview:\n";
        std::cout << "-------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
                 << std::setw(15) << "Credits" << std::setw(10) << "GPA" << std::endl;
        std::cout << "-------------------------------------------------------------------------\n";
        
        for (const auto& semester : student.getSemesters()) {
            std::cout << std::left << std::setw(5) << semester.getId() 
                     << std::setw(25) << semester.getName()
                     << std::setw(15) << semester.getTotalCredits()
                     << std::fixed << std::setprecision(2) << semester.getGPA() << std::endl;
        }
        std::cout << "-------------------------------------------------------------------------\n";
    }
    
    std::cout << "\n";
}

void Display::displaySemesterList(const std::vector<Semester>& semesters) {
    if (semesters.empty()) {
        std::cout << "No semesters found.\n";
        return;
    }
    
    std::cout << "\nAvailable Semesters:\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
             << std::setw(15) << "Credits" << std::setw(10) << "GPA" << std::endl;
    std::cout << "-------------------------------------------------------------------------\n";
    
    for (const auto& semester : semesters) {
        std::cout << std::left << std::setw(5) << semester.getId() 
                 << std::setw(25) << semester.getName()
                 << std::setw(15) << semester.getTotalCredits()
                 << std::fixed << std::setprecision(2) << semester.getGPA() << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------\n";
}

void Display::displaySemesterInfo(const Semester& semester) {
    clearScreen();
    showHeader("SEMESTER INFORMATION");
    
    std::cout << "ID: " << semester.getId() << std::endl;
    std::cout << "Name: " << semester.getName() << std::endl;
    std::cout << "Total Credits: " << semester.getTotalCredits() << std::endl;
    std::cout << "GPA: " << std::fixed << std::setprecision(2) << semester.getGPA() << std::endl;
    
    const auto& courses = semester.getCourses();
    if (courses.empty()) {
        std::cout << "\nNo courses in this semester.\n";
    } else {
        std::cout << "\nCourse Details:\n";
        std::cout << "-------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(5) << "No." << std::setw(30) << "Course Name" 
                 << std::setw(10) << "Credits" << std::setw(10) << "Grade" 
                 << "Grade Points" << std::endl;
        std::cout << "-------------------------------------------------------------------------\n";
        
        for (size_t i = 0; i < courses.size(); i++) {
            const auto& course = courses[i];
            std::cout << std::left << std::setw(5) << (i + 1) 
                     << std::setw(30) << course.getName()
                     << std::setw(10) << course.getCredits()
                     << std::setw(10) << course.getGrade()
                     << std::fixed << std::setprecision(2) << course.getGradePoints() << std::endl;
        }
        std::cout << "-------------------------------------------------------------------------\n";
    }
    
    std::cout << "\n";
}

void Display::displayCourseList(const std::vector<Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses found.\n";
        return;
    }
    
    std::cout << "\nCourses:\n";
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(5) << "No." << std::setw(30) << "Course Name" 
             << std::setw(10) << "Credits" << std::setw(10) << "Grade" 
             << "Grade Points" << std::endl;
    std::cout << "-------------------------------------------------------------------------\n";
    
    for (size_t i = 0; i < courses.size(); i++) {
        const auto& course = courses[i];
        std::cout << std::left << std::setw(5) << (i + 1) 
                 << std::setw(30) << course.getName()
                 << std::setw(10) << course.getCredits()
                 << std::setw(10) << course.getGrade()
                 << std::fixed << std::setprecision(2) << course.getGradePoints() << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------\n";
}

void Display::displayCourseInfo(const Course& course) {
    clearScreen();
    showHeader("COURSE INFORMATION");
    
    std::cout << "Name: " << course.getName() << std::endl;
    std::cout << "Credits: " << course.getCredits() << std::endl;
    std::cout << "Grade: " << course.getGrade() << std::endl;
    std::cout << "Grade Points: " << std::fixed << std::setprecision(2) 
             << course.getGradePoints() << std::endl;
    std::cout << "\n";
}

void Display::displayCGPA(const Student& student) {
    std::cout << "\nCurrent CGPA: " << std::fixed << std::setprecision(2) 
             << student.getCGPA() << std::endl;
    std::cout << "Total Credits: " << student.getTotalCredits() << std::endl;
    std::cout << "Academic Standing: " << student.getAcademicStanding() << std::endl;
}

void Display::displayGPA(const Semester& semester) {
    std::cout << "\nSemester GPA: " << std::fixed << std::setprecision(2) 
             << semester.getGPA() << std::endl;
    std::cout << "Total Credits: " << semester.getTotalCredits() << std::endl;
}

void Display::displayTargetCGPAInfo(double currentCGPA, double targetCGPA, 
                                   double requiredGPA, double futureCredits) {
    clearScreen();
    showHeader("TARGET CGPA CALCULATION RESULTS");
    
    std::cout << "Current CGPA: " << std::fixed << std::setprecision(2) << currentCGPA << std::endl;
    std::cout << "Target CGPA: " << std::fixed << std::setprecision(2) << targetCGPA << std::endl;
    std::cout << "Future Credits Planned: " << futureCredits << std::endl;
    std::cout << "\nRequired GPA in Future Courses: " 
             << std::fixed << std::setprecision(2) << requiredGPA << std::endl;
    
    if (requiredGPA > 4.0) {
        std::cout << "\nNote: The required GPA exceeds the maximum possible value (4.0).\n";
        std::cout << "You may need to take more credits or adjust your target CGPA.\n";
    }
    
    std::cout << "\n";
}

void Display::displayFileList(const std::vector<std::string>& files, const std::string& fileType) {
    if (files.empty()) {
        std::cout << "No " << fileType << " files found.\n";
        return;
    }
    
    std::cout << "\nAvailable " << fileType << " files:\n";
    std::cout << "-------------------------------------------------------------------------\n";
    
    for (size_t i = 0; i < files.size(); i++) {
        std::cout << (i + 1) << ". " << files[i] << std::endl;
    }
    
    std::cout << "-------------------------------------------------------------------------\n";
}

void Display::displayGradingSystem(const GradingSystem& system) {
    std::cout << "\nGrading System: " << system.getName() << std::endl;
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "Grade" << "Grade Points" << std::endl;
    std::cout << "-------------------------------------------------------------------------\n";
    
    auto grades = system.getAvailableGrades();
    std::sort(grades.begin(), grades.end());
    
    for (const auto& grade : grades) {
        std::cout << std::left << std::setw(10) << grade 
                 << std::fixed << std::setprecision(2) << system.getGradePoints(grade) << std::endl;
    }
    
    std::cout << "-------------------------------------------------------------------------\n";
}

void Display::displayAllGradingSystems() {
    clearScreen();
    showHeader("AVAILABLE GRADING SYSTEMS");
    
    std::cout << "1. Standard 4.0 Scale\n";
    std::cout << "2. 5.0 Scale\n";
    std::cout << "3. 10.0 Scale\n";
    std::cout << "4. Custom Grading System\n";
    std::cout << "5. Return to Previous Menu\n\n";
    
    std::cout << "Select a grading system to view details: ";
}

void Display::showHeader(const std::string& title) {
    std::cout << "=========================================================\n";
    std::cout << "                 " << title << "\n";
    std::cout << "=========================================================\n\n";
}

void Display::showFooter() {
    std::cout << "\n=========================================================\n";
}

void Display::showError(const std::string& message) {
    std::cout << "\nERROR: " << message << std::endl;
    pressEnterToContinue();
}

void Display::showSuccess(const std::string& message) {
    std::cout << "\nSUCCESS: " << message << std::endl;
    pressEnterToContinue();
}

void Display::clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void Display::pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}