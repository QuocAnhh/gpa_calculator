#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <iomanip> 

#include "../include/Course.h"
#include "../include/Semester.h"
#include "../include/Student.h"
#include "../include/GradingSystem.h"
#include "../include/FileManager.h"
#include "../include/Display.h"
#include "../include/Utils.h"

// Forward declarations
void runMainMenu();
void createNewStudent();
void loadStudent();
void manageGradingSystems();
void runStudentMenu(Student& student);
void viewStudentInfo(const Student& student);
void editStudentInfo(Student& student);
void addSemester(Student& student);
void manageSemester(Student& student);
void calculateTargetCGPA(const Student& student);
void changeGradingSystem(Student& student);
void saveStudent(const Student& student);
void runSemesterMenu(Student& student, Semester* semester);
void viewSemesterDetails(const Semester& semester);
void editSemesterName(Semester& semester);
void addCourse(Student& student, Semester& semester);
void manageCourse(Semester& semester);
void removeCourse(Semester& semester);
void runCourseMenu(Semester& semester, Course& course);
void viewCourseDetails(const Course& course);
void editCourseName(Course& course);
void editCourseCredits(Course& course, const GradingSystem& system);
void editCourseGrade(Course& course, const GradingSystem& system);
void createGradingSystem();
void loadGradingSystem();
void saveGradingSystem(const GradingSystem& system);

// Main function
int main(int argc, char* argv[]) {
    std::cout << "CGPA Calculator" << std::endl;
    std::cout << "===============" << std::endl;
    
    // Add your CGPA calculation logic here
    
    return 0;
}

// Implementation of menu functions
void runMainMenu() {
    int choice;
    bool exit = false;
    
    while (!exit) {
        Display::showMainMenu();
        choice = Utils::getIntInput("", 1, 4);
        
        switch (choice) {
            case 1:
                createNewStudent();
                break;
            case 2:
                loadStudent();
                break;
            case 3:
                manageGradingSystems();
                break;
            case 4:
                exit = true;
                break;
        }
    }
    
    Display::clearScreen();
    std::cout << "Thank you for using CGPA Calculator!\n";
}

void createNewStudent() {
    Display::clearScreen();
    Display::showHeader("CREATE NEW STUDENT");
    
    std::string name = Utils::getStringInput("Enter student name: ");
    std::string id = Utils::getStringInput("Enter student ID: ");
    
    // Select grading system
    Display::clearScreen();
    Display::showHeader("SELECT GRADING SYSTEM");
    std::cout << "1. Standard 4.0 Scale\n";
    std::cout << "2. 5.0 Scale\n";
    std::cout << "3. 10.0 Scale\n";
    std::cout << "4. Custom Grading System\n";
    
    int choice = Utils::getIntInput("Enter your choice: ", 1, 4);
    GradingSystem system = GradingSystem::createStandardFourPoint();
    
    switch (choice) {
        case 1:
            system = GradingSystem::createStandardFourPoint();
            break;
        case 2:
            system = GradingSystem::createFivePoint();
            break;
        case 3:
            system = GradingSystem::createTenPoint();
            break;
        case 4: {
            auto files = FileManager::getAvailableGradingSystemFiles();
            if (files.empty()) {
                Display::showError("No custom grading systems available. Using standard 4.0 scale.");
            } else {
                Display::displayFileList(files, "grading system");
                int fileChoice = Utils::getIntInput("Select a file (0 to cancel): ", 0, files.size());
                if (fileChoice > 0) {
                    system = FileManager::loadGradingSystem(files[fileChoice - 1]);
                }
            }
            break;
        }
    }
    
    Student student(name, id, system);
    Display::showSuccess("Student profile created successfully!");
    runStudentMenu(student);
}

void loadStudent() {
    Display::clearScreen();
    Display::showHeader("LOAD STUDENT PROFILE");
    
    auto files = FileManager::getAvailableStudentFiles();
    if (files.empty()) {
        Display::showError("No student profiles found.");
        return;
    }
    
    Display::displayFileList(files, "student");
    int choice = Utils::getIntInput("Select a file (0 to cancel): ", 0, files.size());
    
    if (choice == 0) {
        return;
    }
    
    Student student = FileManager::loadStudent(files[choice - 1]);
    if (student.getName().empty()) {
        Display::showError("Failed to load student profile.");
        return;
    }
    
    Display::showSuccess("Student profile loaded successfully!");
    runStudentMenu(student);
}

void manageGradingSystems() {
    int choice;
    bool exit = false;
    
    while (!exit) {
        Display::showGradingSystemMenu();
        choice = Utils::getIntInput("", 1, 5);
        
        switch (choice) {
            case 1: {
                Display::displayAllGradingSystems();
                int systemChoice = Utils::getIntInput("", 1, 5);
                
                if (systemChoice == 1) {
                    Display::displayGradingSystem(GradingSystem::createStandardFourPoint());
                } else if (systemChoice == 2) {
                    Display::displayGradingSystem(GradingSystem::createFivePoint());
                } else if (systemChoice == 3) {
                    Display::displayGradingSystem(GradingSystem::createTenPoint());
                } else if (systemChoice == 4) {
                    auto files = FileManager::getAvailableGradingSystemFiles();
                    if (files.empty()) {
                        Display::showError("No custom grading systems available.");
                    } else {
                        Display::displayFileList(files, "grading system");
                        int fileChoice = Utils::getIntInput("Select a file (0 to cancel): ", 0, files.size());
                        if (fileChoice > 0) {
                            GradingSystem system = FileManager::loadGradingSystem(files[fileChoice - 1]);
                            Display::displayGradingSystem(system);
                        }
                    }
                }
                Display::pressEnterToContinue();
                break;
            }
            case 2:
                createGradingSystem();
                break;
            case 3:
                loadGradingSystem();
                break;
            case 4: {
                Display::clearScreen();
                Display::showHeader("SELECT GRADING SYSTEM TO SAVE");
                std::cout << "1. Standard 4.0 Scale\n";
                std::cout << "2. 5.0 Scale\n";
                std::cout << "3. 10.0 Scale\n";
                std::cout << "4. Cancel\n";
                
                int systemChoice = Utils::getIntInput("Enter your choice: ", 1, 4);
                
                if (systemChoice < 4) {
                    GradingSystem system = GradingSystem::createStandardFourPoint(); // Initialize with a default value
                    switch (systemChoice) {
                        case 1: system = GradingSystem::createStandardFourPoint(); break;
                        case 2: system = GradingSystem::createFivePoint(); break;
                        case 3: system = GradingSystem::createTenPoint(); break;
                    }
                    saveGradingSystem(system);
                }
                break;
            }
            case 5:
                exit = true;
                break;
        }
    }
}

void runStudentMenu(Student& student) {
    int choice;
    bool exit = false;
    
    while (!exit) {
        Display::showStudentMenu();
        choice = Utils::getIntInput("", 1, 8);
        
        switch (choice) {
            case 1:
                viewStudentInfo(student);
                break;
            case 2:
                editStudentInfo(student);
                break;
            case 3:
                addSemester(student);
                break;
            case 4:
                manageSemester(student);
                break;
            case 5:
                calculateTargetCGPA(student);
                break;
            case 6:
                changeGradingSystem(student);
                break;
            case 7:
                saveStudent(student);
                break;
            case 8:
                exit = true;
                break;
        }
    }
}

void viewStudentInfo(const Student& student) {
    Display::displayStudentInfo(student);
    Display::pressEnterToContinue();
}

void editStudentInfo(Student& student) {
    Display::clearScreen();
    Display::showHeader("EDIT STUDENT INFORMATION");
    
    std::cout << "Current Name: " << student.getName() << std::endl;
    std::cout << "Current ID: " << student.getId() << std::endl;
    
    std::cout << "\n1. Edit Name\n";
    std::cout << "2. Edit ID\n";
    std::cout << "3. Return to Student Menu\n";
    
    int choice = Utils::getIntInput("Enter your choice: ", 1, 3);
    
    if (choice == 1) {
        std::string name = Utils::getStringInput("Enter new name: ");
        student.setName(name);
    } else if (choice == 2) {
        std::string id = Utils::getStringInput("Enter new ID: ");
        student.setId(id);
    }
}

void addSemester(Student& student) {
    Display::clearScreen();
    Display::showHeader("ADD NEW SEMESTER");
    
    std::string name = Utils::getStringInput("Enter semester name (e.g., Fall 2023): ");
    
    // Create and add the new semester
    Semester newSemester(name);
    student.addSemester(newSemester);
    
    Display::showSuccess("Semester added successfully!");
}

void manageSemester(Student& student) {
    Display::clearScreen();
    Display::showHeader("MANAGE SEMESTERS");
    
    const auto& semesters = student.getSemesters();
    if (semesters.empty()) {
        Display::showError("No semesters found. Please add a semester first.");
        return;
    }
    
    Display::displaySemesterList(semesters);
    int choice = Utils::getIntInput("Select a semester (0 to cancel): ", 0, semesters.size());
    
    if (choice == 0) {
        return;
    }
    
    // Get the selected semester (need to use a pointer since we're modifying the semester)
    Semester* semester = student.getSemesterByIndex(choice - 1);
    if (semester != nullptr) {
        runSemesterMenu(student, semester);
    } else {
        Display::showError("Invalid semester selection.");
    }
}

void calculateTargetCGPA(const Student& student) {
    Display::clearScreen();
    Display::showTargetCGPAMenu();
    
    double currentCGPA = student.getCGPA();
    int totalCredits = student.getTotalCredits();
    
    std::cout << "Current CGPA: " << std::fixed << std::setprecision(2) << currentCGPA << std::endl;
    std::cout << "Current Total Credits: " << totalCredits << std::endl << std::endl;
    
    double targetCGPA = Utils::getDoubleInput("Enter your target CGPA: ", 0.0, 4.0);
    double futureCredits = Utils::getDoubleInput("Enter number of credits you plan to take: ", 1.0, 200.0);
    
    // Calculate required GPA
    double totalQualityPoints = currentCGPA * totalCredits;
    double targetTotalPoints = targetCGPA * (totalCredits + futureCredits);
    double requiredPoints = targetTotalPoints - totalQualityPoints;
    double requiredGPA = requiredPoints / futureCredits;
    
    Display::displayTargetCGPAInfo(currentCGPA, targetCGPA, requiredGPA, futureCredits);
}

void changeGradingSystem(Student& student) {
    Display::clearScreen();
    Display::showHeader("CHANGE GRADING SYSTEM");
    
    std::cout << "Current Grading System: " << student.getGradingSystem().getName() << std::endl << std::endl;
    std::cout << "WARNING: Changing the grading system may affect existing grades and calculations.\n";
    std::cout << "It is recommended to do this before adding courses.\n\n";
    
    std::cout << "1. Standard 4.0 Scale\n";
    std::cout << "2. 5.0 Scale\n";
    std::cout << "3. 10.0 Scale\n";
    std::cout << "4. Custom Grading System\n";
    std::cout << "5. Cancel\n\n";
    
    int choice = Utils::getIntInput("Enter your choice: ", 1, 5);
    
    if (choice == 5) {
        return;
    }
    
    GradingSystem system = GradingSystem::createStandardFourPoint();
    
    switch (choice) {
        case 1:
            system = GradingSystem::createStandardFourPoint();
            break;
        case 2:
            system = GradingSystem::createFivePoint();
            break;
        case 3:
            system = GradingSystem::createTenPoint();
            break;
        case 4: {
            auto files = FileManager::getAvailableGradingSystemFiles();
            if (files.empty()) {
                Display::showError("No custom grading systems available. Using standard 4.0 scale.");
            } else {
                Display::displayFileList(files, "grading system");
                int fileChoice = Utils::getIntInput("Select a file (0 to cancel): ", 0, files.size());
                if (fileChoice > 0) {
                    system = FileManager::loadGradingSystem(files[fileChoice - 1]);
                } else {
                    return;
                }
            }
            break;
        }
    }
    
    student.setGradingSystem(system);
    Display::showSuccess("Grading system changed successfully!");
}

void saveStudent(const Student& student) {
    Display::clearScreen();
    Display::showHeader("SAVE STUDENT PROFILE");
    
    std::string filename = Utils::getStringInput("Enter filename (without extension): ");
    if (filename.empty()) {
        filename = student.getName();
    }
    
    bool success = FileManager::saveStudent(student, filename);
    if (success) {
        Display::showSuccess("Student profile saved successfully!");
    } else {
        Display::showError("Failed to save student profile.");
    }
}

void createGradingSystem() {
    Display::clearScreen();
    Display::showHeader("CREATE CUSTOM GRADING SYSTEM");
    
    std::string name = Utils::getStringInput("Enter a name for the grading system: ");
    GradingSystem system(name);
    
    bool done = false;
    while (!done) {
        Display::clearScreen();
        Display::showHeader("CREATE CUSTOM GRADING SYSTEM - " + name);
        Display::displayGradingSystem(system);
        
        std::cout << "\n1. Add Grade\n";
        std::cout << "2. Remove Grade\n";
        std::cout << "3. Save Grading System\n";
        std::cout << "4. Cancel\n\n";
        
        int choice = Utils::getIntInput("Enter your choice: ", 1, 4);
        
        switch (choice) {
            case 1: {
                std::string grade = Utils::getStringInput("Enter grade letter/name: ");
                double points = Utils::getDoubleInput("Enter grade points: ", 0.0, 10.0);
                system.addGrade(grade, points);
                break;
            }
            case 2: {
                auto grades = system.getAvailableGrades();
                if (grades.empty()) {
                    Display::showError("No grades to remove.");
                    break;
                }
                
                std::cout << "Available grades:\n";
                for (size_t i = 0; i < grades.size(); i++) {
                    std::cout << (i + 1) << ". " << grades[i] << " (" 
                              << system.getGradePoints(grades[i]) << " points)\n";
                }
                
                int gradeChoice = Utils::getIntInput("Select a grade to remove (0 to cancel): ", 0, grades.size());
                if (gradeChoice > 0) {
                    system.removeGrade(grades[gradeChoice - 1]);
                }
                break;
            }
            case 3:
                saveGradingSystem(system);
                done = true;
                break;
            case 4:
                done = true;
                break;
        }
    }
}

void loadGradingSystem() {
    Display::clearScreen();
    Display::showHeader("LOAD CUSTOM GRADING SYSTEM");
    
    auto files = FileManager::getAvailableGradingSystemFiles();
    if (files.empty()) {
        Display::showError("No custom grading systems available.");
        return;
    }
    
    Display::displayFileList(files, "grading system");
    int choice = Utils::getIntInput("Select a file to load (0 to cancel): ", 0, files.size());
    
    if (choice > 0) {
        GradingSystem system = FileManager::loadGradingSystem(files[choice - 1]);
        Display::displayGradingSystem(system);
        
        std::cout << "\n1. Save with a new name\n";
        std::cout << "2. Return to menu\n";
        
        int option = Utils::getIntInput("Enter your choice: ", 1, 2);
        if (option == 1) {
            saveGradingSystem(system);
        }
    }
}

void saveGradingSystem(const GradingSystem& system) {
    std::string filename = Utils::getStringInput("Enter filename to save (without extension): ");
    if (filename.empty()) {
        filename = system.getName();
    }
    
    bool success = FileManager::saveGradingSystem(system, filename);
    if (success) {
        Display::showSuccess("Grading system saved successfully!");
    } else {
        Display::showError("Failed to save grading system.");
    }
}