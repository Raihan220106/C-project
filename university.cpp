#include <iostream>
#include <vector>
#include <string>

class Student;

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int maxStudents;
    std::vector<Student*> enrolledStudents;

public:
    // Constructor
    Course(std::string code, std::string name, int max)
        : courseCode(code), courseName(name), maxStudents(max) {
        std::cout << "Course Created: " << courseName << " (" << courseCode << ")\n";
    }

    // Destructor
    ~Course() {
        std::cout << "Course Deleted: " << courseName << "\n";
    }

    // Enroll Student
    bool enroll(Student* student);

    // Drop Student
    void drop(Student* student);

    // Display Enrolled Students
    void getEnrolledStudents();
};

class Student {
private:
    std::string studentID;
    std::string studentName;
    std::vector<Course*> enrolledCourses;

public:
    // Constructor
    Student(std::string id, std::string name)
        : studentID(id), studentName(name) {
        std::cout << "Student Created: " << studentName << " (" << studentID << ")\n";
    }

    // Destructor
    ~Student() {
        std::cout << "Student Deleted: " << studentName << "\n";
    }

    // Enroll in Course
    void enrollInCourse(Course* course) {
        if (course->enroll(this)) {
            enrolledCourses.push_back(course);
        }
    }

    // Drop Course
    void dropCourse(Course* course) {
        course->drop(this);
    }
};








int main() {
    // Create Courses
    Course course1("CS101", "Introduction to Programming", 2);
    Course course2("MATH202", "Calculus II", 3);

    // Create Students
    Student student1("S001", "Alice");
    Student student2("S002", "Bob");
    Student student3("S003", "Charlie");

    // Enroll Students
    student1.enrollInCourse(&course1);
    student2.enrollInCourse(&course1);
    student3.enrollInCourse(&course1); // Should fail (course full)

    student3.enrollInCourse(&course2);

    // Display Enrolled Students
    course1.getEnrolledStudents();
    course2.getEnrolledStudents();

    return 0;
}

