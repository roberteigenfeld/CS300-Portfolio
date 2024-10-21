//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Bobby Eigenfeld
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : 7-1 Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Structure to represent a course
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Function to load data from a file into the course data structure
bool loadDataStructure(const std::string& filename, std::map<std::string, Course>& courseData) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string courseNumber, courseTitle;
        std::vector<std::string> prerequisites;

        // Split the line to get courseNumber, courseTitle, and prerequisites
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            courseNumber = line.substr(0, pos);
            line = line.substr(pos + 1);
            
            pos = line.find(',');
            if (pos != std::string::npos) {
                courseTitle = line.substr(0, pos);
                line = line.substr(pos + 1);

                size_t commaPos = 0;
                while ((commaPos = line.find(',')) != std::string::npos) {
                    prerequisites.push_back(line.substr(0, commaPos));
                    line.erase(0, commaPos + 2);
                }
                prerequisites.push_back(line);
            }

            Course course = {courseNumber, courseTitle, prerequisites};
            courseData[courseNumber] = course;
        }
    }

    file.close();
    return true;
}

// Function to print a list of courses
void printCourseList(const std::map<std::string, Course>& courseData) {
    for (const auto& entry : courseData) {
        std::cout << entry.second.courseNumber << ", " << entry.second.courseTitle << std::endl;
    }
}

// Function to display information for a specific course
void printCourseInfo(const std::map<std::string, Course>& courseData, const std::string& courseNumber) {
    auto it = courseData.find(courseNumber);
    if (it != courseData.end()) {
        const Course& course = it->second;
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const std::string& prereq : course.prerequisites) {
                std::cout << prereq << ", ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Course not found." << std::endl;
    }
}

int main() {
    std::map<std::string, Course> courseData;

    std::cout << "Welcome to the course planner." << std::endl;
    int choice;

    while (true) {
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter the filename for course data: ";
                std::cin >> filename;
                if (loadDataStructure(filename, courseData)) {
                    std::cout << "Data loaded successfully." << std::endl;
                }
                break;
            }
            case 2:
                printCourseList(courseData);
                break;
            case 3: {
                std::string courseNumber;
                std::cout << "What course do you want to know about? ";
                std::cin >> courseNumber;
                printCourseInfo(courseData, courseNumber);
                break;
            }
            case 9:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
                break;
        }
    }

    return 0;
}