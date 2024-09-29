#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 50

typedef struct {
    int book_number;
    char title[MAX_NAME_LENGTH];
    char author[MAX_NAME_LENGTH];
    int copies;
    char category[MAX_CATEGORY_LENGTH];
    int status;
} Book;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int penalty;
    int book_loan;
    char time[50];
} Student;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int penalty;
    int book_loan;
    char time[50];
} Staff;

Book books[MAX_BOOKS];
int bookCount = 0;

Student students[MAX_BOOKS];
int studentCount = 0;

Staff staffs[MAX_BOOKS];
int staffCount = 0;

void saveStudentRecords()
{
    FILE* file = fopen("student_records.txt", "w");
    if (file == NULL)
    {
        printf("Error opening student records file.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        fprintf(file, "%s;%d;%d;%s\n", students[i].name, students[i].penalty, students[i].book_loan, students[i].time);
    }

    fclose(file);
}

void loadStudentRecords()
{
    FILE* file = fopen("student_records.txt", "r");
    if (file == NULL)
    {
        printf("No student records file found. Starting with an empty student records.\n");
        getch();
        return;
    }

    studentCount = 0;
    while (fscanf(file, "%[^;];%d;%d;%[^\n]\n", students[studentCount].name, &students[studentCount].penalty, &students[studentCount].book_loan, students[studentCount].time) == 4)
    {
        studentCount++;
    }

    fclose(file);
}

void saveStaffRecords()
{
    FILE* file = fopen("staff_records.txt", "w");
    if (file == NULL)
    {
        printf("Error opening staff records file.\n");
        return;
    }

    for (int i = 0; i < staffCount; i++)
    {
        fprintf(file, "%s;%d;%d;%s\n", staffs[i].name, staffs[i].penalty, staffs[i].book_loan, staffs[i].time);
    }

    fclose(file);
}

void loadStaffRecords()
{
    FILE* file = fopen("staff_records.txt", "r");
    if (file == NULL)
    {
        printf("No staff records file found. Starting with an empty staff records.\n");
        getch();
        return;
    }

    staffCount = 0;
    while (fscanf(file, "%[^;];%d;%d;%[^\n]\n", staffs[staffCount].name, &staffs[staffCount].penalty, &staffs[staffCount].book_loan, staffs[staffCount].time) == 4)
    {
        staffCount++;
    }

    fclose(file);
}

void saveLibrary()
{
    FILE* file = fopen("library.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d\n", bookCount);
    for (int i = 0; i < bookCount; i++)
    {
        fprintf(file, "%d;%s;%s;%d;%s;%d\n", books[i].book_number, books[i].title, books[i].author, books[i].copies, books[i].category,books[i].status);
    }

    fclose(file);
}


void loadLibrary()
{
    FILE* file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("No library file found. Starting with an empty library.\n");
        getch();
        return;
    }

    fscanf(file, "%d\n", &bookCount);
    for (int i = 0; i < bookCount; i++)
    {
        fscanf(file, "%d;%[^;];%[^;];%d;%[^;];%d\n", &books[i].book_number, books[i].title, books[i].author, &books[i].copies, books[i].category, &books[i].status);
    }

    fclose(file);
}


void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("\t\t\tMaximum book capacity reached.\n");
        getch();
        return;
    }

    printf("\t\t\t=================================================\n\n");
    printf("\t\t\t                   ADD BOOK                       \n");
    printf("\t\t\t=================================================\n\n");

    Book newBook;

    newBook.book_number = (bookCount + 1) * 100;

    printf("\n\n\t\t\tEnter Book Title: ");
    scanf(" %[^\n]%*c", newBook.title);

    printf("\n\n\t\t\tEnter Book Author: ");
    scanf(" %[^\n]%*c", newBook.author);

    printf("\n\n\t\t\tEnter Book Copies: ");
    scanf("%d", &newBook.copies);
    getchar();

    printf("\n\n\t\t\tEnter Book Category: ");
    scanf(" %[^\n]%*c", newBook.category);

    printf("\n\n\t\t\tEnter '1' if the book is for everybody, '2' for staff only, '3' for library use only");
    printf("\n\n\t\t\tEnter Book Status: ");
    scanf("%d", &newBook.status);

    books[bookCount] = newBook;
    bookCount++;

    printf("\n\n\n\t\t\tBook Added Successfully.");
    printf("\n\n\t\t\t=================================================\n\n");

    getch();

    saveLibrary();
}


void removeBook()
{
    if (bookCount <= 0)
    {
        printf("\t\t\tNo books available.\n");
        getch();
        system("cls");
        return;
    }

    printf("\n\n\t\t\t=================================================\n\n");
    printf("\t\t\t                   REMOVE BOOK                       ");
    printf("\n\n\t\t\t=================================================\n\n");

    char searchTitle[MAX_NAME_LENGTH];
    printf("\t\t\tEnter book title to remove: ");
    scanf(" %[^\n]%*c", searchTitle);

    int i;
    for (i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, searchTitle) == 0)
        {
            int j;
            for (j = i; j < bookCount - 1; j++)
            {
                books[j] = books[j + 1];
            }
            bookCount--;

            printf("\n\n\t\t\tBook removed successfully.\n");
            printf("\n\n\t\t\t=================================================\n\n");

            saveLibrary();
            getch();
            system("cls");
            return;
        }
    }

    printf("\t\t\tBook not found.\n");
    printf("\n\n\t\t\t=================================================\n\n");
    getch();
}

char* getCurrentTime()
{
    time_t currentTime;
    time(&currentTime);

    char* timeString = ctime(&currentTime);

    size_t stringLength = strlen(timeString);
    if (stringLength > 0 && timeString[stringLength - 1] == '\n')
    {
        timeString[stringLength - 1] = '\0';
    }

    return timeString;
}

void searchBook()
{
    if (bookCount <= 0)
    {
        printf("\t\t\tNo books available.\n");
        getch();
        return;
    }

    printf("\t\t\t=================================================\n");
    printf("\t\t\t                    SEARCH BOOK                \n");
    printf("\t\t\t=================================================\n\n");

    char searchTitle[MAX_NAME_LENGTH];
    printf("\t\t\tEnter Book Title: ");
    scanf(" %[^\n]%*c", searchTitle);

    int i;
    for (i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, searchTitle) == 0)
        {
            printf("\t+------------------------------------------------------------------------------------------------------+\n");
            printf("\t| Book Number |                Title              |   Author            |  Copies  |     Categories    |\n");
            printf("\t+------------------------------------------------------------------------------------------------------+\n");

            printf("\t| %d\t      | %s\t                  | %s        |   %d      |    %s        |\n", books[i].book_number, books[i].title, books[i].author, books[i].copies, books[i].category);
            printf("\t+------------------------------------------------------------------------------------------------------+\n");

            getch();
            return;

        }
    }

    printf("\t\t\tBook not found.\n");
    getch();
}

void searchByCategory()
{
    printf("\t\t\t====================================================\n");
    printf("\t\t\t                      CATEGORY                   \n");
    printf("\t\t\t====================================================\n\n");


    if (bookCount <= 0)
    {
        printf("\t\t\tNo books available.\n");
        getch();
        return;
    }
    printf("\t\t\t+------------------------+--------------------------+\n");
    printf("\t\t\t|CATEGORIES:                                        |\n");
    printf("\t\t\t+------------------------+--------------------------+\n");


    char searchCategory[MAX_CATEGORY_LENGTH];
    printf("\t\t\tEnter the category to search: ");
    scanf(" %[^\n]%*c", searchCategory);

    printf("\n\t\t\t                                               \n");
    printf("\t\t\t=================================================\n\n");
    printf("\t\t\tSearch Results by Category: \n");
    printf("\t+------------------------------------------------------------------------------------------------------+\n");
    printf("\t| Book Number |                Title              |   Author            |  Copies  |     Categories    |\n");
    printf("\t+------------------------------------------------------------------------------------------------------+\n");


    int found = 0;
    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].category, searchCategory) == 0)
        {
            printf("\t+------------------------------------------------------------------------------------------------------+\n");
            printf("\t| %d\t      | %s\t                  | %s        |   %d      |    %s        |\n", books[i].book_number, books[i].title, books[i].author, books[i].copies, books[i].category);
            printf("\t+------------------------------------------------------------------------------------------------------+\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("\t\t\tNo books found in the specified category.\n");
        printf("\t\t\t=================================================\n\n");
    }
    getch();
}


void loanBook()
{
    printf("\t\t\t=================================================\n");
    printf("\n\t\t\tEnter borrower type (1 for student, 2 for staff): ");
    int borrowerType;
    scanf("%d", &borrowerType);
    getchar();

    printf("\n\t\t\t                     BORROW                      \n\n");

    if (borrowerType == 1)
    {
        if (studentCount >= MAX_BOOKS)
        {
            printf("\n\n\t\t\tMaximum student borrower capacity reached.\n");
            getch();
            system("cls");
            return;
        }
        printf("\t\t\t=================================================\n\n");

        char searchTitle[MAX_NAME_LENGTH];
        printf("\t\t\tEnter book title: ");
        scanf(" %[^\n]%*c", searchTitle);

        char checkStudent [MAX_NAME_LENGTH];

        int i;
        for (i = 0; i < bookCount; i++)
        {
            if (strcmp(books[i].title, searchTitle) == 0)
            {
                if (books[i].status != 1)
                {
                    printf ("\n\n\t\t\tYou don't have access to borrow this book.");
                    getch();
                    system("cls");
                    return;
                }

                if (books[i].copies > 0)
                {
                    printf("\n\n\t\t\tName of the Student: ");
                    scanf(" %[^\n]%*c", checkStudent);

                    int existingStudentIndex = -1;
                    for (int j = 0; j < studentCount; j++)
                    {
                        if (strcmp(students[j].name, checkStudent) == 0)
                        {
                            existingStudentIndex = j;
                            break;
                        }
                    }

                    if (existingStudentIndex != -1)
                    {
                        if (students[existingStudentIndex].penalty >= 2)
                        {
                            printf("\n\n\n\t\t\tYou have too many penalties.\n");
                            students[existingStudentIndex].penalty = 0;
                            getch();
                            system("cls");
                            return;
                        }

                        strcpy(students[existingStudentIndex].time, getCurrentTime());
                        students[existingStudentIndex].book_loan = i;

                        printf ("\n\n\n\t\t\tPenalty count: %i\n", students[existingStudentIndex].penalty);

                        books[i].copies--;

                    }
                    else
                    {
                        Student newStudent;

                        strcpy(newStudent.time, getCurrentTime());
                        strcpy (newStudent.name, checkStudent);
                        newStudent.book_loan = i;
                        newStudent.penalty = 0;
                        students[studentCount] = newStudent;
                        studentCount++;

                        books[i].copies--;
                    }

                    printf("\n\n\n\t\t\tBook Loaned Succesfully. \n");
                    printf("\n\n\t\t\t=================================================\n\n");

                    saveLibrary();
                    saveStudentRecords();
                    getch();
                    system("cls");
                    return;
                }
                else
                {
                    printf("\n\n\n\t\t\tBook is not available for loan.\n");
                    printf("\n\n\t\t\t=================================================\n\n");
                }
                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\n\t\t\tBook not found.\n");
        printf("\n\n\t\t\t=================================================\n\n");
    }
    else if (borrowerType == 2)
    {
        if (staffCount >= MAX_BOOKS)
        {
            printf("\n\n\n\t\t\tMaximum staff borrower capacity reached.\n");
            getch();
            system("cls");
            return;
        }

        printf("\t\t\t=================================================\n\n");
        char searchTitle[MAX_NAME_LENGTH];
        printf("\t\t\tEnter book title to loan: ");
        scanf(" %[^\n]%*c", searchTitle);

        char checkStaff [MAX_NAME_LENGTH];

        int i;
        for (i = 0; i < bookCount; i++)
        {
            if (strcmp(books[i].title, searchTitle) == 0)
            {
                if (books[i].status == 3)
                {
                    printf ("\n\n\t\t\tYou don't have access to borrow this book.");
                    getch();
                    system("cls");
                    return;
                }

                if (books[i].copies > 0)
                {
                    printf("\n\n\t\t\tName of the Staff: ");
                    scanf(" %[^\n]%*c", checkStaff);

                    int existingStudentIndex = -1;
                    for (int j = 0; j < staffCount; j++)
                    {
                        if (strcmp(staffs[j].name, checkStaff) == 0)
                        {
                            existingStudentIndex = j;
                            break;
                        }
                    }

                    if (existingStudentIndex != -1)
                    {
                        if (staffs[existingStudentIndex].penalty >= 3)
                        {
                            printf("\n\n\n\t\t\tYou have too many penalties.\n");
                            staffs[existingStudentIndex].penalty = 0;
                            getch();
                            system("cls");
                            return;
                        }

                        strcpy(staffs[existingStudentIndex].time, getCurrentTime());
                        staffs[existingStudentIndex].book_loan = i;

                        printf ("\n\n\n\t\t\tPenalty count: %i\n", students[existingStudentIndex].penalty);

                        books[i].copies--;

                    }
                    else
                    {
                        Staff newStaff;

                        strcpy(newStaff.time, getCurrentTime());
                        strcpy (newStaff.name, checkStaff);
                        newStaff.book_loan = i;
                        newStaff.penalty = 0;
                        staffs[staffCount] = newStaff;
                        staffCount++;

                        books[i].copies--;
                    }

                    printf("\n\n\n\t\t\tBook loaned successfully.\n");
                    printf("\n\n\t\t\t=================================================\n\n");

                    saveLibrary();
                    saveStaffRecords();
                    getch();
                system("cls");
                    return;
                }
                else
                {
                    printf("\n\n\n\t\t\tBook is not available for loan.\n");
                    printf("\n\n\t\t\t=================================================\n\n");
                }
                getch();
                system("cls");
                return;
            }
        }

        printf("\n\n\n\t\t\tBook not found.\n");
        printf("\n\n\t\t\t=================================================\n\n");
    }
    else
    {
        printf("\n\n\n\t\t\tInvalid borrower type.\n");
        printf("\n\n\t\t\t=================================================\n\n");
    }
    getch();
}

void returnBook()
{
    printf("\n\n\t\t\t=================================================\n\n");
    printf("\t\t\t                  RETURN BOOK                    \n\n");
    printf("\t\t\tEnter borrower type (1 for student, 2 for staff): ");
    int borrowerType;
    scanf("%d", &borrowerType);
    getchar();

    if (borrowerType == 1)
    {
        char borrowerName[MAX_NAME_LENGTH];
        printf("\t\t\tName of the Student: ");
        scanf(" %[^\n]%*c", borrowerName);

        int i;
        for (i = 0; i < studentCount; i++)
        {
            if (strcmp(students[i].name, borrowerName) == 0)
            {
                printf("\n\n\t\t\tTime Borrowed: %s\n\n", students[i].time);

                int penalty_count;
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t|                    PENALTY!                   |\n");
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t|                                               |\n");
                printf("\t\t\t|                 YES[1]  NO[2]                 |\n");
                printf("\t\t\t|                                               |\n");
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\tAdd penalty: ");
                scanf("%d", &penalty_count);

                if (penalty_count == 1)
                {
                    students[i].penalty++;
                    printf("\n\t\t\tPenalty count: %i\n", students[i].penalty);
                }


                int bookIndex = students[i].book_loan;

                books[bookIndex].copies++;

                students[i].book_loan = -1;

                printf("\n\t\t\tBook returned successfully. \n");

                saveLibrary();
                saveStudentRecords();

                printf("\n\n\t\t\t=================================================\n\n");

                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\n\t\t\tStudent borrower not found.\n");
    }
    else if (borrowerType == 2)
    {
        char borrowerName[MAX_NAME_LENGTH];
        printf("\t\t\tName of the Staff: ");
        scanf(" %[^\n]%*c", borrowerName);

        int i;
        for (i = 0; i < staffCount; i++)
        {
            if (strcmp(staffs[i].name, borrowerName) == 0)
            {
                printf("\n\n\t\t\tTime Borrowed: %s\n\n", staffs[i].time);

                int penalty_count;
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t|                    PENALTY!                   |\n");
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\t|                                               |\n");
                printf("\t\t\t|                 YES[1]  NO[2]                 |\n");
                printf("\t\t\t|                                               |\n");
                printf("\t\t\t+-----------------------------------------------+\n");
                printf("\t\t\tAdd penalty: ");
                scanf("%d", &penalty_count);

                if (penalty_count == 1)
                {
                    staffs[i].penalty++;
                    printf("\n\t\t\tPenalty count: %i\n", staffs[i].penalty);
                }

                int bookIndex = staffs[i].book_loan;

                books[bookIndex].copies++;

                staffs[i].book_loan = -1;

                printf("\n\t\t\tBook returned successfully. \n");

                saveLibrary();
                saveStaffRecords();

                printf("\n\n\t\t\t=================================================\n\n");

                getch();
                system("cls");
                return;
            }
        }
        printf("\n\n\n\t\t\tStaff borrower not found.\n");
    }
    else
    {
        printf("\n\n\n\t\t\tInvalid borrower type.\n");
    }
    printf("\n\n\t\t\t=================================================\n\n");
    getch();
}

void printLibrary()
{
    if (bookCount <= 0)
    {
        printf("\t\t\tThe library is empty.\n");
        return;
    }

    printf("\t+------------------------------------------------------------------------------------------------------+\n");
    printf("\t\t\t\t                     Library                       \n");
    printf("\t+------------------------------------------------------------------------------------------------------+\n");
    printf("\t| Book Number |                Title              |   Author            |  Copies  |     Categories    |\n");

    for (int i = 0; i < bookCount; i++)
    {
        printf("\t+------------------------------------------------------------------------------------------------------+\n");
        printf("\t| %d\t      | %s\t                  | %s        |   %d      |    %s        |\n", books[i].book_number, books[i].title, books[i].author, books[i].copies, books[i].category);
        printf("\t+------------------------------------------------------------------------------------------------------+\n");

    }
}

void search()
{
    int choices;
    printf("\n\n\n\n\n\n\n\t\t\t=================================================\n");
    printf("\t\t\t                      SEARCH                     \n");
    printf("\t\t\t=================================================\n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                   1. SEARCH BOOKS               \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                   2. CATEGORIES                 \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                   3. LIBRARY                  \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t=================================================\n\n");
    printf("\t\t\t  Enter your choice: ");
    scanf("%d", &choices);
    printf("\n\t\t\t=================================================\n\n");

    if (choices == 1)
    {
        system("cls");
        searchBook();
    }
    else if (choices == 2)
    {
        system("cls");
        searchByCategory();
    }
    else if (choices == 3)
    {
        system("cls");
        printLibrary();
        getch();
    }
}

void access_database()
{
    int choices;
    system("cls");
    printf("\n\n\n\t\t\t=================================================\n");
    printf("\t\t\t                 ACCESS DATABASE                 \n");
    printf("\t\t\t=================================================\n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                  1. ADD BOOK                    \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                  2. REMOVE BOOK                 \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                  3. BORROW                      \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t                  4. RETURN                      \n");
    printf("\t\t\t                                                 \n");
    printf("\t\t\t=================================================\n\n");
    printf("\t\t\t  Enter your choice: ");
    scanf("%d", &choices);
    printf("\n\t\t\t=================================================\n\n");

    if (choices == 1)
    {
        system("cls");
        addBook();
    }
    else if (choices == 2)
    {
        system("cls");
        printLibrary();
        removeBook();
    }
    else if (choices == 3)
    {
        system("cls");
        printLibrary();
        loanBook();
    }
    else if (choices == 4)
    {
        system("cls");
        returnBook();
    }
}

int main()
{
    loadLibrary();
    loadStudentRecords();
    loadStaffRecords();
    int number, incorrect = 0;
    do
    {
    system("cls");
    printf("\n\n\n\t\t\t=====================================================\n");
    printf("\t\t\t             LIBRARIAN'S CHOICE [LC]                 \n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t                [1] SEARCH                              \n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t                [2] ACCESS DATABASE                     \n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t                [0] EXIT                             \n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t    Enter your Choice:                               \n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t+---------------------------------------------------+\n");
    printf("\t\t\t|This library management system was created by:     |\n");
    printf("\t\t\t+------------------------+--------------------------+\n");
    printf("\t\t\t| BARIT,   VAUGHN JOSHUA | PUSE,    CEDRICK         |\n");
    printf("\t\t\t|                        |                          |\n");
    printf("\t\t\t| ESTA,    KIEL ANDREW   | SAGUN,   MARCK LERIC     |\n");
    printf("\t\t\t|                        |                          |\n");
    printf("\t\t\t| LAGANAS, ANDREA        | SUBIDO,  PRINCES ANGELIE |\n");
    printf("\t\t\t+------------------------+--------------------------+\n");
    switch(number = getch())
        {
           case '1': search(); incorrect = 0; break;
           case '2': access_database(); incorrect = 0; break;
           case '0': return 0; break;

           default: incorrect ++; break;
        }
    }
    while(incorrect <= 3);

    printf ("\n\n\t\t\tReminder: You need to enter either '1', '2' or '0'\n");
    return 0;
}