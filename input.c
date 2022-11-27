#include <stdio.h>
#include <string.h>

struct user_t scan_user_file(char filename[], struct user_t user_2[])
{
    FILE *inputfile_1;
    struct user_t user_1;
    inputfile_1 = fopen(filename, "r");
    int lineCounter = 0, arrayIndex = 0,user_1Counter = 0;
    
    if (inputfile_1 != NULL)
    {
        char line[20];
        while (fgets(line, sizeof line, inputfile_1) != NULL)
        {
            lineCounter++;
            if (lineCounter == 1)
            {
                
                continue;
            }
            else if (lineCounter <= 6)
            {
                if (user_1Counter == 0) 
                {
                    strcpy(user_1.name, strtok(line,"\n"));
                }
                else if (user_1Counter == 1)
                {
                    sscanf(line, "%d", &user_1.time);
                }
                else if (user_1Counter == 2)
                {
                    user_1.lattitude = strtod(line, NULL);
                }
                else if (user_1Counter == 3)
                {
                    user_1.longitude = strtod(line, NULL);
                }
                else if (user_1Counter == 4)
                {
                    user_1.altitude = strtod(line, NULL);
                }
                user_1Counter++;
            }
            else if (lineCounter > 6)
            {
                if ((lineCounter - 2) % 5 == 0)
                {
                    strcpy(user_2[arrayIndex].name, strtok(line,"\n"));
                }
                else if ((lineCounter - 2) % 5 == 1)
                {
                    sscanf(line, "%d", &user_2[arrayIndex].time);
                }
                else if ((lineCounter - 2) % 5 == 2)
                {
                    user_2[arrayIndex].lattitude = strtod(line, NULL);
                }
                else if ((lineCounter - 2) % 5 == 3)
                {
                    user_2[arrayIndex].longitude = strtod(line, NULL);
                }
                else if ((lineCounter - 2) % 5 == 4)
                {
                    user_2[arrayIndex].altitude = strtod(line, NULL);
                    arrayIndex++;
                }
            }
        }
    }
    fclose(inputfile_1);
    return user_1;
}