//
// Created by joo on 1/14/25.
//

#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGenrator.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
class ActionInitialization : public G4VUserActionInitialization {
    public:
        ActionInitialization();
        ~ActionInitialization() override;
        void Build() const override;
        void BuildForMaster() const override;
};


#endif //ACTIONINITIALIZATION_HH
