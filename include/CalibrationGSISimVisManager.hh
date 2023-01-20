/// CalibrationGSISimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2023 (C) LP2IB-ENL

#ifndef CalibrationGSISimVisManager_h
#define CalibrationGSISimVisManager_h 1

#include "G4VisManager.hh"


class CalibrationGSISimVisManager: public G4VisManager {

public:

  CalibrationGSISimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
