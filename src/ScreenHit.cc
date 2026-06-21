#include "ScreenHit.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<ScreenHit>* ScreenHitAllocator = nullptr;

ScreenHit::ScreenHit()
  : G4VHit(), fHitX(-9999999999.9), fHitY(-9999999999.9), fEnergy(-9999999999.9)
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 

ScreenHit::~ScreenHit()
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 

ScreenHit::ScreenHit(const ScreenHit& /*right*/)
  : G4VHit() 
{}

//..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. ..ooO0Ooo.. 
