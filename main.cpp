//HW3 by Dane Brazinski
//SU Net ID: dbbrazin SUID: 533140379
//Due: 11:59PM, February 19 (Wednesday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <iomanip>

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

    float getGPA();
    bool operator==(const course& c);
    bool operator<(const course& c);



};

float course::getGPA() {
    if (grade == "A")
        return 4.0;
    else if (grade == "A-")
        return 3.6666;
    else if (grade == "B+")
        return 3.3333;
    else if (grade == "B")
        return 3.0;
    else if (grade == "B-")
        return 2.6666;
    else if (grade == "C+")
        return 2.3333;
    else if (grade == "C")
        return 2.0;
    else if (grade == "C-")
        return 1.6666;
    else if (grade == "D")
        return 1.0;
    else if (grade == "D-")
        return 0.666;
    else if (grade == "F")
        return 0.0;
    return 0;
}

bool course::operator==(const course& c) {
    return name == c.name;
}

bool course::operator<(const course& c) {
    return name < c.name;
}

template <class T>
ostream& operator<<(ostream& str, const map<int, T*>& m) {
    str << "DB: " << endl;
    for (auto i : m) {
        str << "ID: " << i.first << endl << *(i.second);
    }
    return str;
}

template  <class T>
ostream& operator<<(ostream& str, const tuple<int, float, map<int, T>* >& t) {
    str << "Overall GPA: " << setprecision(2) << fixed << get<1>(t) << endl << "Overall Credits: " << get<0>(t) << endl << *(get<2>(t));
    return str;
}

template  <class T>
ostream& operator<<(ostream& str, const map<int, T>& m) {
    for (auto i : m) {
        str << "Semester: " << i.first << endl << (i.second) << endl;
    }
    return str;
}


template <class T>
ostream& operator<<(ostream& str, const tuple<int, float, T*>& t) {
    str << "GPA: " << setprecision(2) << fixed << get<1>(t) << endl << "Credits: " << get<0>(t) << endl << *(get<2>(t));
    return str;
}

template<class T>
ostream& operator<<(ostream& str, const list<T>& l) {
    for (auto i : l) {
        str << *i << " ";
    }
    return str;
}

ostream& operator<<(ostream& str, const course& c) {
    str << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ")";
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
    drop_course(DB, 20171, 11111, C1);
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
    return 0;
}

void add_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
    if (DB.find(id) != DB.end()) {
        //student already in DB
        return;
    }
    DB[id] = new tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>;
}
void remove_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
    if (DB.find(id) == DB.end()) {
        //student to remove does not exist
        return;
    }
    auto& semMap = get<2>(*DB[id]);
    if (semMap == nullptr) {
        //semester map does not exist
        delete semMap;
        DB.erase(DB.find(id));
        return;
    }
    for (auto i : *semMap) {
        auto& courseList = get<2>(i.second);
        for (course* j : *courseList) {
            delete j;
        }
        courseList->clear();
        if (semMap->empty())
            break;
        delete courseList;
    }
    delete semMap;
    DB.erase(DB.find(id));
}

//have to delete one by one
//find if

void add_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {
    if (DB.find(id) == DB.end()) {
        //student to add course to does not exist
        return;
    }
    auto& semMap = get<2>(*DB[id]);

    if (semMap == nullptr) {
        //semester map not created, create it
        semMap = new map<int, tuple<int, float, list<course*>* > >;
    }
    if (semMap->find(semester) == semMap->end()) {
        //semester does not exist, add it
        tuple<int, float, list<course*>* > semTup;
        semMap->emplace(semester, semTup);
    }

    auto& sem = (*get<2>(*DB[id]))[semester];
    auto& courses = get<2>(sem);

    if (courses == nullptr) {
        //no course list, create one
        courses = new list<course*>;
        courses->push_front(new course(c));
    }
    else {
        //check if course already in semMap
        for (auto x : *semMap) {
            auto& cl = get<2>(x.second);
            for (auto y : *cl) {
                if (y->name == c.name) {
                    //course already exists
                    return;
                }
            }
        }
        //add course to course list
        auto it1 = courses->begin();
        auto it2 = courses->begin();
        it2++;
        while (true) {
            if (it1 == courses->begin() && (*it1)->name.compare(c.name) > 0) {
                courses->push_front(new course(c));
                break;
            }
            else if (it2 == courses->end()) {
                if ((*it1)->name.compare(c.name) < 0)
                    courses->push_back(new course(c));
                else {
                    courses->insert(it1, new course(c));
                }
                break;
            }
            else if ((*it1)->name.compare(c.name) < 0 && (*it2)->name.compare(c.name) > 0) {
                courses->insert(++it1, new course(c));
                break;
            }
            it1++;
            it2++;
        }

    }
    int& semCreds = get<0>(sem);
    float& semGPA = get<1>(sem);
    int& overCreds = get<0>(*DB[id]);
    float& overGPA = get<1>(*DB[id]);
    float semUnscaledGPA = semGPA * (float)semCreds;
    float overUnscaledGPA = overGPA * (float)overCreds;
    semUnscaledGPA += c.getGPA() * c.credits;
    semCreds += c.credits;
    semGPA = semUnscaledGPA / (float)semCreds;
    overUnscaledGPA += c.getGPA() * c.credits;
    overCreds += c.credits;
    overGPA = overUnscaledGPA / (float)overCreds;
}

void drop_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {
    if (DB.find(id) == DB.end()) {
        //student to drop course does not exist
        return;
    }
    auto& semMap = get<2>(*DB[id]);
    if (semMap == nullptr) {
        //semester map does not exist
        return;
    }
    if (semMap->find(semester) == semMap->end()) {
        //semester does not exist
        return;
    }

    auto& sem = (*get<2>(*DB[id]))[semester];
    auto& courses = get<2>(sem);

    if (courses == nullptr) {
        //no course list
        return;
    }
    else {
        auto it1 = courses->begin();
        auto it2 = courses->begin();
        it2++;
        while (true) {
            if ((*it1)->name == c.name) {
                courses->erase(it1);
                break;
            }
            else if (it2 == courses->end()) {
                //course does not exist
                return;
            }
            it1++;
            it2++;
        }
    }
    int& semCreds = get<0>(sem);
    float& semGPA = get<1>(sem);
    int& overCreds = get<0>(*DB[id]);
    float& overGPA = get<1>(*DB[id]);
    float semUnscaledGPA = semGPA * (float)semCreds;
    float overUnscaledGPA = overGPA * (float)overCreds;
    semUnscaledGPA -= c.getGPA() * c.credits;
    semCreds -= c.credits;
    semGPA = semUnscaledGPA / (float)semCreds;
    overUnscaledGPA -= c.getGPA() * c.credits;
    overCreds -= c.credits;
    overGPA = overUnscaledGPA / (float)overCreds;
}

void print_student_semester_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id) {
    if (DB.find(id) == DB.end()) {
        //student to print does not exist
        return;
    }
    auto& semMap = get<2>(*DB[id]);
    if (semMap == nullptr) {
        //semester map does not exists
        return;
    }
    if (semMap->find(semester) == semMap->end()) {
        //semester does not exist
        return;
    }
    auto& sem = (*semMap)[semester];
    cout << "ID: " << id << endl;
    cout << "Semester: " << semester << endl;
    cout << sem << endl << endl;

}
void print_student_all_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
    if (DB.find(id) == DB.end()) {
        //student to print does not exist
        return;
    }
    auto& overCreds = get<0>(*DB[id]);
    auto& overGPA = get<1>(*DB[id]);
    auto& semMap = get<2>(*DB[id]);
    if (semMap == nullptr) {
        //semester map does not exists
        return;
    }
    cout << "ID: " << id << endl;
    cout << "Overall GPA: " << overGPA << endl;
    cout << "Overall Credits: " << overCreds << endl;
    cout << *semMap << endl;
}