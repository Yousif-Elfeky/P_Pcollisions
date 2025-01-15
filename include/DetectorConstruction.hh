//
// Created by joo on 1/14/25.
//

#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"
#include "SensitveDetector.hh"
#include "G4Tubs.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction() override;
    G4VPhysicalVolume* Construct() override;
private:
    G4LogicalVolume *logicDetector{};
    void ConstructSDandField() override;
};

#endif //DETECTORCONSTRUCTION_HH
