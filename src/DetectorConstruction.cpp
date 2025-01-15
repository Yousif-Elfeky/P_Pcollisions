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
    G4Material *siliconMat = nistManager->FindOrBuildMaterial("G4_Si");
    G4Material *leadMat = nistManager->FindOrBuildMaterial("G4_Pb");
    G4Material *scintillatorMat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");




    //the world length, since it is a box, we multiply by half in the solid world
    G4double xWorld = 30. * m;
    G4double yWorld = 30. * m;
    G4double zWorld = 30. * m;

    auto *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    auto *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld", nullptr, false, 0, checkOverlaps);


    // Define the dimensions of the cylinder and the hole
    G4double cylinderRadius = 10.0 * m;
    G4double cylinderHeight = 20.0 * m;
    G4double holeRadius = 30.0 * cm;
    G4double holeHeight = cylinderHeight + 1.0 * cm; // Slightly taller to ensure complete subtraction

    // Create the main cylinder
    auto* solidCylinder = new G4Tubs("Cylinder", 0, cylinderRadius, cylinderHeight / 2, 0, 360 * deg);
    auto* solidHole = new G4Tubs("Hole", 0, holeRadius, holeHeight / 2, 0, 360 * deg); //hole for the particles to enter
    auto solidDetector = new G4SubtractionSolid("Detector", solidCylinder, solidHole);
    logicDetector = new G4LogicalVolume(solidDetector, scintillatorMat, "Detector");
    auto* physDetector = new G4PVPlacement(nullptr, G4ThreeVector(), logicDetector, "Detector", logicWorld, false, 0);



    G4double siliconThickness = 1.0 * mm;
    G4double siliconRadius = cylinderRadius;
    G4double siliconHeight = cylinderHeight;


    auto *solidSilicon = new G4Tubs("SiliconLayer", 0, siliconRadius, siliconHeight / 2, 0, 360 * deg);
    auto* siliconHole = new G4Tubs("Hole", 0, holeRadius, holeHeight / 2, 0, 360 * deg); //hole for the particles to enter
    auto solidSiliconHole = new G4SubtractionSolid("Selecon Detector", solidSilicon, siliconHole);
    logicSilicon = new G4LogicalVolume(solidSiliconHole, siliconMat, "SiliconLayer");
    auto *physSilicon = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logicSilicon, "SiliconLayer", logicWorld, false, 0);

    // Add lead layers for calorimetry
    G4double leadThickness = 10.0 * cm;
    G4double leadRadius = cylinderRadius;
    G4double leadHeight = cylinderHeight;

    auto *solidLead = new G4Tubs("LeadLayer", 0, leadRadius, leadHeight / 2, 0, 360 * deg);
    auto* LeadHole = new G4Tubs("Hole", 0, holeRadius, holeHeight / 2, 0, 360 * deg); //hole for the particles to enter
    auto solidLeadHole = new G4SubtractionSolid("Lead Detector", solidLead, LeadHole);
    logicLead = new G4LogicalVolume(solidLeadHole, leadMat, "LeadLayer");
    auto *physLead = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logicLead, "LeadLayer", logicWorld, false, 0);

    // Visualization attributes
    auto *detVisAtt = new G4VisAttributes(G4Color(1.0,0.,1.0,0.3));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    auto *siliconVisAtt = new G4VisAttributes(G4Color(0., 1., 0., 0.5)); // Green for silicon
    siliconVisAtt->SetForceSolid(true);
    logicSilicon->SetVisAttributes(siliconVisAtt);

    auto *leadVisAtt = new G4VisAttributes(G4Color(0., 0., 1., 0.5)); // Blue for lead
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);




    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    G4ThreadLocal auto *sensDet1 = new SensitiveDetector("SensitiveDetector1");
    logicDetector->SetSensitiveDetector(sensDet1);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet1);
}
