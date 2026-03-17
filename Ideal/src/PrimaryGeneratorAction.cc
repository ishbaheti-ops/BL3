#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh" 
#include "G4ParticleDefinition.hh" 
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh" 
#include "G4Event.hh" 
#include "Randomize.hh" 
#include "G4RandomDirection.hh"
#include "G4PhysicalConstants.hh" //pi and whatnot

PrimaryGeneratorAction::PrimaryGeneratorAction() 
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr) 
{ 
    G4int n_particle = 1; 
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleDefinition* geantino = G4Geantino::GeantinoDefinition();
    fParticleGun->SetParticleDefinition(geantino);

    //G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("alpha"); 
    //fParticleGun->SetParticleDefinition(particle); 

    fParticleGun->SetParticlePosition(G4ThreeVector());

    //G4double energy = 1.9*MeV + 100*keV*G4UniformRand();
    //fParticleGun->SetParticleEnergy(energy); 
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() 
{
    delete fParticleGun; 
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) 
{

    G4double cosTheta = 2*G4UniformRand() - 1;
    G4double sinTheta = std::sqrt(1 - cosTheta*cosTheta);
    G4double phi = 2*pi*G4UniformRand();

    G4double px = sinTheta * std::cos(phi);
    G4double py = sinTheta * std::sin(phi);
    G4double pz = cosTheta;


    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px, py, pz)); //set direction of particle

    //fParticleGun->SetParticleMomentumDirection(G4RandomDirection()); 

    fParticleGun->GeneratePrimaryVertex(anEvent); //generate the particle
}