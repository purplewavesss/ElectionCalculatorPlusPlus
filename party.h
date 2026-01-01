#ifndef PARTY_H
#define PARTY_H

#include <string>
using std::string;

class Party
{
public:
    Party(const string& name, uint votes = 0, uint electorates = 0, uint listSeats = 0);
    Party(const Party& other);
    Party operator=(const Party& other);
    /// \brief Returns the number of electorates and list seats combined.
    int getTotalSeats();

    string name;
    uint votes;
    uint electorates;
    uint listSeats;
};

#endif // PARTY_H
