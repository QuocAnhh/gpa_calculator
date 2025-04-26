#include "../include/FileManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

bool FileManager::saveStudent(const Student& student, const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing.\n";
            return false;
        }
        
        file << student.serialize();
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving student data: " << e.what() << std::endl;
        return false;
    }
}

Student FileManager::loadStudent(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for reading.\n";
            return Student(); // Return empty student
        }
        
        std::string data;
        std::getline(file, data);
        file.close();
        
        return Student::deserialize(data);
    } catch (const std::exception& e) {
        std::cerr << "Error loading student data: " << e.what() << std::endl;
        return Student(); // Return empty student
    }
}

bool FileManager::saveGradingSystem(const GradingSystem& system, const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing.\n";
            return false;
        }
        
        file << system.serialize();
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving grading system: " << e.what() << std::endl;
        return false;
    }
}

GradingSystem FileManager::loadGradingSystem(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for reading.\n";
            return GradingSystem::createStandardFourPoint(); // Return default system
        }
        
        std::string data;
        std::getline(file, data);
        file.close();
        
        return GradingSystem::deserialize(data);
    } catch (const std::exception& e) {
        std::cerr << "Error loading grading system: " << e.what() << std::endl;
        return GradingSystem::createStandardFourPoint(); // Return default system
    }
}

std::vector<std::string> FileManager::getAvailableStudentFiles() {
    std::vector<std::string> files;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            if (entry.path().extension() == ".student") {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing student files: " << e.what() << std::endl;
    }
    return files;
}

std::vector<std::string> FileManager::getAvailableGradingSystemFiles() {
    std::vector<std::string> files;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            if (entry.path().extension() == ".grading") {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing grading system files: " << e.what() << std::endl;
    }
    return files;
}

bool FileManager::fileExists(const std::string& filename) {
    try {
        return std::filesystem::exists(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error checking file existence: " << e.what() << std::endl;
        return false;
    }
}