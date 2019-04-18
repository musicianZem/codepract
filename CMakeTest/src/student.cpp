
#include <iostream>
#include "student.h"

Student::Student() : st_name(""), st_classNumber(0) {
}
Student::Student(string &name) : st_name(name) {
}
Student::Student(string &name, int classNumber) : st_name(name), st_classNumber(classNumber) {
}
