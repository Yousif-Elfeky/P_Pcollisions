#include "SteppingAction.hh"
#include "G4Gamma.hh"

std::map<std::string, G4Colour> SteppingAction::particleColorMap = {
    {"gamma", G4Colour(0., 1., 0.)},       // Green
    {"e-", G4Colour(0., 1., 0.)},          // Blue
    {"e+", G4Colour(1., 0., 1.)},          // Magenta
    {"proton", G4Colour(1., 0., 0.)},      // Red
    {"neutron", G4Colour(0.5, 0.5, 0.5)},  // Gray
    {"pi+", G4Colour(1., 1., 0.)},         // Yellow
    {"pi-", G4Colour(1., 0.5, 0.)},        // Orange
    {"kaon+", G4Colour(0., 1., 1.)},       // Cyan
    {"kaon-", G4Colour(0.5, 0., 0.5)}      // Purple
};

SteppingAction::SteppingAction() {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {

    G4Track* track = step->GetTrack();
    const G4ParticleDefinition *particleDef = track->GetParticleDefinition();
    G4String particleName = particleDef->GetParticleName();
    G4double energy = track->GetKineticEnergy();

    G4cout << "Particle: " << particleName << ", Energy: " << energy / CLHEP::MeV << " MeV" << G4endl;


    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
        G4ThreeVector preStepPoint = step->GetPreStepPoint()->GetPosition();
        G4ThreeVector postStepPoint = step->GetPostStepPoint()->GetPosition();
        G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();

        G4Colour colour = particleColorMap.count(particleName) ? particleColorMap[particleName] : G4Colour(1., 1., 1.); // White for unknown particles

        // G4cout << "Pre-step position: " << preStepPoint << G4endl;
        // G4cout << "Post-step position: " << postStepPoint << G4endl;

        G4Polyline polyline;
        G4VisAttributes attribs(colour);
        polyline.SetVisAttributes(attribs);
        polyline.push_back(preStepPoint);
        polyline.push_back(postStepPoint);

        pVVisManager->Draw(polyline);
    }
}