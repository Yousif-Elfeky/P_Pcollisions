//
// Created by joo on 1/14/25.
//
#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction() = default;
DetectorConstruction::~DetectorConstruction() = default;

G4VPhysicalVolume *DetectorConstruction::Construct() {

    G4bool checkOverlaps= true;//cleaner

    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *worldMat = nistManager->FindOrBuildMaterial("G4_AIR");
    //detector material, feel free to change it as much as you like
    // https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
    G4Material *detMat = nistManager->FindOrBuildMaterial("G4_Pb");


    //the world length, since it is a box, we multiply by half in the solid world
    G4double xWorld = 2. * m;
    G4double yWorld = 2. * m;
    G4double zWorld = 2. * m;

    auto *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    auto *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld", nullptr, false, 0, checkOverlaps);

    //Lead detector
    constexpr G4double detectorSize = 10.0 * cm;
    auto *solidDetector = new G4Box("solidDetector", 0.5 * detectorSize, 0.5 * detectorSize, 0.5 * detectorSize);
    logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,0.0 * cm),logicDetector,"physDetector" , logicWorld, false ,checkOverlaps);
    //detector color for better visuals, also purple is the best :)
    auto *detVisAtt = new G4VisAttributes(G4Color(1.0,0.,1.0,0.3));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    auto *sensDet = new SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}
