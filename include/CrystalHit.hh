#ifndef __CrystalHit_hh__
#define __CrystalHit_hh__

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class CrystalHit : public G4VHit
{
    public:
        CrystalHit();
        virtual ~CrystalHit();
        CrystalHit(const CrystalHit& right);

        inline void* operator new(size_t);
        inline void  operator delete(void* hit);

        void AddEdep(G4double edep)       { fTotalEdep += edep; }

        G4double GetTotalEdep() const   { return fTotalEdep; }
    

    private:
        G4double       fTotalEdep;
};

typedef G4THitsCollection<CrystalHit> CrystalHitsCollection;

extern G4ThreadLocal G4Allocator<CrystalHit>* CrystalHitAllocator;

inline void* CrystalHit::operator new(size_t)
{
  if (! CrystalHitAllocator)
        CrystalHitAllocator = new G4Allocator<CrystalHit>;
  return (void*)CrystalHitAllocator->MallocSingle();
}

inline void CrystalHit::operator delete(void* hit)
{
  CrystalHitAllocator->FreeSingle((CrystalHit*) hit);
}

#endif //__CrystalHit_hh__