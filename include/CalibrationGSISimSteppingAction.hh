/// CalibrationGSISimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef CalibrationGSISimSteppingAction_h
#define CalibrationGSISimSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "TH2F.h"
#include "TFile.h"

class G4Step;
class G4SteppingManager;

class CalibrationGSISimSteppingAction : public G4UserSteppingAction
{
public:
  CalibrationGSISimSteppingAction();
  ~CalibrationGSISimSteppingAction();
public:
  void UserSteppingAction(const G4Step*);



private:
  static const G4String path;
  int PreviousTrack;
  double NRJ1;
  double Length_Track;
  double Total_Length_Track;


};
#endif
