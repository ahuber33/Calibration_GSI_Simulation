// CalibrationGSISimGeometry_test.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#include "CalibrationGSISimGeometry.hh"
#include "CalibrationGSISimRunAction.hh"
#include "CalibrationGSISimMaterials.hh"
#include "CalibrationGSISimSteppingAction.hh"
#include "Geometry.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4MaterialTable.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4Transform3D.hh"
#include "G4SurfaceProperty.hh"
#include "globals.hh"
#include <fstream>
#include <iostream>

using namespace CLHEP;

const G4String CalibrationGSISimGeometry::path_bin = "../bin/";
const G4String CalibrationGSISimGeometry::path = "../simulation_input_files/";

// Constructor
CalibrationGSISimGeometry::CalibrationGSISimGeometry(){}

// Destructor
CalibrationGSISimGeometry::~CalibrationGSISimGeometry()
{
}

// Main Function: Builds Full block, coupling, and PMT geometries
G4VPhysicalVolume* CalibrationGSISimGeometry::Construct( ){
  // Initialize scint classes
  scintProp = new CalibrationGSISimMaterials(path_bin+"Materials.cfg");
  Vacuum = scintProp->GetMaterial("Vacuum");
  VacuumWorld = scintProp->GetMaterial("VacuumWorld");
  Air = scintProp->GetMaterial("Air");
  Alu = scintProp->GetMaterial("Alu");
  Geom = new Geometry(path_bin+"CalibrationGSISim.cfg");


  // ***********************
  // Visualization Colors
  // ***********************
  // Create some colors for visualizations
  invis = new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));
  invis->SetVisibility(false);

  white = new G4VisAttributes(G4Colour(1,1,1,0.1)); // Sets the color (can be looked up online)
  //white->SetForceWireframe(true); // Sets to wire frame mode for coloring the volume
  white->SetForceSolid(true); // Sets to solid mode for coloring the volume
  white->SetVisibility(true); // Makes color visible in visualization

  gray = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
  //  gray->SetForceWireframe(true);
  gray->SetForceSolid(true);
  gray->SetVisibility(true);

  gray_bis = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.25));
  //  gray->SetForceWireframe(true);
  gray_bis->SetForceSolid(true);
  gray_bis->SetVisibility(true);

  black = new G4VisAttributes(G4Colour(0,0,0,0.7));
  //  black->SetForceWireframe(true);
  black->SetForceSolid(true);
  black->SetVisibility(true);


  black_bis = new G4VisAttributes(G4Colour(0,0,0,0.4));
  //  black->SetForceWireframe(true);
  black_bis->SetForceSolid(true);
  black_bis->SetVisibility(true);

  red = new G4VisAttributes(G4Colour(1,0,0,0.5));
  //  red->SetForceWireframe(true);
  red->SetForceSolid(true);
  red->SetVisibility(true);


  red_hot = new G4VisAttributes(G4Colour(1,0,0,1));
  //  red->SetForceWireframe(true);
  red_hot->SetForceSolid(true);
  red_hot->SetVisibility(true);

  orange = new G4VisAttributes(G4Colour(1,0.5,0,0.2));
  //  orange->SetForceWireframe(true);
  orange->SetForceSolid(true);
  orange->SetVisibility(true);

  yellow = new G4VisAttributes(G4Colour(1,1,0,0.39));
  //  yellow->SetForceWireframe(true);
  yellow->SetForceSolid(true);
  yellow->SetVisibility(true);

  green = new G4VisAttributes(G4Colour(0,1,0,0.35));
  //  green->SetForceWireframe(true);
  green->SetForceSolid(true);
  green->SetVisibility(true);

  green_hot = new G4VisAttributes(G4Colour(0,1,0,1));
  //  green_hot->SetForceWireframe(true);
  green_hot->SetForceSolid(true);
  green_hot->SetVisibility(true);

  cyan = new G4VisAttributes(G4Colour(0,1,1,0.55));
  //  cyan->SetForceWireframe(true);
  cyan->SetForceSolid(true);
  cyan->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0,0,1,0.3));
  //  blue->SetForceWireframe(true);
  blue->SetForceSolid(true);
  blue->SetVisibility(true);

  magenta = new G4VisAttributes(G4Colour(1,0,1,0.85));
  //  magenta->SetForceWireframe(true);
  //magenta->SetForceSolid(true);
  magenta->SetVisibility(true);

  // Define common rotations
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);
  G4RotationMatrix Flip;
  Flip.rotateZ(0*deg);
  Flip.rotateX(180*deg);
  Flip.rotateY(0*deg);


  // ***********************
  // Various dimensions
  // ***********************

  Stack_IP_pos_ini = Geom->GetStackIPPosIni();
  SourceHolderRadius = Geom->GetSourceHolderRadius();
  SourceHolderThickness = Geom->GetSourceHolderThickness();
  IPLength = Geom->GetIPLength();
  IPWidth = Geom->GetIPWidth();
  IPa1_z = Geom->GetIPa1z();
  IPa2_z = Geom->GetIPa2z();
  IPa3_z = Geom->GetIPa3z();
  IPa4_z = Geom->GetIPa4z();

  G4double epaisseur_IP = IPa1_z + IPa2_z + IPa3_z + IPa4_z;



  //#########################
  // DEFINE GEOMETRY VOLUMES#
  //#########################

  // Create World Volume
  // This is just a big box to place all other logical volumes inside
  G4Box *SolidWorld = new G4Box("SolidWorld", 110*cm, 110*cm, 110*cm );
  LogicalWorld = new G4LogicalVolume(SolidWorld, VacuumWorld,"LogicalWorld",0,0,0);
  LogicalWorld->SetVisAttributes(invis);

  // Place the world volume: center of world at origin (0,0,0)
  PhysicalWorld = new G4PVPlacement(G4Transform3D(DontRotate,G4ThreeVector(0,0,0)),"PhysicalWorld",LogicalWorld,NULL,false,0);


  //*********************************
  // Build scint et wrapping volumes*
  //*********************** *********
  //Simply calls functions from Scintillator() class
  LogicalIP1 = Geom->GetMSStack1();
  LogicalIP2 = Geom->GetMSStack2();
  LogicalIP3 = Geom->GetMSStack3();
  LogicalIP4 = Geom->GetMSStack4();
  LogicalTable = Geom->GetTable();
  LogicalSourceHolder = Geom->GetSourceHolder();


  // Set colors of various block materials
  LogicalIP1->SetVisAttributes(gray_bis);
  LogicalIP2->SetVisAttributes(red_hot);
  LogicalIP3->SetVisAttributes(green);
  LogicalIP4->SetVisAttributes(black);
  LogicalTable->SetVisAttributes(gray);
  LogicalSourceHolder->SetVisAttributes(cyan);




  //############################
  // DEFINE GEOMETRY PLACEMENTS#
  //############################

  #ifndef disable_gdml


  //***********************
  // Various Positioning values
  //***********************

  float distance=Stack_IP_pos_ini;

  PhysicalTable = new G4PVPlacement(G4Transform3D
    (DontRotate,G4ThreeVector(0*mm,0.*mm, -30*mm)),
    LogicalTable,"Table",
    LogicalWorld,false,0);

  PhysicalIP1 = new G4PVPlacement(G4Transform3D
    (DontRotate,G4ThreeVector(0*mm,0.*mm, distance)),
    LogicalIP1,"IP1",
    LogicalWorld,false,0);

    distance += IPa1_z/2 + IPa2_z/2;


    PhysicalIP2 = new G4PVPlacement(G4Transform3D
      (DontRotate,G4ThreeVector(0*mm,0.*mm, distance)),
      LogicalIP2,"IP2_Sensitive",
      LogicalWorld,false,0);

      distance += IPa2_z/2 + IPa3_z/2;


      PhysicalIP3 = new G4PVPlacement(G4Transform3D
        (DontRotate,G4ThreeVector(0*mm,0.*mm, distance)),
        LogicalIP3,"IP3",
        LogicalWorld,false,0);


        distance += IPa3_z/2 + IPa4_z/2;


        PhysicalIP4 = new G4PVPlacement(G4Transform3D
          (DontRotate,G4ThreeVector(0*mm,0.*mm, distance)),
          LogicalIP4,"IP4",
          LogicalWorld,false,0);


          distance += IPa4_z/2 + SourceHolderThickness/2;


          PhysicalSourceHolder = new G4PVPlacement(G4Transform3D
            (DontRotate,G4ThreeVector(0*mm,0.*mm, distance)),
            LogicalSourceHolder,"SourceHolder",
            LogicalWorld,false,0);


    #else

    #endif





    // Returns world with everything in it and all properties set
    return PhysicalWorld;
  }
