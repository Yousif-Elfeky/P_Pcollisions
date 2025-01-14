//
// Created by joo on 1/14/25.
//
#include "PhysicsList.hh"

PhysicsList::PhysicsList() {
    //Register the Electro-Magnetic physics
    RegisterPhysics(new G4EmStandardPhysics);
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT);
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
    RegisterPhysics(new G4DecayPhysics());
};
PhysicsList::~PhysicsList() =default;

