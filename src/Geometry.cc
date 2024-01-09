// Geometry.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#include "CalibrationGSISimMaterials.hh"
#include "Geometry.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include <fstream>
#include <iostream>
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include <G4Polycone.hh>
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include <math.h>

//#ifndef disable_gdml
#include "G4GDMLParser.hh"
//#endif


using namespace CLHEP;

// ***********************
// Constructor
// ***********************
const G4String Geometry::path_bin = "../bin/";


Geometry::Geometry(G4String buildfile){

  // Read keys and values from file buildfile defined in x_blockGeometry.cc
  // Some of these variables may not be needed.
  std::ifstream config;
  config.open(buildfile);
  if ( !config.is_open() )
    G4cout << "Error opening file " << buildfile << G4endl;
  else{
    while( config.is_open() ){
      G4String variable;
      G4String unit;
      G4double value;

      config >> variable;
      if(!config.good()) break;
      //####################### COMMON variables ###########################
      if(variable == "SourceHolderThickness"){
  	config >> value >> unit;
  	SourceHolderThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SourceHolderRadius"){
  	config >> value >> unit;
  	SourceHolderRadius = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Stack_IP_pos_ini"){
  	config >> value >> unit;
  	Stack_IP_pos_ini = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPLength"){
  	config >> value >> unit;
  	IPLength = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPWidth"){
  	config >> value >> unit;
  	IPWidth = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa1_z"){
  	config >> value >> unit;
  	IPa1_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa2_z"){
    config >> value >> unit;
    IPa2_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa3_z"){
    config >> value >> unit;
    IPa3_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa4_z"){
    config >> value >> unit;
    IPa4_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Labs"){
    config >> value >> unit;
    Labs = value*G4UnitDefinition::GetValueOf(unit);
      }
    }
  }
  config.close();



    G4cout << "\n The Variables that we read in are: "
    << "\n Source Holder Thickness = " << SourceHolderThickness
    << "\n Source Holder Radius = " << SourceHolderRadius
    << "\n IP Length = " << IPLength
    << "\n IP Width = " << IPWidth
    << "\n IPa1_z = " << IPa1_z
    << "\n IPa2_z = " << IPa2_z
    << "\n IPa3_z = " << IPa3_z
    << "\n IPa4_z = " << IPa4_z
    << "\n Labs = " << Labs

    << "\n " << G4endl;

}
// ***********************
// Destructor
// ***********************
Geometry::~Geometry(){
  if(scintProp) { delete scintProp; scintProp = 0; }
  if(clear) { delete clear; clear = 0; }
}


G4LogicalVolume *Geometry::GetMSStack1(){

  Material = scintProp->GetMaterial("Polyester");

  G4Box *Box = new G4Box   ("Box",             //its name
            IPLength/2, IPWidth/2, IPa1_z/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Stack_IP1");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetMSStack2(){

  Material = scintProp->GetMaterial("Sensitive");

  G4Box *Box = new G4Box   ("Box",             //its name
            IPLength/2, IPWidth/2, IPa2_z/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Stack_IP2");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetMSStack3(){

  Material = scintProp->GetMaterial("Polyester");

  G4Box *Box = new G4Box   ("Box",             //its name
            IPLength/2, IPWidth/2, IPa3_z/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Stack_IP3");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetMSStack4(){

  Material = scintProp->GetMaterial("Base");

  G4Box *Box = new G4Box   ("Box",             //its name
            IPLength/2, IPWidth/2, IPa4_z/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Stack_IP4");

  return LogicalVolume;
}

G4LogicalVolume *Geometry::GetTable(){

  Material = scintProp->GetMaterial("plastic");

  G4Box *Box = new G4Box   ("Box",             //its name
            200, 200, 60/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Table");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetSourceHolder(){

  //Material = scintProp->GetMaterial("plastic");
  Material = scintProp->GetMaterial("mylar");
  //Material = scintProp->GetMaterial("Polyester");

  G4VSolid* solid = new G4Tubs("SourceHolder",0., SourceHolderRadius,SourceHolderThickness/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"SourceHolder");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetSourcePlastic(){

  //Material = scintProp->GetMaterial("plastic");
  Material = scintProp->GetMaterial("mylar");
  //Material = scintProp->GetMaterial("Polyester");

  G4VSolid* solid = new G4Tubs("SourceHolder", SourceHolderRadius, 12.5*mm, 1.5*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"SourceHolder");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetMylar(){

  Material = scintProp->GetMaterial("mylar");

  G4Box *Box = new G4Box   ("Box",             //its name
            IPLength/2, IPWidth/2, 125./2.*um);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material,"Mylar");

  return LogicalVolume;
}
