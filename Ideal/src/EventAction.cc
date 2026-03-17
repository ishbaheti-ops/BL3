#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"




EventAction::EventAction()
  : G4UserEventAction(),
    fHits{0,0,0,0,0,0},
    eventID(0),
    falphaDetected(false)
{}

EventAction::~EventAction()
{
    eventID = 0;
    falphaDetected = false;
    fHits[0] = 0;
    fHits[1] = 0;
    fHits[2] = 0;
    fHits[3] = 0;
    fHits[4] = 0;
    fHits[5] = 0;
} 

void EventAction::BeginOfEventAction(const G4Event* event) 
{
    falphaDetected = false;
}

void EventAction::RecordAlphaDetection(G4int detID, G4int eventid)
{
    falphaDetected = true;
    eventID = eventid;
    if(detID>=0 && detID<6)
        fHits[detID]++;

}


void EventAction::EndOfEventAction(const G4Event* event)
{   
    G4int currentID = event->GetEventID();
    if (currentID % 10000000 == 0)
    {
        G4cout << "Progress at event " << currentID << ": {TL: "
        << fHits[0] 
        << ", ML: " << fHits[1] 
        << ", BL: " << fHits[2] 
        << ", TR: " << fHits[3] 
        << ", MR: " << fHits[4] 
        << ", BR: " << fHits[5] 
        << "}. The total number of hits are: " 
        << fHits[0] + fHits[1] + fHits[2] + fHits[3] + fHits[4] + fHits[5] 
        << G4endl;
    }
}