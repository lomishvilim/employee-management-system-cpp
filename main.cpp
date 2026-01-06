#include "employee_management.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// function to help validating
template<typename T>
T getValidInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid input, try again\n";
    }
}

// helper function for displaying
void printEmployeeDetails(const Employee* emp) {
    cout << "\nEmployee details:"
              << "\nname: " << emp->getName()
              << "\nID: " << emp->getEmployeeId()
              << "\nexperience: " << emp->getExperience() << " months"
              << "\nsalary: $" << fixed << setprecision(2) << emp->getSalary()
              << endl;
}

int main() {
    try {
        EmployeePriorityQueue employeeQueue;

        cout << "--testing begins--\n";
        cout << "creating+adding 10 employees:\n\n";

        // 1: Cio
        cout << "1: Creating and adding CIO\n";
        CIO* cio = new CIO("John Smith", 1001, 60);
        printEmployeeDetails(cio);
        employeeQueue.insert(cio);
        cout << "\npriority queue after 1:\n";
        employeeQueue.print();

        // 2: PM
        cout << "\n2: Creating and adding PM\n";
        ProjectManager* pm = new ProjectManager("Jane Doe", 1002, 48);
        printEmployeeDetails(pm);
        employeeQueue.insert(pm);
        cout << "\npriority queue after step 2:\n";
        employeeQueue.print();

        //  3: backend dev
        cout << "\n 3: Creating and adding Senior backend dev\n";
        BackendDeveloper* bd1 = new BackendDeveloper("John Mchedeli", 1003, 36,
            QualificationLevel::SENIOR, BackendTechnology::NET);
        printEmployeeDetails(bd1);
        employeeQueue.insert(bd1);
        cout << "\npriority queue after step 3:\n";
        employeeQueue.print();

        //  4: middle backend dev
        cout << "\n 4: Creating and adding Middle backend dev\n";
        BackendDeveloper* bd2 = new BackendDeveloper("Chemi Kurseli", 1004, 24,
            QualificationLevel::MIDDLE, BackendTechnology::SPRING);
        printEmployeeDetails(bd2);
        employeeQueue.insert(bd2);
        cout << "\npriority queue after step 4:\n";
        employeeQueue.print();

        //  5: Sr. frontend dev
        cout << "\n 5: Creating and adding Senior frontend dev\n";
        FrontendDeveloper* fd1 = new FrontendDeveloper("Boo boba", 1005, 30,
            QualificationLevel::SENIOR, FrontendTechnology::REACT);
        printEmployeeDetails(fd1);
        employeeQueue.insert(fd1);
        cout << "\npriority queue after step 5:\n";
        employeeQueue.print();

        //  6: Junior drontend dev
        cout << "\n 6: Creating and adding Junior drontend dev\n";
        FrontendDeveloper* fd2 = new FrontendDeveloper("Shrek Movie", 1006, 18,
            QualificationLevel::JUNIOR, FrontendTechnology::ANGULAR);
        printEmployeeDetails(fd2);
        employeeQueue.insert(fd2);
        cout << "\npriority queue after step 6:\n";
        employeeQueue.print();

        //  7: senior database eng
        cout << "\n 7: Creating and adding Senior database engineer\n";
        DatabaseEngineer* dbe = new DatabaseEngineer("Rob Banks", 1007, 42,
            QualificationLevel::SENIOR);
        printEmployeeDetails(dbe);
        employeeQueue.insert(dbe);
        cout << "\npriority queue after step 7:\n";
        employeeQueue.print();

        //  8: Create and add devops eng
        cout << "\n 8: Creating and adding Middle DevOps engineer\n";
        DevOpsEngineer* devops = new DevOpsEngineer("Research paper", 1008, 36,
            QualificationLevel::MIDDLE);
        printEmployeeDetails(devops);
        employeeQueue.insert(devops);
        cout << "\npriority queue after step 8:\n";
        employeeQueue.print();

        //  9: Create and add tester
        cout << "\n 9: Creating and adding Middle tester\n";
        Tester* tester1 = new Tester("Harry Styles", 1009, 24,
            QualificationLevel::MIDDLE);
        printEmployeeDetails(tester1);
        employeeQueue.insert(tester1);
        cout << "\npriority queue after step 9:\n";
        employeeQueue.print();

        //  10: Create and add another tester to reach 10
        cout << "\n 10: Creating and adding Junior tester\n";
        Tester* tester2 = new Tester("Final Exams", 1010, 12,
            QualificationLevel::JUNIOR);
        printEmployeeDetails(tester2);
        employeeQueue.insert(tester2);
        cout << "\npriority queue after step 10:\n";
        employeeQueue.print();


        // tests round 2
        cout << "\n--testing priority queue functions--\n";

        // peek (just look at highest paid)
        cout << "\nPeeking at highest paid employee:\n";
        Employee* topEmployee = employeeQueue.peek();
        if (topEmployee) {
            printEmployeeDetails(topEmployee);
        }

        // extractMax = peek + pop
        cout << "\nRemoving the highest paid employee:\n";
        Employee* highestPaid = employeeQueue.extractMax();
        if (highestPaid) {
            printEmployeeDetails(highestPaid);
            cout << "\nPriority queue after extraction:\n";
            employeeQueue.print();
            delete highestPaid;
        }


        // cin tetsing -- add an employee from input
        cout << "Add a new backend developer yourself.\n";

        string name;
        cout << "Enter employee's name: ";
        getline(cin, name);

        int id = getValidInput<int>("Enter employee'd ID: ");
        int experience = getValidInput<int>("Enter employee's experience in months: ");

        int levelChoice = getValidInput<int>(
            "Enter level (0 junior, 1 middle, 2 senior): ");
        QualificationLevel level = static_cast<QualificationLevel>(levelChoice);

        int techChoice = getValidInput<int>(
            "Enter technology (0 .NET, 1 Spring, 2 Django): ");
        BackendTechnology tech = static_cast<BackendTechnology>(techChoice);

        try {
            BackendDeveloper* newDev = new BackendDeveloper(name, id, experience, level, tech);
            employeeQueue.insert(newDev);
            cout << "\nnewest employee added successfully!\n";
            printEmployeeDetails(newDev);
            cout << "\nFINAL priority queue after adding new employee:\n";
            employeeQueue.print();
        }
        catch (const exception& e) {
            cout << "Error adding employee: " << e.what() << endl;
        }

        // testing ERROR HANDLING
        cout << "\n--testing ERROR HANDLING--\n";

        try {
            cout << "Trying to create an employee with an invalid ID...\n";
            CIO* invalidCIO = new CIO("invalid", -1, 12);
            delete invalidCIO;
        }
        catch (const exception& e) {
            cout << "caught expected error: " << e.what() << endl;
        }

        try {
            cout << "Trying to create an employee with an invalid experience...\n";
            ProjectManager* invalidPM = new ProjectManager("Invalid", 9999, -6);
            delete invalidPM;
        }
        catch (const exception& e) {
            cout << "caught expected error: " << e.what() << endl;
        }

        // Final output
        cout << "(actual) final priority queue contents:\n";
        employeeQueue.print();

    }
    catch (const exception& e) {
        cout << "program terminated due to an error: " << e.what() << endl;
        return 1;
    }

    cout << "\ntesting finished!\n";
    return 0;
}