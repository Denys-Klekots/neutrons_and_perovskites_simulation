
#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGun = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fGun -> GeneratePrimaryVertex(anEvent);
}