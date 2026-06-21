#ifndef __ScreenHit_hh__
#define __ScreenHit_hh__

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class ScreenHit : public G4VHit
{
    public:
        ScreenHit();
        virtual ~ScreenHit();
        ScreenHit(const ScreenHit& right);

        inline void* operator new(size_t);
        inline void  operator delete(void* hit);

        void SetX(G4double X) { fHitX = X; }
        void SetY(G4double Y) { fHitY = Y; }
        void SetE(G4double E) { fEnergy = E; }

        G4double GetX() const   { return fHitX; }
        G4double GetY() const   { return fHitY; }
        G4double GetE() const   { return fEnergy; }
    

    private:
        G4double fHitX;
        G4double fHitY;
        G4double fEnergy;
};

typedef G4THitsCollection<ScreenHit> ScreenHitsCollection;

extern G4ThreadLocal G4Allocator<ScreenHit>* ScreenHitAllocator;

inline void* ScreenHit::operator new(size_t)
{
  if (! ScreenHitAllocator)
        ScreenHitAllocator = new G4Allocator<ScreenHit>;
  return (void*)ScreenHitAllocator->MallocSingle();
}

inline void ScreenHit::operator delete(void* hit)
{
  ScreenHitAllocator->FreeSingle((ScreenHit*) hit);
}

#endif //__ScreenHit_hh__