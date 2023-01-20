/// CalibrationGSISimGeometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef CalibrationGSISimGeometry_h
#define CalibrationGSISimGeometry_h  1

#include "G4MaterialPropertiesTable.hh"

class Geometry;
class CalibrationGSISimMaterials;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class  CalibrationGSISimGeometry:  public G4VUserDetectorConstruction
{
public:
  CalibrationGSISimGeometry();
  ~CalibrationGSISimGeometry();

public:
  G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetLWorld() {return LogicalWorld;}

private:
  static const G4String path_bin;
  static const G4String path;
  // Classes for building various components
  //     LogicalHolder *holder;
  CalibrationGSISimMaterials *scintProp;
  Geometry *Geom;
  G4Material *Vacuum;
  G4Material *VacuumWorld;
  G4Material *Air;
  G4Material *Alu;

  // Colors for visualizations
  G4VisAttributes *invis;
  G4VisAttributes *white;
  G4VisAttributes *gray;
  G4VisAttributes *gray_bis;
  G4VisAttributes *black;
  G4VisAttributes *black_bis;
  G4VisAttributes *red;
  G4VisAttributes *red_hot;
  G4VisAttributes *orange;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *green_hot;
  G4VisAttributes *cyan;
  G4VisAttributes *blue;
  G4VisAttributes *magenta;

  // Logical Volumes
  G4LogicalVolume *LogicalWorld;
  G4LogicalVolume *LogicalIP1;
  G4LogicalVolume *LogicalIP2;
  G4LogicalVolume *LogicalIP3;
  G4LogicalVolume *LogicalIP4;
  G4LogicalVolume *LogicalTable;
  G4LogicalVolume *LogicalSourceHolder;


  // Physical volumes
  G4VPhysicalVolume *PhysicalWorld;
  G4VPhysicalVolume *PhysicalIP1;
  G4VPhysicalVolume *PhysicalIP2;
  G4VPhysicalVolume *PhysicalIP3;
  G4VPhysicalVolume *PhysicalIP4;
  G4VPhysicalVolume *PhysicalTable;
  G4VPhysicalVolume *PhysicalSourceHolder;


  G4double SourceHolderThickness;
  G4double SourceHolderRadius;
  G4double RayonSource;
  G4double Stack_IP_pos_ini;
  G4double IPLength;
  G4double IPWidth;
  G4double IPa1_z;
  G4double IPa2_z;
  G4double IPa3_z;
  G4double IPa4_z;




};
#endif
