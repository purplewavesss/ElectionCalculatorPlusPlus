#ifndef VOTECOUNT_H
#define VOTECOUNT_H

#include <expected>
#include <stdexcept>
using std::expected;
using std::logic_error;

class VoteCount
{
public:
    VoteCount(uint validVotes = 0);
    VoteCount(uint validVotes, uint blankVotes, uint notaVotes);

    /// \brief Creates a new vote count with arbitrary number of votes.
    /// \remarks For example, this allows a vote count for an election to be created with the correct number of votes without inputting every party that participated in that election.
    /// \return Either the new VoteCount, or a logic_error if the vote count given is smaller than the actual vote count.
    [[nodiscard]] static expected<VoteCount, logic_error> createForcedCount(uint totalVotes, uint validVotes, uint blankVotes, uint notaVotes);

    uint getValidVotes() { return validVotes; };
    uint getTotalVotes() { return totalVotes; };

    /// \brief Adds valid votes to the count. This also adds them to total votes if a vote count has not been forced.
    /// \return Either void, or a logic_error if adding votes
    [[nodiscard]] expected<void, logic_error> addVotes(uint votes);

    /// \brief Removes votes from the count. This also removes them from total votes if a vote count has not been forced.
    /// \throws overflow_error Throws if the requested vote removal is larger than the number of valid votes.
    /// \remarks This throws instead of returning expected, because going below zero votes should not be allowed in normal usage.
    void removeVotes(uint votes);
private:
    VoteCount(uint totalVotes, uint validVotes, uint blankVotes, uint notaVotes);
    uint getActualVotes();

    uint totalVotes;
    uint validVotes;

    // Modifying these in the program should require a new vote count.
    uint blankVotes;
    uint notaVotes;
    bool voteCountForced;
};

#endif // VOTECOUNT_H
