//
// Created by joo on 1/14/25.
//
#include "RunAction.hh"


RunAction::RunAction() {

}
RunAction::~RunAction() = default;

void RunAction::BeginOfRunAction(const G4Run *run) {

    G4int runID = run->GetRunID();
    G4int threadID = G4Threading::G4GetThreadId();
    G4long seed = static_cast<G4long>(runID) + static_cast<G4long>(threadID) + static_cast<G4long>(std::time(nullptr));
    G4Random::setTheSeed(seed);

}
void RunAction::EndOfRunAction(const G4Run *) {

}