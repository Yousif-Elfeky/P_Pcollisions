#include <thread>

#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"


int main(int argc, char** argv) {

#ifdef G4MULTITHREADED //multithreading check
    auto *runManager = new G4MTRunManager;
    G4int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 4; // Fallback to a default value if detection fails
    }
    runManager->SetNumberOfThreads(numThreads);
#else
     G4RunManager *runManager = new G4RunManager;
#endif

    //initializing the parts of the code
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4VisManager *visManager = new G4VisExecutive();

    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();

    delete runManager;
    delete ui;
    delete visManager;
}