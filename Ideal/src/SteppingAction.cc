#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh" 
#include "G4Track.hh" 
#include "G4LogicalVolume.hh" 
#include "G4Neutron.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt) 
 : fDetectorConstruction(det), fEventAction(evt)
{}


SteppingAction::~SteppingAction() {} 

void SteppingAction::UserSteppingAction(const G4Step* step) 
{

    G4StepPoint* prePoint = step->GetPreStepPoint();

    if(prePoint->GetStepStatus() != fGeomBoundary)
    return;


    G4TouchableHandle touchable = prePoint->GetTouchableHandle();
    G4VPhysicalVolume* volume = touchable->GetVolume();

    if(volume->GetName() == "Aperture") {
        step->GetTrack()->SetTrackStatus(fStopAndKill);
        return;
    }
        
    
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    if(volume->GetLogicalVolume() != fDetectorConstruction->GetDetectorVolume())
    return;
        
    G4int detID = touchable->GetCopyNumber();
    fEventAction->RecordAlphaDetection(detID, eventID);

}