//
// Created by joo on 1/14/25.
//
#include "PrimaryGenrator.hh"

#include <G4Event.hh>

PrimaryGenrator::PrimaryGenrator() {
    energy = 10 * GeV; //initial value, change in the ActionInitialization.cpp
}
PrimaryGenrator::~PrimaryGenrator() {}

void PrimaryGenrator::GeneratePrimaries(G4Event* anEvent) {
    // Get the proton definition
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");

    // Proton 1
    auto* vertex1 = new G4PrimaryVertex(pos1, 0. * ns); // Correct time offset
    G4PrimaryParticle* primary1 = new G4PrimaryParticle(particle, mom1.x(), mom1.y(), mom1.z());
    primary1->SetKineticEnergy(energy); // Set energy explicitly
    vertex1->SetPrimary(primary1);
    anEvent->AddPrimaryVertex(vertex1);

    // Proton 2
    auto* vertex2 = new G4PrimaryVertex(pos2, 0. * ns); // Correct time offset
    G4PrimaryParticle* primary2 = new G4PrimaryParticle(particle, mom2.x(), mom2.y(), mom2.z());
    primary2->SetKineticEnergy(energy); // Set energy explicitly
    vertex2->SetPrimary(primary2);
    anEvent->AddPrimaryVertex(vertex2);

    // Debug output (optional)
    // G4cout << "Generated proton 1 at " << pos1 << " with momentum " << mom1 << G4endl;
    // G4cout << "Generated proton 2 at " << pos2 << " with momentum " << mom2 << G4endl;
}
void PrimaryGenrator::SetParticleEnergy(G4double energy) {
    this->energy = energy;
}
