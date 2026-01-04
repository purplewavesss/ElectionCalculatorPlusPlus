#ifndef ELECTION_H
#define ELECTION_H

#include "electiontype.h"
#include "extraseatsstrategy.h"
#include "levelingstrategy.h"
#include "party.h"
#include "seatallocation.h"
#include "votecount.h"
#include <vector>
#include <functional>
#include <set>
using std::vector;
using std::function;
using std::set;
using std::unordered_map;

class Election
{
public:
    Election();
    /// \brief Calculates election results using a highest averages method and a given divisor.
    /// \param divisor A function that takes a number of seats, and returns the divisor for that number of seats.
    void calculateHighestAveragesResults(function<double(int)> divisor);

    /// \brief Calculates election results using a largest remainder method and a given quota.
    /// \param quota A function that takes a total number of seats, and returns the quota for that number of seats.
    void calculateLargestRemainderResults(function<int(int)> quota);

    // TODO: Write docstrings for these
    [[nodiscard]] bool addParty(Party&& party);
    [[nodiscard]] bool removeParty(const QString& name);
    [[nodiscard]] bool removeMostRecent();

    /// \brief Takes a new vote count and tries to set it as the election vote count.
    /// \return Whether the vote count switch was successful. A vote count switch can fail if it includes less valid votes than currently exist in the election.
    [[nodiscard]] bool setVoteCount(VoteCount&& newCount);

    /// \brief Sets the election type, and resets any settings conflicting with the current election type to default values.
    void setElectionType(ElectionType newType);

    /// \brief Takes a new extra seats strategy and tries to set it as the election extra seats strategy.
    /// \return Whether the ESS is valid for the election state. An MMP election cannot accept no ESS.
    [[nodiscard]] bool setExtraSeatsStrategy(ExtraSeatsStrategy newEss);

    uint threshold;
    uint tagAlongSeats;
    LevelingStrategy::Strategy levelingStrat;
    SeatAllocation seats;
private:
    /// \brief Helper for calculateHighestAveragesResults that calculates proportional results.
    unordered_map<Party, uint> getInitialHighestAveragesResults(function<double(int)> divisor);

    /// \brief Helper for calculateLargestRemainderResults that calculates proportional results.
    unordered_map<Party, uint> getInitialLargestRemainderResults(function<double(int)> divisor);

    vector<Party> electionData;
    VoteCount votes;
    ElectionType electionType;
    ExtraSeatsStrategy extraStrat;
    set<QString> partyNames;
};

#endif // ELECTION_H
