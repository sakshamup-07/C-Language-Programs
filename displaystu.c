#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { perror("File open failed"); return; }
    Student s;
    printf("Enter Roll No: "); scanf("%d", &s.roll);
    getchar(); // flush newline
    printf("Enter Name: "); fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline
    printf("Enter Marks: "); scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { perror("File open failed"); return; }
    Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { perror("File open failed"); return; }
    int roll;
    printf("Enter Roll No to search: ");
    scanf("%d", &roll);
    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            printf("Found: Roll %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("No record found!\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { perror("File open failed"); return; }
    FILE *temp = fopen("temp.dat", "wb");
    int roll;
    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);
    Student s;
    int deleted = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            deleted = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    if (deleted) printf("Record deleted.\n");
    else printf("No record found.\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
