#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_EMPLOYEES 100
#define MAX_TASKS 1000

typedef struct {
    int ID;
    int dateDay;
    int dateMonth;
    int dateYear;
    int hour;
    int minutes;
    char description[105];
    int regularity; //0 - One-off   1 - Monthly
    int state; //0 - Open   1 - Completed  2 = ???
    int employeeID;
    int slotAvailability; //0 - empty     1 - filled
}Task;
Task tasks[MAX_TASKS];
int taskLastID;

typedef struct {
    int ID;
    char name[50];
    int dateBirthDay;
    int dateBirthMonth;
    int dateBirthYear;
    int contactNumberSet1;
    int contactNumberSet2;
    int contactNumberSet3;
    char email[50];
    char residence[25];
    char department[15];
    int slotAvailability; //0 - empty     1 - filled
}Employee;
Employee employees[MAX_EMPLOYEES];
int employeeLastID;

void date() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}
void initializeStructsEmployees() {
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        employees[i].slotAvailability = 0;
    }
}
void initializeStructsTasks() {
    for (int i = 0; i < MAX_TASKS; ++i) {
        tasks[i].slotAvailability = 0;
        tasks[i].state = 2;
    }
}
void initializeStructs() {
    initializeStructsEmployees();
    initializeStructsTasks();
}
void initializeIDs() {
    taskLastID = 0;
    employeeLastID = 0;
}
void initializeFiles() {
    FILE* employeesFile;
    FILE* employeesLastIDFile;
    FILE* tasksFile;
    FILE* tasksLastIDFile;

    employeesFile = fopen("employees.txt", "a");
    employeesLastIDFile = fopen("employees-last-id.txt", "a");
    tasksFile = fopen("tasks.txt", "a");
    tasksLastIDFile = fopen("tasks-last-id.txt", "a");

    if (employeesLastIDFile == NULL || employeesFile == NULL || tasksLastIDFile == NULL || tasksFile == NULL) {
        printf("Error");
        exit(1);
    }

    fclose(employeesFile);
    fclose(employeesLastIDFile);
    fclose(tasksFile);
    fclose(tasksLastIDFile);
}
void loadEmployeeFiles() {
    FILE* employeesFile;
    FILE* employeesLastIDFile;

    employeesFile = fopen("employees.txt", "r");
    employeesLastIDFile = fopen("employees-last-id.txt", "r");

    if (employeesFile == NULL && employeesLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }
    if (employeesFile == NULL || employeesLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }

    fscanf(employeesLastIDFile, "%d", &employeeLastID);

    fclose(employeesLastIDFile);

    while (!feof(employeesFile)) {
        for (int i = 0; i < MAX_EMPLOYEES; ++i) {
            fscanf(employeesFile, "%d\n", &employees[i].ID);
            fscanf(employeesFile, " %[^\n]", employees[i].name);
            fscanf(employeesFile, "%d\n", &employees[i].dateBirthDay);
            fscanf(employeesFile, "%d\n", &employees[i].dateBirthMonth);
            fscanf(employeesFile, "%d\n", &employees[i].dateBirthYear);
            fscanf(employeesFile, "%d\n", &employees[i].contactNumberSet1);
            fscanf(employeesFile, "%d\n", &employees[i].contactNumberSet2);
            fscanf(employeesFile, "%d\n", &employees[i].contactNumberSet3);
            fscanf(employeesFile, " %[^\n]", employees[i].email);
            fscanf(employeesFile, " %[^\n]", employees[i].residence);
            fscanf(employeesFile, " %[^\n]", employees[i].department);
            fscanf(employeesFile, "%d", &employees[i].slotAvailability);

        }
    }
}
void loadTaskFiles() {

    FILE* tasksFile;
    FILE* tasksLastIDFile;

    tasksFile = fopen("tasks.txt", "r");
    tasksLastIDFile = fopen("tasks-last-id.txt", "r");

    if (tasksFile == NULL && tasksLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }
    if (tasksFile == NULL || tasksLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }

    fscanf(tasksLastIDFile, "%d", &taskLastID);

    fclose(tasksLastIDFile);

    while (!feof(tasksFile)) {
        for (int i = 0; i < MAX_TASKS; ++i) {
            fscanf(tasksFile, "%d\n", &tasks[i].ID);
            fscanf(tasksFile, "%d\n", &tasks[i].dateDay);
            fscanf(tasksFile, "%d\n", &tasks[i].dateMonth);
            fscanf(tasksFile, "%d\n", &tasks[i].dateYear);
            fscanf(tasksFile, "%d\n", &tasks[i].hour);
            fscanf(tasksFile, "%d\n", &tasks[i].minutes);
            fscanf(tasksFile, " %[^\n]", tasks[i].description);
            fscanf(tasksFile, "%d\n", &tasks[i].regularity);
            fscanf(tasksFile, "%d\n", &tasks[i].state);
            fscanf(tasksFile, "%d\n", &tasks[i].employeeID);
            fscanf(tasksFile, "%d\n", &tasks[i].slotAvailability);
        }
    }
}
void bootProtocol() {
    initializeStructs();
    initializeIDs();
    initializeFiles();
    loadEmployeeFiles();
    loadTaskFiles();
}
void saveEmployeeFiles() {
    FILE* employeesFile;
    FILE* employeesLastIDFile;

    employeesFile = fopen("employees.txt", "w");
    employeesLastIDFile = fopen("employees-last-id.txt", "w");

    if (employeesFile == NULL && employeesLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }
    if (employeesFile == NULL || employeesLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }

    fprintf(employeesLastIDFile, "%d", employeeLastID);

    fclose(employeesLastIDFile);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employees[i].slotAvailability == 1) {
            fprintf(employeesFile, "%d\n", employees[i].ID);
            fprintf(employeesFile, "%s\n", employees[i].name);
            fprintf(employeesFile, "%d\n", employees[i].dateBirthDay);
            fprintf(employeesFile, "%d\n", employees[i].dateBirthMonth);
            fprintf(employeesFile, "%d\n", employees[i].dateBirthYear);
            fprintf(employeesFile, "%d\n", employees[i].contactNumberSet1);
            fprintf(employeesFile, "%d\n", employees[i].contactNumberSet2);
            fprintf(employeesFile, "%d\n", employees[i].contactNumberSet3);
            fprintf(employeesFile, "%s\n", employees[i].email);
            fprintf(employeesFile, "%s\n", employees[i].residence);
            fprintf(employeesFile, "%s\n", employees[i].department);
            fprintf(employeesFile, "%d\n", employees[i].slotAvailability);
        }
    }

    fclose(employeesFile);
}
void saveTaskFiles() {
    FILE* tasksFile;
    FILE* tasksLastIDFile;

    tasksFile = fopen("tasks.txt", "w");
    tasksLastIDFile = fopen("tasks-last-id.txt", "w");

    if (tasksFile == NULL && tasksLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }
    if (tasksFile == NULL || tasksLastIDFile == NULL) {
        printf("Error");
        exit(1);
    }

    fprintf(tasksLastIDFile, "%d", taskLastID);

    fclose(tasksLastIDFile);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].slotAvailability == 1) {
            fprintf(tasksFile, "%d\n", tasks[i].ID);
            fprintf(tasksFile, "%d\n", tasks[i].dateDay);
            fprintf(tasksFile, "%d\n", tasks[i].dateMonth);
            fprintf(tasksFile, "%d\n", tasks[i].dateYear);
            fprintf(tasksFile, "%d\n", tasks[i].hour);
            fprintf(tasksFile, "%d\n", tasks[i].minutes);
            fprintf(tasksFile, "%s\n", tasks[i].description);
            fprintf(tasksFile, "%d\n", tasks[i].regularity);
            fprintf(tasksFile, "%d\n", tasks[i].state);
            fprintf(tasksFile, "%d\n", tasks[i].employeeID);
            fprintf(tasksFile, "%d\n", tasks[i].slotAvailability);
        }
    }

    fclose(tasksFile);
}
void exitProtocol() {
    saveEmployeeFiles();
    saveTaskFiles();
}
int countRegisteredTasks() {
    int counter = 0;
    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].slotAvailability == 1) {
            counter++;
        }
    }
    return counter;
}
int countEmptyTaskSlots() {
    int counter = 0;
    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].slotAvailability == 0) {
            counter++;
        }
    }
    return counter;
}
int findEmptyTaskSlot() {
    int index = 0;
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (tasks[i].slotAvailability == 0) {
            index = i;
            break;
        }
    }
    return index;
}
int employeeTaskCheck(int employeeID) {
    int counter = 0;
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        counter++;
        if (counter == MAX_EMPLOYEES) {
            return 1;
        } else if (employees[i].ID == employeeID) {
            return 0;
        }
    }
}
void newTask() {
    int taskCount = countRegisteredTasks();
    int i = findEmptyTaskSlot();
    int employeeID;
    int check;

    if (taskCount == MAX_TASKS) {
        printf("You have reached the maximum number of registered employees in the system\n");
        printf("Please contact support\n\n");
        system("pause");
    } else {
        system("cls");
        printf("### New Task Form ###\n\n");

        printf("Assign the task to an employee via ID: ");
        fflush(stdin);
        scanf("%d", &employeeID);

        check = employeeTaskCheck(employeeID);

        if (check == 1) {
            printf("\nEmployee's ID is invalid. Create a new task with a valid ID. ");
            system("pause");
            return;
        }

        taskLastID++;
        tasks[i].ID = taskLastID;

        printf("Task's description: ");
        fflush(stdin);
        gets(tasks[i].description);

        printf("Task's date (DD/MM/YYYY): ");
        fflush(stdin);
        scanf("%d/%d/%d", &tasks[i].dateDay, &tasks[i].dateMonth, &tasks[i].dateYear);

        printf("Task's hour (HH:MM): ");
        fflush(stdin);
        scanf("%d:%d", &tasks[i].hour, &tasks[i].minutes);

        printf("Task's regularity (0 --> One-off     1 --> Monthly): ");
        fflush(stdin);
        scanf("%d", &tasks[i].regularity);

        tasks[i].state = 0;

        tasks[i].employeeID = employeeID;

        tasks[i].slotAvailability = 1;

        printf("\n\nNew task registered in the system successfully. ");
        system("pause");
    }
}
void listTasks() {
    int emptyTaskSlots = countEmptyTaskSlots();
    system("cls");
    printf("### Full Task List ###\n\n");
    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].slotAvailability == 1) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: (ID: %d)\n\n\n", tasks[i].employeeID);




        } else if (emptyTaskSlots == MAX_TASKS) {
            printf("The list is empty\n\n");
            break;
        }
    }
    system("pause");
}
void deleteTask() {
    int taskID;

    system("cls");

    printf("### Deleting Task ###");

    printf("\n\nEnter the task's ID: ");
    fflush(stdin);
    scanf("%d", &taskID);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (taskID == tasks[i].ID) {
            tasks[i].slotAvailability = 0;
        }
    }
    printf("\nTask successfully deleted. ");
    system("pause");
}
void editTask() {
    int taskID;

    system("cls");

    printf("### Editing Task ###\n");

    printf("\nEnter the task's ID: ");
    fflush(stdin);
    scanf("%d", &taskID);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (taskID == tasks[i].ID) {
            system("cls");
            printf("### Editing Task ###\n\n");

            int employeeID;
            int check;

            printf("Assign the task to an employee via ID: ");
            fflush(stdin);
            scanf("%d", &employeeID);

            check = employeeTaskCheck(employeeID);
            if (check == 1) {
                printf("\nEmployee's ID is invalid. Edit the task with a valid ID. ");
                system("pause");
                return;
            }

            printf("Task's description: ");
            fflush(stdin);
            gets(tasks[i].description);

            printf("Task's date (DD/MM/YYY): ");
            fflush(stdin);
            scanf("%d/%d/%d", &tasks[i].dateDay, &tasks[i].dateMonth, &tasks[i].dateYear);

            printf("Task's hour (HH:MM): ");
            fflush(stdin);
            scanf("%d:%d", &tasks[i].hour, &tasks[i].minutes);

            printf("Task's regularity (0 - One-off     1 - Monthly): ");
            fflush(stdin);
            scanf("%d", &tasks[i].regularity);

            tasks[i].employeeID = employeeID;
        }

            printf("\n\nTask edited successfully. ");
            system("pause");
            break;
    }
}
void searchTaskByID() {
    int ID;

    printf("\nBy what ID would you like to search?: ");
    fflush(stdin);
    scanf("%d", &ID);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (ID == tasks[i].ID) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: %d\n\n\n", tasks[i].employeeID);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchTaskByDate() {
    int dateDay, dateMonth, dateYear;

    printf("\nBy what date would you like to search? (DD/MM/YYYY): ");
    fflush(stdin);
    scanf("%d/%d/%d", &dateDay, &dateMonth, &dateYear);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (dateDay == tasks[i].dateDay && dateMonth == tasks[i].dateMonth
            && dateYear == tasks[i].dateYear) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: %d\n\n\n", tasks[i].employeeID);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchTaskByHour() {
    int hour, minutes;

    printf("\nBy what hour would you like to search? (HH:MM): ");
    fflush(stdin);
    scanf("%d:%d", &hour, &minutes);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (hour == tasks[i].hour && minutes == tasks[i].minutes) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: %d\n\n\n", tasks[i].employeeID);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchTaskByDescription() {
    char description[120];

    printf("\nBy what e-mail would you like to search?: ");
    fflush(stdin);
    gets(description);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        char* check = strstr(tasks[i].description, description);
        if (check != NULL) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: %d\n\n\n", tasks[i].employeeID);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchTaskByEmployee() {
    int ID;

    printf("\nBy what employee ID would you like to search?: ");
    fflush(stdin);
    scanf("%d", &ID);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (ID == tasks[i].employeeID) {
            printf("Task ID: %d (Index: %d)\n", tasks[i].ID, i);
            printf("    - Date: %d/%d/%d\n", tasks[i].dateDay, tasks[i].dateMonth, tasks[i].dateYear);
            printf("    - Hour: %d:%d\n", tasks[i].hour, tasks[i].minutes);
            printf("    - Description: %s\n", tasks[i].description);
            printf("    - Regularity: ");

            if (tasks[i].regularity == 1) {
                printf("Monthly\n");
            } else {
                printf("One-off\n");
            }

            printf("    - State: ");

            if (tasks[i].state == 1) {
                printf("Completed\n");
            } else {
                printf("Open\n");
            }

            printf("    - Employee: %d\n\n\n", tasks[i].employeeID);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchTaskMenu() {

    int option;

    do {
        system("cls");
        printf("### Task search and listing menu ###\n\n");
        printf("[1] - ID            [2] - Date\n");
        printf("[3] - Hour          [4] - Description\n");
        printf("[5] - Employee\n");
        printf("[0] - Exit\n\n");
        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                searchTaskByID();
                break;
            case 2:
                searchTaskByDate();
                break;
            case 3:
                searchTaskByHour();
                break;
            case 4:
                searchTaskByDescription();
                break;
            case 5:
                searchTaskByEmployee();
                break;
            default:
                printf("\nInvalid option\n\n");
                system("pause");
                break;
        }
    } while (option != 0);
}
int countRegisteredEmployees() {
    int counter = 0;
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employees[i].slotAvailability == 1) {
            counter++;
        }
    }
    return counter;
}
int countEmptyEmployeeSlots() {
    int counter = 0;
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employees[i].slotAvailability == 0) {
            counter++;
        }
    }
    return counter;
}
int findEmptyEmployeeSlot() {
    int index = 0;
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employees[i].slotAvailability == 0) {
            index = i;
            break;
        }
    }
    return index;
}
void newEmployee() {
    int employeeCount = countRegisteredEmployees();
    int i = findEmptyEmployeeSlot();

    if (employeeCount == MAX_EMPLOYEES) {
        printf("You have reached the maximum number of registered employees in the system\n");
        printf("Please contact support\n\n");
        system("pause");
    } else {
        system("cls");
        printf("### New Employee Form ###\n\n");

        employeeLastID++;
        employees[i].ID = employeeLastID;

        printf("Employee's name: ");
        fflush(stdin);
        gets(employees[i].name);

        printf("Employee's date of birth (DD/MM/YYYY): ");
        fflush(stdin);
        scanf("%d/%d/%d", &employees[i].dateBirthDay, &employees[i].dateBirthMonth, &employees[i].dateBirthYear);

        printf("Employee's contact number (XXX-XXX-XXX): ");
        fflush(stdin);
        scanf("%d-%d-%d", &employees[i].contactNumberSet1, &employees[i].contactNumberSet2, &employees[i].contactNumberSet3);

        printf("Employee's e-mail: ");
        fflush(stdin);
        gets(employees[i].email);

        printf("Employee's town of residence: ");
        fflush(stdin);
        gets(employees[i].residence);

        printf("Employee's department: ");
        fflush(stdin);
        gets(employees[i].department);

        employees[i].slotAvailability = 1;

        printf("\n\nNew employee registered in the system successfully. ");
        system("pause");
    }
}
void listEmployees() {
    int emptyEmployeeSlots = countEmptyEmployeeSlots();
    system("cls");
    printf("### Full Employee List ###\n\n");
    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employees[i].slotAvailability == 1) {
            printf("%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        } else if (emptyEmployeeSlots == MAX_EMPLOYEES) {
            printf("The list is empty\n\n");
            break;
        }
    }
    system("pause");
}
void deleteEmployee(){
    int employeeID;

    system("cls");

    printf("### Deleting Employee ###\n");

    printf("\nEnter the employee's ID: ");
    fflush(stdin);
    scanf("%d", &employeeID);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employeeID == employees[i].ID) {
            employees[i].slotAvailability = 0;
        }
    }
    printf("\nEmployee successfully deleted. ");
    system("pause");
}
void deletingEmployeeMenu() {
    int option;

    do {
        system("cls");
        printf("### Delete Employee ###\n\n");
        printf("[1] - List employees    [2] - Delete employee via ID\n");
        printf("[0] - Exit\n\n");
        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);
        switch (option) {
            case 0:
                break;
            case 1:
                listEmployees();
                break;
            case 2:
                deleteEmployee();
                break;
            default:
                printf("\nInvalid option. ");
                system("pause");
                break;
        }
    } while (option != 0);
}
void editEmployee() {
    int employeeID;

    printf("\nEnter the employee's ID: ");
    fflush(stdin);
    scanf("%d", &employeeID);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (employeeID == employees[i].ID) {
            system("cls");
            printf("### Editing Employee ###\n\n");

            printf("Employee's name: ");
            fflush(stdin);
            gets(employees[i].name);

            printf("Employee's date of birth (DD/MM/YYYY): ");
            fflush(stdin);
            scanf("%d/%d/%d", &employees[i].dateBirthDay, &employees[i].dateBirthMonth, &employees[i].dateBirthYear);

            printf("Employee's contact number (XXX-XXX-XXX): ");
            fflush(stdin);
            scanf("%d-%d-%d", &employees[i].contactNumberSet1, &employees[i].contactNumberSet2, &employees[i].contactNumberSet3);

            printf("Employee's e-mail: ");
            fflush(stdin);
            gets(employees[i].email);

            printf("Employee's town of residence: ");
            fflush(stdin);
            gets(employees[i].residence);

            printf("Employee's department: ");
            fflush(stdin);
            gets(employees[i].department);

            printf("\n\nEmployee edited successfully. ");
            system("pause");
            break;
        }
    }
}
void editingEmployeeMenu() {
    int option;

    do {
        system("cls");
        printf("### Edit Employee ###\n\n");
        printf("[1] - List employees    [2] - Edit employee via ID\n");
        printf("[0] - Exit\n\n");
        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);
        switch (option) {
            case 0:
                break;
            case 1:
                listEmployees();
                break;
            case 2:
                editEmployee();
                break;
            default:
                printf("\nInvalid option. ");
                system("pause");
                break;
        }
    } while (option != 0);
}
void searchEmployeeByID() {
    int ID;

    printf("\nBy what ID would you like to search?: ");
    fflush(stdin);
    scanf("%d", &ID);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (ID == employees[i].ID) {
            printf("\n%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchEmployeeByName() {
    char name[55];

    printf("\nBy what name would you like to search?: ");
    fflush(stdin);
    gets(name);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        char* check = strstr(employees[i].name, name);
        if (check != NULL) {
            printf("\n%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchEmployeeByEmail() {
    char email[55];

    printf("\nBy what e-mail would you like to search?: ");
    fflush(stdin);
    gets(email);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        char* check = strstr(employees[i].email, email);
        if (check != NULL) {
            printf("\n%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchEmployeeByDepartment() {
    char department[55];

    printf("\nBy what department would you like to search?: ");
    fflush(stdin);
    gets(department);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        char* check = strstr(employees[i].department, department);
        if (check != NULL) {
            printf("\n%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchEmployeeByContact() {
    int set1, set2, set3;

    printf("\nBy what contact number would you like to search? (XXX-XXX-XXX): ");
    fflush(stdin);
    scanf("%d-%d-%d", &set1, &set2, &set3);

    for (int i = 0; i < MAX_EMPLOYEES; ++i) {
        if (set1 == employees[i].contactNumberSet1 && set2 == employees[i].contactNumberSet2
        && set3 == employees[i].contactNumberSet3) {
            printf("\n%s (Index: %d)\n", employees[i].name, i);
            printf("    - ID: %d\n", employees[i].ID);
            printf("    - Date of birth: %d/%d/%d\n", employees[i].dateBirthDay, employees[i].dateBirthMonth, employees[i].dateBirthYear);
            printf("    - Contact Number: %d-%d-%d\n", employees[i].contactNumberSet1, employees[i].contactNumberSet2, employees[i].contactNumberSet3);
            printf("    - E-mail: %s\n", employees[i].email);
            printf("    - Town of residence: %s\n", employees[i].residence);
            printf("    - Department: %s\n\n\n", employees[i].department);
        }
    }
    printf("\nNo further results were found. ");
    system("pause");
}
void searchEmployeeMenu() {

    int option;

    do {
        system("cls");
        printf("### Employee search and listing menu ###\n\n");
        printf("[1] - ID                [2] - Name\n");
        printf("[3] - Contact number    [4] - E-mail\n");
        printf("[5] - Department\n");
        printf("[0] - Exit\n\n");
        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                searchEmployeeByID();
                break;
            case 2:
                searchEmployeeByName();
                break;
            case 3:
                searchEmployeeByContact();
                break;
            case 4:
                searchEmployeeByEmail();
                break;
            case 5:
                searchEmployeeByDepartment();
                break;
            default:
                printf("\nInvalid option\n\n");
                system("pause");
                break;
        }
    } while (option != 0);
}
int countOpenTasks() {
    int counter = 0;
    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].state == 0) {
            counter++;
        }
    }
    return counter;
}
void closeCompletedTasks() {
    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].state == 1) {
            tasks[i].slotAvailability = 0;
        }
    }
    system("cls");
    printf("All tasks marked as completed have been delete. ");
    system("pause");
}
void markTasksCompleted() {
    int taskID;
    system("cls");
    printf("### Marking task as complete ###\n\n");
    printf("What task would you like to mark as complete? Insert it's ID: ");
    scanf("%d", &taskID);

    for (int i = 0; i < MAX_TASKS; ++i) {
        if (tasks[i].ID == taskID) {
            tasks[i].state = 1;
        }
    }
    printf("\n\nThe task has been marked as completed. ");
    system("pause");
}
void statsMenu() {

    int registeredEmployees, registeredTasks, openTasks, emptyEmployees, emptyTasks;

    registeredEmployees = countRegisteredEmployees();
    registeredTasks = countRegisteredTasks();
    emptyEmployees = countEmptyEmployeeSlots();
    emptyTasks = countEmptyTaskSlots();
    openTasks = countOpenTasks();

    system("cls");

    printf("### Statistics Menu ###\n\n");
    printf("Number of registered employees: %d\n\n", registeredEmployees);
    printf("Number of registered tasks: %d\n", registeredTasks);
    printf("Number of \"Open\" tasks: %d\n\n", openTasks);
    printf("Number of available employee slots in memory: %d\n", emptyEmployees);
    printf("Number of available task slots in memory: %d\n\n", emptyTasks);
    system("pause");

}
void adminMenu() {

    int option;

    do {

        system("cls");

        printf("### Administrator Menu ###\n\n");

        printf("Current date: "); date();

        printf("\n\n[1]  - Insert new employee\n");
        printf("[2]  - Edit employee information\n");
        printf("[3]  - Delete employee\n");
        printf("[4]  - List employees\n");
        printf("[5]  - Search for employee\n\n");

        printf("[6]  - Insert new task\n");
        printf("[7]  - Edit task information\n");
        printf("[8]  - Delete task\n");
        printf("[9]  - List tasks\n");
        printf("[10] - Search for task\n");
        printf("[11] - Mark task as complete\n");
        printf("[12] - Close all completed tasks\n\n");

        printf("[13] - Statistics\n\n");

        printf("[0]  - Exit Menu\n\n");

        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                newEmployee();
                break;
            case 2:
                editingEmployeeMenu();
                break;
            case 3:
                deletingEmployeeMenu();
                break;
            case 4:
                listEmployees();
                break;
            case 5:
                searchEmployeeMenu();
                break;
            case 6:
                newTask();
                break;
            case 7:
                editTask();
                break;
            case 8:
                deleteTask();
                break;
            case 9:
                listTasks();
                break;
            case 10:
                searchTaskMenu();
                break;
            case 11:
                markTasksCompleted();
                break;
            case 12:
                closeCompletedTasks();
                break;
            case 13:
                statsMenu();
                break;
            default:
                printf("\nInvalid Option\n\n");
                system("pause");
                break;

        }

    } while (option != 0);

}
void entryScreen() {

    int option;

    do {

        system("cls");

        printf("### Entry Menu ###\n\n");

        printf("Current date: "); date();

        printf("\n\nTasks for the day:\n");
        printf("some random listing of tasks\n\n");

        printf("Tasks for the month:\n");
        printf("some random listing of tasks\n\n");

        printf("[1] - Administrator Screen\n");
        printf("[0] - Exit\n\n");

        printf("Enter option: ");
        fflush(stdin);
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                adminMenu();
                break;
            default:
                printf("\nInvalid Option\n\n");
                system("pause");
                break;
        }

    } while (option != 0);

}

int main() {
    bootProtocol();
    entryScreen();
    exitProtocol();
    return 0;
}

// todo: on task listing instead of showing the ID it shows both name and ID of the employee