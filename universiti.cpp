#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Forward declaration
class Course;

// Student class
class Student {
private:
    int id;
    std::string name;
    std::vector<Course*> enrolledCourses;

public:
    // Constructor
    Student(int studentId, std::string studentName) {
        id = studentId;
        name = studentName;
        std::cout << "Student created: " << name << " (ID: " << id << ")" << std::endl;
    }

    // Destructor
    ~Student() {
        std::cout << "Student record deleted: " << name << " (ID: " << id << ")" << std::endl;
    }

    // Getter methods
    int getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    const std::vector<Course*>& getEnrolledCourses() const {
        return enrolledCourses;
    }

    // Enroll in a course (implementation defined after Course class)
    bool enrollIn(Course* course);

    // Drop a course (implementation defined after Course class)
    bool dropCourse(Course* course);

    // Display student information and enrolled courses
    void displayInfo() const;
};

// Course class
class Course {
private:
    std::string code;
    std::string title;
    int maxEnrollment;
    std::vector<Student*> enrolledStudents;

public:
    // Constructor
    Course(std::string courseCode, std::string courseTitle, int maxStudents) {
        code = courseCode;
        title = courseTitle;

        // Validate max enrollment
        if (maxStudents <= 0) {
            std::cout << "Max enrollment must be positive. Setting to default (30)." << std::endl;
            maxEnrollment = 30;
        } else {
            maxEnrollment = maxStudents;
        }

        std::cout << "Course created: " << title << " (" << code << ") - Max enrollment: "
                  << maxEnrollment << std::endl;
    }

    // Destructor
    ~Course() {
        std::cout << "Course deleted: " << title << " (" << code << ")" << std::endl;
    }

    // Getter methods
    std::string getCode() const {
        return code;
    }

    std::string getTitle() const {
        return title;
    }

    int getMaxEnrollment() const {
        return maxEnrollment;
    }

    int getCurrentEnrollment() const {
        return enrolledStudents.size();
    }

    const std::vector<Student*>& getEnrolledStudents() const {
        return enrolledStudents;
    }

    // Check if a student is enrolled
    bool isStudentEnrolled(Student* student) const {
        return std::find(enrolledStudents.begin(), enrolledStudents.end(), student) != enrolledStudents.end();
    }

    // Enroll a student in this course
    bool enrollStudent(Student* student) {
        // Check if the course is full
        if (enrolledStudents.size() >= maxEnrollment) {
            std::cout << "Cannot enroll in " << code << ": Course is full." << std::endl;
            return false;
        }

        // Check if student is already enrolled
        if (isStudentEnrolled(student)) {
            std::cout << "Student " << student->getName() << " is already enrolled in " << code << std::endl;
            return false;
        }

        // Add student to the course
        enrolledStudents.push_back(student);
        std::cout << "Student " << student->getName() << " enrolled in " << title << " (" << code << ")" << std::endl;
        return true;
    }

    // Remove a student from this course
    bool dropStudent(Student* student) {
        auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), student);

        // Check if student is enrolled
        if (it == enrolledStudents.end()) {
            std::cout << "Student " << student->getName() << " is not enrolled in " << code << std::endl;
            return false;
        }

        // Remove student from the course
        enrolledStudents.erase(it);
        std::cout << "Student " << student->getName() << " dropped course: " << title << " (" << code << ")" << std::endl;
        return true;
    }

    // Display course information and enrolled students
    void displayInfo() const {
        std::cout << "\n----- Course Information -----" << std::endl;
        std::cout << "Code: " << code << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Enrollment: " << enrolledStudents.size() << "/" << maxEnrollment << std::endl;

        std::cout << "Enrolled Students:" << std::endl;
        if (enrolledStudents.empty()) {
            std::cout << "  No students enrolled." << std::endl;
        } else {
            for (const Student* student : enrolledStudents) {
                std::cout << "  - " << student->getName() << " (ID: " << student->getId() << ")" << std::endl;
            }
        }
        std::cout << "-------------------------------\n" << std::endl;
    }
};

// Implementation of Student methods that require Course class
bool Student::enrollIn(Course* course) {
    if (course == nullptr) {
        std::cout << "Invalid course." << std::endl;
        return false;
    }

    // Try to enroll in the course
    if (course->enrollStudent(this)) {
        // Add course to student's enrolled courses
        enrolledCourses.push_back(course);
        return true;
    }

    return false;
}

bool Student::dropCourse(Course* course) {
    if (course == nullptr) {
        std::cout << "Invalid course." << std::endl;
        return false;
    }

    // Try to drop the course
    if (course->dropStudent(this)) {
        // Remove course from student's enrolled courses
        auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), course);
        if (it != enrolledCourses.end()) {
            enrolledCourses.erase(it);
        }
        return true;
    }

    return false;
}

void Student::displayInfo() const {
    std::cout << "\n----- Student Information -----" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;

    std::cout << "Enrolled Courses:" << std::endl;
    if (enrolledCourses.empty()) {
        std::cout << "  Not enrolled in any courses." << std::endl;
    } else {
        for (const Course* course : enrolledCourses) {
            std::cout << "  - " << course->getTitle() << " (" << course->getCode() << ")" << std::endl;
        }
    }
    std::cout << "-------------------------------\n" << std::endl;
}

// University class to manage students and courses
class University {
private:
    std::vector<Student*> students;
    std::vector<Course*> courses;

public:
    // Constructor
    University() {
        std::cout << "University system initialized." << std::endl;
    }

    // Destructor
    ~University() {
        // Clean up all students
        for (Student* s : students) {
            delete s;
        }
        students.clear();

        // Clean up all courses
        for (Course* c : courses) {
            delete c;
        }
        courses.clear();

        std::cout << "University system shutdown." << std::endl;
    }

    // Add a student to the university
    void addStudent(Student* student) {
        students.push_back(student);
    }

    // Add a course to the university
    void addCourse(Course* course) {
        courses.push_back(course);
    }

    // Find a student by ID
    Student* findStudentById(int id) {
        for (Student* s : students) {
            if (s->getId() == id) {
                return s;
            }
        }
        return nullptr;
    }

    // Find a course by code
    Course* findCourseByCode(const std::string& code) {
        for (Course* c : courses) {
            if (c->getCode() == code) {
                return c;
            }
        }
        return nullptr;
    }

    // Display all students
    void displayAllStudents() const {
        std::cout << "\n===== ALL STUDENTS =====" << std::endl;
        if (students.empty()) {
            std::cout << "No students registered." << std::endl;
        } else {
            for (const Student* s : students) {
                std::cout << s->getName() << " (ID: " << s->getId() << ")" << std::endl;
            }
        }
        std::cout << "=======================\n" << std::endl;
    }

    // Display all courses
    void displayAllCourses() const {
        std::cout << "\n===== ALL COURSES =====" << std::endl;
        if (courses.empty()) {
            std::cout << "No courses available." << std::endl;
        } else {
            for (const Course* c : courses) {
                std::cout << c->getTitle() << " (" << c->getCode() << ") - Enrollment: "
                          << c->getCurrentEnrollment() << "/" << c->getMaxEnrollment() << std::endl;
            }
        }
        std::cout << "======================\n" << std::endl;
    }
};

int main() {
    // Create university system
    University university;

    // Create courses
    Course* cs101 = new Course("CS101", "Introduction to Programming", 3);
    Course* cs201 = new Course("CS201", "Data Structures", 2);
    Course* math101 = new Course("MATH101", "Calculus I", 5);
    Course* eng101 = new Course("ENG101", "English Composition", 4);

    // Add courses to university
    university.addCourse(cs101);
    university.addCourse(cs201);
    university.addCourse(math101);
    university.addCourse(eng101);

    // Create students
    Student* student1 = new Student(1001, "John Smith");
    Student* student2 = new Student(1002, "Emily Johnson");
    Student* student3 = new Student(1003, "Michael Brown");
    Student* student4 = new Student(1004, "Sophia Wilson");
    Student* student5 = new Student(1005, "David Lee");

    // Add students to university
    university.addStudent(student1);
    university.addStudent(student2);
    university.addStudent(student3);
    university.addStudent(student4);
    university.addStudent(student5);

    // Display all students and courses
    university.displayAllStudents();
    university.displayAllCourses();

    // Test enrollment functionality
    student1->enrollIn(cs101);
    student1->enrollIn(math101);
    student2->enrollIn(cs101);
    student3->enrollIn(cs101);

    // This should fail due to max enrollment limit for CS101
    student4->enrollIn(cs101);

    // Enroll students in other courses
    student2->enrollIn(cs201);
    student3->enrollIn(cs201);
    student4->enrollIn(math101);
    student5->enrollIn(eng101);

    // Test drop functionality
    student1->dropCourse(math101);

    // Display updated course information
    cs101->displayInfo();
    cs201->displayInfo();
    math101->displayInfo();

    // Display student information
    student1->displayInfo();
    student2->displayInfo();

    // Try to enroll in a course again (should fail)
    student1->enrollIn(cs101);

    // The university destructor will automatically delete all students and courses
    return 0;
}
