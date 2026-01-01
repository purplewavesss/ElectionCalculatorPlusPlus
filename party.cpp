#include "party.h"

Party::Party(const string& name, uint votes, uint electorates, uint listSeats):
    name(name), votes(votes), electorates(electorates), listSeats(listSeats)
{}

Party::Party(const Party& other):
    name(other.name), votes(other.votes), electorates(other.electorates), listSeats(other.listSeats)
{}

Party Party::operator=(const Party& other) {
    if (&other == this) {
        return *this;
    }

    name = other.name;
    votes = other.votes;
    electorates = other.electorates;
    listSeats = other.listSeats;

    return *this;
}

int Party::getTotalSeats() {
    return electorates + listSeats;
}
