//
// Created by joo on 1/14/25.
//
#include <utility>
#include "G4Neutron.hh"
#include "RunAction.hh"
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

    G4double energyDeposited = aStep->GetTotalEnergyDeposit();

    if (energyDeposited > 0)
    {
        fTotalEnergyDeposited += energyDeposited / GeV ;
    }

    if (energyDeposited < 10.0 * MeV) {
        return false;
    }

    const G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
    G4String particleName = particle->GetParticleName();
    G4double E = aStep->GetTrack()->GetTotalEnergy();
    G4ThreeVector momentum = aStep->GetTrack()->GetMomentum();
    G4double pT = momentum.perp();
    G4double eta = momentum.pseudoRapidity();
    G4double phi = momentum.phi();
    G4double charge = particle->GetPDGCharge();
    G4double mass = particle->GetPDGMass();

    // Fill particle-level ntuple
    if (RunAction::IsBatchMode) {
        analysisManager->FillNtupleIColumn(1, 0, particle->GetParticleDefinitionID()); // Particle type
        analysisManager->FillNtupleDColumn(1, 1, E); // Energy
        analysisManager->FillNtupleDColumn(1, 2, momentum.x()); // px
        analysisManager->FillNtupleDColumn(1, 3, momentum.y()); // py
        analysisManager->FillNtupleDColumn(1, 4, momentum.z()); // pz
        analysisManager->FillNtupleDColumn(1, 5, pT); // pT
        analysisManager->FillNtupleDColumn(1, 6, eta); // eta
        analysisManager->FillNtupleDColumn(1, 7, phi); // phi
        analysisManager->FillNtupleDColumn(1, 8, charge); // charge
        analysisManager->FillNtupleDColumn(1, 9, mass); // mass
        analysisManager->AddNtupleRow(1);

    }

    if (particle == G4Neutron::NeutronDefinition()) {
        return false;
    }


    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *) {
    G4cout << "Deposited energy: " << fTotalEnergyDeposited << " GeV"  << G4endl;
}
G4int SensitiveDetector::GetParticleTypeID(const G4String& particleName) {
    if (particleName == "gamma") return 1;
    if (particleName == "e-") return 2;
    if (particleName == "proton") return 3;
    // Add more particles as needed
    return 0; // Unknown particle
}