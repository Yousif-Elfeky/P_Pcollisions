//
// Created by joo on 1/14/25.
//

#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization() = default;
ActionInitialization::~ActionInitialization() = default;

void ActionInitialization::BuildForMaster() const {
    auto *runAction = new RunAction();
    SetUserAction(runAction);
}
void ActionInitialization::Build() const {
    auto *runAction = new RunAction();
    SetUserAction(runAction);

    auto* primaryGenerator = new PrimaryGenrator();
    primaryGenerator->SetParticleEnergy(13 * TeV); // Set energy to 20 GeV
    SetUserAction(primaryGenerator);

    // auto *steppingAction = new SteppingAction(); //stepping action is only neaded for debuging and partilce ID, run it at you ou
    // SetUserAction(steppingAction);
}
