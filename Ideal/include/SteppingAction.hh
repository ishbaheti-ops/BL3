#ifndef SteppingAction_hh
#define SteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction; //need for detector volumes
class EventAction; //need for recording events

class SteppingAction : public G4UserSteppingAction 
{
    public:
        SteppingAction(DetectorConstruction* det, EventAction* evt);
        virtual ~SteppingAction();

        virtual void UserSteppingAction(const G4Step* step); 
    private:
        DetectorConstruction* fDetectorConstruction; //pointer to access volume
        EventAction* fEventAction; //pointer to record events
};


#endif