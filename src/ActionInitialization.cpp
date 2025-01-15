//
// Created by joo on 1/14/25.
//

#include "ActionInitialization.hh"

#include "EventAction.hh"

ActionInitialization::ActionInitialization() = default;
ActionInitialization::~ActionInitialization() = default;

void ActionInitialization::BuildForMaster() const {
    auto *runAction = new RunAction();
    SetUserAction(runAction);
}
void ActionInitialization::Build() const {
    auto *runAction = new RunAction();
    SetUserAction(runAction);

    auto *primaryGenerator = new PrimaryGenrator();
    SetUserAction(primaryGenerator);

    auto *eventAction = new EventAction();
    SetUserAction(eventAction);


    // auto *steppingAction = new SteppingAction(); //stepping action is only neaded for debuging and partilce ID, run it at you ou
    // SetUserAction(steppingAction);
}
