#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Needed for string functions

struct Node {
    int booking_ID;
    char Name[50];
    char CheckInDate[15];
    char CheckOutDate[15];
    int room_Number;
    struct Node* next;
};

struct Node* head = NULL;

// FIX 1: Helper function to clear the input buffer after scanf
// This prevents leftover '\n' characters from breaking fgets
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addbooking() {
    struct Node* Newnode = (struct Node*)malloc(sizeof(struct Node));
    if (Newnode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    printf("Enter Booking ID: ");
    // FIX 2: Added ampersand (&)
    scanf("%d", &Newnode->booking_ID);
    clearInputBuffer(); // Clear the '\n' left by scanf

    printf("Enter Name: ");
    // FIX 3: Replaced scanf("%s") with fgets for safety
    fgets(Newnode->Name, 50, stdin);
    Newnode->Name[strcspn(Newnode->Name, "\n")] = 0; // Remove trailing newline from fgets

    printf("Enter the date(DD/MM/YYYY) of check in: ");
    fgets(Newnode->CheckInDate, 15, stdin);
    Newnode->CheckInDate[strcspn(Newnode->CheckInDate, "\n")] = 0;

    printf("Enter the date(DD/MM/YYYY) of check out: ");
    fgets(Newnode->CheckOutDate, 15, stdin);
    Newnode->CheckOutDate[strcspn(Newnode->CheckOutDate, "\n")] = 0;

    printf("Enter Room Number: ");
    // FIX 4: Added ampersand (&)
    scanf("%d", &Newnode->room_Number);
    clearInputBuffer();

    Newnode->next = head;
    head = Newnode;
    printf("Booking ID %d added successfully.\n", Newnode->booking_ID);
}

void displaybooking() {
    struct Node* Current = head;
    if (Current == NULL) {
        printf("No bookings available.\n");
        return;
    }
    printf("\n--- All Bookings ---\n");
    while (Current != NULL) {
        printf("Booking ID: %d\n", Current->booking_ID);
        printf("Name: %s\n", Current->Name);
        printf("Check-In Date: %s\n", Current->CheckInDate);
        printf("Check-Out Date: %s\n", Current->CheckOutDate);
        printf("Room Number: %d\n", Current->room_Number);
        printf("--------------------------\n");
        Current = Current->next;
    }
}

// FIX 5: Added the missing Search function
void searchbooking(int id) {
    struct Node* Current = head;
    while (Current != NULL && Current->booking_ID != id) {
        Current = Current->next;
    }

    if (Current == NULL) {
        printf("Booking ID %d not found.\n", id);
    } else {
        printf("--- Booking Found ---\n");
        printf("Booking ID: %d\n", Current->booking_ID);
        printf("Name: %s\n", Current->Name);
        printf("Check-In Date: %s\n", Current->CheckInDate);
        printf("Check-Out Date: %s\n", Current->CheckOutDate);
        printf("Room Number: %d\n", Current->room_Number);
        printf("-----------------------\n");
    }
}

void deletebooking(int id) {
    struct Node* Current = head;
    struct Node* Previous = NULL;
    while (Current != NULL && Current->booking_ID != id) {
        Previous = Current;
        Current = Current->next;
    }
    if (Current == NULL) {
        printf("Booking ID %d not found.\n", id);
        return;
    }
    if (Previous == NULL) {
        head = Current->next;
    } else {
        Previous->next = Current->next;
    }
    free(Current);
    printf("Booking ID %d deleted successfully.\n", id);
}

void updatedetails(int id) {
    struct Node* Current = head;
    while (Current != NULL && Current->booking_ID != id)
        Current = Current->next;
    if (Current == NULL) {
        printf("Booking ID %d not found.\n", id);
        return;
    }

    printf("Enter the new details for Booking ID %d:\n", id);
    printf("Enter Name: ");
    // FIX 6: Also fixed input safety here
    clearInputBuffer(); // Clear any pending newlines
    fgets(Current->Name, 50, stdin);
    Current->Name[strcspn(Current->Name, "\n")] = 0;

    printf("Enter the date(DD/MM/YYYY) of check in: ");
    fgets(Current->CheckInDate, 15, stdin);
    Current->CheckInDate[strcspn(Current->CheckInDate, "\n")] = 0;

    printf("Enter the date(DD/MM/YYYY) of check out: ");
    fgets(Current->CheckOutDate, 15, stdin);
    Current->CheckOutDate[strcspn(Current->CheckOutDate, "\n")] = 0;

    printf("Enter Room Number: ");
    // FIX 7: Added ampersand (&)
    scanf("%d", &Current->room_Number);
    clearInputBuffer();

    printf("Booking ID %d updated successfully.\n", id);
}

// FIX 8: Added this function to free all memory
void freeAllBookings() {
    struct Node* Current = head;
    struct Node* nextNode = NULL;
    printf("Exiting... clearing all memory.\n");
    while (Current != NULL) {
        nextNode = Current->next; // Save the next pointer
        free(Current);           // Free the current node
        Current = nextNode;        // Move to the next node
    }
    head = NULL; // List is now empty
}

int main() {
    int choice, id;
    while (1) {
        printf("\n--- Hotel Management System ---\n");
        printf("1. Add Booking\n");
        printf("2. Display All Bookings\n");
        printf("3. Search for Booking\n"); // FIX 9: Added to menu
        printf("4. Delete Booking\n");
        printf("5. Update Booking Details\n");
        printf("6. Exit\n"); // FIX 10: Changed Exit to 6
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer(); // Clear the invalid input
            continue;
        }

        switch (choice) {
            case 1:
                addbooking();
                break;
            case 2:
                displaybooking();
                break;
            case 3: // FIX 11: Added case for search
                printf("Enter Booking ID to search: ");
                scanf("%d", &id);
                searchbooking(id);
                break;
            case 4:
                printf("Enter Booking ID to delete: ");
                scanf("%d", &id);
                deletebooking(id);
                break;
            case 5:
                printf("Enter Booking ID to update: ");
                scanf("%d", &id);
                updatedetails(id);
                break;
            case 6: // FIX 12: Call the free memory function before exiting
                freeAllBookings();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
