//
// Created by joo on 1/14/25.
//

#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"
#include "G4Run.hh"
#include "ctime"


class RunAction : public G4UserRunAction {
    public:
    RunAction();
    ~RunAction() override;
    static bool IsBatchMode;
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

};

#endif //RUNACTION_HH
