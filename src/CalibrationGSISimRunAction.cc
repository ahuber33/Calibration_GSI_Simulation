/// CalibrationGSISimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#include "CalibrationGSISimRunAction.hh"
#include "Randomize.hh"
#include <time.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH2I.h"
#include "TH1D.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>

CalibrationGSISimRunAction::CalibrationGSISimRunAction(char* suff):suffixe(suff){}
CalibrationGSISimRunAction::~CalibrationGSISimRunAction(){}


//-----------------------------------------------------
//  BeginOfRunAction:  used to calculate the start time and
//  to set up information in the run tree.
//-----------------------------------------------------
void CalibrationGSISimRunAction::BeginOfRunAction(const G4Run* aRun){

  //gROOT->ProcessLine("#include <vector>");

  G4String fileName = suffixe+".root";
  //f = new TFile("test.root","UPDATE");

    start = time(NULL);     //start the timer clock to calculate run times

    theRunTree = new TTree("IP","Tree_Information");

    // create the branch for each event.
    // Be careful of the data structure here!  /F is a float  /I is an integer
    RunBranch = theRunTree->Branch("IncidentElectron", "vector<float>", &Stats.IncidentElectron);
    RunBranch = theRunTree->Branch("IncidentGamma", "vector<float>", &Stats.IncidentGamma);
    //RunBranch = theRunTree->Branch("Deposit", &Stats.Deposit, "Deposit/F");
    //RunBranch = theRunTree->Branch("DepositEff", &Stats.DepositEff, "DepositEff/F");
    RunBranch = theRunTree->Branch("DepositTot", &Stats.DepositTot, "DepositTot/F");
    RunBranch = theRunTree->Branch("DepositEffTot", &Stats.DepositEffTot, "DepositEffTot/F");
    RunBranch = theRunTree->Branch("Deposit", "vector<float>", &Stats.Deposit);
    RunBranch = theRunTree->Branch("DepositEff", "vector<float>", &Stats.DepositEff);
    RunBranch = theRunTree->Branch("PositionX", "vector<float>", &Stats.PositionX);
    RunBranch = theRunTree->Branch("PositionY", "vector<float>", &Stats.PositionY);
    RunBranch = theRunTree->Branch("PositionZ", "vector<float>", &Stats.PositionZ);

    //set the random seed to the CPU clock
  //G4Random::setTheEngine(new CLHEP::HepJamesRandom);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);
    G4cout << "seed = " << seed << G4endl;

    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    if (G4VVisManager::GetConcreteInstance()){
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    }


}  //end BeginOfRunAction


//-----------------------------------------------------
//  EndOfRunAction:  used to calculate the end time and
//  to write information to the run tree.
//-----------------------------------------------------
void CalibrationGSISimRunAction::EndOfRunAction(const G4Run*aRun){

    //update the temp root file
    G4String fileName = suffixe+".root";
    f = new TFile(fileName,"update");
    theRunTree->Write();
    f->Close();

    if (G4VVisManager::GetConcreteInstance()){
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
    }

    //display run time and write to file Rntime.out
    time_t end = time(NULL);
    G4int elapsed = end-start;
    G4cout << "Run Completed in " << elapsed/3600
	   << ":" << (elapsed%3600)/60 << ":"
	   << ((elapsed%3600)%60) << G4endl;

    // Output the time in the file Runtime.out
    std::ofstream timeout;
    timeout.open("Runtime.out",std::ios::app);
    timeout << "Run " << aRun->GetRunID()
	    << ": " <<elapsed/3600
	    << ":" <<(elapsed%3600)/60
	    << ":" <<((elapsed%3600)%60) << G4endl;
    timeout.close();

      G4cout<<"Leaving Run Action"<<G4endl;
}

//---------------------------------------------------------
//  For each event update the statistics in the Run tree
//---------------------------------------------------------

void CalibrationGSISimRunAction::UpdateStatistics(RunTally aRunTally){
    Stats = aRunTally;
    theRunTree->Fill();
}
