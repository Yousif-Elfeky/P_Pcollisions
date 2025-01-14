//
// Created by joo on 1/14/25.
//

#ifndef PRIMARYGENRATOR_HH
#define PRIMARYGENRATOR_HH
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4IonTable.hh"

class PrimaryGenrator:public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGenrator();
    ~PrimaryGenrator() override;
    void GeneratePrimaries(G4Event*) override;
    // Setter for particle energy
    void SetParticleEnergy(G4double energy);

private:
    G4double energy = 100 * GeV; // Energy for both protons
    // Constants for positions and momenta
    const G4ThreeVector pos1 = G4ThreeVector(0., 0., -10. * cm);
    const G4ThreeVector pos2 = G4ThreeVector(0., 0., 10. * cm);
    const G4ThreeVector mom1 = G4ThreeVector(0., 0., 1.);
    const G4ThreeVector mom2 = G4ThreeVector(0., 0., -1.);
    G4ParticleGun* protonGun1;
    G4ParticleGun* protonGun2;
};

#endif //PRIMARYGENRATOR_HH
