//
// Created by joo on 1/14/25.
//
#include "RunAction.hh"


bool RunAction::IsBatchMode = false;


RunAction::RunAction() {
    if (RunAction::IsBatchMode) {
        //Ntuples for photons
        G4cout << "Running in batch mode. Creating Ntupels." << G4endl;

        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

        analysisManager->CreateNtuple("Event", "Event Information");
        analysisManager->CreateNtupleIColumn("EventID");
        analysisManager->CreateNtupleIColumn("RunNumber");
        analysisManager->CreateNtupleIColumn("NumberOfPrimaryVertices");
        // analysisManager->CreateNtupleDColumn("EventWeight");
        analysisManager->FinishNtuple(0);

        // Ntuple for particle-level information
        analysisManager->CreateNtuple("Particles", "Particle Information");
        analysisManager->CreateNtupleIColumn("ParticleType");
        analysisManager->CreateNtupleDColumn("E");
        analysisManager->CreateNtupleDColumn("px");
        analysisManager->CreateNtupleDColumn("py");
        analysisManager->CreateNtupleDColumn("pz");
        analysisManager->CreateNtupleDColumn("pT");
        analysisManager->CreateNtupleDColumn("eta");
        analysisManager->CreateNtupleDColumn("phi");
        analysisManager->CreateNtupleDColumn("Charge");
        analysisManager->CreateNtupleDColumn("Mass");
        analysisManager->FinishNtuple(1);

        // Ntuple for jet information
        analysisManager->CreateNtuple("Jets", "Jet Information");
        analysisManager->CreateNtupleDColumn("JetEnergy");
        analysisManager->CreateNtupleDColumn("Jetpx");
        analysisManager->CreateNtupleDColumn("Jetpy");
        analysisManager->CreateNtupleDColumn("Jetpz");
        analysisManager->CreateNtupleDColumn("JetpT");
        analysisManager->CreateNtupleDColumn("JetEta");
        analysisManager->CreateNtupleDColumn("JetPhi");
        analysisManager->FinishNtuple(2);

        // Ntuple for missing transverse energy (MET)
        analysisManager->CreateNtuple("MET", "Missing Transverse Energy");
        analysisManager->CreateNtupleDColumn("METMagnitude");
        analysisManager->CreateNtupleDColumn("METPhi");
        analysisManager->FinishNtuple(3);
    }
}
RunAction::~RunAction() = default;

void RunAction::BeginOfRunAction(const G4Run *run) {


    G4int runID = run->GetRunID();
    G4int threadID = G4Threading::G4GetThreadId();
    G4long seed = static_cast<G4long>(runID) + static_cast<G4long>(threadID) + static_cast<G4long>(std::time(nullptr));
    G4Random::setTheSeed(seed);

    if (RunAction::IsBatchMode) {
        // Only open the file in batch mode
        G4cout << "Running in batch mode. Creating ROOT Files." << G4endl;

        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        std::stringstream strRunID;
        strRunID << runID;
        analysisManager->OpenFile("output" + strRunID.str() + ".root");
    }

}


void RunAction::EndOfRunAction(const G4Run *) {
    if (RunAction::IsBatchMode) {
        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile();
    }

}