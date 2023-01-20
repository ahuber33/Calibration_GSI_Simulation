/// Geometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

// This class is used to create a plastic scintillator.

#ifndef Geometry_h
#define Geometry_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class ENLOpticalSimMaterials;
class Geometry

{
public:

  //constructor, builds from keys specified in buildfile
  Geometry(G4String buildfile);
  ~Geometry();
  //  void Construct();

public:

  G4LogicalVolume *GetMSStack1();
  G4LogicalVolume *GetMSStack2();
  G4LogicalVolume *GetMSStack3();
  G4LogicalVolume *GetMSStack4();
  G4LogicalVolume *GetTable();
  G4LogicalVolume *GetSourceHolder();


  G4double GetSourceHolderRadius(){return SourceHolderRadius;}
  G4double GetSourceHolderThickness(){return SourceHolderThickness;}
  G4double GetStackIPPosIni(){return Stack_IP_pos_ini;}
  G4double GetIPLength(){return IPLength;}
  G4double GetIPWidth(){return IPWidth;}
  G4double GetIPa1z(){return IPa1_z;}
  G4double GetIPa2z(){return IPa2_z;}
  G4double GetIPa3z(){return IPa3_z;}
  G4double GetIPa4z(){return IPa4_z;}
  G4double GetLabs(){return Labs;}


private:


  Geometry *Geom;
  CalibrationGSISimMaterials* scintProp;

  static const G4String path_bin;


  // Materials
  G4Material *Material;

  // Logical Volumes
  G4LogicalVolume *LogicalVolume;

  G4double SourceHolderThickness;
  G4double SourceHolderRadius;
  G4double Stack_IP_pos_ini;
  G4double IPLength;
  G4double IPWidth;
  G4double IPa1_z;
  G4double IPa2_z;
  G4double IPa3_z;
  G4double IPa4_z;
  G4double Labs;

  // Other
  G4VisAttributes *clear;

};
#endif
