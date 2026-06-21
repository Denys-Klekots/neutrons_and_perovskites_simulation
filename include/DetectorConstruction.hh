#ifndef __DetectorConstruction_h__
#define __DetectorConstruction_h__

#include "G4VUserDetectorConstruction.hh"

#include <G4GenericMessenger.hh>


class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    G4GenericMessenger* fMessenger;
    G4String fShieldMaterial;

};

#endif // __DetectorConstruction_h__

