#include "EventAction.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "LYSOHit.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ios.hh" // For G4cout / G4cerr

EventAction::EventAction() {
    outFile.open("energy_deposition.csv");
    if (!outFile.is_open()) {
        G4cerr << "❌ ERROR: Failed to open energy_deposition.csv for writing." << G4endl;
    } else {
        G4cout << "✅ Output file energy_deposition.csv opened successfully." << G4endl;
        outFile << "Event,CrystalID,Edep_keV\n";
    }
}

EventAction::~EventAction() {
    if (outFile.is_open()) {
        outFile.close();
        G4cout << "💾 Output file closed." << G4endl;
    }
}

void EventAction::BeginOfEventAction(const G4Event* event) {
    G4cout << "🔄 Starting Event: " << event->GetEventID() << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) {
        G4cerr << "⚠️ No hit collection found for event " << event->GetEventID() << G4endl;
        return;
    }

    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID("LYSOSD/LYSOHitsCollection");
    auto hitsCollection = dynamic_cast<LYSOHitsCollection*>(hce->GetHC(hcID));
    if (!hitsCollection) {
        G4cerr << "⚠️ No LYSO hit collection for event " << event->GetEventID() << G4endl;
        return;
    }

    for (size_t i = 0; i < hitsCollection->GetSize(); ++i) {
        auto hit = (*hitsCollection)[i];
        G4double edep = hit->GetEdep();
        outFile << event->GetEventID() << "," << i << "," << edep / keV << "\n";
    }

    G4cout << "✅ Event " << event->GetEventID() << " energy data recorded." << G4endl;
}

