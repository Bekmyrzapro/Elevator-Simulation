#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstdlib>
#include <ctime>

struct PassengerRequest {
    int sourceFloor;
    PassengerRequest(int floor) : sourceFloor(floor) {}
};

class Floor {
public:
    std::queue<PassengerRequest> requests;
    void addRequest(PassengerRequest request) {
        requests.push(request);
    }
};

class Elevator {
public:
    int currentFloor = 0;
    void moveToFloor(int floor) {
        currentFloor = floor;
        std::cout << "Elevator moving to floor " << floor << ".\n";
    }
};

class Building {
public:
    std::vector<Floor> floors;
    Elevator elevator;
    std::map<int, int> callFrequencies;

    Building(int numberOfFloors) {
        floors.resize(numberOfFloors);
    }

    void simulateCalls(int duration) {
        for (int i = 0; i < duration; ++i) {
            int randomFloor = rand() % floors.size();
            floors[randomFloor].addRequest(PassengerRequest(randomFloor));
            callFrequencies[randomFloor]++;
            std::cout << "Passenger called elevator from floor " << randomFloor << ".\n";
        }
    }

    void processRequests() {
        for (size_t i = 0; i < floors.size(); ++i) {
            while (!floors[i].requests.empty()) {
                elevator.moveToFloor(i);
                floors[i].requests.pop(); // Process request
            }
        }
    }
};

int main() {
    srand(time(nullptr)); 

    std::cout << "Welcome to Elevator Simulation!\n";
    Building building(10); // 10 floors
    building.simulateCalls(20); // Simulate 20 calls
    building.processRequests();

    std::cout << "Frequency of calls from each floor:\n";
    for (auto& freq : building.callFrequencies) {
        std::cout << "Floor " << freq.first << ": " << freq.second << " calls\n";
    }

    std::cout << "Simulation completed.\n";
    return 0;
}
