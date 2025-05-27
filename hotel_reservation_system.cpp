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

