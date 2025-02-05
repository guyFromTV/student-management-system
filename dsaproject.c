#include "dsaproject.h"

int is_id_unique(Tstudent* head, long id) {
    while (head) {
        if (head->id_num == id) {
            return 0;
        }
        head = head->next;
    }
    return 1;
}


Tstudent* enter_students(Tstudent* head) {
    int num_students;
    char name[30];
    long id_num;
    float grade;
    int result;
    
    printf("How many students would you like to enter? ");
    scanf("%d", &num_students);

    for (int i = 0; i < num_students; i++) {
        printf("\033[0;34m\nStudent %d:\033[0m\n", i + 1);
        if (i != 0)
        printf("\nPress Enter to continue..\n");

    getchar();

    printf("Enter student full name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    do {
        printf("Enter student ID (numeric): ");
        result = scanf("%ld", &id_num);

        if (result != 1 || getchar() != '\n') {
            printf("\nInvalid input! The ID must contain only digits\n");
            SLEEP(2);
            while (getchar() != '\n');
            printf("\n");
            result = 0;
        }
    } while (result != 1);

    
    if (!is_id_unique(head, id_num)) {
        printf("\nError: A student with ID %ld already exists!\n", id_num);
        SLEEP(2);
        return head;
    }
    

    do {
        printf("Enter student grade: ");
        result = scanf("%f", &grade);

        if (result != 1 || getchar() != '\n' || grade < 0 || grade > 100) {
            printf("\nInvalid input! Make sure that grade contains only digits and it is in the range [0,100]\n");
            SLEEP(1);
            if (result != 1) while (getchar() != '\n');
            printf("\n");
            result = 0;
        }
    } while (result != 1);

    Tstudent* new_student = malloc(sizeof(Tstudent));
    if (!new_student) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(new_student->name, name);
    new_student->id_num = id_num;
    new_student->grade = grade;
    new_student->next = head;
    head = new_student;
}

    return head;
}

void delete_last_student(Tstudent** head) {
    if (!(*head)) return;
    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    Tstudent* temp = *head;
    while (temp->next->next) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void studentcount(Tstudent* head)
{
    if (!head) {
        printf("\nNo students in the list.\n");
        return;
    }
    
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    printf("\n%d student(s) in the list\n\n", count);
}


void display_list(Tstudent* head) {
    if (!head) {
        printf("No students in the list.\n");
        return;
    }

    printf("\n%-30s %-15s %-10s\n", "Name", "ID Number", "Grade");
    printf("------------------------------------------------------------\n");

    while (head) {
        printf("%-30s %-15ld ", head->name, head->id_num);

        if (head->grade < 65) 
            printf("\033[0;31m"); // Set text color to red
        else
            printf("\033[0m"); // Reset text color to default

        printf("%-10.2f\033[0m\n", head->grade);
        head = head->next;
    }
}

int find_student(Tstudent* head, long id) {
    while (head) {
        if (head->id_num == id) {
            printf("\n%-30s %-15s %-10s\n", "Name", "ID Number", "Grade");
            printf("------------------------------------------------------------\n");

            printf("%-30s %-15ld ", head->name, head->id_num);

            if (head->grade < 65) 
                printf("\033[0;31m"); // Set text color to red
            else
                printf("\033[0m"); // Reset text color to default

            printf("%-10.2f\033[0m\n", head->grade);
            return 1;
        }
        head = head->next;
    }
    printf("\nStudent with ID %ld not found.\n", id);
    return 0;
}

void sort_list(Tstudent** head) {
    if (!(*head) || !(*head)->next) return;
    int swapped;
    Tstudent *ptr1, *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            if (ptr1->grade < ptr1->next->grade) {
                char temp_name[30];
                long temp_id;
                float temp_grade;

                strcpy(temp_name, ptr1->name);
                temp_id = ptr1->id_num;
                temp_grade = ptr1->grade;

                strcpy(ptr1->name, ptr1->next->name);
                ptr1->id_num = ptr1->next->id_num;
                ptr1->grade = ptr1->next->grade;

                strcpy(ptr1->next->name, temp_name);
                ptr1->next->id_num = temp_id;
                ptr1->next->grade = temp_grade;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void split_and_sort_list(Tstudent* head, Tstudent** low, Tstudent** high) {
    Tstudent* current = head;
    Tstudent* low_tail = NULL;
    Tstudent* high_tail = NULL;

    while (current) {
        Tstudent* next_node = current->next;
        current->next = NULL;

        if (current->grade >= 65) {
            if (!*high) {          // *high 
                *high = current;
                high_tail = current;
            } else {
                high_tail->next = current;
                high_tail = current;
            }
        } else {
            if (!*low) {
                *low = current;
                low_tail = current;
            } else {
                low_tail->next = current;
                low_tail = current;
            }
        }
        current = next_node;
    }

    sort_list(low);
    sort_list(high);
}

Tstudent* merge_sorted_lists(Tstudent* low, Tstudent* high) {
    if (!high) return low;
    if (!low) return high;

    Tstudent* tail = high;
    while (tail->next) {
        tail = tail->next;
    }

    tail->next = low;

    return high;
}

float average_exam(Tstudent* head) {
    if (!head) return 0.0;
    int count = 0;
    float total = 0.0;
    while (head) {
        total += head->grade;
        count++;
        head = head->next;
    }
    float avg = total / count;
    printf("\nExam average: %.2f\n", avg);
    if (avg >= 65) {
        printf("\033[0;32mGoing to strasbourg this year ;)).\033[0m\n");
    } else if (avg >= 50) {
        printf("\033[0;33mAverage.\033[0m\n");
    } else {
        printf("\033[0;31mBelow average.\033[0m\n");
    }
    return avg;
}

void free_list(Tstudent* head) {
    Tstudent* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}