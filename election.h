#ifndef ELECTION_H
#define ELECTION_H

#include "party.h"
#include <qabstractitemmodel.h>
#include <vector>
#include <functional>
using std::vector;
using std::function;

class Election
{
public:
    Election();
    Election(const Election& other);
    Election& operator=(const Election& other);
    /// \brief Calculates election results using a highest averages method and a given divisor.
    /// \param divisor A function that takes a number of seats, and returns the divisor for that number of seats.
    void calculateHighestAveragesResults(function<double(double)> divisor);
    /// \brief Calculates election results using a largest remainder method and a given quota.
    /// \param quota A function that takes a total number of seats, and returns the quota for that number of seats.
    void calculateLargestRemainderResults(function<int(int)> quota);
private:
    vector<Party> electionData;
    uint threshold;
    bool hasOverhang;
    int tagAlong;
};

#endif // ELECTION_H
