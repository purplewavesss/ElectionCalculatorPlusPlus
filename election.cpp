#include "election.h"
using std::partial_sort;
using std::greater;

Election::Election() {
    threshold = 0;
    tagAlongSeats = 0;
    levelingStrat = LevelingStrategy::None();
    electionType = ElectionType::MMP;
    extraStrat = ExtraSeatsStrategy::Overhang;
}

bool Election::addParty(Party&& party) {
    if (count.addVotes(party.votes) && !partyNames.contains(party.name)) {
        partyNames.insert(party.name);
        partyVotes[party.name] = party.votes;
        electionData.push_back(std::move(party));
        return true;
    }

    return false;
}

bool Election::removeParty(const QString& name) {
    for (int i = 0; i < electionData.size(); i++) {
        if (electionData[i].name == name) {
            partyNames.erase(electionData[i].name);
            partyVotes.erase(electionData[i].name);
            electionData.erase(electionData.begin() + i);
            return true;
        }
    }

    return false;
}

bool Election::removeMostRecent() {
    uint recentLoc = electionData.size() - 1;
    if (recentLoc < 0) return false;

    partyNames.erase(electionData[recentLoc].name);
    partyVotes.erase(electionData[recentLoc].name);
    electionData.pop_back();
    return true;
}

bool Election::setVoteCount(VoteCount&& newCount) {
    if (count.getValidVotes() > newCount.getTotalVotes()) {
        return false;
    }

    count = std::move(newCount);
    return true;
}

void Election::setElectionType(ElectionType newType) {
    electionType = newType;

    // MMP requires an ESS
    if (electionType == ElectionType::MMP) {
        extraStrat = ExtraSeatsStrategy::Overhang;
    }
}

bool Election::setExtraSeatsStrategy(ExtraSeatsStrategy newEss) {
    if (electionType == ElectionType::MMP && newEss == ExtraSeatsStrategy::None) {
        return false;
    }

    extraStrat = newEss;
    return true;
}

unordered_map<QString, uint> Election::getInitialHighestAveragesResults(function<double(int)> divisor, int seats) {
    priority_queue<pair<double, QString>> parties = getPartyQueue();
    unordered_map<QString, uint> results;

    for (int _ = 0; _ < seats; _++) {
        pair<double, QString> topParty = parties.top();
        results[topParty.second]++;
        parties.emplace(partyVotes[topParty.second] / divisor(results[topParty.second]), topParty.second);
    }

    return results;
}

unordered_map<QString, uint> Election::getInitialLargestRemainderResults(function<int(int)> quota, int seats) {
    unordered_map<QString, uint> fullResults;
    vector<pair<double, QString>> remainders;

    // Calculate quota results
    for (const auto& [name, votes] : partyVotes) {
        fullResults[name] = votes / seats;
        remainders.push_back(pair<double, QString>(votes % seats, name));
    }

    // Assign missing seats
    uint missingSeats = sumMapContents(fullResults) - seats;
    partial_sort(remainders.begin(), remainders.begin() + missingSeats, remainders.end(), greater<pair<double, QString>>());
    for (const auto& [_, name] : remainders) {
        fullResults[name]++;
    }

    return fullResults;
}

priority_queue<pair<double, QString>> Election::getPartyQueue() {
    priority_queue<pair<double, QString>> parties;

    for (const Party& party: electionData) {
        if (recievesListSeats(party)) {
            parties.push(pair<double, QString>(
                party.votes,
                party.name
            ));
        }
    }

    return parties;
}

bool Election::recievesListSeats(const Party& party) {
    if (party.votes / count.getTotalVotes() > threshold) {
        return true;
    }

    else if (party.electorates >= tagAlongSeats) {
        return true;
    }

    return false;
}

uint Election::sumMapContents(unordered_map<QString, uint>& contents) {
    uint sum = 0;

    for (const auto& [_, value] : contents) {
        sum += value;
    }

    return sum;
}
