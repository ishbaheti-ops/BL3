#ifndef EventAction_hh
#define EventAction_hh

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"

class EventAction : public G4UserEventAction
{
    public:
        EventAction();
        virtual ~EventAction();

        virtual void BeginOfEventAction(const G4Event*); 
        virtual void EndOfEventAction(const G4Event*); 

        void RecordAlphaDetection(G4int id, G4int eventid); 
    private:

        G4int fHits[6];
        G4int eventID;
        G4bool falphaDetected;

};

#endif