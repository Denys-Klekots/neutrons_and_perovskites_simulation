#include "SteppingAction.hh"

#include <G4Step.hh>
#include <G4AnalysisManager.hh>
#include <G4RunManager.hh>

#include <G4SystemOfUnits.hh>

#include <G4VProcess.hh>


GRAiNTIASteppingAction::GRAiNTIASteppingAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GRAiNTIASteppingAction::~GRAiNTIASteppingAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GRAiNTIASteppingAction::UserSteppingAction(const G4Step* aStep)
{

    // If primary particle escaping from the crystal
    if(aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName() == "World" &
       aStep->GetTrack()->GetTrackID() != 1 )
    {
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

        G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double escapedEnergy;
        G4String processName = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
        G4int pdgNumber = aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding();


        if(processName == "conv" && pdgNumber == -11) // if escaping positron created in pair production
        {
            // positron carry out the it's kinetic energy + 1022 KeV because othervise it will anihilate to deposit that energy
            escapedEnergy = aStep->GetPreStepPoint()->GetKineticEnergy() + 2*aStep->GetTrack()->GetParticleDefinition()->GetPDGMass();
        }
        else
        {
            escapedEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
        }


        analysisManager->FillNtupleIColumn(1, 0, evID);
        analysisManager->FillNtupleDColumn(1, 1, escapedEnergy/ MeV);
        analysisManager->FillNtupleDColumn(1, 2, aStep->GetPreStepPoint()->GetPosition().getX() / mm);
        analysisManager->FillNtupleDColumn(1, 3, aStep->GetPreStepPoint()->GetPosition().getY() / mm);
        analysisManager->FillNtupleDColumn(1, 4, aStep->GetPreStepPoint()->GetPosition().getZ() / mm);
        analysisManager->FillNtupleSColumn(1, 5, processName);
        analysisManager->FillNtupleIColumn(1, 6, pdgNumber);
        analysisManager->AddNtupleRow(1);

        aStep->GetTrack()->SetTrackStatus(fStopAndKill);

    }



}