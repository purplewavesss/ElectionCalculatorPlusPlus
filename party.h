#ifndef PARTY_H
#define PARTY_H

#include <qobject.h>

struct Party {
    QString name;
    uint votes;
    uint electorates;
    uint listSeats;
    bool representsMinority;

    /// \brief Returns the number of electorates and list seats combined.
    int getTotalSeats();
};

#endif // PARTY_H
