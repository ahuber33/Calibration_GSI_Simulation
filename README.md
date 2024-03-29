# Calibration_GSI_Simulation for simulation of the calibration sources in GSI for the TR/MS IPs [huber@ecnbg.in2p3.fr, huberarnaud@gmail.com]

# INSTRUCTIONS TO USE THE SIMULATION
# - Download the VMWare Geant4.11.0.0 from https://heberge.lp2ib.in2p3.fr/G4VM/index.html
# - Copy all the files from Calibration_GSI_Simulation folder (https://github.com/ahuber33/Calibration_GSI_Simulation)
# - Create a build folder in the Calibration_GSI_Simulation folder and go inside.
# - Use this command : "cmake -DGeant4_DIR=$G4COMP ../" and compile it with make
# - The executable CalibrationGSISim will be add to your bin folder
# - If you want to have a visualization, launch this command : "./CalibrationGSISim [name of ROOT file ]". It will generate 1 particle according to the vis.mac with QT and you will have a ROOT file with the name you gave in response located in the Resultats folder.
# - If you want to have statistics without the visualization, use this command : "./CalibrationGSISim [name of ROOT file] [number of events generated] [name of macro]". Personnaly, I used the vrml.mac but you can create another one. Just to remember that you need to write the name of your macro when you launch the simulation.
# - An CalibrationGSISim.cfg file is located in bin directory. All the dimensions necessary are in this file to avoid recompilation when you want to change some parameters. If you add some other dimensions, don't forget to add the variables in Geometry.cc.
# - Based on G4EmStandardPhysics_option3 with additional Photonuclear process pour gammas. All neutron interactions are also taken into account with HP data for neutrons.
# - theRunTree contains all datas about gamma from bremsstrahlung (creation and a the exit of the steel plate), neutrons from (gamma, n) process (creation and a the exit of the steel plate)corresponds to general optical datas from 1 event (number of photons generated, ect). You have also the information about the initial energy of the electron and the energy deposition in to the steel plate.
# - DO NOT HESITATE TO REPORT BUGS OR ANY IDEAS THAT WILL IMPROVE THE SIMULATION !!!!

# Commit #1 [CalibrationGSISim.0.1.0]
# - Passage du code sur la version 11.2.0 de GEANT4
# - Passage de Atom vers Visual Code Studio avec notamment création d'une branche save permettant de push les changements d'une journée avant demerge sur la branche principale

# PAST COMMITS FROM THE ORIGINAL CODE !!!

# Commit #1 [ENLegnSim.0.0.0]
# - Structure from ENLOpticalSim with a lot of code cleaning (all the optical part).
# - Add of photon nuclear process for gammas (process g,n)
# - Add of NeutronHPphysics
# - Creation of vectors in the ROOT Tree to obtain all datas about gammas and neutrons for each events

# commit #2 [ENLegnSim.0.0.1]
# - Cleaning of vis.mac and vmrl.mac
# - Add a condition for the datas integration -> ROOT files too fat due to IncidentE and deposit if you want information on neutron with stat

# commit #3 [ENLegnSim.0.0.2] le 24/03/2022
# - Add of INL cross sections data from different materials in order ton plot and compare with simulation. OK even is accuracy can be better with utilisation of LEND DATA.
# - Add some materials (Pb, W)
# - Add new geometries for studies with more than 1 plate

# commit #4 [ENLegnSim.0.0.3] le 20/07/2022
# - All the data files for cross section (ENDF, JENDL, ...) commit.
# - Ajout du matériau Silicon
# - Ajout d'une branche interaction pour connaitre les interactions liés aux gammas (utilisé lors du stage de Samuel Lecanuet pour comparaison).

# Commit #5 [ENLegnSim.0.0.4] le 26/09/2022
# - A la demande du groupe pour Emmanuel, simulation rapide du Co57 afin d'avoir un spectre simulé + génération d'un spectre exp gamma. Le tout sur un CdTe de 2mm de profondeur avec 1mm d'alu juste devant. Les modifications dans le SteppingAction sont délimités.
# - Afin de gagner du temps, la PhysicsList neutron a été commentée.
# - Ajout élements Or, Cd et Te
# - Ajout matériaux Or, CdTe
# - Ajout de nouvelles fonctions et variables dans EventAction.hh et initialisation et Fill dans .cc
# - Ajout Plot_Manu.cc pour plotter les résultats que demandait Emmanuel
