/// CalibrationGSISimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef CalibrationGSISimEventAction_h
#define CalibrationGSISimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;


//This struct carries statistics for the whole Run
struct RunTally {
  std::vector<float> IncidentElectron;
  std::vector<float> IncidentGamma;
    //float  Deposit;
    //float  DepositEff;
  float DepositTot;
  float DepositEffTot;
  std::vector<float> Deposit;
  std::vector<float> DepositEff;
  std::vector<float> PositionX;
  std::vector<float> PositionY;
  std::vector<float> PositionZ;

  inline int operator ==(const RunTally& right) const
  {return (this==&right);}
};



class CalibrationGSISimEventAction : public G4UserEventAction
{
public:
  CalibrationGSISimEventAction(char*);
  ~CalibrationGSISimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void FillIncidentElectron(G4float e){Statistics.IncidentElectron.push_back(e);}
  void FillIncidentGamma(G4float e){Statistics.IncidentGamma.push_back(e);}
  //void AddEdep(G4double edep){Statistics.Deposit+=edep;}
  //G4double GetEdep(){return Statistics.Deposit;}
  //void AddEdepEff(G4double edep){Statistics.DepositEff+=edep;}
  //G4double GetEdepEff(){return Statistics.DepositEff;}
  void AddEdepTot(G4double edep){Statistics.DepositTot+=edep;}
  void AddEdepEffTot(G4double edep){Statistics.DepositEffTot+=edep;}
  G4double GetEdepTot(){return Statistics.DepositTot;}
  G4double GetEdepEffTot(){return Statistics.DepositEffTot;}
  void FillEdep(G4float e){Statistics.Deposit.push_back(e);}
  void FillEdepEff(G4float e){Statistics.DepositEff.push_back(e);}
  void FillPositionX(G4float e){Statistics.PositionX.push_back(e);}
  void FillPositionY(G4float e){Statistics.PositionY.push_back(e);}
  void FillPositionZ(G4float e){Statistics.PositionZ.push_back(e);}


private:

  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;

  G4String suffixe;





};


#endif
