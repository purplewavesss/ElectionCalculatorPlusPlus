#ifndef LEVELINGSTRATEGY_H
#define LEVELINGSTRATEGY_H

#include <qtypes.h>
#include <variant>
using std::variant;

namespace LevelingStrategy {
    struct None {};
    struct Arbitrary {};
    struct Specified {
        uint seatNum;
    };

    using Strategy = variant<None, Arbitrary, Specified>;
}

#endif // LEVELINGSTRATEGY_H
