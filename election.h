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
#include <unordered_set>
#include <queue>
using std::vector;
using std::function;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::priority_queue;

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
    unordered_map<QString, uint> getInitialHighestAveragesResults(function<double(int)> divisor, int seats);

    /// \brief Helper for calculateLargestRemainderResults that calculates proportional results.
    unordered_map<QString, uint> getInitialLargestRemainderResults(function<int(int)> quota, int seats);

    /// \brief Returns a priority queue of all parties and the votes they recieved.
    priority_queue<pair<double, QString>> getPartyQueue();

    bool recievesListSeats(const Party& party);
    uint sumMapContents(unordered_map<QString, uint>& contents);

    vector<Party> electionData;
    unordered_map<QString, uint> partyVotes;
    VoteCount count;
    ElectionType electionType;
    ExtraSeatsStrategy extraStrat;
    unordered_set<QString> partyNames;
};

#endif // ELECTION_H
