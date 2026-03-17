#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsList : public G4VModularPhysicsList
{
public:
    PhysicsList();
    virtual ~PhysicsList();
/*
    virtual void ConstructParticle() override; 
    virtual void ConstructProcess() override; 
    virtual void SetCuts(); 
    */
};

#endif