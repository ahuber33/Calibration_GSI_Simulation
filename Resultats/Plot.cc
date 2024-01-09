#include "Plot.hh"

void Plot()
{
  string filename = "Co60_MS.root";
  
  // TFile* file = new TFile(filename.c_str());
  // std::vector<float>* x=0;
  // std::vector<float>* y=0;
  // std::vector<float>* z=0;
  // std::vector<float>* EdepEff=0;
  // TTree *Tree = (TTree*)file->Get("IP");
  // Tree->SetBranchAddress("PositionX", &x);
  // Tree->SetBranchAddress("PositionY", &y);
  // Tree->SetBranchAddress("PositionZ", &z);
  // Tree->SetBranchAddress("DepositEff", &EdepEff);
  // const int Entries = Tree->GetEntries();

  // TH2F* f = new TH2F("test", "test", 1200, -60, 60, 1200, -60, 60);

  // float xvalue, yvalue =0;
  // float radius = 1;


  
  // for(int i=0; i<Entries; i++)
  // {
  //   Tree->GetEntry(i);

  //   for (int j=0; j<x->size(); j++)
  //     {
  // 	xvalue = x->at(j);
  // 	yvalue = y->at(j);

  // 	if (xvalue*xvalue + yvalue*yvalue < radius*radius)
  // 	{
  // 	  f->Fill(xvalue, yvalue);
  // 	}
  //     }
  // }


  // f->Draw("colz");

  float totCs, totCo, totNa =0;
  float ECo, ECs, ENa, ES =0;


  //totCo = GetEdepEffTot("Co60_MS.root");
  //totCs = GetEdepEffTot("Cs137_MS.root");
  //totNa = GetEdepEffTot("Na22_MS.root");
  float CoR[200], CoP[200], CoeR[200], CoeP[200];
  float CsR[200], CsP[200], CseR[200], CseP[200];
  float NaR[200], NaP[200], NaeR[200], NaeP[200];
  float SR[200], SP[200], SeR[200], SeP[200];
  int n=0;
  float nEventsim =1000000./1000.; ///1000 car exprimé /kBq !!!!

  for (float j=0; j<30; j+=0.5)
    {
      
      //ECo = GetEdepEffRadius("Co60_TR_EGSA.root", j);
      ECs = GetEdepEffRadius("Cs137_MS_EGSA_LULI.root", j);
      //ENa = GetEdepEffRadius("Na22_MS_EGSA.root", j);
      //ES = GetEdepEffRadius("Co57_MS_EGSA.root", j);
      
      CoR[n] = j;
      CsR[n] = j;
      NaR[n] = j;
      //SR[n] = j;
      
      CoeR[n] = 0.5;
      CseR[n] = 0.5;
      NaeR[n] = 0.5;
      //SeR[n] = 0.5;
      
      CoP[n] = ECo/nEventsim;
      CsP[n] = ECs/nEventsim;
      NaP[n] = ENa/nEventsim;
      //SP[n] = ES/nEventsim;
      
      CoeP[n] = CoP[n]*(sqrt(ECo)/ECo + sqrt(nEventsim)/nEventsim);
      CseP[n] = CsP[n]*(sqrt(ECs)/ECs + sqrt(nEventsim)/nEventsim);
      NaeP[n] = NaP[n]*(sqrt(ENa)/ENa + sqrt(nEventsim)/nEventsim);
      //SeP[n] = SP[n]*(sqrt(ES)/ES + sqrt(nEventsim)/nEventsim);
      
      n++;
      cout << "\r" << n << flush;
    }
      

  //TGraphErrors* Co = new TGraphErrors(n, CoR, CoP, CoeR, CoeP);
  TGraphErrors* Cs = new TGraphErrors(n, CsR, CsP, CseR, CseP);
  //TGraphErrors* Na = new TGraphErrors(n, NaR, NaP, NaeR, NaeP);
  //TGraphErrors* S = new TGraphErrors(n, SR, SP, SeR, SeP);

  //Co->Draw();
  //Co->SetLineColor(kBlack);
  //S->Draw();
  //S->SetLineColor(kBlack);
  Cs->Draw("");
  Cs->SetLineColor(kCyan);
  //Na->Draw("same");
  //Na->SetLineColor(kRed);



  //TFile* fileCo = new TFile("TR_EdepeffA_Co60_EGSA.root", "recreate");
  //Co->Write();
  //fileCo->Close();
  
  TFile* fileCs = new TFile("MS_EdepeffA_Cs137_EGSA_LULI.root", "recreate");
  Cs->Write();
  fileCs->Close();
  
  //TFile* fileNa = new TFile("MS_EdepeffA_Na22_EGSA.root", "recreate");
  //Na->Write();
  //fileNa->Close();

  //TFile* fileS = new TFile("MS_EdepeffA_Co57_EGSA.root", "recreate");
  //S->Write();
  //fileS->Close();

  

  
}
