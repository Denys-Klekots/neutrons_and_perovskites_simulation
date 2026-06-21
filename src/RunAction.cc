#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  G4cout << "Using " << analysisManager->GetType() 
         << " analysis manager" << G4endl;
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetFileName("Default_filename.root");


  analysisManager->CreateNtuple("Crystal", "Crystal events"); // Ntuple ID = 0
  analysisManager->CreateNtupleIColumn("eventId"      ); // column id = 0
  analysisManager->CreateNtupleDColumn("depositEnergy"); // column id = 1
  analysisManager->FinishNtuple(0);

  analysisManager->CreateNtuple("Screen", "Screen hist"); // Ntuple ID = 1
  analysisManager->CreateNtupleDColumn("primaryEnergy"); // column id = 0
  analysisManager->CreateNtupleIColumn("eventId"      ); // column id = 1
  analysisManager->CreateNtupleDColumn("primaryX"     ); // column id = 2
  analysisManager->CreateNtupleDColumn("primaryY"     ); // column id = 3
  analysisManager->CreateNtupleDColumn("primaryZ"     ); // column id = 4
  analysisManager->CreateNtupleDColumn("exitEnergy"   ); // column id = 5
  analysisManager->CreateNtupleDColumn("exitX"        ); // column id = 6
  analysisManager->CreateNtupleDColumn("exitY"        ); // column id = 7
  analysisManager->FinishNtuple(1);
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}