/// CalibrationGSISimPhysics.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef  CalibrationGSISimPhysics_h
#define   CalibrationGSISimPhysics_h  1

//#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
class  CalibrationGSISimPhysics:  public G4VModularPhysicsList
{      public:
  CalibrationGSISimPhysics();
  virtual ~CalibrationGSISimPhysics();

protected:
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  virtual void ConstructNeutron();
  virtual void SetCuts();
protected:
  //virtual void ConstructBosons();
  //virtual void ConstructLeptons();
  //virtual void ConstructMesons();
  //virtual void ConstructBaryons();
protected:
  //virtual void ConstructGeneral();
  //virtual void ConstructEM();
  //virtual void ConstructAllShortLiveds();

private:
  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  particleList;
  G4VPhysicsConstructor*  raddecayList;
  G4bool              fThermal;
};
#endif
