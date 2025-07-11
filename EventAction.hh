#pragma once
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include <fstream>

class EventAction : public G4UserEventAction {
public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*) override;
    virtual void EndOfEventAction(const G4Event*) override;

private:
    std::ofstream outFile;
};

