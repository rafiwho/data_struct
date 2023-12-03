#include <stdio.h>
#include <stdlib.h>
//attribiutes of Seat
struct Seat {
	int seat_number;
	int is_reserved;
	struct Seat* next;
};
//attributes of Bus
struct Bus {
	int bus_number;
	struct Seat* seats;
	struct Bus* next;
};
//attributes of Reservation
struct Reservation {
	int bus_number;
	int seat_number;
	struct Reservation* next;
};

//return a link list of (totalBuses) number of bus
struct Bus* initializeBuses(int totalBuses) {
	struct Bus* head = NULL;

	for (int busNumber = 1; busNumber <= totalBuses; busNumber++) {

		struct Bus* tempBus = (struct Bus*)malloc(sizeof(struct Bus));

		tempBus->bus_number = busNumber;
		tempBus->seats = NULL;
		tempBus->next = head; // conecting tempbus to head
		head = tempBus;

		for (int seatNumber = 1; seatNumber <= 10; seatNumber++) {

			struct Seat* tempSeat = (struct Seat*)malloc(sizeof(struct Seat));

			tempSeat->seat_number = seatNumber;
			tempSeat->is_reserved = 0; // is_reserved zero means it is not yet reservered
			tempSeat->next = tempBus->seats; // connecting seat to bus
			tempBus->seats = tempSeat;
		}
	}
	return head;
}
//display all buses just like traversing linklist
void displayAvailableBuses(struct Bus* head) {
	struct Bus* temp = head; // taking tempbus for traversing buses

	while (temp != NULL) {
		printf("Bus %d:\n", temp->bus_number);

		struct Seat* currentSeat = temp->seats; // taking tempseat for traversing seat

		int availableSeats = 0;

		while (currentSeat != NULL) {

			if (currentSeat->is_reserved == 0) {
				availableSeats++;
			}

			printf("Seat %d: %s\n", currentSeat->seat_number, currentSeat->is_reserved ? "Reserved" : "Available");
			currentSeat = currentSeat->next; // going to next node
		}

		printf("Available Seats: %d\n", availableSeats);
		temp = temp->next; // going to next node
	}
}
//this func will reserve a specific bus's seat
int makeReservation(struct Bus* head, int busNumber, int seatNumber) {
	struct Bus* tempbus = head; // taking tempbus

	while (tempbus != NULL && tempbus->bus_number != busNumber) {
		tempbus = tempbus->next;
	}

	if (tempbus == NULL) {
		printf("Bus %d not found.\n", busNumber); // invalid info
		return 0;
	}

	struct Seat* tempSeat = tempbus->seats;

	while (tempSeat != NULL && tempSeat->seat_number != seatNumber) {
		tempSeat = tempSeat->next;
	}

	if (tempSeat == NULL) {
		printf("Seat %d not found on Bus %d.\n", seatNumber, busNumber); // invalid info
		return 0;
	}

	if (tempSeat->is_reserved == 1) {
		printf("Seat %d on Bus %d is already reserved.\n", seatNumber, busNumber);
		return 0;
	}

	tempSeat->is_reserved = 1; // making it 1 -> means reservation done
	printf("Reservation successful: Bus %d, Seat %d\n", busNumber, seatNumber);
	return 1;
}

//same like makereservation func
int cancelReservation(struct Bus* head, int busNumber, int seatNumber) {
	struct Bus* tempbus = head;
	while (tempbus != NULL && tempbus->bus_number != busNumber) {
		tempbus = tempbus->next;
	}

	if (tempbus == NULL) {
		printf("Bus %d not found.\n", busNumber);
		return 0;
	}

	struct Seat* currentSeat = tempbus->seats;
	while (currentSeat != NULL && currentSeat->seat_number != seatNumber) {
		currentSeat = currentSeat->next;
	}

	if (currentSeat == NULL) {
		printf("Seat %d not found on Bus %d.\n", seatNumber, busNumber); // invalid info
		return 0;
	}

	if (!currentSeat->is_reserved) {
		printf("Seat %d on Bus %d is not reserved.\n", seatNumber, busNumber);//if this is already not reserved
		return 0;
	}

	currentSeat->is_reserved = 0; // make it zero to cancel reservation
	printf("Cancellation successful: Bus %d, Seat %d\n", busNumber, seatNumber);
	return 1;
}
//this will display reservation details
void viewReservationDetails(struct Bus* head, int busNumber, int seatNumber) {

	struct Bus* tempbus = head;

	while (tempbus != NULL && tempbus->bus_number != busNumber) {
		tempbus = tempbus->next;
	}

	if (tempbus == NULL) {
		printf("Bus %d not found.\n", busNumber); // invalid info
		return;
	}

	struct Seat* currentSeat = tempbus->seats;

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

void swapBuses(struct Bus* bus1, struct Bus* bus2) { // swap two buses if needed

	int temp_bus_number = bus1->bus_number;

	struct Seat* temp_seats = bus1->seats;

	bus1->bus_number = bus2->bus_number;   // swap two buses using temp_node
	bus1->seats = bus2->seats;

	bus2->bus_number = temp_bus_number;
	bus2->seats = temp_seats;
}

//count the number of buses
int countBuses(struct Bus* head) {
	int count = 0;

	struct Bus* tempbus = head;

	while (tempbus != NULL) {
		count++;
		tempbus = tempbus->next; // going to the next node
	}

	return count;
}


void bubbleSortBuses(struct Bus* head) { // sort by bus number
	int n = countBuses(head);

	struct Bus* tempbus;

	for (int i = 0; i < n - 1; i++) {
		tempbus = head;
		for (int j = 0; j < n - i - 1; j++) {

			if (tempbus->bus_number > tempbus->next->bus_number) { // sorting in assending order

				swapBuses(tempbus, tempbus->next);

			}

			tempbus = tempbus->next;
		}

	}
}
//count available seat a bus
int countAvailableSeats(struct Bus* bus) {
	int count = 0;

	struct Seat* currentSeat = bus->seats;

	while (currentSeat != NULL) {
		if (currentSeat->is_reserved == 1) {
			count++;
		}
		currentSeat = currentSeat->next;//going to the next node
	}

	return count;
}

void bubbleSort_Buses_By_AvailableSeats(struct Bus* head) { // sort by available seat
	int n = countBuses(head);
	struct Bus* tempbus;

	for (int i = 0; i < n - 1; i++) {
		tempbus = head;
		for (int j = 0; j < n - i - 1; j++) {
			if (countAvailableSeats(tempbus) > countAvailableSeats(tempbus->next)) {
				swapBuses(tempbus, tempbus->next);
			}
			tempbus = tempbus->next;
		}
	}
}

void GENERATE_PDF(struct Bus* head, const char* filename) {

	FILE* file = fopen(filename, "w");

	if (!file) {
		printf("Error: Cannot open file %s.\n", filename);
		return;
	}

	struct Bus* tempbus = head;
	while (tempbus != NULL) {
		fprintf(file, "Bus %d:\n", tempbus->bus_number); // writing bus_num in file

		struct Seat* currentSeat = tempbus->seats;

		while (currentSeat != NULL) {
			fprintf(file, "Seat %d: %s\n", currentSeat->seat_number, // writing seat info in file
			        currentSeat->is_reserved ? "Reserved" : "Available");
			currentSeat = currentSeat->next;
		}

		fprintf(file, "\n");

		tempbus = tempbus->next;// going to the next info
	}

	fclose(file);

	printf("Bus information saved to %s\n", filename);
}

int main() {
	int totalBuses = 5;
	struct Bus* buses = initializeBuses(totalBuses); //a link list of (totalbuses) number of bus will be stored in buses

	int choice, busNumber, seatNumber, cancelBusNumber, cancelSeatNumber,
	    viewBusNumber, viewSeatNumber;

	do {
		printf("\n************************************************************\n");
		printf("*                 Bus Reservation System Menu              *\n");
		printf("*--------------------------------------------------------  *\n");
		printf("*  1. Display available buses and seats                    *\n");
		printf("*  2. Make a reservation                                   *\n");
		printf("*  3. Cancel a reservation                                 *\n");
		printf("*  4. View reservation details                             *\n");
		printf("*  5. Sort buses by number                                 *\n");
		printf("*  6. Sort buses by available seats                        *\n");
		printf("*  7. Generate PDF of all available buses                  *\n");
		printf("*  8. Exit                                                 *\n");
		printf("************************************************************\n");

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
			bubbleSort_Buses_By_AvailableSeats(buses);
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