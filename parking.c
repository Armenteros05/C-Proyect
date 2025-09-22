#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a vehicle
typedef struct Vehicle {
    char plate[10];
    int ticketNumber;
    struct Vehicle *next;
} Vehicle;

// Structure to represent a parking spot
typedef struct ParkingSpot {
    int id;
    int isOccupied;
} ParkingSpot;

// Global variables
ParkingSpot *parkingSpots = NULL;
int totalSpots = 0;
Vehicle *vehicleList = NULL;

// Function to load the initial parking map from a file
void loadParkingMap(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &totalSpots);
    parkingSpots = (ParkingSpot *)malloc(totalSpots * sizeof(ParkingSpot));
    for (int i = 0; i < totalSpots; i++) {
        parkingSpots[i].id = i + 1;
        parkingSpots[i].isOccupied = 0;
    }

    fclose(file);
}

// Function to display the menu
void displayMenu() {
    printf("\nParking Management System\n");
    printf("1. Vehicle entry\n");
    printf("2. Vehicle exit\n");
    printf("3. Show parking status\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Function to handle vehicle entry
void vehicleEntry() {
    char plate[10];
    printf("Enter vehicle license plate: ");
    scanf("%9s", plate);

    // Look for a free spot
    for (int i = 0; i < totalSpots; i++) {
        if (!parkingSpots[i].isOccupied) {
            parkingSpots[i].isOccupied = 1;

            // Create a new vehicle
            Vehicle *newVehicle = (Vehicle *)malloc(sizeof(Vehicle));
            strcpy(newVehicle->plate, plate);
            newVehicle->ticketNumber = parkingSpots[i].id;
            newVehicle->next = vehicleList;
            vehicleList = newVehicle;

            printf("Vehicle parked in spot %d. Ticket: %d\n", parkingSpots[i].id, parkingSpots[i].id);
            return;
        }
    }

    printf("No available spots.\n");
}

// Function to handle vehicle exit
void vehicleExit() {
    int ticket;
    printf("Enter ticket number: ");
    scanf("%d", &ticket);

    Vehicle *prev = NULL, *current = vehicleList;
    while (current) {
        if (current->ticketNumber == ticket) {
            // Free the spot
            parkingSpots[ticket - 1].isOccupied = 0;

            // Remove the vehicle from the list
            if (prev) {
                prev->next = current->next;
            } else {
                vehicleList = current->next;
            }
            free(current);

            printf("Vehicle with ticket %d has exited.\n", ticket);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Invalid ticket.\n");
}

// Function to display parking status
void displayParkingStatus() {
    printf("\nParking status:\n");
    for (int i = 0; i < totalSpots; i++) {
        printf("Spot %d: %s\n", parkingSpots[i].id, parkingSpots[i].isOccupied ? "Occupied" : "Free");
    }
}

// Main function
int main() {
    loadParkingMap("parking_map.txt");

    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                vehicleEntry();
                break;
            case 2:
                vehicleExit();
                break;
            case 3:
                displayParkingStatus();
                break;
            case 4:
                printf("Exiting program.\n");
                free(parkingSpots);
                while (vehicleList) {
                    Vehicle *temp = vehicleList;
                    vehicleList = vehicleList->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}
