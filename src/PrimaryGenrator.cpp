//
// Created by joo on 1/14/25.
//
#include "PrimaryGenrator.hh"

#include <G4Event.hh>

PrimaryGenrator::PrimaryGenrator() {
    protonGun1 = new G4ParticleGun();
    protonGun2 = new G4ParticleGun();

    G4ParticleDefinition* proton = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    protonGun1->SetParticleDefinition(proton);
    protonGun2->SetParticleDefinition(proton);

    protonGun1->SetParticlePosition(pos1);
    protonGun1->SetParticleMomentumDirection(mom1);
    protonGun2->SetParticlePosition(pos2);
    protonGun2->SetParticleMomentumDirection(mom2);

}
PrimaryGenrator::~PrimaryGenrator() {}

void PrimaryGenrator::GeneratePrimaries(G4Event* anEvent) {

    protonGun1->GeneratePrimaryVertex(anEvent);
    protonGun2->GeneratePrimaryVertex(anEvent);

    // Debug output (optional)
    // G4cout << "Generated proton 1 at " << pos1 << " with momentum " << mom1 << G4endl;
    // G4cout << "Generated proton 2 at " << pos2 << " with momentum " << mom2 << G4endl;
}
void PrimaryGenrator::SetParticleEnergy(G4double energy) {
    this->energy = energy;
    protonGun1->SetParticleEnergy(energy);
    protonGun2->SetParticleEnergy(energy);
}
