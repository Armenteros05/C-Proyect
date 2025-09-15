#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar un vehículo
typedef struct Vehicle {
    char plate[10];
    int ticketNumber;
    struct Vehicle *next;
} Vehicle;

// Estructura para representar una plaza de aparcamiento
typedef struct ParkingSpot {
    int id;
    int isOccupied;
} ParkingSpot;

// Variables globales
ParkingSpot *parkingSpots = NULL;
int totalSpots = 0;
Vehicle *vehicleList = NULL;

// Función para cargar el mapa inicial desde un archivo
void loadParkingMap(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
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

// Función para mostrar el menú
void displayMenu() {
    printf("\nParking Management System\n");
    printf("1. Entrada de vehículo\n");
    printf("2. Salida de vehículo\n");
    printf("3. Mostrar estado del aparcamiento\n");
    printf("4. Salir\n");
    printf("Ingrese su opción: ");
}

// Función para gestionar la entrada de vehículos
void vehicleEntry() {
    char plate[10];
    printf("Ingrese la matrícula del vehículo: ");
    scanf("%s", plate);

    // Buscar una plaza libre
    for (int i = 0; i < totalSpots; i++) {
        if (!parkingSpots[i].isOccupied) {
            parkingSpots[i].isOccupied = 1;

            // Crear un nuevo vehículo
            Vehicle *newVehicle = (Vehicle *)malloc(sizeof(Vehicle));
            strcpy(newVehicle->plate, plate);
            newVehicle->ticketNumber = parkingSpots[i].id;
            newVehicle->next = vehicleList;
            vehicleList = newVehicle;

            printf("Vehículo estacionado en la plaza %d. Ticket: %d\n", parkingSpots[i].id, parkingSpots[i].id);
            return;
        }
    }

    printf("No hay plazas disponibles.\n");
}

// Función para gestionar la salida de vehículos
void vehicleExit() {
    int ticket;
    printf("Ingrese el número de ticket: ");
    scanf("%d", &ticket);

    Vehicle *prev = NULL, *current = vehicleList;
    while (current) {
        if (current->ticketNumber == ticket) {
            // Liberar la plaza
            parkingSpots[ticket - 1].isOccupied = 0;

            // Eliminar el vehículo de la lista
            if (prev) {
                prev->next = current->next;
            } else {
                vehicleList = current->next;
            }
            free(current);

            printf("Vehículo con ticket %d ha salido.\n", ticket);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Ticket no válido.\n");
}

// Función para mostrar el estado del aparcamiento
void displayParkingStatus() {
    printf("\nEstado del aparcamiento:\n");
    for (int i = 0; i < totalSpots; i++) {
        printf("Plaza %d: %s\n", parkingSpots[i].id, parkingSpots[i].isOccupied ? "Ocupada" : "Libre");
    }
}

// Función principal
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
                printf("Saliendo del programa.\n");
                free(parkingSpots);
                while (vehicleList) {
                    Vehicle *temp = vehicleList;
                    vehicleList = vehicleList->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }
}