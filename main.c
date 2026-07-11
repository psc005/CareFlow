#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//patient stack 
typedef struct Patient{
    char *name;
    int age; 
    int painLevel; 
    int severity; 
    int priorityScore;
    time_t arrivalTime;
    struct Patient *next; 
}Patient; 

//function prototypes
void displayMenu(); //complete
int isEmpty(Patient **head); //complete 
Patient* createPatient(); //complete 
void updatePriorities(Patient **head);
void printPatient(Patient *Patient); //complete 
int calculatePriority(Patient *Patient); //complete 
void addPatient(Patient **head, Patient *newPatient); //complete 
void displayPatients(Patient *head); //complete 
Patient* searchPatient(Patient *head, char *name); //complete 
void editPatient(Patient **Head); 
void showNextPatient(Patient **head); //complete 
void displayStatistics(Patient *head); //complete 
void freeList(Patient *head); //complete 

int main(){
    Patient *head = NULL; 
    Patient *newPatient = NULL; 
    int choice; 
    displayMenu(); 
    

    if (scanf("%d", &choice) != 1) {
    printf("Invalid input.\n");
    while(getchar() != '\n'); // clear bad input
    continue;
    }
    
    switch(choice){
        case 1:
            newPatient = createPatient(); 
            if(newPatient){
                addPatient(&head, newPatient); 
                printf("Patient added successfully!\n"); 
            }
            break; 

        case 2:
            showNextPatient(&head); 
            break; 

        case 3:
            editPatient(&head); 
            break; 

        case 4:
            displayPatients(head); 
            break; 

        case 5:
            displayStatistics(head); 
            break; 

        case 6:
            printf("Exiting the program...\n"); 
            break;

        default:
            printf("Invalid choice.\n"); 
        
    }

freeList(head); 
    
return 0; 

}

void displayMenu(){
    printf("Please enter the number corresponding to the menu choice:\n\n");
    printf("1: Add new patient\n2: Get next patient\n3: Update patient information\n4: Display waitlist\n5: Display ER statistics\n6: Exit\n\n");
    
}

int isEmpty(Patient** head) {
    if (*head == NULL)
        return 1;

    return 0;
}

Patient* createPatient() {

    char name[50];
    int age;
    int painLevel;
    int severity;

    printf("Enter Name: ");
    scanf("%49s", name);

    printf("Enter Age: ");
    scanf("%d", &age);

    printf("Enter Pain Level (1-10): ");
    scanf("%d", &painLevel);

    printf("Enter Severity (1 = Non-Urgent, 2 = Urgent, 3 = Critical): ");
    scanf("%d", &severity);

    Patient *newPatient = malloc(sizeof(Patient));
    if (newPatient == NULL)
        return NULL;

    newPatient->name = malloc(strlen(name) + 1);
    if (newPatient->name == NULL) {
        free(newPatient);
        return NULL;
    }

    strcpy(newPatient->name, name);

    newPatient->age = age;
    newPatient->painLevel = painLevel;
    newPatient->severity = severity;
    newPatient->priorityScore = calculatePriority(newPatient);
    newPatient->arrivalTime = time(NULL);
    newPatient->next = NULL;

    return newPatient;
}

int calculatePriority(Patient *Patient){
    int priority = 0; 

    //severity of condition 
    if(Patient->severity == 3)
        priority += 50; 
    else if (Patient->severity == 2)
        priority += 30; 
    else
        priority += 10; 

    //age of patient 
    if(Patient->age >= 65)
        priority +=10; 
    else if(Patient->age <= 12)
        priority += 5;

    //pain level patient 
    if(Patient->painLevel > 5)
        priority +=10; 
    else if(Patient->painLevel <= 5)
        priority += 5;

    return priority;
}

void updatePriorities(Patient **head){
    if(isEmpty(head))
        return;

    Patient *current = *head;
    Patient *newHead = NULL;

    while(current != NULL){

        Patient *next = current->next;

        time_t currentTime = time(NULL);
        int waitMinutes = (currentTime - current->arrivalTime) / 60;

        current->priorityScore = calculatePriority(current) + (waitMinutes / 30) * 5;

        current->next = NULL;

        addPatient(&newHead, current);

        current = next;
    }

    *head = newHead;
}


void addPatient(Patient **head, Patient *newPatient){
    newPatient->priorityScore = calculatePriority(newPatient);
    if(*head == NULL){
        *head = newPatient; 
        newPatient->next = NULL; 
        return; 
    }

    if(newPatient->priorityScore > (*head)->priorityScore){
        newPatient->next = *head; 
        *head = newPatient; 
        return; 
    }

    Patient *current = *head; 
 while (current->next != NULL &&
           current->next->priorityScore >= newPatient->priorityScore)
    {
        current = current->next;
    }

    newPatient->next = current->next;
    current->next = newPatient;
}

void printPatient(Patient* patient) {
    if(patient == NULL)
        return; 
    
    time_t currentTime = time(NULL);
    
    int waitMinutes = (currentTime - patient->arrivalTime) / 60;
    
    printf("Patient name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Pain Level: %d\n", patient->painLevel);
    printf("Priority Score: %d\n", patient->priorityScore);
    printf("Wait Time: %d minutes\n", waitMinutes);
    printf("\n\n");
}

void displayPatients(Patient *head){
    if (head == NULL){
        printf("No patients currently waiting.\n"); 
        return;
    }
    Patient* currentPtr = head;
    
    while(currentPtr){
        printPatient(currentPtr); 
        currentPtr = currentPtr->next; 
    }

}

Patient* searchPatient(Patient *head, char *name){
    
    Patient *curr = head;

    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
            return curr;

        curr = curr->next;
    }

    printf("PATIENT NOT FOUND!!\n"); 
    return NULL;
    
}

void editPatient(Patient** Head) {
    char* searchName = malloc(50 * sizeof(char));
    printf("Enter a name:\n");
    scanf("%s", searchName);

    if (*Head == NULL) {
        free(searchName);
        return;
    }

    Patient* found = searchPatient(*Head, searchName);
    if (found == NULL) {
        free(searchName);
        return;
    }

    printPatient(found);

    int choice;
    do {
        printf("1. Edit name\n2. Edit age\n3. Edit pain level\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char* newName = malloc(50 * sizeof(char));
            printf("Enter new name:\n");
            scanf("%s", newName);
            free(found->name);
            found->name = malloc((strlen(newName) + 1) * sizeof(char));
            strcpy(found->name, newName);
            free(newName);
            break;
        }
        case 2: {
            int newAge;
            printf("Enter new age:\n");
            scanf("%d", &newAge);
            found->age = newAge;
            found->priorityScore = calculatePriority(found);
            break;
        }
        case 3: {
            int newPainLevel;
            printf("Enter new pain level:\n");
            scanf("%d", &newPainLevel);
            found->painLevel = newPainLevel;
            found->priorityScore = calculatePriority(found);
            break;
        }
        case 4:
            break;
        }

        printPatient(found);

    } while (choice != 4);

    free(searchName);
}

void showNextPatient(Patient **head){
    if(isEmpty(head)){
        printf("No patients currently waiting.\n"); 
        return; 
    }

    Patient *nextPatient = *head; 

    printf("Next Patient:\n"); 
    printPatient(nextPatient); 
    *head = nextPatient->next; 
    free(nextPatient->name); 
    free(nextPatient); 
}

void displayStatistics(Patient *head){
    if(isEmpty(&head)){
        printf("No patients currently waiting.\n"); 
        return;
    }

    int totalPatients = 0; 
    int critical = 0; 
    int urgent = 0; 
    int nonUrgent = 0; 

    Patient *highestPriority = head; 
    Patient *curr = head; 

    while(curr){
        totalPatients++; 
        if(curr->severity == 3){
            critical++; 
        }
        else if(curr->severity == 2){
            urgent++; 
        }
        else{
            nonUrgent++; 
        }

        curr = curr->next; 
    }

    printf("\nER Statistics:\n********************\n");
    printf("Total patients waiting: %d\n\n", totalPatients); 
    printf("Highest priority patient:\n"); 
    printf("Name: %s\n", highestPriority->name); 
    printf("Priority Score: %d\n\n", highestPriority->priorityScore); 
    printf("Severity Breakdown:\n");
    printf("Critical: %d\n", critical);
    printf("Urgent: %d\n", urgent);
    printf("Non-Urgent: %d\n", nonUrgent);

    printf("********************\n\n"); 
}

void freeList(Patient *head){

    Patient *curr = head; 
    Patient *next; 

    while(curr){
        next = curr->next; 
        free(curr->name); 
        free(curr); 
        curr = next; 
    }
}

