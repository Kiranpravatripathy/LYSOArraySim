#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction() = default;
    virtual ~DetectorConstruction() = default;

    virtual G4VPhysicalVolume* Construct() override;
};

