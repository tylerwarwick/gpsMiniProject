#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define nameBuf 25

struct position
    {
        double latitude;
        double longitude;
        double altitude;
    };

struct user_t
    {
        char name[nameBuf];
        struct position pos;
        double time;
        double distanceAway;
    };

//Input and storage functions
FILE* openInputFile(char* n);
void storeName(char *name, FILE* inputFile);
void storeData(double *value, FILE* inputFile);
void fillOutStruct(struct user_t *user, FILE* inputFile);

//Math Functions
void distanceFromOurUser(struct user_t ourUser, struct user_t otherUsers[], int size);
struct user_t *closestUser(struct user_t otherUsers[], int size);


int main(void)
{
    //Get input file from user
    printf("Enter a file with the name (as well as path if necessary): ");
    
    char input[1024];
    char *inputStrings[256];            
                                
    char delimit[]=" \t\r\n\v\f"; 
    int argumentCounter = 0;

    if(fgets(input, sizeof input, stdin))                             
        {                                        
            inputStrings[argumentCounter] = strtok(input, delimit);    
            while(inputStrings[argumentCounter] != NULL)                    
            {
                argumentCounter++;
                inputStrings[argumentCounter]=strtok(NULL,delimit);
            }
        }


    //If users enters a file name then attempt to open it
    if (argumentCounter == 1)
    {
        //Attempt to open file given to use from user
        //If file doesn't exist then print ivalid message and exit
        FILE *inputFile = openInputFile(inputStrings[0]);

        //First fill out all of our struct's data
        //Get the number of other users first
        char amountC[5];
        fgets(amountC, sizeof(amountC), inputFile);
        int amount = atoi(&amountC[0]);

        //Initialize our user and array of other users
        struct user_t our_user;
        struct user_t other_users[amount];

        //Store our user's data in corresponding struct
        fillOutStruct(&our_user, inputFile);
        

        //Fill out array of other users
        for (int i = 0; i < amount; i++)
        {
            fillOutStruct(&other_users[i], inputFile);
        }
        

        //Can close our file now because we've taken the data from it
        fclose(inputFile);


        //Get the distances away and find the closest neighbour to our_user
        distanceFromOurUser(our_user, other_users, amount);
        struct user_t *closestPtr = closestUser(other_users, amount);

        printf("Closest person is %s\nHe is %0.2fm away\n", closestPtr->name, closestPtr->distanceAway);
    }

    //If user enters too many agruments (more than 1), exit the program
    else 
    {
        perror("Invalid file inputted");
        exit(1);
    }
    

  

}

//Opens file to be read from
FILE* openInputFile(char* n)
{       
    FILE * readingFile = fopen(n, "r");
    if (readingFile == NULL) 
    {
        perror("Input file couldn't be opened");
        exit(1);

    }

    return readingFile;
}   

//Store names in user's name
void storeName(char *name, FILE* inputFile)
{
    fgets(name, nameBuf, inputFile);
    name[strcspn(name, "\n")] = 0;
}

//Store time and position values in user struct
void storeData(double *value, FILE* inputFile)
{
    char lineContents[nameBuf];
    fgets(lineContents, sizeof(lineContents), inputFile);

    *value = atof(&lineContents[0]);
}

//Fill out entire struct with name and all values
void fillOutStruct(struct user_t *user, FILE* inputFile)
{
    storeName(&user->name[0], inputFile);
    storeData(&user->time, inputFile);
    storeData(&user->pos.latitude, inputFile);
    storeData(&user->pos.longitude, inputFile);
    storeData(&user->pos.altitude, inputFile);
}


//Actual arithimetic performed
//Calculates distance from user and stores in struct
void distanceFromOurUser(struct user_t ourUser, struct user_t otherUsers[], int size)
{
    for (int i = 0; i < size; i++)
    {
        otherUsers[i].distanceAway 
        = (sqrt(pow(ourUser.pos.latitude - otherUsers[i].pos.latitude, 2) + 
        pow(ourUser.pos.longitude - otherUsers[i].pos.longitude, 2) +
        pow(ourUser.pos.altitude - otherUsers[i].pos.altitude, 2)));
    }    
}

//Returns a pointer to the closest other_user to our_user
struct user_t *closestUser(struct user_t otherUsers[], int size)
{
    double min = otherUsers[0].distanceAway;
    struct user_t *closest = &otherUsers[0];

    for (int i = 0; i < size; i++)
    {
        if (otherUsers[i].distanceAway < min)
        {
            min = otherUsers[i].distanceAway;
            closest = &otherUsers[i];
        }
    }
    
    return closest;
}