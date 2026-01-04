#ifndef SEATALLOCATION_H
#define SEATALLOCATION_H

#include <qtypes.h>
class SeatAllocation
{
public:
    SeatAllocation();
    SeatAllocation(uint electorates, uint listSeats);
    uint getElectorates() { return electorates; };
    uint getListSeats() { return listSeats; };
    uint getTotalSeats() { return totalSeats; };
    void setElectorates(uint newElectorates);
    void setListSeats(uint newListSeats);
    /// \returns Whether or not the new total is above (true) or below (false) the number of electorates.
    bool setTotalSeats(uint newTotalSeats);
private:
    void calculateTotalSeats() { totalSeats = electorates + listSeats; };

    uint electorates;
    uint listSeats;
    uint totalSeats;
};

#endif // SEATALLOCATION_H
