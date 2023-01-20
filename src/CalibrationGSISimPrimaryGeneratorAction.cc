/// CalibrationGSISimPrimaryGeneratorAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#include "CalibrationGSISimPrimaryGeneratorAction.hh"
#include "CalibrationGSISimEventAction.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4UImanager.hh"
#include "globals.hh"
#include "G4EventManager.hh"
#include "CalibrationGSISimEventAction.hh"


// The commented out commands are to use this module with a G4ParticleGun
// Note that setgun.mac is used with G4ParticleGun
// Note that setsource.mac is used with G4GeneralParticleSource
// More information about how to use G4GeneralParticleSouce at:
// http://reat.space.qinetiq.com/gps/


G4UImanager* UI = G4UImanager::GetUIpointer();
CalibrationGSISimPrimaryGeneratorAction::CalibrationGSISimPrimaryGeneratorAction(){
  //G4int n_particle = 1;

  //particleGun = new G4ParticleGun(n_particle);
  //UI->ApplyCommand("/control/execute setgun.mac");
  //UI->ApplyCommand("/control/execute setgun_script_use.mac");

  particleSource = new G4GeneralParticleSource();
  //UI->ApplyCommand("/control/execute setsource.mac");
}

CalibrationGSISimPrimaryGeneratorAction::~CalibrationGSISimPrimaryGeneratorAction(){
  //delete particleGun;
  delete particleSource;
}

void CalibrationGSISimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

  //particleGun->GeneratePrimaryVertex(anEvent);
  particleSource->GeneratePrimaryVertex(anEvent);

  //  always require these two lines
  G4EventManager *evtman = G4EventManager::GetEventManager();
  CalibrationGSISimEventAction *evtac = (CalibrationGSISimEventAction*)evtman->GetUserEventAction();

  //evtac->SetIncidentE(particleGun->GetParticleEnergy());
  //evtac->SetIncidentE(particleSource->GetParticleEnergy());
}
