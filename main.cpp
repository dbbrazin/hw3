//HW3 by Dane Brazinski
//SU Net ID: dbbrazin SUID: 533140379
//Due: 11:59PM, February 19 (Wednesday)

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    string grade;
    course() {}
    course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

    //You might need to implement some overloaded operators here.

};
/*
ID: 11111
Semester: 20171
GPA: x.xx
Credits: 13
(CIS554 1 3 A-) (CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)

ID: 11111
Semester: 20171
GPA: x.xx
Credits: 10
(CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)

 */
ostream& operator<<(ostream& str, const map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*> m){
    for(auto i = m.begin(); i != m.end(); i++){
        str << "SUID: "<< i->first << endl << i->second << endl;
    }
    return str;
}

ostream& operator<<(ostream& str, const tuple<int, float, map<int, tuple<int, float, list<course*> *>>*> t){
    str << "Overall GPA: " << get<1>(t) << endl << "Overall Credits: " << get<0>(t) << endl << get<2>(t);
    return str;
}

ostream& operator<<(ostream& str, const map<int, tuple<int, float, list<course*> *>* > m ){
    for(auto i = m.begin(); i != m.end(); i++){
        str << "Semester: " << i->first << endl << i->second << endl;
    }
    return str;
}

ostream& operator<<(ostream& str, const tuple<int, float, list<course*> *> t){
    str << "Semester GPA: " << get<1>(t) << endl << "Semester Credits: " << get<0>(t) << endl << get<2>(t);
    return str;
}

ostream& operator<<(ostream& str, const list<course*> l){
    for(auto i: l){
        str << i << " ";
    }
    return str << endl;
}

ostream& operator<<(ostream& str, const course c){
    str << "("<< c.name << " " << c.section << " " << c.credits << " " << c.grade << ")";
    return str;
}
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.

void add_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);
void remove_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);
void add_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
//All courses in the list should be sorted according to name (increasing order)
void drop_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id);
void print_student_all_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.

int main() {
    map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>  DB;

    add_student(DB, 11111);
    course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);

    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

    course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
    add_course(DB, 20172, 11111, C5);
    add_course(DB, 20172, 11111, C6);
    add_course(DB, 20172, 11111, C7);
    add_course(DB, 20172, 11111, C8);
    add_course(DB, 20172, 11111, C3);
    print_student_all_courses(DB, 11111);//ID GPA

    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C5);
    add_course(DB, 20171, 11112, C7);
    add_course(DB, 20171, 11112, C4);
    print_student_semester_courses(DB, 20171, 11112);

    add_course(DB, 20172, 11112, C8);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C5);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);

    print_student_all_courses(DB, 11112);

    cout << DB << endl;
    remove_student(DB, 11111);
    cout << DB << endl;
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
    DB[id] = new tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>;
}
void remove_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
    DB.erase(id);
}


void add_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {
    int a; float b
    tie(a,b,c) = DB.find(id)->second;

}

void drop_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {

}

void print_student_semester_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id) {

}
void print_student_all_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {

}



