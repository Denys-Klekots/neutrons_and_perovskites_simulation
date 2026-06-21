#include "DetectorConstruction.hh"
#include "CrystalSD.hh"
#include "ScreenSD.hh"

#include <G4NistManager.hh>
#include <G4SDManager.hh>
#include <G4Material.hh>
#include <G4Element.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ProductionCuts.hh>
#include <G4SystemOfUnits.hh>
#include <G4UserLimits.hh>
#include <G4LogicalVolumeStore.hh>

#include <stdexcept>

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), fShieldMaterial("aluminum")
{ 

  fMessenger = new G4GenericMessenger(this, "/customDet/", "Detector properties customization");


  G4GenericMessenger::Command& setShieldMaterialCmd = 
                                fMessenger->DeclareProperty("setShieldMaterial", fShieldMaterial,
                                                            "Set shield material. Availible options: aluminum (default), steel, polypropylene, wax");
  setShieldMaterialCmd.SetStates(G4State_Idle);

}

DetectorConstruction::~DetectorConstruction()
{ 
  delete fMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
  
  /////////////////////
  // Shield material //
  /////////////////////

  G4Material* shieldMaterial;

  if(fShieldMaterial == "aluminum")
  {
    shieldMaterial = nistManager->FindOrBuildMaterial("G4_Al");
  }
  else if(fShieldMaterial == "steel")
  {
    shieldMaterial = new G4Material("steel", 7.850*g/cm3, 2);
    shieldMaterial->AddMaterial( nistManager->FindOrBuildMaterial("G4_Fe"), 99*perCent);
    shieldMaterial->AddMaterial( nistManager->FindOrBuildMaterial("G4_C"),   1*perCent);
  }
  else if(fShieldMaterial == "polypropylene")
  {
    shieldMaterial = nistManager->FindOrBuildMaterial("G4_POLYPROPYLENE");    
  }
  else if(fShieldMaterial == "wax")
  {
    shieldMaterial = new G4Material("wax", 0.91*g/cm3, 2);
    shieldMaterial->AddElement( nistManager->FindOrBuildElement(6), 34);
    shieldMaterial->AddElement( nistManager->FindOrBuildElement(1), 70);
  }
  else
  {
    G4String errMest = "Invalud shield material " + fShieldMaterial + ".\n";
    errMest += "The valid materials are aluminum, steel, polypropylene, wax";

    throw std::invalid_argument(errMest);
  }

  //////////////////////
  // Crystal material //
  //////////////////////  

  G4Element* H  = nistManager->FindOrBuildElement( 1);
  G4Element* C  = nistManager->FindOrBuildElement( 6);
  G4Element* N  = nistManager->FindOrBuildElement( 7);
  G4Element* Pb = nistManager->FindOrBuildElement(82);
  G4Element* Br = nistManager->FindOrBuildElement(35);
  

  G4double density_MAPbBr3 = 3.83 * g / cm3;
  G4Material* MAPbBr3 = new G4Material("MAPbBr3", density_MAPbBr3, 5);
  MAPbBr3->AddElement(C,  1);  // 1 Carbon atom
  MAPbBr3->AddElement(H,  6);  // 3 Hydrogen atoms
  MAPbBr3->AddElement(N,  1);  // 1 Nitrogen atom
  MAPbBr3->AddElement(Pb, 1);  // 1 Lead atom
  MAPbBr3->AddElement(Br, 3);  // 3 Bromine atoms

  //////////////////
  // World volume //
  //////////////////

  // De registed the logival volume if it is already registered
  // this is applied because the geometry is rebuild with corresponding UI comands  
	G4LogicalVolume *worldLV = 
		G4LogicalVolumeStore::GetInstance()->GetVolume("WorldLV");
	if (worldLV){
		G4LogicalVolumeStore::GetInstance()->DeRegister(worldLV);
	}


  G4double r_world  = 1.0*m;
  G4double hz_world = 0.2*m;

  G4Tubs* worldS = new G4Tubs("WorldS", 0, r_world, hz_world, 0, 360.*deg);
      
  worldLV = new G4LogicalVolume(worldS, air, "WorldLV");
                       
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,                   //no rotation
                        G4ThreeVector(),     //at (0,0,0)
                        worldLV,             //its logical volume
                        "World",             //its name
                        0,                   //its mother  volume
                        false,               //no boolean operation
                        0,                   //copy number
                        true);               //overlaps checking

  ////////////////////
  // Crystal volume //
  ////////////////////

  // De registed the logival volume if it is already registered
  // this is applied because the geometry is rebuild with corresponding UI comands
	G4LogicalVolume *crystalLV = 
		G4LogicalVolumeStore::GetInstance()->GetVolume("CrystalLV");
	if (crystalLV){
		G4LogicalVolumeStore::GetInstance()->DeRegister(crystalLV);
	}

  G4double hx_crys = 0.5*cm;
  G4double hy_crys = 0.5*cm;
  G4double hz_crys = 1.5*mm;
  
  G4VSolid* crystalS = new G4Box("Crystal", hx_crys, hy_crys, hz_crys);

  crystalLV = new G4LogicalVolume(crystalS, MAPbBr3, "CrystalLV");
 
  new G4PVPlacement(0, 
                    G4ThreeVector(0, 0, hz_crys), //position
                    crystalLV,                    //its logical volume
                    "Crystal",                    //its name
                    worldLV,                      //its mother  volume
                    false,                        //no boolean operation
                    0,                            //copy number
                    true);                        //overlaps checking

  ///////////////////
  // Screen volume //
  ///////////////////


  // De registed the logival volume if it is already registered
  // this is applied because the geometry is rebuild with corresponding UI comands
	G4LogicalVolume *screenLV = 
		G4LogicalVolumeStore::GetInstance()->GetVolume("ScreenLV");
	if (screenLV){
		G4LogicalVolumeStore::GetInstance()->DeRegister(screenLV);
	} 

  G4double hz_screen = 0.05*mm;

  G4Tubs* screenS = new G4Tubs("ShieldS", 0, r_world, hz_screen, 0, 360.*deg);

  screenLV = new G4LogicalVolume(screenS, air, "ScreenLV");

  new G4PVPlacement(0,                              // no rotation
                    G4ThreeVector(0, 0, -hz_screen),//position
                    screenLV,                       //its logical volume
                    "Screen",                       //its name
                    worldLV,                        //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking  


  ///////////////////
  // Shield volume //
  ///////////////////

  // De registed the logival volume if it is already registered
  // this is applied because the geometry is rebuild with corresponding UI comands
	G4LogicalVolume *shieldLV = 
		G4LogicalVolumeStore::GetInstance()->GetVolume("ShieldLV");
	if (shieldLV){
		G4LogicalVolumeStore::GetInstance()->DeRegister(shieldLV);
	} 
  
  G4double hz_shield = 5.0*cm;

  G4Tubs* shieldS = new G4Tubs("ShieldS", 0, r_world, hz_shield, 0, 360.*deg);

  shieldLV = new G4LogicalVolume(shieldS, shieldMaterial, "ShieldLV");

  new G4PVPlacement(0,                              // no rotation
                    G4ThreeVector(0, 0, -hz_shield-2*hz_screen),//position
                    shieldLV,                       //its logical volume
                    "Shield",                       //its name
                    worldLV,                        //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking  

  return worldPV;
}

void DetectorConstruction::ConstructSDandField()
{
  CrystalSD* crystalSD =
	 	(CrystalSD*)G4SDManager::GetSDMpointer()->FindSensitiveDetector("CrystalSD");
	if (!crystalSD)
	{
		crystalSD = new CrystalSD("CrystalSD", "CrystalHitsCollection");
	}
  G4SDManager::GetSDMpointer()->AddNewDetector(crystalSD);
  SetSensitiveDetector("CrystalLV", crystalSD);



  ScreenSD* screenSD =
	 	(ScreenSD*)G4SDManager::GetSDMpointer()->FindSensitiveDetector("ScreenSD");
	if (!screenSD)
	{
		screenSD = new ScreenSD("ScreenSD", "ScreenHitsCollection");
	}
  G4SDManager::GetSDMpointer()->AddNewDetector(screenSD);
  SetSensitiveDetector("ScreenLV", screenSD);

}  
