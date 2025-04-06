#include <stdio.h>
#include <string.h>
typedef struct {
    int bedID;
    int isOccupied;
    char patient[100];
}Bed;
Bed beds[50];
void initializebeds() {
    for (int i=0;i<50;i++) {
        beds[i].bedID=i+1;
        beds[i].isOccupied=0;
        strcpy(beds[i].patient,"None");
    }
}
void assignbed() {
    char name[100];
    printf("Enter patient name: ");
    scanf("%s",name);
    for (int i = 0; i < 50; i++){
        if (beds[i].isOccupied==0){
            beds[i].isOccupied = 1;
            strcpy(beds[i].patient, name);
            printf("Patient '%s' assigned to bed ID %d\n",name,beds[i].bedID);
            return;
        }
    }
    printf("No available beds right now.\n");
}
void showtotal() {
    int occupied = 0;
    for (int i = 0; i < 50; i++) {
        if (beds[i].isOccupied) {
            occupied++;
        }
    }
    printf("\n--- Bed Status ---\n");
    printf("Total Beds     : %d\n",50);
    printf("Occupied Beds  : %d\n",occupied);
    printf("Available Beds : %d\n",50-occupied);
}

int main() {
  initializebeds();
	assignbed();
	showtotal();
    return 0;
}
