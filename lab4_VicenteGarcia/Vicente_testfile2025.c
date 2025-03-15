#include "Vicente_libFS2025.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    getchar();  // Clear the newline character from the buffer
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Vicente Garcia.\n\n"
                          "I am a computer science student that has found my favorite programming language to be python.\n"
                          "I think that my favorite topic in CS so far has been learning about the many different types\n"
                          "of data structures in c. My favorite class outside of my cs classes has probably been sociology\n"
                          "becuase of how much it deals with analyzing society.\n\n"
                          "This project implements procceses that deal with  files in c through a menu system\n"
                          "you have to open a file to change it. This project is very neatly organized for you \n"
                          "the user in mind when being designed. There is many more updates to come sometime in\n"
                          "the future so saty tuned. I hope you found this application easier to use!\n";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("reading file '%s'...\n", filename);
                    if (fileRead(file_index) != 0) {
                        printf("Error Reading file.\n");
                    }
                }
                waitForUser();
                break;

            case 5:  // Close a file
                if (file_index == -1) { // Check if there is a file open
                    printf("Error: No file is open. Please open a file first.\n");
                } else{
                    file_index = fileClose(file_index);
                    if (file_index == 0) {
                        printf("Error close file.\n");
                    }
                }
                waitForUser();
                break;

            case 6:  // Delete a file
                printf("Enter the filename to delete: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) {
                    printf("Error deleteing file.\n");
                }
                waitForUser();
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}