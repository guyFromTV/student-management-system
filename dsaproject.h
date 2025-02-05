#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h> 
    #define SLEEP(seconds) Sleep((seconds) * 1000) // Convert seconds to milliseconds
#else
    #include <unistd.h>
    #define SLEEP(seconds) sleep(seconds) // Use Linux's sleep function
#endif

typedef struct Student {
    char name[30];
    long id_num;
    float grade;
    struct Student *next;
} Tstudent;

int is_id_unique(Tstudent* head, long id);

Tstudent* enter_students(Tstudent* head);

void delete_last_student(Tstudent** head);

void studentcount(Tstudent* head);

void display_list(Tstudent* head);

int find_student(Tstudent* head, long id);

void sort_list(Tstudent** head);

void split_and_sort_list(Tstudent* head, Tstudent** low, Tstudent** high);

Tstudent* merge_sorted_lists(Tstudent* low, Tstudent* high);

float average_exam(Tstudent* head);

void free_list(Tstudent* head);