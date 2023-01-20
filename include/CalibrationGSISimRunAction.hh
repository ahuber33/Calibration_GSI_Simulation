/// CalibrationGSISimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef CalibrationGSISimRunAction_h
#define CalibrationGSISimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "CalibrationGSISimEventAction.hh"
#include <TFile.h>
#include <vector>

class G4Run;

class CalibrationGSISimRunAction : public G4UserRunAction
{

public:
  CalibrationGSISimRunAction(char*);
  ~CalibrationGSISimRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);




private:
  G4String suffixe;
  RunTally Stats;
  TFile *f;
  TTree *theRunTree;
  TBranch *RunBranch;
  time_t start;

};

#endif
