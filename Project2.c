//Rowel Espejo
//Comp 322 Spring 2025
//Project 2

#include <stdio.h>
#include <stdlib.h>

//Data Structs
typedef struct relation {
    int * to_resource;
    //Indicies: Resoucres
    //Values:
    //0 - none
    //1 - Process requested resource
    //2 - Process allocated resorce
} relation;
//Global Variables
int processes = 0;
int resources = 0;
relation * process = NULL;

//Function Prototypes
void print_relations();
void change_relations();
void detect_deadlock();
int detect_deadlock_recursively(int target_index, int current_index);

//Functions
int main(){
    int i;
    int j;
    int option = 0;//Any value other than 4
    //Enter the number of processes
    printf("Enter the number of processes:\n");
    scanf("%d", &processes);
    if(processes <= 0){
        printf("Invalid number of processes:\n");
        return 0;
    }
    //Enter the number of resources
    printf("Enter the number of resources:\n");
    scanf("%d", &resources);
    if(resources <= 0){
        printf("Invalid number of resources:\n");
        return 0;
    }
    //Create the process-to-resource relations
    process = (relation *)malloc(processes * sizeof(relation));
    for(i = 0 ; i < processes; i++){
        process[i].to_resource = (int *)malloc(resources * sizeof(int));
        for(j = 0; j < resources; j++){
            process[i].to_resource[j] = 0;

        }
    }
    //Main loop
    while(option != 4){
        option = 4; //Infinite loop fail safe
        printf("\n1) Print the process-to-resource relations\n");
        printf("2) Change a process-to-resource relation\n");
        printf("3) Detect the system for deadlock\n");
        printf("4) Quit the program\n");
        printf("Enter selection:\n");
        scanf("%d", &option);
    switch (option){
        case 1:
            print_relations();
            break;
        case 2:
            change_relations();
            break;
        case 3:
            detect_deadlock();
            break;
        case 4:
            printf("Goodbye. \n");
            break;
        default: 
            printf("invalid option, try again.\n");
    }
    }
    //Deallocate the process-to-resources relations
    for(i = 0 ; i < processes; i++){
            free(process[i].to_resource);
    }
    free(process);
    return 0;
}//End main
void print_relations(){
    int i;
    int j;
    //Print header row
    for(int j = 0; j < resources; j++){
        printf("\tr%d", j);
    }
    printf("\n");
    //Print every process-to-resource relation as a row
    for(i = 0; i < processes; i++){
        printf("p%d",i);
        for(j = 0; j < resources; j++){
            printf("\t");
            if(process[i].to_resource[j] != 0){
            printf("%d", process[i].to_resource[j]);
            }
        }
        printf("\n");
    }
}//End print relations

void change_relations(){
    int i;
    int process_index = -1;
    int resource_index = -1;
    int new_relation = -1;
    //Enter the process index
    printf("Enter the process index.\n");
    scanf("%d", &process_index);
    if(process_index < 0 || process_index >= processes){
        printf("Invalid process index.\n");
        return;
    }
    //Enter the resource index 
    printf("Enter the resource index.\n");
    scanf("%d", &resource_index);
    if(resource_index < 0 || resource_index >= resources){
        printf("Invalid resource index.\n");
        return;
    }
    //Enter the new relation between the process and resource
    printf("Enter the new relation (0: None, 1: P requests R, 2: P allocated R):\n");
    scanf("%d", &new_relation);
    //Preform a different action based on the new relation
    switch(new_relation){
        case 0:
            process[process_index].to_resource[resource_index] = 0;
            printf("There is now no relation between process %d and resource %d .\n",process_index, resource_index);
            break;
        case 1: //Proecess requested resource
            process[process_index].to_resource[resource_index] = 1;
            printf("Process %d is now requesting to use resource %d.\n",process_index, resource_index);
            return;
        case 2: //Process allocated resource
            for(i = 0; i < processes; i++){
                if(i != process_index && process[i].to_resource[resource_index] == 2){
                    printf("Process %d cannot be allocated resource %d because process %d is using it.\n",process_index,resource_index, i);
                    return;
                }
            }
            process[process_index].to_resource[resource_index] = 2;
            printf("Process %d has been allocated resource %d for usage.\n",process_index,resource_index);
            break; 
        default://Error
        printf("Invalid relation value.\n");
    }
}//End change relations

void detect_deadlock(){
    int i;
    int j;
    int k;
    int dlfound = 0;
    //Check all process-to-resource relations for a directed cycle of dependencies
    for(i = 0; i < processes; i++){
        for(j = 0; j < resources; j++){
            if(process[i].to_resource[j] == 2){
                //Preform an additonal for-loop if an allocation is detected
                for(k = 0; k < processes; k++){
                    if(process[k].to_resource[j] == 1){
                        //Run the recursive function if a request is detected
                        if(detect_deadlock_recursively(i, k)){
                            //Deadlock detected - Print the request and the allocation 
                            dlfound = 1;
                            printf("Process %d is requesting resource %d.\n",k,j);
                            printf("Process %d is allocated resource %d.\n",i,j);
                            return;
                        }
                    }//End of the Request Check
                }//End of Third Loop
            }//End of Allocation Check
        }//End of Second Loop
    }//End of the First Loop
    //No deadlocks exist if all relation comparisons are exhausted
    if(dlfound == 0)
    printf("The system is not deadlocked, and is currently safe.\n");
}//End detect deadlock

int detect_deadlock_recursively(int target_index, int current_index){
    //Check all process-to-resource relations for a directed cucle fo dependencies
    int j;
    int k;
    int prnt = 0;
    for(j = 0; j < resources; j++){
        if(process[current_index].to_resource[j] == 2){
            for(k = 0; k < processes; k++){
                if(process[k].to_resource[j] == 1){
                    //Preform addition evalulatios if a request if detected
                    if(k == target_index){
                        //Deadlock detected - Print the request and the allocation 
                        if(prnt == 0){
                        printf("The system is deadlocked due to the following relations: \n");
                        prnt = 1;
                        }
                        printf("Process %d is requesting resource %d.\n",k,j);
                        printf("Process %d is allocated resource %d\n",current_index,j);
                        return 1;
                    }
                        else if(detect_deadlock_recursively(target_index,k)){
                        printf("Process %d is requesting resource %d.\n",k,j);
                        printf("Process %d is allocated resource %d.\n",current_index,j);
                        return 1;
                        }

                }//End of Request Check
            }//End of Second Loop
        }//End of Allocation Check
    }//End of first loop
    //Return false if all relation comparisons are exhausted
    return 0;
}//End detect deadlock recursively
