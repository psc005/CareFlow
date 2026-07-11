#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//patient stack 
typedef struct Patient{
    char *name;
    int age; 
    int painLevel; 
    int severity; 
    int priorityScore;
    struct Patient *next; 
}Patient; 

//function prototypes
void displayMenu(); //complete
int isEmpty(Patient **head); //complete 
Patient* createPatient(); //complete 
void printPatient(Patient *Patient); 
int calculatePriority(Patient *Patient); //complete 
void addPatient(Patient **head, Patient *newPatient); 
void displayPatients(Patient *head); 
Patient* searchPatient(Patient *head, char *name); 
void editPatient(Patient **Head); 
void showNextPatient(Patient **head); //complete 
void displayStatistics(Patient *head); //complete 
void freeList(Patient *head); //complete 

int main(){
    Patient *head = NULL; 
    int choice; 
    displayMenu(); 
    do{
        switch(choice){
        case 1:
            //create a patient 
            //calculate priority 
            //add patient to the list 
            break; 

        case 2:
            //display all waiting patients
            break; 

        case 3:
            //call the next patient 
            break; 

        case 4:
            //edit patient information 
            break; 

        case 6:
            //display statistics
            break; 

        case 7:
            //exit the program 
            break;

        
        }
    } while(choice != 7); 

freeList(head); 
    
return 0; 

}

void displayMenu(){
    printf("Please enter the number corresponding to the menu choice:\n\n");
    printf("1: Add new patient\n2: Get next patient\n3: Update patient information\n4: Display waitlist\n5: Display ER statistics\n6: Exit\n\n");
    
}

int isEmpty(Patient** head) {
    if (head == NULL)
        return 1;

    return 0;
}

Patient* createPatient(){
    char* name;
    int age;
    int painLevel;
    int priorityScore;

    printf("Enter Name:\n");
    scanf("%s", &name);
    printf("Name: %s", name);

    printf("Enter Age:\n");
    scanf("%d", &age);
    printf("Age: %d", age);

    printf("Enter pain level:\n");
    scanf("%d", &painLevel);
    printf("Pain Level: %d", painLevel);

    printf("Enter priority score:\n");
    scanf("%d", &priorityScore);
    printf("Priority Score: %d", priorityScore);
    
    Patient* newPatient = malloc(sizeof(Patient));
    if (newPatient == NULL)
        return NULL;

    newPatient->age = age;
    newPatient->painLevel = painLevel;
    newPatient->priorityScore = priorityScore;
    char* ptr = malloc((strlen(name) + 1) * sizeof(char));
    if (ptr == NULL)
        return NULL;
    strcpy(newPatient->name, ptr);
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
    if (isEmpty(patient))
        return;
    printf("%s\n", patient->name);
    printf("%d\n", patient->age);
    printf("%d\n", patient->painLevel);
    printf("%d\n", patient->priorityScore);

    printf("\n\n");
}

void displayPatients(Patient *head){
    if (head == NULL)
        return NULL;
    Patient* currentPtr = head;
    while (currentPtr->next) {
        printf("%s\n", currentPtr->name);
        printf("%d\n", currentPtr-> age);
        printf("%d\n", currentPtr->painLevel);
        printf("%d\n", currentPtr->priorityScore);
        currentPtr = currentPtr->next;

        printf("\n\n");
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

void editPatient(Patient **Head){
    
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
    int crital = 0; 
    int urgemt = 0; 
    int nonUrgent = 0; 

    Patient *highestPriority = head; 
    Patient *curr = head; 

    while(!curr){
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
    printf(Name: %s\n", highestPriority->name); 
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

    while(!curr){
        next = curr->next; 
        free(curr); 
        curr = next; 
    }
}

