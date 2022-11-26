#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct position
    {
        double latitude;
        double longitude;
        double altitude;
    };

struct user_t
    {
        char name[25];
        struct position pos;
        double time;
        double distanceAway;
    };

void distanceFromOurUser(struct user_t ourUser, struct user_t otherUsers[], int size);

struct user_t *closestUser(struct user_t otherUsers[], int size);

int main(void)
{
    struct user_t our_user;
    struct user_t other_users[3];
    
    /* Sample Data: 
    Now we can work with the values and worry about
    reading them from a text file and assigning them later
    3 - # of other users
    3 - # of other users
    Zac - name of our user
    1000013 - time of our user
    1543.21 - lat of our user
    2503.02 - long of our user
    155.30 - alt of our user
    Lise - name of other user #1
    1000015 - time of other user #1
    2501.87 - lat of other user #1
    1100.21 - long of other user #1
    266.30 - alt of other user #1
    Hermanus - rest of lines follow same pattern as above (other 2 users)...
    1000014
    1541.54
    2470.33
    153.92
    Petros
    1000011
    921.88
    3100.21
    92.17 */

    //Assign Our Users's Data:
    strcpy(our_user.name, "Zac");
    our_user.time = 1000013;
    our_user.pos.latitude = 1543.21;
    our_user.pos.longitude = 2503.02;
    our_user.pos.altitude = 155.30;

    //Assign Lisa's Data:
    strcpy(other_users[0].name, "Lisa");
    other_users[0].time = 1000015;
    other_users[0].pos.latitude = 2501.87;
    other_users[0].pos.longitude = 1100.21;
    other_users[0].pos.altitude = 266.30;

    //Assign Hermanus' Data:
    strcpy(other_users[1].name, "Hermanus");
    other_users[1].time = 1000012;
    other_users[1].pos.latitude = 1541.54;
    other_users[1].pos.longitude = 2470.33;
    other_users[1].pos.altitude = 153.92;

    //Assign Petros' Data:
    strcpy(other_users[2].name, "Petros");
    other_users[2].time = 1000011;
    other_users[2].pos.latitude = 921.88;
    other_users[2].pos.longitude = 3100.21;
    other_users[2].pos.altitude = 92.17;

    distanceFromOurUser(our_user, other_users, 3);
    struct user_t *closestPtr = closestUser(other_users, 3);

    printf("Closest person is %s\nHe is %0.2f km away\n", closestPtr->name, closestPtr->distanceAway);
}

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