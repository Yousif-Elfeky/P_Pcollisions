//
// Created by joo on 1/14/25.
//
#ifndef PHYSICSLIST_CC_HH
#define PHYSICSLIST_CC_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"


class PhysicsList: public G4VModularPhysicsList {
  public:
    PhysicsList();
    ~PhysicsList() override;

};

#endif //PHYSICSLIST_CC_HH
