#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "Student.h"
#include "GradingSystem.h"

class FileManager {
public:
    // Save and load student data
    static bool saveStudent(const Student& student, const std::string& filename);
    static Student loadStudent(const std::string& filename);
    
    // Save and load grading systems
    static bool saveGradingSystem(const GradingSystem& system, const std::string& filename);
    static GradingSystem loadGradingSystem(const std::string& filename);
    
    // Get available student files
    static std::vector<std::string> getAvailableStudentFiles();
    
    // Get available grading system files
    static std::vector<std::string> getAvailableGradingSystemFiles();
    
    // File existence check
    static bool fileExists(const std::string& filename);
};

#endif // FILE_MANAGER_H