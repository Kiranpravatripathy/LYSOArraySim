/*#include "LYSOSensitiveDetector.hh"
#include "LYSOHit.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TouchableHandle.hh"
#include "G4SystemOfUnits.hh"

LYSOSensitiveDetector::LYSOSensitiveDetector(const G4String& name)
: G4VSensitiveDetector(name), fHitsCollection(nullptr) {
    collectionName.insert("LYSOHitsCollection");
}

LYSOSensitiveDetector::~LYSOSensitiveDetector() {}

void LYSOSensitiveDetector::Initialize(G4HCofThisEvent* hce) {
    fHitsCollection = new LYSOHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hce->AddHitsCollection(hcID, fHitsCollection);

    // Pre-fill with one hit per crystal
    for (int i = 0; i < 100; ++i) {
        auto hit = new LYSOHit();
        hit->SetEdep(0.);
        fHitsCollection->insert(hit);
    }
}

G4bool LYSOSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* touchable) {
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0) return false;

    G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    auto hit = (*fHitsCollection)[copyNo];
    hit->SetEdep(hit->GetEdep() + edep);
    return true;
}*/

#include "LYSOSensitiveDetector.hh"
#include "LYSOHit.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

LYSOSensitiveDetector::LYSOSensitiveDetector(const G4String& name)
: G4VSensitiveDetector(name), fHitsCollection(nullptr) {
    collectionName.insert("LYSOHitsCollection");
}

LYSOSensitiveDetector::~LYSOSensitiveDetector() {}

void LYSOSensitiveDetector::Initialize(G4HCofThisEvent* hce) {
    fHitsCollection = new LYSOHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hce->AddHitsCollection(hcID, fHitsCollection);

    // Pre-create hits for all 100 crystals
    for (int i = 0; i < 100; ++i) {
        auto hit = new LYSOHit();
        hit->SetEdep(0.0);
        fHitsCollection->insert(hit);
    }
}

G4bool LYSOSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.) return false;

    G4int crystalID = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    // Safety check
    if (crystalID < 0 || crystalID >= 100) return false;

    auto hit = (*fHitsCollection)[crystalID];
    hit->SetEdep(hit->GetEdep() + edep);

    return true;
}

