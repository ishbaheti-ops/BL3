#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh" 

class G4ParticleGun; 

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction 
{
public:
    PrimaryGeneratorAction(); 
    virtual ~PrimaryGeneratorAction(); 

    virtual void GeneratePrimaries(G4Event* anEvent); 
private:
    G4ParticleGun* fParticleGun;
};

#endif