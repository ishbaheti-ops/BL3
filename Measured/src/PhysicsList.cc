#include "PhysicsList.hh"

//#include "G4DecayPhysics.hh"
//#include "G4IonPhysics.hh"
//#include "G4EmStandardPhysics.hh"    
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
 : G4VModularPhysicsList()
{
    //RegisterPhysics(new G4IonPhysics()); //don't need these two because its a geantino
    //RegisterPhysics(new G4EmStandardPhysics());
    //RegisterPhysics(new G4DecayPhysics());
}

PhysicsList::~PhysicsList() {}
/*
void PhysicsList::SetCuts()
{
    SetCutsWithDefault();
}

void PhysicsList::ConstructParticle()
{
    G4VModularPhysicsList::ConstructParticle(); //don't need this because it a geantino
}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess(); //don't need this becasue its a geantino
}
    */