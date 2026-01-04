#include "seatallocation.h"

SeatAllocation::SeatAllocation() {
    electorates = 0;
    listSeats = 0;
    totalSeats = 0;
}

SeatAllocation::SeatAllocation(uint electorates, uint listSeats) {
    this->electorates = electorates;
    this->listSeats = listSeats;
    calculateTotalSeats();
}

void SeatAllocation::setElectorates(uint newElectorates) {
    electorates = newElectorates;
    calculateTotalSeats();
}

void SeatAllocation::setListSeats(uint newListSeats) {
    listSeats = newListSeats;
    calculateTotalSeats();
}

bool SeatAllocation::setTotalSeats(uint newTotalSeats) {
    if (newTotalSeats < electorates) {
        return false;
    }

    totalSeats = newTotalSeats;
    listSeats = totalSeats - electorates;
    return true;
}
