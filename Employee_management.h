#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

using namespace std;

#include <string>
#include <iostream>
#include <vector>

//enum for employee types
enum class EmployeeClass {
    CIO,    // chief info officer
    PM,     // project manager
    BD,     // backend dev
    FD,     // frontend dev
    DB,     // database eng
    DE,     // Devops eng
    TST     // testers
};

// qualification levels  - developers, engineers, testers
enum class QualificationLevel {
    JUNIOR,
    MIDDLE,
    SENIOR
};

// possible  backend technologies
enum class BackendTechnology {
    NET,
    SPRING,
    DJANGO
};

// possible frontend technologies
enum class FrontendTechnology {
    ANGULAR,
    REACT,
    VUE
};

// abstract base class Employee
class Employee {
protected:
    string name;
    int employeeId;
    EmployeeClass employeeClass; //using enums
    double salary;
    int experienceMonths;

public:
    // explicit constructor.  when used by a child class, you manually enter the eClass yourself
    Employee(const string& name, int id, EmployeeClass eClass, int experience);
    
    // pure virtual function to allow for overriding //=0 forces child classes to override
    //salary calculations need to be overriden bc different people get different base/bonus salary
    virtual double calculateSalary() = 0;
    
    // getters, inline implementations bc they're short
    string getName() const { return name; }
    int getEmployeeId() const { return employeeId; }
    EmployeeClass getEmployeeClass() const { return employeeClass; }
    double getSalary() const { return salary; }
    int getExperience() const { return experienceMonths; }
    
    //destructor needs to be virtual so children also clean fully
    virtual ~Employee() = default;
};

// base for employees with qualification levels, so they're children of both this and Employee
class QualifiedEmployee : public Employee {
protected:
    QualificationLevel qualificationLevel;

public:
    QualifiedEmployee(const string& name, int id, EmployeeClass eClass, 
                     int experience, QualificationLevel level);
    
    QualificationLevel getQualificationLevel() const { return qualificationLevel; }
};

// now specific employee types

class CIO : public Employee {
public:
    CIO(const string& name, int id, int experience);
    virtual double calculateSalary() override; //as said, different  versions of salary calc are needed
};

class ProjectManager : public Employee {
public:
    ProjectManager(const string& name, int id, int experience);
    virtual double calculateSalary() override;
};


//children of QualifiedEmployee, therefore Employee too
class BackendDeveloper : public QualifiedEmployee {
private:
    BackendTechnology technology; //technology types backend can have

public:
    BackendDeveloper(const string& name, int id, int experience,
                    QualificationLevel level, BackendTechnology tech);
    virtual double calculateSalary() override;
    BackendTechnology getTechnology() const { return technology; }
};

class FrontendDeveloper : public QualifiedEmployee {
private:
    FrontendTechnology technology; //technology types frontend can have

public:
    FrontendDeveloper(const string& name, int id, int experience,
                     QualificationLevel level, FrontendTechnology tech);
    virtual double calculateSalary() override;
    FrontendTechnology getTechnology() const { return technology; }
};




class DatabaseEngineer : public QualifiedEmployee {
public:
    DatabaseEngineer(const string& name, int id, int experience,
                    QualificationLevel level);
    virtual double calculateSalary() override;
};

class DevOpsEngineer : public QualifiedEmployee {
public:
    DevOpsEngineer(const string& name, int id, int experience,
                   QualificationLevel level);
    virtual double calculateSalary() override;
};

class Tester : public QualifiedEmployee {
public:
    Tester(const string& name, int id, int experience,
           QualificationLevel level);
    virtual double calculateSalary() override;
};



// create a priority queue for ranking and storing  employees on salary
class EmployeePriorityQueue {
private:
    vector<Employee*> employees;

public:
    //construct, destruct
    EmployeePriorityQueue() = default;
    ~EmployeePriorityQueue();

    //basic priority queue functionality
    void insert(Employee* employee);
    Employee* extractMax();
    Employee* peek() const;
    void remove(int employeeId);
    
    // utility
    bool isEmpty() const { return employees.empty(); }
    size_t size() const { return employees.size(); }
    void print() const;
    
    // we do NOT need these, so they're deleted to avoid shallow copy memory issues as we're not using/handling these cases
    EmployeePriorityQueue(const EmployeePriorityQueue&) = delete;
    EmployeePriorityQueue& operator=(const EmployeePriorityQueue&) = delete;
};

#endif