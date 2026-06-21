#include "CrystalHit.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<CrystalHit>* CrystalHitAllocator = nullptr;

CrystalHit::CrystalHit()
  : G4VHit(), fTotalEdep(0.0)
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 

CrystalHit::~CrystalHit()
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 

CrystalHit::CrystalHit(const CrystalHit& /*right*/)
  : G4VHit() 
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 
