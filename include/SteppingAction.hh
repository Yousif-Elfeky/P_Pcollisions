//
// Created by joo on 1/14/25.
//

#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Track.hh"
#include "G4VisManager.hh"
#include "G4Polyline.hh"
#include "G4VisAttributes.hh"
#include "G4VTrajectory.hh"
#include "G4Color.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Neutron.hh"

#include <map>

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction();
    ~SteppingAction() override;

    void UserSteppingAction(const G4Step* step) override;

private:
    static std::map<std::string, G4Colour> particleColorMap;
};


#endif //STEPPINGACTION_HH
