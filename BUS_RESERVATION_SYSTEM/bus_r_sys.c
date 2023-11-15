#include <stdio.h>
#include <stdlib.h>

struct Seat {
	int seat_number;
	int is_reserved;
	struct Seat* next;
};

struct Bus {
	int bus_number;
	struct Seat* seats;
	struct Bus* next;
};

struct Reservation {
	int bus_number;
	int seat_number;
	struct Reservation* next;
};

struct Bus* initializeBuses(int totalBuses) {
	struct Bus* head = NULL;
	for (int busNumber = 1; busNumber <= totalBuses; busNumber++) {
		struct Bus* newBus = (struct Bus*)malloc(sizeof(struct Bus));
		newBus->bus_number = busNumber;
		newBus->seats = NULL;
		newBus->next = head;
		head = newBus;

		for (int seatNumber = 1; seatNumber <= 10; seatNumber++) {
			struct Seat* newSeat = (struct Seat*)malloc(sizeof(struct Seat));
			newSeat->seat_number = seatNumber;
			newSeat->is_reserved = 0;
			newSeat->next = newBus->seats;
			newBus->seats = newSeat;
		}
	}
	return head;
}

void displayAvailableBuses(struct Bus* head) {
	struct Bus* currentBus = head;
	while (currentBus != NULL) {
		printf("Bus %d:\n", currentBus->bus_number);
		struct Seat* currentSeat = currentBus->seats;
		int availableSeats = 0;
		while (currentSeat != NULL) {
			if (currentSeat->is_reserved == 0) {
				availableSeats++;
			}
			printf("Seat %d: %s\n", currentSeat->seat_number, currentSeat->is_reserved ? "Reserved" : "Available");
			currentSeat = currentSeat->next;
		}
		printf("Available Seats: %d\n", availableSeats);
		currentBus = currentBus->next;
	}
}

int makeReservation(struct Bus* head, int busNumber, int seatNumber) {
	struct Bus* currentBus = head;
	while (currentBus != NULL && currentBus->bus_number != busNumber) {
		currentBus = currentBus->next;
	}

	if (currentBus == NULL) {
		printf("Bus %d not found.\n", busNumber);
		return 0;
	}

	struct Seat* currentSeat = currentBus->seats;
	while (currentSeat != NULL && currentSeat->seat_number != seatNumber) {
		currentSeat = currentSeat->next;
	}

	if (currentSeat == NULL) {
		printf("Seat %d not found on Bus %d.\n", seatNumber, busNumber);
		return 0;
	}

	if (currentSeat->is_reserved) {
		printf("Seat %d on Bus %d is already reserved.\n", seatNumber, busNumber);
		return 0;
	}

	currentSeat->is_reserved = 1;
	printf("Reservation successful: Bus %d, Seat %d\n", busNumber, seatNumber);
	return 1;
}

int cancelReservation(struct Bus* head, int busNumber, int seatNumber) {
	struct Bus* currentBus = head;
	while (currentBus != NULL && currentBus->bus_number != busNumber) {
		currentBus = currentBus->next;
	}

	if (currentBus == NULL) {
		printf("Bus %d not found.\n", busNumber);
		return 0;
	}

	struct Seat* currentSeat = currentBus->seats;
	while (currentSeat != NULL && currentSeat->seat_number != seatNumber) {
		currentSeat = currentSeat->next;
	}

	if (currentSeat == NULL) {
		printf("Seat %d not found on Bus %d.\n", seatNumber, busNumber);
		return 0;
	}

	if (!currentSeat->is_reserved) {
		printf("Seat %d on Bus %d is not reserved.\n", seatNumber, busNumber);
		return 0;
	}

	currentSeat->is_reserved = 0;
	printf("Cancellation successful: Bus %d, Seat %d\n", busNumber, seatNumber);
	return 1;
}

void viewReservationDetails(struct Bus* head, int busNumber, int seatNumber) {
	struct Bus* currentBus = head;
	while (currentBus != NULL && currentBus->bus_number != busNumber) {
		currentBus = currentBus->next;
	}

	if (currentBus == NULL) {
		printf("Bus %d not found.\n", busNumber);
		return;
	}

	struct Seat* currentSeat = currentBus->seats;
	while (currentSeat != NULL && currentSeat->seat_number != seatNumber) {
		currentSeat = currentSeat->next;
	}

	if (currentSeat == NULL) {
		printf("Seat %d not found on Bus %d.\n", seatNumber, busNumber);
		return;
	}

	printf("Reservation Details for Bus %d, Seat %d:\n", busNumber, seatNumber);
	printf("Status: %s\n", currentSeat->is_reserved ? "Reserved" : "Available");
}

void swapBuses(struct Bus* bus1, struct Bus* bus2) {
	int temp_bus_number = bus1->bus_number;
	struct Seat* temp_seats = bus1->seats;

	bus1->bus_number = bus2->bus_number;
	bus1->seats = bus2->seats;

	bus2->bus_number = temp_bus_number;
	bus2->seats = temp_seats;
}


int countBuses(struct Bus* head) {
	int count = 0;
	struct Bus* currentBus = head;
	while (currentBus != NULL) {
		count++;
		currentBus = currentBus->next;
	}
	return count;
}


void bubbleSortBuses(struct Bus* head) {
	int n = countBuses(head);
	struct Bus* currentBus;
	struct Bus* last = NULL;

	for (int i = 0; i < n - 1; i++) {
		currentBus = head;
		for (int j = 0; j < n - i - 1; j++) {
			if (currentBus->bus_number > currentBus->next->bus_number) {
				swapBuses(currentBus, currentBus->next);
			}
			currentBus = currentBus->next;
		}
		last = currentBus;
	}
}

int countAvailableSeats(struct Bus* bus) {
	int count = 0;
	struct Seat* currentSeat = bus->seats;
	while (currentSeat != NULL) {
		if (currentSeat->is_reserved == 1) {
			count++;
		}
		currentSeat = currentSeat->next;
	}
	return count;
}

void bubbleSortBusesByAvailableSeats(struct Bus* head) {
	int n = countBuses(head);
	struct Bus* currentBus;
	struct Bus* last = NULL;

	for (int i = 0; i < n - 1; i++) {
		currentBus = head;
		for (int j = 0; j < n - i - 1; j++) {
			if (countAvailableSeats(currentBus) > countAvailableSeats(currentBus->next)) {
				swapBuses(currentBus, currentBus->next);
			}
			currentBus = currentBus->next;
		}
		last = currentBus;
	}
}
void GENERATE_PDF(struct Bus* head, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) {
		printf("Error: Cannot open file %s.\n", filename);
		return;
	}

	struct Bus* currentBus = head;
	while (currentBus != NULL) {
		fprintf(file, "Bus %d:\n", currentBus->bus_number);

		struct Seat* currentSeat = currentBus->seats;
		while (currentSeat != NULL) {
			fprintf(file, "Seat %d: %s\n", currentSeat->seat_number,
			        currentSeat->is_reserved ? "Reserved" : "Available");
			currentSeat = currentSeat->next;
		}

		fprintf(file, "\n");
		currentBus = currentBus->next;
	}

	fclose(file);

	printf("Bus information saved to %s\n", filename);
}

int main() {
	int totalBuses = 5;
	struct Bus* buses = initializeBuses(totalBuses);

	int choice, busNumber, seatNumber, cancelBusNumber, cancelSeatNumber,
	    viewBusNumber, viewSeatNumber;
	do {
		printf("\nBus Reservation System Menu:\n");
		printf("1. Display available buses and seats\n");
		printf("2. Make a reservation\n");
		printf("3. Cancel a reservation\n");
		printf("4. View reservation details\n");
		printf("5. Sort buses by number \n");
		printf("6. Sort buses by available seats \n");
		printf("7. Generate Pdf of all available buses \n");
		printf("8. Exit\n");

		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			displayAvailableBuses(buses);
			break;
		case 2:
			printf("Enter bus number: ");
			scanf("%d", &busNumber);
			printf("Enter seat number: ");
			scanf("%d", &seatNumber);
			makeReservation(buses, busNumber, seatNumber);
			break;
		case 3:
			printf("Enter bus number for cancellation: ");
			scanf("%d", &cancelBusNumber);
			printf("Enter seat number for cancellation: ");
			scanf("%d", &cancelSeatNumber);
			cancelReservation(buses, cancelBusNumber, cancelSeatNumber);
			break;
		case 4:
			printf("Enter bus number to view details: ");
			scanf("%d", &viewBusNumber);
			printf("Enter seat number to view details: ");
			scanf("%d", &viewSeatNumber);
			viewReservationDetails(buses, viewBusNumber, viewSeatNumber);
			break;
		case 5:
			bubbleSortBuses(buses);
			printf("Buses sorted by number using Bubble Sort.\n");
			break;
		case 6:
			bubbleSortBusesByAvailableSeats(buses);
			printf("Buses sorted by available seats using Bubble Sort.\n");
			break;
		case 7:
			GENERATE_PDF(buses, "info.pdf");
			break;
		case 8:
			printf("Exiting the program. Goodbye!\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 8);

	return 0;
}
