#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* openInputFile(char* n);
void storeName(char name[], FILE* inputFile);


int main(void)
{
    FILE *x = openInputFile("sample_users.txt");

    char linecontents[50];
    fgets(linecontents, sizeof(linecontents), x);
    fgets(linecontents, sizeof(linecontents), x);
    //fgets(linecontents, sizeof(linecontents), x);
    int z = atoi(&linecontents[0]);
    fclose(x);

    printf("%s\n", linecontents);


}

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

//Function that takes line of text and stores it in variable 
void storeName(char name[25], FILE* inputFile)
{
    fgets(name, sizeof(name), inputFile);
}


//Function that stores mutliple values into a struct
