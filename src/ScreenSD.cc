#include "ScreenSD.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

ScreenSD::ScreenSD(const G4String &name,
                     const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name),
      fHitsCollection(0)
{
  collectionName.insert(hitsCollectionName);
}

ScreenSD::~ScreenSD()
{

}

void ScreenSD::Initialize(G4HCofThisEvent *hce)
{
  fHitsCollection = new ScreenHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

  ScreenHit* newHit = new ScreenHit();
  fHitsCollection->insert(newHit);

}

G4bool ScreenSD::ProcessHits(G4Step *step,
                              G4TouchableHistory * /*history*/)
{
  G4double edep = step->GetTotalEnergyDeposit();

  if(step->GetTrack()->GetTrackID() == 1) // if primary particle
  {

    ScreenHit* aHit = (*fHitsCollection)[0];
    aHit->SetX(step->GetPostStepPoint()->GetPosition().getX());
    aHit->SetY(step->GetPostStepPoint()->GetPosition().getY());

    aHit->SetE(step->GetPostStepPoint()->GetKineticEnergy());
  }



  return true;
}

void ScreenSD::EndOfEvent(G4HCofThisEvent * /*hce*/)
{
  ScreenHit* hit = (ScreenHit*)(*fHitsCollection)[0];
  G4double exitE = hit->GetE();
  G4double exitX = hit->GetX();
  G4double exitY = hit->GetY();

  const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
  const G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
  const G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
  G4double primaryEnergy = primaryParticle->GetKineticEnergy();

  G4int eventId = event->GetEventID();

  G4double primaryX = primaryVertex->GetPosition().getX();
  G4double primaryY = primaryVertex->GetPosition().getY();
  G4double primaryZ = primaryVertex->GetPosition().getZ();


  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(1, 0, primaryEnergy/eV);
  analysisManager->FillNtupleIColumn(1, 1, eventId         );
  analysisManager->FillNtupleDColumn(1, 2, primaryX     /mm);
  analysisManager->FillNtupleDColumn(1, 3, primaryY     /mm);
  analysisManager->FillNtupleDColumn(1, 4, primaryZ     /mm);
  analysisManager->FillNtupleDColumn(1, 5, exitE        /eV);
  analysisManager->FillNtupleDColumn(1, 6, exitX        /mm);
  analysisManager->FillNtupleDColumn(1, 7, exitY        /mm);
  analysisManager->AddNtupleRow(1);


}
