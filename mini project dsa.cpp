#include <iostream>
#include <string>
using namespace std;

const int SEAT_COUNT = 5; 


struct SeatNode {
    int seatNo;
    string* passengerName; 
    SeatNode* prev;
    SeatNode* next;
};


struct BusNode {
    int busID;
    string route;
    string driver;
    SeatNode* seats;
    BusNode* next;
};


SeatNode* createSeats() {
    SeatNode* head = NULL;
    SeatNode* tail = NULL;

    for (int i = 1; i <= SEAT_COUNT; i++) {
        SeatNode* newSeat = new SeatNode();
        newSeat->seatNo = i;
        newSeat->passengerName = NULL;
        newSeat->prev = tail;
        newSeat->next = NULL;

        if (tail)
            tail->next = newSeat;
        else
            head = newSeat;

        tail = newSeat;
    }
    return head;
}

// Add new bus
BusNode* addBus(BusNode* head) {
    BusNode* newBus = new BusNode();
    cout << "Enter Bus ID: ";
    cin >> newBus->busID;
    cin.ignore();
    cout << "Enter Route: ";
    getline(cin, newBus->route);
    cout << "Enter Driver Name: ";
    getline(cin, newBus->driver);

    newBus->seats = createSeats();
    newBus->next = head;
    return newBus;
}

// Display all buses
void showBuses(BusNode* head) {
    if (!head) {
        cout << "No buses available.\n";
        return;
    }
    BusNode* temp = head;
    while (temp) {
        cout << "\nBus ID: " << temp->busID
             << "\nRoute: " << temp->route
             << "\nDriver: " << temp->driver << endl;
        temp = temp->next;
    }
}

// Reserve a seat
void reserveSeat(BusNode* head, int busID) {
    BusNode* bus = head;
    while (bus && bus->busID != busID)
        bus = bus->next;

    if (!bus) {
        cout << "Bus not found.\n";
        return;
    }

    int seatNum;
    cout << "Enter seat number (1-" << SEAT_COUNT << "): ";
    cin >> seatNum;

    SeatNode* seat = bus->seats;
    while (seat && seat->seatNo != seatNum)
        seat = seat->next;

    if (!seat) {
        cout << "Invalid seat number.\n";
        return;
    }

    if (seat->passengerName) {
        cout << "Seat already reserved by " << *(seat->passengerName) << endl;
    } else {
        seat->passengerName = new string;
        cin.ignore();
        cout << "Enter passenger name: ";
        getline(cin, *(seat->passengerName));
        cout << "Seat reserved successfully.\n";
    }
}

// Show seat status
void showSeatStatus(BusNode* head, int busID) {
    BusNode* bus = head;
    while (bus && bus->busID != busID)
        bus = bus->next;

    if (!bus) {
        cout << "Bus not found.\n";
        return;
    }

    SeatNode* seat = bus->seats;
    while (seat) {
        cout << "Seat " << seat->seatNo << ": ";
        if (seat->passengerName)
            cout << *(seat->passengerName) << endl;
        else
            cout << "Empty\n";
        seat = seat->next;
    }
}

int main() {
    BusNode* busList = NULL;
    int choice, busID;

    do {
        cout << "\n--- Bus Reservation Menu ---\n";
        cout << "1. Add Bus\n2. Show Buses\n3. Reserve Seat\n4. Show Seat Status\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                busList = addBus(busList);
                break;
            case 2:
                showBuses(busList);
                break;
            case 3:
                cout << "Enter Bus ID: ";
                cin >> busID;
                reserveSeat(busList, busID);
                break;
            case 4:
                cout << "Enter Bus ID: ";
                cin >> busID;
                showSeatStatus(busList, busID);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
