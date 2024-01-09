/// CalibrationGSISimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#include "G4SteppingManager.hh"
#include "CalibrationGSISimSteppingAction.hh"
#include "G4Run.hh"
#include "CalibrationGSISimEventAction.hh"
#include "G4RunManager.hh"
#include "CalibrationGSISimRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "G4PrimaryVertex.hh"
#include <math.h>
#include "TRandom3.h"
#include "TGraph.h"

using namespace CLHEP;

CalibrationGSISimEventAction::CalibrationGSISimEventAction(char* suff):suffixe(suff){}

CalibrationGSISimEventAction::~CalibrationGSISimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void CalibrationGSISimEventAction::BeginOfEventAction(const G4Event* evt){

  G4int event_id = evt->GetEventID();

  //G4cout << "EVENT : " << event_id << G4endl;

  Statistics.IncidentElectron.clear();
  Statistics.IncidentGamma.clear();
  if(event_id==0)
  {
    Statistics.DepositTot = 0;
    Statistics.DepositEffTot = 0;
  }
  //Statistics.Deposit = 0;
  //Statistics.DepositEff = 0;
  Statistics.Deposit.clear();
  Statistics.DepositEff.clear();
  Statistics.PositionX.clear();
  Statistics.PositionY.clear();
  Statistics.PositionZ.clear();

}


// Get the number of stored trajectories and calculate the statistics
void CalibrationGSISimEventAction::EndOfEventAction(const G4Event* evt){
  G4int event_id = evt->GetEventID();

  CalibrationGSISimRunAction *runac = (CalibrationGSISimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  //G4double Resolution = 9 / sqrt(Statistics.Deposit/122) ;
  //G4long seed = time(NULL)+10;
  //TRandom3* gen = new TRandom3(seed);
  //Statistics.Deposit_with_resolution = gen->Gaus(Statistics.Deposit, (Statistics.Deposit * 0.01*Resolution) / 2.355);
  //G4cout << "Edep = " << Statistics.Deposit << " keV" << G4endl;
  //G4cout << "Resolution = " << Resolution << " % " << G4endl;
  //G4cout << "Edep with resolution = " << Statistics.Deposit_with_resolution << " keV" << G4endl;


  //if(Statistics.PositionDeposit.size() >0) runac->UpdateStatistics(Statistics);


  //if(Statistics.EBremCreation.size()>0)
  // if(Statistics.Interaction !=0)
  //{
  runac->UpdateStatistics(Statistics);
  //}
}
