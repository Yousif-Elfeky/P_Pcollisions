//
// Created by joo on 1/14/25.
//
#include <utility>

#include "SensitveDetector.hh"
SensitiveDetector::SensitiveDetector(G4String name):G4VSensitiveDetector(std::move(name)) {
    fTotalEnergyDeposited = 0.0 * GeV;
}
SensitiveDetector::~SensitiveDetector()=default;

void SensitiveDetector::Initialize(G4HCofThisEvent *) {
    fTotalEnergyDeposited = 0.0 * GeV;
}


G4bool SensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory *ROhist) {
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();

    G4double energyDeposited = aStep->GetTotalEnergyDeposit();

    if (energyDeposited > 0)
    {
        fTotalEnergyDeposited += energyDeposited ;
    }

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *) {
    G4cout << "Deposited energy: " << fTotalEnergyDeposited  << G4endl;
}