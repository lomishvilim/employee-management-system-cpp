#include "employee_management.h"
using namespace std;

#include <algorithm>
#include <stdexcept>
#include <iomanip>


// base Employee class
Employee::Employee(const string& name, int id, EmployeeClass eClass, int experience)
    : name(name), employeeId(id), employeeClass(eClass), salary(0.0), experienceMonths(experience) {
    //invalid input handling
    if (name.empty()) {
        throw invalid_argument("Employee name cant be empty");
    }
    if (id <= 0) {
        throw invalid_argument("Employee id cant be negative");
    }
    if (experience < 0) {
        throw invalid_argument("experience cannot be negative");
    }
}

// qualified employees' base class, which is a child/derivation of Employee
QualifiedEmployee::QualifiedEmployee(const string& name, int id, EmployeeClass eClass, 
                                   int experience, QualificationLevel level)
    : Employee(name, id, eClass, experience), qualificationLevel(level) {}

// helper functions for salary calculator function

    double getQualificationMultiplier(QualificationLevel level) {
        switch (level) {
            case QualificationLevel::JUNIOR: return 1.0;
            case QualificationLevel::MIDDLE: return 1.50;
            case QualificationLevel::SENIOR: return 2.0;
            default: return 1.0;
        }
    }

    double getExperienceBonus(int months) {
        return 1.0 + (months / 12.0) * 0.10; // 10% bonus a year
    }


//specific employee types, starting business

//CIO just uses Employee constructor, and I manually enter CIO for eclass -- enums turned out to be just extra work..
CIO::CIO(const string& name, int id, int experience)
    : Employee(name, id, EmployeeClass::CIO, experience) {
    salary = calculateSalary();
}

// hardcoded common salaries into each override
double CIO::calculateSalary() {
    const double baseSalary = 15000.0;
    return baseSalary * getExperienceBonus(getExperience()); //getExperience() gives months
}

// PM is also only a child of employee
ProjectManager::ProjectManager(const string& name, int id, int experience)
    : Employee(name, id, EmployeeClass::PM, experience) {
    salary = calculateSalary();
}

double ProjectManager::calculateSalary() {
    const double baseSalary = 10000.0;
    return baseSalary * getExperienceBonus(getExperience());
}

//developers
//children of both QualifiedEmployee and EMployee

BackendDeveloper::BackendDeveloper(const string& name, int id, int experience,
                                 QualificationLevel level, BackendTechnology tech)
    : QualifiedEmployee(name, id, EmployeeClass::BD, experience, level), technology(tech) {
    salary = calculateSalary();
}

double BackendDeveloper::calculateSalary() {
    const double baseSalary = 7000.0;
    double techBonus = 1.0;
    
    // bonuses are offered based on which tech skills u have
    switch (technology) {
        case BackendTechnology::NET: techBonus = 1.15; break;
        case BackendTechnology::SPRING: techBonus = 1.10; break;
        case BackendTechnology::DJANGO: techBonus = 1.05; break;
    }
    //final salary calculation
    return baseSalary * 
           getQualificationMultiplier(qualificationLevel) * 
           getExperienceBonus(getExperience()) * 
           techBonus;
}


FrontendDeveloper::FrontendDeveloper(const string& name, int id, int experience,
                                   QualificationLevel level, FrontendTechnology tech)
    : QualifiedEmployee(name, id, EmployeeClass::FD, experience, level), technology(tech) {
    salary = calculateSalary();
}

double FrontendDeveloper::calculateSalary() {
    const double baseSalary = 6500.0; //frontend < backend 0o0
    double techBonus = 1.0;
    
    //bonuses are offered based on which tech skills u have
    switch (technology) {
        case FrontendTechnology::REACT: techBonus = 1.15; break;
        case FrontendTechnology::ANGULAR: techBonus = 1.10; break;
        case FrontendTechnology::VUE: techBonus = 1.05; break;
    }
    
    return baseSalary * 
           getQualificationMultiplier(qualificationLevel) * 
           getExperienceBonus(getExperience()) * 
           techBonus;
}


// engineers, similar to devs, except no tech skill bonuses
DatabaseEngineer::DatabaseEngineer(const string& name, int id, int experience,
                                 QualificationLevel level)
    : QualifiedEmployee(name, id, EmployeeClass::DB, experience, level) {
    salary = calculateSalary();
}

double DatabaseEngineer::calculateSalary() {
    const double baseSalary = 8000.0;
    return baseSalary * 
           getQualificationMultiplier(qualificationLevel) * 
           getExperienceBonus(getExperience());
}


DevOpsEngineer::DevOpsEngineer(const string& name, int id, int experience,
                              QualificationLevel level)
    : QualifiedEmployee(name, id, EmployeeClass::DE, experience, level) {
    salary = calculateSalary();
}

double DevOpsEngineer::calculateSalary() {
    const double baseSalary = 7500.0;
    return baseSalary * 
           getQualificationMultiplier(qualificationLevel) * 
           getExperienceBonus(getExperience());
}


Tester::Tester(const string& name, int id, int experience,
               QualificationLevel level)
    : QualifiedEmployee(name, id, EmployeeClass::TST, experience, level) {
    salary = calculateSalary();
}

double Tester::calculateSalary() {
    const double baseSalary = 5500.0;
    return baseSalary * 
           getQualificationMultiplier(qualificationLevel) * 
           getExperienceBonus(getExperience());
}


// priority Queue
EmployeePriorityQueue::~EmployeePriorityQueue() {
    for (Employee* emp : employees) {
        delete emp;
    }
    employees.clear(); //fully clear the queue
}

void EmployeePriorityQueue::insert(Employee* employee) {
    if (!employee) {
        throw invalid_argument("can't insert null employee");
    }
    
    //check for duplicates in id s
    auto it = find_if(employees.begin(), employees.end(),
        [employee](const Employee* emp) {
            return emp->getEmployeeId() == employee->getEmployeeId();
        });
    //if we didn't get to the last id (without returning), then we found a duplicate
    if (it != employees.end()) {
        throw invalid_argument("employee with this ID already exists");
    }
    employees.push_back(employee);
    
    // maintain the priority based on the salary
    push_heap(employees.begin(), employees.end(),
        [](const Employee* a, const Employee* b) {
            return a->getSalary() < b->getSalary();
        });
}

//pop/remove employee with biggest salary
Employee* EmployeePriorityQueue::extractMax() {
    if (employees.empty()) {
        return nullptr;
    }
    
    pop_heap(employees.begin(), employees.end(),
        [](const Employee* a, const Employee* b) {
            return a->getSalary() < b->getSalary();
        });
    
    Employee* maxEmployee = employees.back();
    employees.pop_back();
    return maxEmployee;
}
//only peek the biggest salary person, don't pop
Employee* EmployeePriorityQueue::peek() const {
    if (employees.empty()) {
        return nullptr;
    }
    return employees.front();
}


//remove an employee based on their id number
void EmployeePriorityQueue::remove(int employeeId) {
    auto it = find_if(employees.begin(), employees.end(),
        [employeeId](const Employee* emp) {
            return emp->getEmployeeId() == employeeId;
        });
    
    if (it == employees.end()) { //reached end, nothing matched
        throw invalid_argument("employee not found");
    }
    
    delete *it;
    employees.erase(it);
    
    // rebuild the peiority queue after removal
    make_heap(employees.begin(), employees.end(),
        [](const Employee* a, const Employee* b) {
            return a->getSalary() < b->getSalary();
        });
}

//display fucntion
void EmployeePriorityQueue::print() const {
    if (employees.empty()) {
        cout << "priority queue is empty" << endl;
        return;
    }
    
    cout << "\nEmployee priority queue (salary):\n";
    cout << setw(5) << "ID" << setw(20) << "name"
              << setw(15) << "salary" << setw(15) << "exp\n";
    cout << string(55, '-') << endl;
    
    // create a copy of the vector to sort without modifying the original heap
    vector<Employee*> sortedEmployees = employees;

    sort(sortedEmployees.begin(), sortedEmployees.end(),
        [](const Employee* a, const Employee* b) {
            return a->getSalary() > b->getSalary();
        });
    
    for (const Employee* emp : sortedEmployees) {
        cout << setw(5) << emp->getEmployeeId()
                  << setw(20) << emp->getName()
                  << setw(15) << fixed << setprecision(2) << emp->getSalary()
                  << setw(15) << emp->getExperience() << " months\n";
    }
    cout << endl;
}