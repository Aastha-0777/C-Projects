/* ==========================================================================
 * Project: In-Memory Employee Management System (EMS)
 * Author: Aastha M. Lakhatariya
 * Description: A robust console-based system applying enterprise-level
 *              business logic, data validation, and analytics in C.
 * ==========================================================================
 *
 * MODULES & BUSINESS LOGIC TO IMPLEMENT:
 *
 * 1. STRUCT & DATA MODEL:
 *    - Define an 'Employee' struct containing:
 *      * int id (Primary Key - must be unique)
 *      * char name[50] (Employee full name)
 *      * float salary (Compensation - must be positive)
 *      * int age (Demographic data - must be within realistic bounds)
 *
 * 2. DATA INTEGRITY & UNIQUE CONSTRAINTS (Primary Key Validation):
 *    - Function: int isDuplicateID(int id, struct Employee emp[], int count)
 *    - Rule: Before inserting any new record, scan existing records.
 *      If the ID already exists, reject the entry and alert the user.
 *
 * 3. STRICT INPUT VALIDATION:
 *    - Rule: Validate all user inputs.
 *    - Check for negative salaries, invalid ages, and empty name strings.
 *      Prompt the user to re-enter if validation fails.
 *
 * 4. ANALYTICS & REPORTING DASHBOARD:
 *    - Function: void displayAnalytics(struct Employee emp[], int count)
 *    - Metrics to calculate and display:
 *      * Total headcount (active records)
 *      * Average salary across all employees
 *      * Identify and display the highest-paid employee
 *
 * 5. ADVANCED SORTING & FILTERING:
 *    - Function: void sortEmployees(struct Employee emp[], int count, int choice)
 *    - Rule: Implement a sorting algorithm (e.g., Bubble Sort) allowing
 *      managers to sort records by ID, alphabetically by Name, or by Salary.
 *
 * 6. GRACEFUL CAPACITY & STATE MANAGEMENT:
 *    - Rule: Maintain a max capacity constant (e.g., MAX_EMPLOYEES = 100)
 *      and track the current count. If full, print a clean warning message
 *      instead of letting the program crash.
 *
 *
 *  ==================================================
 *         EMPLOYEE MANAGEMENT SYSTEM
 *  ==================================================
 *   1. Add New Employee
 *   2. View All Employee Records
 *   3. Search Employee by ID
 *   4. Sort Employees (by ID, Name, or Salary)
 *   5. View Analytics & Summary Report
 *   6. Delete/Remove Employee Record
 *   7. Exit Program
 *  ==================================================
 *  Enter your choice (1-7):
 *
 * ==========================================================================
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMPLOYEES 100

struct Employee
{

    int id;
    char name[50];
    float salary;
    int age;
    int active;
};

struct Employee empList[MAX_EMPLOYEES]; // to store the employees
int empCounter = 0;                     // to count and make a track of total nos. of employees
int activeEmpCounter = 0;               // to count the active employees

int getIdxById(int id);     // to get the idx by provided employee ID
void addNewEmp();           // to add one new emp at a time
void displayByIdx(int idx); // to display one employee at a time by its index
void viewAllEmp();          // to display all the active employees
void searchEmpById();       // to search a perticular employee at a time by it's ID
void sortById();            // to sort every employee by it's ID using bubble sort
void sortByName();          // to sort every employee by it's Name using bubble sort
void sortBySalary();        // to sort every employee by it's Salary using bubble sort
void viewAnalSummReport();  // to display the anual summary report
void deleteEmployeeById();  // to delete a perticular employee at a time by it's ID

int main()
{

    int choice;

    do
    {

        printf("------------------------------------------------------------\n");
        printf("\t\tEMPLOYEE MANAGEMENT SYSTEM\n");
        printf("------------------------------------------------------------\n");
        printf("1. Add New Employee\n");
        printf("2. View All Employee Records\n");
        printf("3. Search Employee by ID\n");
        printf("4. Sort Employees (by ID, Name, or Salary)\n");
        printf("5. View Analytics & Summary Report\n");
        printf("6. Delete/Remove Employee Record\n");
        printf("7. Exit Program\n");
        printf("------------------------------------------------------------\n");
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;        // throw away the bad input
            choice = -1; // lands in the 'default' message
        }

        switch (choice)
        {

        case 1:
            addNewEmp();
            break;
        case 2:
            viewAllEmp();
            break;
        case 3:
            searchEmpById();
            break;
        case 4:
            //  created another menu for sorting option i.e. (by ID, Name, or Salary)

            int sortChoice;

            printf("\t-----------SORT MENU -----------\n");
            printf("\t1. Sort by ID\n");
            printf("\t2. Sort by Name\n");
            printf("\t3. Sort by Salary\n");
            printf("\t4. Return Back to Main Menu\n");
            printf("\tEnter your choice (1-4): ");
            scanf("%d", &sortChoice);

            switch (sortChoice)
            {

            case 1:
                sortById();
                break;
            case 2:
                sortByName();
                break;
            case 3:
                sortBySalary();
                break;
            case 4:
                break;
            default:
                printf("\tPlease Enter Choice b/w (1-4).\n");

            } // end of sorting switch-case

            break;
        case 5:
            viewAnalSummReport();
            break;
        case 6:
            deleteEmployeeById();
            break;
        case 7:
            printf("Exting the Employee Management System....\n");
            exit(0);
            break;
        default:
            printf("Please Enter Choice b/w 1-7.\n");

        } // end of switch-case

    } while (choice != 0);

} // end of main

int getIdxById(int id)
{

    // checks if the ID is present

    for (int i = 0; i < empCounter; i++)
    {

        if (empList[i].id == id)
        {

            // if present than return the index i
            return i;
        }

    } // end of for

    // else return -1 which represent no index i.e. not present in the list
    return -1;

} // end of getIdxById

void addNewEmp()
{

    if (empCounter >= MAX_EMPLOYEES)
    {
        printf("The Employee List is Full (max %d). Delete a record first.\n", MAX_EMPLOYEES);
        return;
    }

    printf("----------- ADD NEW EMPLOYEE -----------\n");
    struct Employee e;

    e.active = 1;

    printf("Enter the Employee's ID : ");
    scanf("%d", &e.id);
    // checks is ID valid or not
    if (e.id <= 0)
    {

        printf("Please Provide a Valid ID.\n");
        return;

    } // end of if
    if (getIdxById(e.id) == -1)
    {

        if (e.active)
        {

            activeEmpCounter++;
        }
        printf("Enter the Employee's Name : ");
        scanf(" %[^\n]", e.name);
        printf("Enter the Employee's Age : ");
        scanf("%d", &e.age);
        // checks is age valid or not
        if (e.age <= 0 || e.age >= 80)
        {

            printf("Please Provide a Valid Age.\n");
            return;

        } // end of if
        printf("Enter the Employee's Salary : ");
        scanf("%f", &e.salary);
        // checks is salary valid or not
        if (e.salary <= 0)
        {

            printf("Please Provide a Valid Salary.\n");
            return;

        } // end of if

        empList[empCounter] = e;
        empCounter++;

        printf("Employee Added Successfully!!\n");
    }
    else
    {

        printf("ID %d already Exits in the Employee List.\n", e.id);
    }

} // end of addNewEmp

void displayByIdx(int idx)
{

    // if the idx is valid i.e. id is present in the employee list
    if (idx >= 0)
    {

        // only display if the employee is active
        if (empList[idx].active)
        {

            printf("| Id : %d  Name : %s Age : %d Salary : %.2f |\n", empList[idx].id, empList[idx].name, empList[idx].age, empList[idx].salary);
        }
    }
    else
    {

        printf("Employee with at Index %d Is Not Present in the Employee List.\n", idx);

    } // end of outer if-else

} // end of displayByIdx

void viewAllEmp()
{

    printf("------------- ALL ACTIVE EMPLOYEE'S RECORD -------------\n");

    for (int i = 0; i < empCounter; i++)
    {

        displayByIdx(i);

    } // end of for

} // end of viewAllEmp

void searchEmpById()
{

    int id;

    printf("Enter the Employee's Id You want to Search : ");
    scanf("%d", &id);

    int idx = getIdxById(id);

    // if the idx is valid i.e. id is present in the employee list
    if (idx != -1)
    {

        // only display if the employee is active
        if (empList[idx].active)
        {

            printf("| Id : %d  Name : %s Age : %d Salary : %.2f |\n", id, empList[idx].name, empList[idx].age, empList[idx].salary);
        }
        else
        {

            printf("Employee with ID %d Is Not Active.\n", id);
        } // end of inner if-else
    }
    else
    {

        printf("Employee with ID %d Is Not Present in the Employee List.\n", id);

    } // end of outer if-else

} // end of searchEmpById

void viewAnalSummReport()
{

    if (empCounter == 0)
    {

        printf("The Employee List Is Empty!!\n");
    }
    else
    {

        float avgSalary, totalSalary = 0;
        printf("---------------- ANUAL SUMMARY REPROT ----------------\n");
        printf("Total headcount (active records) : %d\n", activeEmpCounter);

        // counting avg salary and highest paid employee
        struct Employee highestPaidEmp = empList[0];
        int idx;
        for (int i = 0; i < empCounter; i++)
        {
            totalSalary += empList[i].salary;

            if (empList[i].salary > highestPaidEmp.salary)
            {

                highestPaidEmp = empList[i];
                idx = i;

            } // end of if

        } // end of for

        // counted the avg salary
        avgSalary = totalSalary / empCounter;

        printf("Average salary across all employees : %.2f\n", avgSalary);
        printf("------ HIGHEST PAID EMPLOYEE DETAILS ------\n");
        displayByIdx(idx);
    }

} // end of viewAnalSummReport

void sortById()
{

    int exchange;

    for (int i = 0; i < empCounter; i++)
    {

        exchange = 0;

        for (int j = 0; j < empCounter - 1 - i; j++)
        {

            if (empList[j].id > empList[j + 1].id)
            {

                struct Employee temp = empList[j];
                empList[j] = empList[j + 1];
                empList[j + 1] = temp;
                exchange = 1;

            } // end of if

        } // end of inner for

        if (!exchange)
        {
            printf("The Employee List is Sorted By ID Successfully.\n");
            return;
        } // end of outer if

    } // end of outter for

    printf("The Employee List is Sorted By ID Successfully.\n");

} // end of sortById

void sortByName()
{

    int exchange;

    for (int i = 0; i < empCounter; i++)
    {

        exchange = 0;

        for (int j = 0; j < empCounter - 1 - i; j++)
        {

            if (strcmp(empList[j].name, empList[j + 1].name) > 0)
            {

                struct Employee temp = empList[j];
                empList[j] = empList[j + 1];
                empList[j + 1] = temp;
                exchange = 1;

            } // end of if

        } // end of inner for

        if (!exchange)
        {
            printf("The Employee List is Sorted By Name Successfully.\n");
            return;
        } // end of outer if

    } // end of outter for

    printf("The Employee List is Sorted By Name Successfully.\n");

} // end of sortByName

void sortBySalary()
{

    int exchange;

    for (int i = 0; i < empCounter; i++)
    {

        exchange = 0;

        for (int j = 0; j < empCounter - 1 - i; j++)
        {

            if (empList[j].salary > empList[j + 1].salary)
            {

                struct Employee temp = empList[j];
                empList[j] = empList[j + 1];
                empList[j + 1] = temp;
                exchange = 1;

            } // end of if

        } // end of inner for

        if (!exchange)
        {
            printf("The Employee List is Sorted By Salary Successfully.\n");
            return;
        } // end of outer if

    } // end of outter for

    printf("The Employee List is Sorted By Salary Successfully.\n");

} // end of sortBySalary

void deleteEmployeeById()
{

    int id, idx;

    printf("Enter the Employee's ID Whome You wnat to Delete : ");
    scanf("%d", &id);

    idx = getIdxById(id);

    if (idx != -1)
    {

        for (int i = idx; i < empCounter; i++)
        {

            empList[i] = empList[i + 1];

        } // end of for

        empCounter--;
        activeEmpCounter--;

        printf("Employee with ID %d Deleted Successfully!!\n", id);
    }
    else
    {

        printf("Employee With ID %d Does not Exits in the Employee List.\n", id);
    }

} // end of deleteEmployeeById