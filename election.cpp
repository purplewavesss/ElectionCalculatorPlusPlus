#include "election.h"

Election::Election() {
    threshold = 0;
    tagAlongSeats = 0;
    levelingStrat = LevelingStrategy::None();
    electionType = ElectionType::MMP;
    extraStrat = ExtraSeatsStrategy::Overhang;
}

bool Election::addParty(Party&& party) {
    if (votes.addVotes(party.votes) && !partyNames.contains(party.name)) {
        partyNames.insert(party.name);
        electionData.push_back(std::move(party));
        return true;
    }

    return false;
}

bool Election::removeParty(const QString& name) {
    for (int i = 0; i < electionData.size(); i++) {
        if (electionData[i].name == name) {
            partyNames.erase(electionData[i].name);
            electionData.erase(electionData.begin() + i);
            return true;
        }
    }

    return false;
}

bool Election::removeMostRecent() {
    if (electionData.size() == 0) return false;
    electionData.pop_back();
    return true;
}

bool Election::setVoteCount(VoteCount&& newCount) {
    if (votes.getValidVotes() > newCount.getTotalVotes()) {
        return false;
    }

    votes = std::move(newCount);
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
