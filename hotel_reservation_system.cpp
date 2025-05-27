#include <iostream>
#include <string>

using namespace std;

// Strategy for room pricing
class RoomPriceStrategy {
public:
    virtual double getPrice() const = 0;
    virtual ~RoomPriceStrategy() {}
};

class RoomAPriceStrategy : public RoomPriceStrategy {
public:
    double getPrice() const override { return 2000.0; }
};

class RoomBPriceStrategy : public RoomPriceStrategy {
public:
    double getPrice() const override { return 1500.0; }
};

class RoomCPriceStrategy : public RoomPriceStrategy {
public:
    double getPrice() const override { return 1000.0; }
};

void printCurrency(double value) {
    if (value < 0) {
        cout << "-";
        value = -value;
    }
    long long totalCents = static_cast<long long>(value * 100.0 + 0.5);
    long long pesos = totalCents / 100;
    int centavos = totalCents % 100;
    cout << pesos << ".";
    if (centavos < 10) cout << "0";
    cout << centavos;
}

// Simulate room availability (could be randomized or fixed for demo)
bool isRoomAvailable(char room) {
    // For demo: Room A and C are available, B is not
    if (room == 'A') return true;
    if (room == 'B') return false;
    if (room == 'C') return true;
    return false;
}

class HotelReservationSystem {
private:
    RoomPriceStrategy* priceStrategy;
    char selectedRoom;
public:
    HotelReservationSystem() : priceStrategy(nullptr), selectedRoom(' ') {}
    void setRoomPriceStrategy(RoomPriceStrategy* strategy, char room) {
        delete priceStrategy;
        priceStrategy = strategy;
        selectedRoom = room;
    }
    void displayBill() const {
        if (!priceStrategy) {
            cout << "Error: No room selected.\n";
            return;
        }
        double price = priceStrategy->getPrice();
        cout << "\n--- Receipt ---\n";
        cout << "Room " << selectedRoom << " Price: ";
        printCurrency(price);
        cout << " Pesos\n";
        cout << "Thank you for your payment!\n";
    }
    ~HotelReservationSystem() { delete priceStrategy; }
    HotelReservationSystem(const HotelReservationSystem&) = delete;
    HotelReservationSystem& operator=(const HotelReservationSystem&) = delete;
};

int main() {
    HotelReservationSystem system;
    string roomChoice;
    char room = ' ';
    bool validRoomSelected = false;
    cout << "Welcome to the Hotel Reservation System!\n";
    while (!validRoomSelected) {
        cout << "Select a room (A, B, C): ";
        getline(cin, roomChoice);
        if (roomChoice.size() == 1 && (roomChoice[0] == 'A' || roomChoice[0] == 'B' || roomChoice[0] == 'C')) {
            room = roomChoice[0];
            if (isRoomAvailable(room)) {
                validRoomSelected = true;
            } else {
                cout << "Room " << room << " is not available.\n";
                // Show available rooms and their prices
                cout << "Available rooms:\n";
                bool anyAvailable = false;
                if (isRoomAvailable('A')) {
                    cout << "  A - ";
                    printCurrency(RoomAPriceStrategy().getPrice());
                    cout << " Pesos\n";
                    anyAvailable = true;
                }
                if (isRoomAvailable('B')) {
                    cout << "  B - ";
                    printCurrency(RoomBPriceStrategy().getPrice());
                    cout << " Pesos\n";
                    anyAvailable = true;
                }
                if (isRoomAvailable('C')) {
                    cout << "  C - ";
                    printCurrency(RoomCPriceStrategy().getPrice());
                    cout << " Pesos\n";
                    anyAvailable = true;
                }
                if (!anyAvailable) {
                    cout << "No rooms available.\n";
                    return 0;
                }
                // Let user pick again from available rooms
                continue;
            }
        } else {
            cout << "Invalid input. Please enter A, B, or C.\n";
        }
    }
    RoomPriceStrategy* strategy = nullptr;
    double price = 0.0;
    if (room == 'A') { strategy = new RoomAPriceStrategy(); price = strategy->getPrice(); }
    else if (room == 'B') { strategy = new RoomBPriceStrategy(); price = strategy->getPrice(); }
    else if (room == 'C') { strategy = new RoomCPriceStrategy(); price = strategy->getPrice(); }
    system.setRoomPriceStrategy(strategy, room);
    cout << "\nRoom " << room << " Price: ";
    printCurrency(price);
    cout << " Pesos\n";
    // Payment and change calculation
    double payment = 0.0;
    while (true) {
        cout << "Enter payment amount: ";
        cin >> payment;
        if (cin.good() && payment >= price) {
            break;
        } else {
            cout << "Insufficient payment or invalid input. Please enter an amount greater than or equal to the price.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    double change = payment - price;
    cout << "\nUser Pays...\n";
    system.displayBill();
    cout << "Payment: ";
    printCurrency(payment);
    cout << " Pesos\n";
    cout << "Change: ";
    printCurrency(change);
    cout << " Pesos\n";
    cout << "\n--- End of Transaction ---\n";
    return 0;
}