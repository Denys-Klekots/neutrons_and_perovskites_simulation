#ifndef __ScreenSD_hh__
#define __ScreenSD_hh__

#include "G4VSensitiveDetector.hh"
#include "ScreenHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class ScreenSD : public G4VSensitiveDetector
{
  public:
    ScreenSD(const G4String& name, 
                  const G4String& hitsCollectionName);
    virtual ~ScreenSD();

    virtual void   Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hce);

  private:
    ScreenHitsCollection* fHitsCollection;
};

#endif //__ScreenSD_hh__