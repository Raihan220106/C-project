#include <iostream>
#include <string>
#include <vector>

class Student {
private:
    int studentId;
    std::string studentName;

public:
    // Konstruktor
    Student(int id, std::string name) : studentId(id), studentName(name) {
        std::cout << "Mahasiswa " << studentName << " ditambahkan." << std::endl;
    }

    // Destruktor
    ~Student() {
        std::cout << "Mahasiswa " << studentName << " dihapus." << std::endl;
    }

    // Metode untuk mendapatkan ID mahasiswa
    int getStudentId() const {
        return studentId;
    }

    // Metode untuk mendapatkan nama mahasiswa
    std::string getStudentName() const {
        return studentName;
    }
};

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int maxStudents;
    std::vector<Student*> enrolledStudents;

public:
    // Konstruktor
    Course(std::string code, std::string name, int max) : courseCode(code), courseName(name), maxStudents(max) {
        std::cout << "Kursus " << courseName << " dibuat." << std::endl;
    }

    // Destruktor
    ~Course() {
        std::cout << "Kursus " << courseName << " dihapus." << std::endl;
    }

    // Metode untuk mendaftarkan mahasiswa
    void enroll(Student* student) {
        if (enrolledStudents.size() < maxStudents) {
            enrolledStudents.push_back(student);
            std::cout << student->getStudentName() << " berhasil mendaftar ke " << courseName << "." << std::endl;
        } else {
            std::cout << "Pendaftaran " << student->getStudentName() << " gagal. Kuota " << courseName << " penuh." << std::endl;
        }
    }

    // Metode untuk membatalkan pendaftaran mahasiswa
    void drop(Student* student) {
        for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
            if ((*it)->getStudentId() == student->getStudentId()) {
                enrolledStudents.erase(it);
                std::cout << student->getStudentName() << " berhasil membatalkan pendaftaran dari " << courseName << "." << std::endl;
                return;
            }
        }
        std::cout << student->getStudentName() << " tidak terdaftar di " << courseName << "." << std::endl;
    }

    // Metode untuk mendapatkan daftar mahasiswa yang terdaftar
    void getEnrolledStudents() const {
        std::cout << "Mahasiswa yang terdaftar di " << courseName << ":" << std::endl;
        for (const auto& student : enrolledStudents) {
            std::cout << "- " << student->getStudentName() << std::endl;
        }
    }
};

int main() {
    // Membuat objek Student
    Student student1(1, "Alice");
    Student student2(2, "Bob");
    Student student3(3, "Charlie");

    // Membuat objek Course dengan batasan pendaftaran
    Course course1("CS101", "Pengantar Pemrograman", 2);

    // Mendaftarkan mahasiswa ke kursus
    course1.enroll(&student1);
    course1.enroll(&student2);
    course1.enroll(&student3); // Pendaftaran gagal karena kuota penuh

    // Menampilkan daftar mahasiswa yang terdaftar
    course1.getEnrolledStudents();

    // Membatalkan pendaftaran
    course1.drop(&student2);

    // Menampilkan daftar mahasiswa yang terdaftar setelah pembatalan
    course1.getEnrolledStudents();

    return 0;
}
