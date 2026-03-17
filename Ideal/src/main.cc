#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
    auto* runManager = new G4RunManager();
    auto* detector = new DetectorConstruction();
    
    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(new PhysicsList());
    auto* eventAction = new EventAction();
    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(eventAction);    
    runManager->SetUserAction(new SteppingAction(detector, eventAction));
    
    
    runManager->Initialize();

    G4UImanager* uiManager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    //G4VisManager* visManager = new G4VisExecutive();
    //visManager->Initialize();

    
    if (ui) {
        uiManager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        uiManager->ApplyCommand("/run/beamOn 100");
    }

    //delete visManager;
    delete runManager;
    return 0;
}