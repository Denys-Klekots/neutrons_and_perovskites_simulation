#include "CrystalSD.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

CrystalSD::CrystalSD(const G4String &name,
                     const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name),
      fHitsCollection(0)
{
  collectionName.insert(hitsCollectionName);
}

CrystalSD::~CrystalSD()
{

}

void CrystalSD::Initialize(G4HCofThisEvent *hce)
{
  fHitsCollection = new CrystalHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

  CrystalHit* newHit = new CrystalHit();
  fHitsCollection->insert(newHit);

}

G4bool CrystalSD::ProcessHits(G4Step *step,
                              G4TouchableHistory * /*history*/)
{
  G4double edep = step->GetTotalEnergyDeposit();
  

  CrystalHit* aHit = (*fHitsCollection)[0];
  aHit->AddEdep(edep);


  return true;
}

void CrystalSD::EndOfEvent(G4HCofThisEvent * /*hce*/)
{
  const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
  G4int eventId = event->GetEventID();

  CrystalHit* hit = (CrystalHit*)(*fHitsCollection)[0];
  G4double depositEnergy = hit->GetTotalEdep();

  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(0, 0, eventId         );
  analysisManager->FillNtupleDColumn(0, 1, depositEnergy/eV);
  analysisManager->AddNtupleRow(0);

}
