#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//patient stack 
typedef struct Patient{
    char name[50];
    int age; 
    int painLevel; 
    int severity; 
    int priorityScore;
    struct Patient *next; 
}Patient; 

//function prototypes
void displayMenu(); //complete
Patient* createPatient(); 
int calculatePriority(Patient *Patient); 
void addPatient(Patient **head, Patient *newPatient); 
void displayPatients(Patient *head); 
Patient* searchPatient(Patient *head, int patientID); 
void editPatient(Patient **Head); 
void showNextPatient(Patient **head);
void displayStatistics(Patient *head); 
void freeList(Patient *head);

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

//free allocated memory 

return 0; 

}

void displayMenu(){
    printf("Please enter the number corresponding to the menu choice:\n\n");
    printf("1: Add new patient\n2: Get next patient\n3: Update patient information\n4: Display waitlist\n5: Display ER statistics\n6: Exit\n\n");
    
}

Patient* createPatient(){
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
    
}

void displayPatients(Patient *head){
}

Patient* searchPatient(Patient *head, int patientID){
    
}

void editPatient(Patient **Head){
    
}

void showNextPatient(Patient **head){
}

void displayStatistics(Patient *head){
}

void freeList(Patient *head){
}

