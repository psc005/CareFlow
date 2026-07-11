#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
void displayMenu();
Patient* createPatient(); 
int calculatePriority(Patient *Patient); 
void addPatient(Patient **head, Patient *newPatient); 
void displayPatients(Patient *head); 
Patient* searchPatient(Patient *head, int patientID); 
void editPatient(Patient **Head); 
void showNextPatient(Patient **head);
void displayStatistics(Patient *head); 
void freeList(Patient *head);

//patient stack 
typedef struct Patient{
    int id; 
    char name[50];
    int age; 
    int painLevel; 
    int priorityScore;
    struct Patient *next; 
}Patient; 

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

