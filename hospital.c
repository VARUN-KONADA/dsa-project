#include <stdio.h>

#define MAX_PATIENTS 100

typedef struct Patient
{
    char name[50];
    int priority;
    int age;
    char disease[100];
} patient;

patient patients[MAX_PATIENTS];

int patient_count = 0;
int front = 0;
int rear = -1;

void register_patient(void);
void view_waiting_patients(void);
void treat_next_patient(void);
void view_patient_count(void);
void exit_code(void);
void adjust_queue(void);

int main()
{
    int choice = 0;
    while(choice != 5)
    {
        printf("\n------------MENU-------------\n");
        printf("1. Register new patient\n");
        printf("2. View waiting patients\n");
        printf("3. Treat next patient\n");
        printf("4. View patient count\n");
        printf("5. exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: register_patient();
                    break;
            case 2: view_waiting_patients();
                    break;  
            case 3: treat_next_patient();
                    break;
            case 4: view_patient_count();
                    break;
            case 5: exit_code();
                    break;
            default : printf("invalid choice !");
        }
                
    }
    return 0;
}

void register_patient()
{
    if(patient_count >= MAX_PATIENTS)
    {
        printf("Patient registration is full. Cannot register more patients.\n");
        return;
    }
    patient new_patient;
    printf("Enter patient name: ");
    scanf(" %49[^\n]", new_patient.name);
    printf("priorities:\n1. Critical\n2. Serious\n3. Stable\n");
    do 
    {
        printf("Enter patient priority (1-3): ");
        scanf("%d", &new_patient.priority);
    } while (new_patient.priority < 1 || new_patient.priority > 3);

    printf("Enter patient age: ");
    scanf("%d", &new_patient.age);
    printf("Enter patient disease: ");
    scanf(" %99[^\n]", new_patient.disease);

    rear = (rear + 1) % MAX_PATIENTS;
    patients[rear] = new_patient;
    patient_count++;
    adjust_queue();
    printf("Patient registered successfully!\n");
}

void adjust_queue()
{
    int temp = rear;
    int i = 0;
    while(i < patient_count - 1)
    {
        int prev = (temp - 1 + MAX_PATIENTS) % MAX_PATIENTS;
        if(patients[temp].priority < patients[prev].priority)
        {
            patient temp_patient = patients[temp];
            patients[temp] = patients[prev];
            patients[prev] = temp_patient;
        }
        else
        {
            break;
        }
        temp = prev;
        i++;
    }
    return;
}

void view_waiting_patients()
{
    if(patient_count == 0)
    {
        printf("No patients are waiting.\n");
        return;
    }
    int index = front;
    printf("Waiting patients:\n");
    for(int i = 0; i < patient_count; i++)
    {
        printf("Name: %s, Priority: %d, Age: %d, Disease: %s\n", patients[index].name, patients[index].priority, patients[index].age, patients[index].disease);
        index = (index + 1) % MAX_PATIENTS;
    }
}

void treat_next_patient()
{
    if(patient_count == 0)
    {
        printf("No patients are waiting to be treated.\n");
        return;
    }
    printf("Treating patient: %s\n", patients[front].name);
    printf("Priority: %d, Age: %d, Disease: %s\n", patients[front].priority, patients[front].age, patients[front].disease);
    front = (front + 1) % MAX_PATIENTS;
    patient_count--;
}

void view_patient_count()
{
    printf("Total number of patients waiting: %d\n", patient_count);
}

void exit_code()
{
    printf("Exiting the program.....\n");
}