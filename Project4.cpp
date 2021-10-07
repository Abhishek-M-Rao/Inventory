// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Abhishek Rao
// amr7999
// Slip days used: 1
// Fall 2021
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
int count_diapers = 0;
int count_rattles = 0;
int count_bottles = 0;
/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	count_diapers = 0;
    count_rattles = 0;
    count_bottles = 0;
    for(int i=0; i<num_customers; i++){
        customers[i].diapers = 0;
        customers[i].rattles = 0;
        customers[i].bottles= 0;
        StringDestroy(&(customers[i].name));
    }
    num_customers = 0;
}

void DoInventory(String Item, int countI);
void DoInventory(String Item, int countI){
    String diapers = StringCreate("Diapers");
    String rattles = StringCreate("Rattles");
    String bottles = StringCreate("Bottles");
    if (StringIsEqualTo(&diapers, &Item)){
        count_diapers += countI;
    }
    else if(StringIsEqualTo(&rattles, &Item)){
        count_rattles += countI;
    }
    else if(StringIsEqualTo(&bottles, &Item)){
        count_bottles += countI;
    }
    StringDestroy(&diapers);
    StringDestroy(&rattles);
    StringDestroy(&bottles);
    return; //this means that none of them were found, or it is just at the end
}


void processSummarize() {
    printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n", count_bottles, count_diapers, count_rattles);
    printf("we have had a total of %d different customers\n", num_customers);
    //now we find max
    Customer maxDiapersMan;
    Customer maxRattlesMan;
    Customer maxBottlesMan;
    maxDiapersMan.diapers = 0;
    maxRattlesMan.rattles = 0;
    maxBottlesMan.bottles = 0;
    for(int i = 0; i < num_customers; i++){ //need to resolve case where there is a tie
        if(customers[i].diapers > maxDiapersMan.diapers){
            //maxDiapersMan.diapers = customers[i].diapers;
            //maxDiapersMan.name = customers[i].name;
            maxDiapersMan = customers[i]; //this achieves the above two lines
        }
        if(customers[i].rattles > maxRattlesMan.rattles){
            maxRattlesMan = customers[i];
        }
        if(customers[i].bottles > maxBottlesMan.bottles){
            maxBottlesMan = customers[i];
        }
    }
    if(maxBottlesMan.bottles == 0){
        printf("no one has purchased any Bottles\n");
    } else{
        StringPrint(&(maxBottlesMan.name));
        printf(" has purchased the most Bottles (%d)\n", maxBottlesMan.bottles);
    }
    if(maxDiapersMan.diapers == 0){
        printf("no one has purchased any Diapers\n");
    } else{
        StringPrint(&(maxDiapersMan.name));
        printf(" has purchased the most Diapers (%d)\n", maxDiapersMan.diapers);
    }
    if(maxRattlesMan.rattles == 0){
        printf("no one has purchased any Rattles\n");
    } else{
        StringPrint(&(maxRattlesMan.name));
        printf(" has purchased the most Rattles (%d)\n", maxRattlesMan.rattles);
    }

}

void processPurchase() {
    String diapers = StringCreate("Diapers");
    String rattles = StringCreate("Rattles");
    String bottles = StringCreate("Bottles");
    String custName;
    String itemType;
    int wantedNum;
    int indexCapture;
    int flag_newname = 0; //1 if name already exists, 0 if they are new
    readString(&custName);
    for(int index = 0; index < num_customers; index++){
        if(StringIsEqualTo(&(customers[index].name), &custName)){
            flag_newname = 1;
            indexCapture = index; //issue never used
            break;
        }
    }
    readString(&itemType);
    readNum(&wantedNum);
    if (StringIsEqualTo(&itemType, &diapers)) {
        if ((count_diapers - wantedNum) < 0) {
                printf("Sorry ");
                StringPrint(&custName);
                printf(", we only have %d ", count_diapers);
                StringPrint(&itemType);
                printf("\n");
            }
        else {
            if(flag_newname == 0) { //in the case of new customer
                customers[num_customers].name = StringDup(&custName); //num_customers is the next entry in array
                customers[num_customers].diapers = wantedNum;
                count_diapers = count_diapers - wantedNum;
                num_customers++; //increments num_customers, now onto the next
                }
            if(flag_newname == 1){
                customers[indexCapture].diapers += wantedNum;
                count_diapers = count_diapers - wantedNum;
            }
        }
    }
    if (StringIsEqualTo(&itemType, &rattles)) { //case 2 is rattles
        if ((count_rattles - wantedNum) < 0) {
            printf("Sorry ");
            StringPrint(&custName);
            printf(", we only have %d ", count_rattles);
            StringPrint(&itemType);
            printf("\n");
        }
        else {
            if(flag_newname == 0) { //in the case of new customer
                customers[num_customers].name = StringDup(&custName); //num_customers is the next entry in array
                customers[num_customers].rattles = wantedNum;
                count_rattles = count_rattles - wantedNum;
                num_customers++; //increments num_customers, now onto the next
            }
            if(flag_newname == 1){
                customers[indexCapture].rattles += wantedNum;
                count_rattles = count_rattles - wantedNum;
            }
        }
    }
    if (StringIsEqualTo(&itemType, &bottles)) { //case 3 is bottles
        if ((count_bottles - wantedNum) < 0) {
            printf("Sorry ");
            StringPrint(&custName);
            printf(", we only have %d ", count_bottles);
            StringPrint(&itemType);
            printf("\n");
        }
        else {
            if(flag_newname == 0) { //in the case of new customer
                customers[num_customers].name = StringDup(&custName); //num_customers is the next entry in array
                customers[num_customers].bottles = wantedNum;
                count_bottles = count_bottles - wantedNum;
                num_customers++; //increments num_customers, now onto the next
            }
            if(flag_newname == 1){
                customers[indexCapture].bottles += wantedNum;
                count_bottles = count_bottles - wantedNum;
            }
        }
    }

    StringDestroy(&diapers);
    StringDestroy(&rattles);
    StringDestroy(&bottles);
    StringDestroy(&custName);
    StringDestroy(&itemType);
}


void processInventory() {
    int countI = 0;
    String Item;
    readString(&Item);
    readNum(&countI);
    DoInventory(Item, countI);
    StringDestroy(&Item);
}
