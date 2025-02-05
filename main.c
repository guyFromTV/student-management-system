#include "dsaproject.c"

int main() {
    Tstudent* students = NULL;
    Tstudent* low = NULL;
    Tstudent* high = NULL;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("\033[0;32m1. Add student(s)\033[0m\n");
        printf("2. Count students\n");
        printf("3. Search for a student\n");
        printf("4. Display student list\n");
        printf("5. Sort the list by grade\n");
        printf("6. Split, sort, and merge lists by grade\n");
        printf("7. Calculate exam average\n");
        printf("\033[0;31m8. Delete last element\n");
        printf("9. Free list\n");
        printf("10. Exit\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                students = enter_students(students);
                break;
            case 2:
                studentcount(students);
                SLEEP(2);
                break;
            case 3: {
                long id;
                printf("Enter student ID to search: ");
                scanf("%ld", &id);
                find_student(students, id);
                SLEEP(2);
                break;
            }
            case 4:
                display_list(students);
                SLEEP(5);
                break;
            case 5:
                sort_list(&students);
                break;
            case 6:
                split_and_sort_list(students, &low, &high);
                printf("\nLow-grade list (below 65):\n");
                display_list(low);
                SLEEP(3);
                printf("\n\nHigh-grade list (65 and above):\n");
                display_list(high);
                SLEEP(3);
                students = merge_sorted_lists(low, high);
                low = NULL;
                high = NULL;
                break;
            case 7:
                average_exam(students);
                SLEEP(3);
                break;
            case 8:
                delete_last_student(&students);
                break;
            case 9:
                free_list(students);
                students = NULL;
                printf("Lists have been freed.\n");
                break;
            case 10:
                free_list(students);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 10);

    return 0;
}