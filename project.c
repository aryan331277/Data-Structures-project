#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100
#define FILE_NAME "patients.txt"

// Medical History Record Node
typedef struct Record {
    char data[200];
    struct Record* next;
} Record;

// Patient Node
typedef struct Patient {
    char name[50];
    int age;
    char disease[50];
    int severity;
    Record* history;
    struct Patient* next;
    struct Patient* prev;
} Patient;

Patient* head = NULL;

// Function declarations
void savePatientsToFile();
Patient* findPatient(char name[]);

// Stack operations
void addMedicalRecord(Patient* patient, char record[]) {
    Record* newRecord = (Record*)malloc(sizeof(Record));
    strcpy(newRecord->data, record);
    newRecord->next = patient->history;
    patient->history = newRecord;
    printf("Medical record added for %s.\n", patient->name);
}

void getLatestRecord(Patient* patient) {
    if (!patient->history) {
        printf("No medical history available for %s.\n", patient->name);
        return;
    }
    Record* temp = patient->history;
    printf("🩺 Latest Record: %s\n", temp->data);
    patient->history = temp->next;
    free(temp);
}

void viewAllHistory(Patient* patient) {
    printf("Medical History for %s:\n", patient->name);
    Record* temp = patient->history;
    if (!temp) {
        printf("No records found.\n");
        return;
    }
    while (temp) {
        printf("- %s\n", temp->data);
        temp = temp->next;
    }
}

// Patient management
void savePatientsToFile() {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    Patient* temp = head;
    while (temp) {
        fprintf(file, "%s %d %s %d\n", temp->name, temp->age, temp->disease, temp->severity);
        temp = temp->next;
    }
    fclose(file);
}

void registerPatient(char name[], int age, char disease[], int severity) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->severity = severity;
    newPatient->next = NULL;
    newPatient->prev = NULL;
    newPatient->history = NULL;

    if (!head) {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newPatient;
        newPatient->prev = temp;
    }
    savePatientsToFile();
    printf("Patient Registered!\n");
}

void loadPatientsFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    char name[50], disease[50];
    int age, severity;
    while (fscanf(file, "%s %d %s %d", name, &age, disease, &severity) != EOF) {
        registerPatient(name, age, disease, severity);
    }
    fclose(file);
}

Patient* findPatient(char name[]) {
    Patient* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void displayPatients() {
    Patient* temp = head;
    if (!temp) {
        printf("No patients.\n");
        return;
    }
    while (temp) {
        printf("Name: %s | Age: %d | Disease: %s | Severity: %d\n",
               temp->name, temp->age, temp->disease, temp->severity);
        temp = temp->next;
    }
}

void deletePatient(char name[]) {
    Patient* temp = findPatient(name);
    if (!temp) {
        printf("Patient not found.\n");
        return;
    }

    // Remove from list
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    if (temp == head) head = temp->next;

    // Free history stack
    Record* r = temp->history;
    while (r) {
        Record* del = r;
        r = r->next;
        free(del);
    }
    free(temp);
    savePatientsToFile();
    printf("Patient Deleted.\n");
}

void menu() {
    int choice;
    char name[50], disease[50], record[200];
    int age, severity;

    while (1) {
        printf("\n Menu:\n");
        printf("1. Register Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Add Medical History\n");
        printf("6. View Latest Record\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        Patient* p;

        switch (choice) {
            case 1:
                printf("Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Age: ");
                scanf("%d", &age);
                getchar();

                printf("Disease: ");
                fgets(disease, sizeof(disease), stdin);
                disease[strcspn(disease, "\n")] = 0;

                printf("Severity (1-10): ");
                scanf("%d", &severity);
                getchar();

                registerPatient(name, age, disease, severity);
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                p = findPatient(name);
                if (p) {
                    printf("Found: %s | Age: %d | Disease: %s | Severity: %d\n",
                           p->name, p->age, p->disease, p->severity);
                } else {
                    printf("Not Found\n");
                }
                break;

            case 4:
                printf("Enter Name to Delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                deletePatient(name);
                break;

            case 5:
                printf("Patient Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                p = findPatient(name);
                if (p) {
                    printf("Enter Record: ");
                    fgets(record, sizeof(record), stdin);
                    record[strcspn(record, "\n")] = 0;
                    addMedicalRecord(p, record);
                } else {
                    printf("Patient not found.\n");
                }
                break;

            case 6:
                printf("Patient Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                p = findPatient(name);
                if (p) {
                    getLatestRecord(p);
                } else {
                    printf("Patient not found.\n");
                }
                break;

            
            case 7:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

int main() {
    loadPatientsFromFile();
    menu();
    return 0;
}
