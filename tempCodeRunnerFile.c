distanceFromOurUser(our_user, other_users, 3);
    struct user_t *closestPtr = closestUser(other_users, 3);

    printf("Closest person is %s\nHe is %0.2f km away\n", closestPtr->name, closestPtr->distanceAway);