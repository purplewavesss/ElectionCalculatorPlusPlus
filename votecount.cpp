#include "votecount.h"
using std::unexpected;
using std::overflow_error;

VoteCount::VoteCount(uint validVotes)
    : validVotes(validVotes)
    , blankVotes(0)
    , notaVotes(0)
    , voteCountForced(true)
{
    totalVotes = validVotes;
}

VoteCount::VoteCount(uint validVotes, uint blankVotes, uint notaVotes)
    : validVotes(validVotes)
    , blankVotes(blankVotes)
    , notaVotes(notaVotes)
    , voteCountForced(false)
{
    totalVotes = validVotes + blankVotes + notaVotes;
}


VoteCount::VoteCount(uint totalVotes, uint validVotes, uint blankVotes, uint notaVotes)
    : totalVotes(totalVotes)
    , validVotes(validVotes)
    , blankVotes(blankVotes)
    , notaVotes(notaVotes)
    , voteCountForced(true)
{}

expected<VoteCount, logic_error> VoteCount::createForcedCount(uint totalVotes, uint validVotes, uint blankVotes, uint notaVotes) {
    // We can't use getActualVotes here because the vote count hasn't been created yet.
    uint actualTotal = validVotes + blankVotes + notaVotes;
    if (actualTotal > totalVotes) {
        return unexpected(logic_error("There cannot be more votes inputted than exist in the vote count."));
    }

    return VoteCount(totalVotes, validVotes, blankVotes, notaVotes);
}

expected<void, logic_error> VoteCount::addVotes(uint votes) {
    if (voteCountForced && getActualVotes() > totalVotes) {
        return unexpected(logic_error("There cannot be more votes inputted than exist in the vote count."));
    }

    validVotes += votes;
    if (!voteCountForced) {
        totalVotes += votes;
    }

    return {};
}

void VoteCount::removeVotes(uint votes) {
    if (votes > validVotes) {
        throw overflow_error("Attempted to give ");
    }

    validVotes -= votes;
    if (!voteCountForced) {
        totalVotes -= votes;
    }
}

uint VoteCount::getActualVotes() {
    return validVotes + blankVotes + notaVotes;
}
