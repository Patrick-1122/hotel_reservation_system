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
