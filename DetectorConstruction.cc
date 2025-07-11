#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "LYSOSensitiveDetector.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    auto* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Define LYSO manually
    G4Element* Lu = nist->FindOrBuildElement("Lu");
    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* O  = nist->FindOrBuildElement("O");
    G4Material* LYSO = new G4Material("LYSO", 7.1 * g/cm3, 3);
    LYSO->AddElement(Lu, 2);
    LYSO->AddElement(Si, 1);
    LYSO->AddElement(O, 5);

    // World volume
    G4double worldSize = 1.2 * m;
    auto* worldBox = new G4Box("World", worldSize, worldSize, worldSize);
    auto* logicWorld = new G4LogicalVolume(worldBox, worldMat, "World");
    auto* physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0);

    // Crystal dimensions
    auto* crystalBox = new G4Box("Crystal", 5 * cm, 1.5 * cm, 5 * cm);
    auto* logicCrystal = new G4LogicalVolume(crystalBox, LYSO, "Crystal");

    // Sensitive detector setup
    auto* sdManager = G4SDManager::GetSDMpointer();
    auto* lysoSD = new LYSOSensitiveDetector("LYSOSD");
    sdManager->AddNewDetector(lysoSD);
    logicCrystal->SetSensitiveDetector(lysoSD);

    // Place 10×10 crystals
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            G4ThreeVector position((i - 4.5) * 10 * cm, (j - 4.5) * 3 * cm, 0);
            new G4PVPlacement(nullptr, position, logicCrystal, "Crystal", logicWorld, false, i * 10 + j);
        }
    }

    return physWorld;
}


