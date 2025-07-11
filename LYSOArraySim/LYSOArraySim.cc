#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "FTFP_BERT.hh"
#include "EventAction.hh"
#include "G4UImanager.hh"

int main() {
    auto* runManager = new G4RunManager;

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(new EventAction());

    runManager->Initialize();

    auto* uiManager = G4UImanager::GetUIpointer();
    uiManager->ApplyCommand("/run/beamOn 1000");

    delete runManager;
    return 0;
}
