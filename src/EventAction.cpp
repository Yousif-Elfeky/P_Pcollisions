//
// Created by joo on 1/15/25.
//
#include "EventAction.hh"

EventAction::EventAction() : G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    // Optional: Add code to run at the beginning of each event
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4int numPrimaryParticles = 0;
    G4int numSecondaryParticles = 0;

    // Count primary particles
    for (G4int i = 0; i < event->GetNumberOfPrimaryVertex(); i++) {
        G4PrimaryVertex* vertex = event->GetPrimaryVertex(i);
        numPrimaryParticles += vertex->GetNumberOfParticle();
        for (G4int j = 0; j < vertex->GetNumberOfParticle(); j++) {
            G4PrimaryParticle* particle = vertex->GetPrimary(j);
            G4cout << "Primary: " << particle->GetParticleDefinition()->GetParticleName()
                   << " E=" << particle->GetTotalEnergy() / CLHEP::GeV << " GeV" << G4endl;
        }

    }

    // Count secondary particles
    if (G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer()) {
        for (G4int i = 0; i < trajectoryContainer->entries(); i++) {
            if ((*trajectoryContainer)[i]->GetParentID() > 0) {
                numSecondaryParticles++;
            }
        }
    }

    // Print particle counts
    G4cout << "Event ID: " << event->GetEventID() << ", "
           << "Primary Particles: " << numPrimaryParticles << ", "
           << "Secondary Particles: " << numSecondaryParticles << ", "
           << "Total Particles: " << numPrimaryParticles + numSecondaryParticles << G4endl;
}
