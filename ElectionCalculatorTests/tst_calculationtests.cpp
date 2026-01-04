#include <QtTest>
#include "election.h"

// add necessary includes here

class CalculationTests : public QObject
{
    Q_OBJECT

private slots:
    void addAndRemoveParty();
};

void CalculationTests::addAndRemoveParty() {
    Election election;
    Party party = Party(QString("TestParty"), 5, 0, 0, false);
    QVERIFY(election.addParty(std::move(party)));
    QVERIFY(election.removeParty(QString("TestParty")));
}


QTEST_APPLESS_MAIN(CalculationTests)

#include "tst_calculationtests.moc"
