#include <stdio.h>

void displayMenu() {
    printf("Parking Management System\n");
    printf("1. Park a vehicle\n");
    printf("2. Remove a vehicle\n");
    printf("3. Display parking status\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int parkedVehicles = 0;
    int parkingCapacity = 10;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (parkedVehicles < parkingCapacity) {
                    parkedVehicles++;
                    printf("Vehicle parked. Total parked vehicles: %d\n", parkedVehicles);
                } else {
                    printf("Parking is full!\n");
                }
                break;
            case 2:
                if (parkedVehicles > 0) {
                    parkedVehicles--;
                    printf("Vehicle removed. Total parked vehicles: %d\n", parkedVehicles);
                } else {
                    printf("No vehicles to remove!\n");
                }
                break;
            case 3:
                printf("Parking status: %d/%d vehicles parked.\n", parkedVehicles, parkingCapacity);
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}