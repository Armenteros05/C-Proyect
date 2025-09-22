#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======================= Structures =======================

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

// ======================= Globals =======================
ParkingSpot *parkingSpots = NULL;
int totalSpots = 0;
Vehicle *vehicleList = NULL;

// For ASCII map
#define MAX_ROWS 100
#define MAX_COLS 200
char mapData[MAX_ROWS][MAX_COLS];
int mapRows = 0;

// ======================= Functions =======================

// Load parking map from a file
void loadParkingMap(const char *maptxt) {
    FILE *file = fopen(maptxt, "r");
    if (!file) {
        perror("Error opening map file");
        exit(EXIT_FAILURE);
    }

    // First line contains the number of parking spots
    fscanf(file, "%d\n", &totalSpots);
    parkingSpots = (ParkingSpot *)malloc(totalSpots * sizeof(ParkingSpot));
    for (int i = 0; i < totalSpots; i++) {
        parkingSpots[i].id = i + 1;
        parkingSpots[i].isOccupied = 0;
    }

    // Read the rest of the file into mapData
    while (fgets(mapData[mapRows], MAX_COLS, file)) {
        size_t len = strlen(mapData[mapRows]);
        if (len > 0 && mapData[mapRows][len - 1] == '\n') {
            mapData[mapRows][len - 1] = '\0'; // remove newline
        }
        mapRows++;
    }

    fclose(file);
}

// Display the main menu
void displayMenu() {
    printf("\nParking Management System\n");
    printf("1. Vehicle entry\n");
    printf("2. Vehicle exit\n");
    printf("3. Show parking status (map)\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Handle vehicle entry
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

// Handle vehicle exit
void vehicleExit() {
    int ticket;
    printf("Enter ticket number: ");
    scanf("%d", &ticket);

    Vehicle *prev = NULL, *current = vehicleList;
    while (current) {
        if (current->ticketNumber == ticket) {
            // Free the spot
            parkingSpots[ticket - 1].isOccupied = 0;

            // Remove vehicle from list
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

// Display the parking map with occupancy
void displayParkingStatus() {
    system("clear"); // use "cls" on Windows

    printf("\nParking Lot Map:\n\n");

    int spotCounter = 0;

    for (int r = 0; r < mapRows; r++) {
        for (int c = 0; mapData[r][c] != '\0'; c++) {
            if (mapData[r][c] == '[' && mapData[r][c+1] == ' ' && mapData[r][c+2] == ']') {
                if (spotCounter < totalSpots && parkingSpots[spotCounter].isOccupied) {
                    printf("[X]"); // Occupied
                } else {
                    printf("[ ]"); // Free
                }
                c += 2; // Skip next chars
                spotCounter++;
            } else {
                putchar(mapData[r][c]);
            }
        }
        putchar('\n');
    }
}

// ======================= Main =======================
int main() {
    loadParkingMap("map.txt");

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
