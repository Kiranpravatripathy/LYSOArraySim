#pragma once
#include "G4VSensitiveDetector.hh"
#include "LYSOHit.hh"

class LYSOSensitiveDetector : public G4VSensitiveDetector {
public:
    LYSOSensitiveDetector(const G4String& name);
    virtual ~LYSOSensitiveDetector();

    virtual void Initialize(G4HCofThisEvent*) override;
    virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;

private:
    LYSOHitsCollection* fHitsCollection;
};

