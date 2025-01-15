//
// Created by joo on 1/14/25.
//

#ifndef SENSITVEDETECTOR_HH
#define SENSITVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class SensitiveDetector : public G4VSensitiveDetector {
    public:
    SensitiveDetector(G4String);
    ~SensitiveDetector() override;
private:

    G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;
    void Initialize(G4HCofThisEvent*) override;
    void EndOfEvent(G4HCofThisEvent *) override;

    static G4int GetParticleTypeID(const G4String &particleName);
    G4double fTotalEnergyDeposited;
};

#endif //SENSITVEDETECTOR_HH
