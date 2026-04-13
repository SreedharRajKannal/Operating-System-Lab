/*Write a C program to implement a simple social network using linked lists.
The program should allow users to be added, manage their friend lists (add and remove friends),
merge the friend lists of two users, and display all users along with their friends using a menu-driven interface.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Friend {
    char name[50];
    struct Friend *next;
};

struct User {
    char name[50];
    struct Friend *friendList;
    struct User *next;
};

struct User *userHead = NULL; // Global head pointer

// Function to find user by name
struct User* findUser(char *name) {
    struct User *temp = userHead;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add a new user
void addUser(char *name) {
    if (findUser(name)) {
        printf("User '%s' already exists!\n", name);
        return;
    }

    struct User *newUser = (struct User*)malloc(sizeof(struct User));
    strcpy(newUser->name, name);
    newUser->friendList = NULL;
    newUser->next = userHead;
    userHead = newUser;

    printf("User '%s' added successfully.\n", name);
}

// Add friend to a user
void addFriend(char *userName, char *friendName) {
    struct User *user = findUser(userName);
    if (!user) {
        printf("User '%s' not found!\n", userName);
        return;
    }

    struct Friend *temp = user->friendList;
    while (temp) {
        if (strcmp(temp->name, friendName) == 0) {
            printf("%s is already a friend of %s.\n", friendName, userName);
            return;
        }
        temp = temp->next;
    }

    struct Friend *newFriend = (struct Friend*)malloc(sizeof(struct Friend));
    strcpy(newFriend->name, friendName);
    newFriend->next = user->friendList;
    user->friendList = newFriend;

    printf("Friend '%s' added to user '%s'.\n", friendName, userName);
}

// Remove friend
void removeFriend(char *userName, char *friendName) {
    struct User *user = findUser(userName);
    if (!user) {
        printf("User '%s' not found!\n", userName);
        return;
    }

    struct Friend *temp = user->friendList, *prev = NULL;
    while (temp && strcmp(temp->name, friendName) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Friend '%s' not found in %s's friend list.\n", friendName, userName);
        return;
    }

    if (prev)
        prev->next = temp->next;
    else
        user->friendList = temp->next;

    free(temp);
    printf("Friend '%s' removed from %s's list.\n", friendName, userName);
}

// Merge friend lists of two users
void mergeFriends(char *user1, char *user2) {
    struct User *u1 = findUser(user1);
    struct User *u2 = findUser(user2);

    if (!u1 || !u2) {
        printf("Both users must exist to merge friend lists.\n");
        return;
    }

    struct Friend *temp = u2->friendList;
    while (temp) {
        addFriend(user1, temp->name);
        temp = temp->next;
    }

    printf("Friend lists of '%s' and '%s' merged successfully.\n", user1, user2);
}

// Display all users and their friends
void displayAll() {
    struct User *u = userHead;
    if (!u) {
        printf("No users available.\n");
        return;
    }

    while (u) {
        printf("\nUser: %s\nFriends: ", u->name);
        struct Friend *f = u->friendList;
        if (!f) printf("None");
        while (f) {
            printf("%s ", f->name);
            f = f->next;
        }
        printf("\n");
        u = u->next;
    }
}

int main() {
    int choice;
    char user[50], friend[50], user2[50];

    while (1) {
        printf("\n1. Add User\n2. Add Friend\n3. Remove Friend\n4. Merge Friend Lists\n5. Display All\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", user);
                addUser(user);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", user);
                printf("Enter friend name: ");
                scanf("%s", friend);
                addFriend(user, friend);
                break;
            case 3:
                printf("Enter username: ");
                scanf("%s", user);
                printf("Enter friend to remove: ");
                scanf("%s", friend);
                removeFriend(user, friend);
                break;
            case 4:
                printf("Enter first user: ");
                scanf("%s", user);
                printf("Enter second user: ");
                scanf("%s", user2);
                mergeFriends(user, user2);
                break;
            case 5:
                displayAll();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
