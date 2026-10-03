#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct student
{
    char name[20];
    unsigned int id;
    unsigned int grade;
} Student;


typedef struct course
{
    char name[20];
    double averageGrade;
    unsigned int totalStudents;
    Student *studentArray;
} Course;


typedef struct school
{
    char name[20];
    unsigned int totalCourses;
    Course *courseArray;
} School;


Student *createStudent()
{
    Student *newStudent = (Student *)malloc(sizeof(Student));

    if (!newStudent)
    {
        printf("Oops not enough memory to allocate Student :(\n");
        return NULL;
    }

    // Reading Student name
    printf("Enter the student name: ");
    scanf("%19s", newStudent->name);
    fflush(stdin);

    // Reading Student id
    printf("Enter the student id: ");
    scanf("%u", &(newStudent->id));
    fflush(stdin);

    // Reading Student grade
    printf("Enter the student grade: ");
    scanf("%u", &(newStudent->grade));
    fflush(stdin);

    return newStudent; // return the Student Object
}


void updateAverageGrade(Course *course)
{
    double totalGrades = 0;
    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        totalGrades += (course->studentArray[i].grade);
    }
    course->averageGrade = (totalGrades / course->totalStudents);
}


Course *CreateCourse()
{
    Course *newCourse = (Course *)malloc(sizeof(Course));

    if (!newCourse)
    {
        printf("Oops not enough memory to allocate Course :(\n");
        return NULL;
    }

    // Reading Course name
    printf("Enter the Course name: ");
    scanf("%19s", newCourse->name);
    fflush(stdin);

    // Reading number of students enrolled the course
    printf("Enter number of students enrolled: ");
    scanf("%u", &(newCourse->totalStudents));
    fflush(stdin);

    newCourse->studentArray = (Student *)malloc(sizeof(Student) * newCourse->totalStudents);

    if (!(newCourse->studentArray))
    {
        printf("Oops not enough memory to allocate the students list :(\n");
        return NULL;
    }

    // Reading all the students enrolled the course
    for (unsigned int i = 0; i < newCourse->totalStudents; i++)
    {
        printf("Enter details for student #%u\n", i + 1);

        Student *newStudent = createStudent();
        newCourse->studentArray[i] = *newStudent;

        free(newStudent); // Free the student object
    }
    // Calculate the average grade for course
    updateAverageGrade(newCourse);

    return newCourse; // return the Course object
}


School *CreateSchool()
{
    School *newSchool = (School *)malloc(sizeof(School));

    if (!newSchool)
    {
        printf("Not enough memory to allocate School :(\n");
        return NULL;
    }

    // Reading School Name
    printf("Enter School name: ");
    scanf("%19s", newSchool->name);
    fflush(stdin);

    printf("Enter the number of courses: ");
    scanf("%u", &(newSchool->totalCourses));
    fflush(stdin);

    newSchool->courseArray = (Course *)malloc(sizeof(Course) * newSchool->totalCourses);

    if (!(newSchool->courseArray))
    {
        printf("Oops not enough memory to allocate School :(\n");
        return NULL;
    }

    for (unsigned int i = 0; i < newSchool->totalCourses; i++)
    {
        printf("Enter the details for Course#%u\n", i + 1);

        Course *newCourse = CreateCourse();
        newSchool->courseArray[i] = *newCourse;

        free(newCourse); // Free the Course object
    }
    return newSchool; // return the School object
}


void printStudentDetails(Student *student)
{
    if (!student)
    {
        printf("Student object is:(NULL)\n");
        exit(-1);
    }

    printf("----------------------- student details -----------------------\n");

    printf("Student name: %s\n", student->name);
    printf("Student ID: %u\n", student->id);
    printf("Student grade:%u\n", student->grade);

    printf("---------------------------------------------------------------\n");
}


void printCourseDetails(Course *course)
{
    if (!course)
    {
        printf("Course object is:(NULL)\n");
        exit(-1);
    }

    printf("----------------------- course  details -----------------------\n");

    printf("Course name: %s\n", course->name);
    printf("Course Average Grade: %lf\n", course->averageGrade);
    printf("Total no of students enrolled: %u\n", course->totalStudents);

    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        printf("Deatails of student #%u\n", i + 1);
        printStudentDetails(&(course->studentArray[i]));
    }

    printf("---------------------------------------------------------------\n");
}


void printStudentCourses(School *school, unsigned int studentID)
{
    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("----------------------- courses enrolled by %u -----------------------\n", studentID);

    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        for (unsigned int j = 0; i < school->courseArray[i].totalStudents; j++)
        {
            if (school->courseArray[i].studentArray[j].id == studentID)
            {
                printf(" - %s\n", school->courseArray[i].name);
                break; // Found the student in this course
            }
        }
    }

    printf("--------------------------------------------------------------------------------\n");
}


void printStudentsFailedCourse(Course *course, double cutOffGrade)
{
    if (!course)
    {
        printf("Course object is:(NULL)\n");
        exit(-1);
    }

    printf("Students who failed in %s\n", course->name);
    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        if (course->studentArray[i].grade < cutOffGrade)
        {
            printStudentDetails(&(course->studentArray[i]));
        }
    }
}


void printStudentsPassedCourse(Course *course, double cutOffGrade)
{
    if (!course)
    {
        printf("Course object is:(NULL)\n");
        exit(-1);
    }

    printf("Students who passed in %s\n", course->name);
    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        if (course->studentArray[i].grade >= cutOffGrade)
        {
            printStudentDetails(&(course->studentArray[i]));
        }
    }
}


void printCourseWithPassAvgGrade(School *school, double cutOffGrade)
{
    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("Courses with pass average grade:\n");
    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        if (school->courseArray[i].averageGrade >= cutOffGrade)
        {
            printCourseDetails(&(school->courseArray[i]));
        }
    }
}


void printCourseWithFailAvgGrade(School *school, double cutOffGrade)
{
    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("Courses with fail average grade:\n");
    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        if (school->courseArray[i].averageGrade < cutOffGrade)
        {
            printCourseDetails(&(school->courseArray[i]));
        }
    }
}

void printAverageGradeAllCourses(School *school)
{

    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    double totalGrade = 0;
    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        totalGrade += (school->courseArray[i].averageGrade);
    }

    double average = totalGrade / school->totalCourses;
    printf("Average grade between all courses in school %s is %.2f\n", school->name, average);
}

void printCourseWithHighestAverage(School *school)
{

    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    double highestAvg = 0;
    Course *highestAvgCourse = NULL;
    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        if (school->courseArray[i].averageGrade > highestAvg)
        {
            highestAvg = school->courseArray[i].averageGrade;
            highestAvgCourse = &(school->courseArray[i]);
        }
    }

    printf("Course with the highest average grade:\n");
    printCourseDetails(highestAvgCourse);
}

// Step 17: Printing the School Details

void printSchoolDetails(School *school)
{

    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("School name:%s\n", school->name);
    printf("Total no.of courses offering:%u\n", school->totalCourses);
    for (unsigned int i = 0; i < school->totalCourses; i++)
    {
        printCourseDetails(&(school->courseArray[i]));
    }
}

void updateStudentGrade(Course *course, unsigned int studentID, unsigned int newGrade)
{

    if (!course)
    {
        printf("Course object is:(NULL)\n");
        exit(-1);
    }

    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        if (course->studentArray[i].id == studentID)
        {
            course->studentArray[i].grade = newGrade;

            // Automatically upgrade the average grade of the course
            updateAverageGrade(course);

            return;
        }
    }
    printf("Student was not found\n");
}

// Update student Name

void updateStudentName(Course *course, unsigned int studentID, char *newName)
{

    if (!course)
    {
        printf("Course object is:(NULL)\n");
        exit(-1);
    }

    for (unsigned int i = 0; i < course->totalStudents; i++)
    {
        if (course->studentArray[i].id == studentID)
        {
            strcpy(course->studentArray[i].name, newName);

            return;
        }
    }
    printf("Student was not found\n");
}

bool isCourseInSchool(School *school, char *courseName)
{
    if (!school)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    Course *courseArray = school->courseArray;
    unsigned int numCourses = school->totalCourses;

    for (unsigned int i = 0; i < numCourses; i++)
    {
        if (strcmp(courseArray[i].name, courseName) == 0)
        {
            return true;
        }
    }
    return false;
}

// Update Course Name

void updateCourseName(Course *course, char *newName)
{
    if (!course)
    {
        printf("Course object is :(NULL)\n");
        exit(-1);
    }

    strcpy(course->name, newName);
}


void printCommonCoursesBetweenSchool(School *school1, School *school2)
{
    if (!school1 || !school2)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("Common courses between %s and %s:\n", school1->name, school2->name);

    for (unsigned int i = 0; i < school1->totalCourses; i++)
    {
        if (isCourseInSchool(school2, school1->courseArray[i].name))
        {
            printf("- %s\n", school1->courseArray[i].name);
        }
    }
}


void printUniqueCoursesBetweenSchool(School *school1, School *school2)
{
    if (!school1 || !school2)
    {
        printf("School object is :(NULL)\n");
        exit(-1);
    }

    printf("Courses in %s but not in %s:\n", school1->name, school2->name);

    for (unsigned int i = 0; i < school1->totalCourses; i++)
    {
        if (!(isCourseInSchool(school2, school1->courseArray[i].name)))
        {
            printf("- %s\n", school1->courseArray[i].name);
        }
    }
}

void freeStudents(Student *students)
{
    if (!students)
    {
        printf("Null pointer can't be used to free the memory :(\n");
        exit(-1);
    }
    free(students);
}


void freeCourses(Course *courses, unsigned int totalCourses)
{
    if (!courses)
    {
        printf("Null pointer can't be used to free the memory :(\n");
        exit(-1);
    }

    for (unsigned int i = 0; i < totalCourses; i++)
    {
        // Cleaning students details
        freeStudents(courses[i].studentArray);

        // Handling dangling pointer
        courses[i].studentArray = NULL;
    }
}

// Step 26: Free School
void freeSchool(School **school)
{
    if (!*school)
    {
        printf("Null pointer can't be used to free the memory :(\n");
        exit(-1);
    }


    freeCourses((*school)->courseArray, (*school)->totalCourses);
    // Cleaning courses details
    free((*school)->courseArray);
    // Handling dangling pointer
    (*school)->courseArray = NULL;
    free(*school);
    *school = NULL;
}

// Entry point
int main()
{
    // Create a new school
    School *mySchool = CreateSchool();
    if (!mySchool)
    {
        return EXIT_FAILURE;
    }
    // Print details about the school
    printSchoolDetails(mySchool);
    // Free the heap memory
    freeSchool(&mySchool);
    return EXIT_SUCCESS;
}