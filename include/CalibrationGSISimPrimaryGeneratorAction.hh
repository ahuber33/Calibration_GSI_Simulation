/// CalibrationGSISimPrimaryGeneratorAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL
#ifndef CalibrationGSISimPrimaryGeneratorAction_h
#define CalibrationGSISimPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4Event;

class CalibrationGSISimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  CalibrationGSISimPrimaryGeneratorAction();
  ~CalibrationGSISimPrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event* anEvent);
  void SetEnergy(G4double en){particleGun->SetParticleEnergy(en);};

  G4double GetEnergy(){return particleGun->GetParticleEnergy();};

private:
  G4ParticleGun* particleGun;
  G4GeneralParticleSource *particleSource;
  G4double IncidentE;
};

#endif
