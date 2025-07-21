#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Untuk std::remove

class Student; // Forward declaration

class Course {
private:
    std::string courseName;
    int maxEnrollment;
    std::vector<Student*> enrolledStudents; // Menyimpan pointer ke objek Student

public:
    // Konstruktor
    Course(std::string name, int maxEnroll) : courseName(name), maxEnrollment(maxEnroll) {}

    // Destruktor
    ~Course() {
        std::cout << "Kursus " << courseName << " telah dihapus." << std::endl;
    }

    // Metode untuk mendaftar siswa
    bool enroll(Student* student);

    // Metode untuk membatalkan pendaftaran siswa
    void drop(Student* student);

    // Metode untuk mendapatkan daftar siswa yang terdaftar
    void getEnrolledStudents() const;

    // Metode untuk mendapatkan nama kursus
    std::string getCourseName() const {
        return courseName;
    }
};

class Student {
private:
    std::string name;
    std::vector<Course*> enrolledCourses; // Menyimpan pointer ke objek Course

public:
    // Konstruktor
    Student(std::string studentName) : name(studentName) {}

    // Destruktor
    ~Student() {
        std::cout << "Siswa " << name << " telah dihapus." << std::endl;
    }

    // Metode untuk mendaftar ke kursus
    void enroll(Course* course) {
        if (course->enroll(this)) {
            enrolledCourses.push_back(course);
            std::cout << name << " berhasil mendaftar ke kursus " << course->getCourseName() << "." << std::endl;
        } else {
            std::cout << name << " gagal mendaftar ke kursus " << course->getCourseName() << " (penuh)." << std::endl;
        }
    }

    // Metode untuk membatalkan pendaftaran dari kursus
    void drop(Course* course) {
        course->drop(this);
        enrolledCourses.erase(std::remove(enrolledCourses.begin(), enrolledCourses.end(), course), enrolledCourses.end());
    }

    // Metode untuk mendapatkan nama siswa
    std::string getName() const {
        return name;
    }
};

// Implementasi metode enroll pada kelas Course
bool Course::enroll(Student* student) {
    if (enrolledStudents.size() < maxEnrollment) {
        enrolledStudents.push_back(student);
        return true;
    } else {
        return false; // Kursus sudah penuh
    }
}

// Implementasi metode drop pada kelas Course
void Course::drop(Student* student) {
    auto it = std::remove(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it, enrolledStudents.end());
        std::cout << student->getName() << " telah dibatalkan pendaftarannya dari kursus " << courseName << "." << std::endl;
    } else {
        std::cout << student->getName() << " tidak terdaftar di kursus " << courseName << "." << std::endl;
    }
}

// Implementasi metode untuk mendapatkan daftar siswa yang terdaftar
void Course::getEnrolledStudents() const {
    std::cout << "Siswa terdaftar di kursus " << courseName << ":" << std::endl;
    for (const auto& student : enrolledStudents) {
        std::cout << "- " << student->getName() << std::endl;
    }
}

int main() {
    // Membuat objek kursus
    Course course1("Matematika", 2);
    Course course2("Fisika", 3);

    // Membuat objek siswa
    Student student1("Alice");
    Student student2("Bob");
    Student student3("Charlie");

    // Mendaftar siswa ke kursus
    student1.enroll(&course1);
    student2.enroll(&course1);
    student3.enroll(&course1); // Ini harus gagal karena kursus penuh

    // Menampilkan siswa yang terdaftar di kursus
    course1.getEnrolledStudents();

    // Membatalkan pendaftaran
    student1.drop(&course1);
    course1.getEnrolledStudents();

    // Menutup program
    return 0;
}
