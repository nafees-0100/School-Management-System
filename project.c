#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct student
{
    char name[20];
    unsigned int id;
    unsigned int grade;
}Student;

typedef struct course
{
    char name[20];
    double averageGrade;
    unsigned int totalStudents;
    Student *studentarr;
}Course;

typedef struct school{
    char name[20];
    unsigned int totalcourse;
    Course *coursearr;
}School; 

Student *createstudent(){
    Student *newstudent=(Student *)malloc(sizeof(Student));
    printf("Enter Student Name:");
    scanf("%s",newstudent->name);
    printf("Enter Student ID:");
    scanf("%u",&newstudent->id);
    printf("Enter Student Grade:");
    scanf("%u",&newstudent->grade);
    return newstudent;
}

void updateAvg(Course *course){
    double totalgrade=0;
    for(int i=0;i<course->totalStudents;i++)
        totalgrade+=course->studentarr[i].grade;
    course->averageGrade=totalgrade/course->totalStudents;
}

Course *createcourse(){
    Course *newcourse=(Course *)malloc(sizeof(Course));
    printf("Enter Course Name:");
    scanf("%s",newcourse->name);
    printf("Enter Number of Student:");
    scanf("%u",&newcourse->totalStudents);
    newcourse->studentarr=(Student *)malloc(sizeof(Student)*newcourse->totalStudents);
    for(int i=0;i<newcourse->totalStudents;i++){
        printf("Enter details of Student %d\n",i+1);
        Student *newstudent=createstudent();
        newcourse->studentarr[i]=*newstudent;
        free(newstudent);
    }
    updateAvg(newcourse);
    return newcourse;
}

School *createschool(){
    School *newschool=(School *)malloc(sizeof(School));
    printf("Enter School name:");
    scanf("%s",newschool->name);
    printf("Enter School Total course:");
    scanf("%u",&newschool->totalcourse);
    newschool->coursearr=(Course *)malloc(sizeof(Course)*newschool->totalcourse);
    for(int i=0;i<newschool->totalcourse;i++){
        printf("Enter details for course %d\n",i+1);
        Course *newcourse=createcourse();
        newschool->coursearr[i]=*newcourse;
        free(newcourse);
    }
    return newschool;
}

void printstudentdetail(Student *student){
    printf("Student name: %s\n",student->name);
    printf("Student ID: %u\n",student->id);
    printf("Student Grade: %u\n",student->grade);
}

void printcoursedetail(Course *course){
    printf("Course Name: %s\n",course->name);
    printf("Course Average: %.2lf\n",course->averageGrade);
    printf("Course Total Student: %u\n",course->totalStudents);
    for(int i=0;i<course->totalStudents;i++){
        printf("Details for Student %d:\n",i+1);
        printstudentdetail(&(course->studentarr[i]));
    }
}

void printstudentcourse(School *school,int studentid){
    printf("Course for Student with ID %d:\n",studentid);
    for(int i=0;i<school->totalcourse;i++){
        for(int j=0;j<school->coursearr[i].totalStudents;j++){
            if(school->coursearr[i].studentarr[j].id==studentid){
                printf(" - %s\n",school->coursearr[i].name);
                break;
            }
        }
    }
}

void printstudentwhofailed(Course *course,double cutoff){
    printf("Student who failed in %s:\n",course->name);
    for(int i=0;i<course->totalStudents;i++){
        if(course->studentarr[i].grade<cutoff){
            printstudentdetail(&(course->studentarr[i]));
        }
    }
}

void printstudentwhopassed(Course *course,double cutoff){
    printf("Student who passed in %s:\n",course->name);
    for(int i=0;i<course->totalStudents;i++){
        if(course->studentarr[i].grade>=cutoff){
            printstudentdetail(&(course->studentarr[i]));
        }
    }
}

void printCourseWithPassAvgGrade(School *school,double cutoff){
    printf("Courses with pass Average Grade:\n");
    for(int i=0;i<school->totalcourse;i++){
        if(school->coursearr[i].averageGrade>=cutoff){
            printcoursedetail(&(school->coursearr[i]));
        }
    }
}

void printCourseWithFailAvgGrade(School *school,double cutoff){
    printf("Courses with fail Average Grade:\n");
    for(int i=0;i<school->totalcourse;i++){
        if(school->coursearr[i].averageGrade<cutoff){
            printcoursedetail(&(school->coursearr[i]));
        }
    }
}

void printAvgGradeAllCourse(School *school){
    double totalgrade=0;
    for(int i=0;i<school->totalcourse;i++){
        totalgrade+=school->coursearr[i].averageGrade;
    }
    double average=totalgrade/school->totalcourse;
    printf("Average grade between all courses in school %s is %.2f\n",school->name,average);
}

void printCourseWithHighAvg(School *school,double cutoff){
    double highestAvg=0;
    Course *highAvgCourse=NULL;
    for(int i=0;i<school->totalcourse;i++){
        if(school->coursearr[i].averageGrade>=cutoff){
            highestAvg=school->coursearr[i].averageGrade;
            highAvgCourse=&(school->coursearr[i]);
        }
    }
    printf("Course with the highest average grade:\n");
    printcoursedetail(highAvgCourse);
}

void printschooldetails(School *school){
    for(int i=0;i<school->totalcourse;i++){
        printcoursedetail(&(school->coursearr[i]));
    }
}

void updateStudentGrade(Course *course,unsigned int studentID,unsigned int newgrade){
    for(int i=0;i<course->totalStudents;i++){
        if(course->studentarr[i].id==studentID){
            course->studentarr[i].grade=newgrade;
            updateAvg(course);
            return;
        }
    }
    printf("Student was not found!\n");
}

void updateStudentName(Course *course,unsigned int studentID,char *newname){
    for(int i=0;i<course->totalStudents;i++){
        if(course->studentarr[i].id==studentID){
            strcpy(course->studentarr[i].name,newname);
            return;
        }
    }
    printf("Student was not found!\n");
}

bool iscourseInSchool(School *school,char *coursename){
    Course *coursearray=school->coursearr;
    unsigned int numcourse=school->totalcourse;
    for(int i=0;i<numcourse;i++){
        if(strcmp(coursearray[i].name,coursename)==0)
            return true;
    }
    return false;
}

void updateCourseName(Course *course,char *newname){
    strcpy(course->name,newname);
}

void printCommonCourseBetweenSchool(School *school1,School *school2){
    printf("Common Courses between %s and %s:\n",school1->name,school2->name);
    for(int i=0;i<school1->totalcourse;i++){
        if(iscourseInSchool(school2,school1->coursearr[i].name))
            printf(" -%s",school1->coursearr[i].name);
    }
}

void printUniqueCourseBetweenSchool(School *school1,School *school2){
    printf("Courses in %s but not in %s:\n",school1->name,school2->name);
    for(int i=0;i<school1->totalcourse;i++){
        if(!iscourseInSchool(school2,school1->coursearr[i].name))
            printf(" -%s",school1->coursearr[i].name);
    }
}

void freestudent(Student *student){
    free(student);
}

void freecourse(Course *course,unsigned int totalcourse){
    for(int i=0;i<totalcourse;i++){
        freestudent(course[i].studentarr);
        course[i].studentarr=NULL;
    }
}

void freeschool(School *school){
    freecourse(school->coursearr,school->totalcourse);
    free(school->coursearr);
    school->coursearr=NULL;
    free(school);
}

int main(){
     School *myschool=createschool();
     printschooldetails(myschool);
     printstudentcourse(myschool,123);
     printstudentwhofailed(&(myschool->coursearr[0]),60.0);
     printstudentwhopassed(&(myschool->coursearr[0]),60.0);
     char name[10]="Nafees";
     updateStudentName(&myschool->coursearr[0],123,name);
     printf("\nUpdated Name:%s",myschool->coursearr[0].studentarr[0].name);
     freeschool(myschool);
}