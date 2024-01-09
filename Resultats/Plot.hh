float GetEdepEffRadius(const char* filename, float radius)
{

  TFile* file = new TFile(filename);
  std::vector<float>* x=0;
  std::vector<float>* y=0;
  std::vector<float>* z=0;
  std::vector<float>* EdepEff=0;
  TTree *Tree = (TTree*)file->Get("IP");
  Tree->SetBranchAddress("PositionX", &x);
  Tree->SetBranchAddress("PositionY", &y);
  Tree->SetBranchAddress("PositionZ", &z);
  Tree->SetBranchAddress("DepositEff", &EdepEff);
  const int Entries = Tree->GetEntries();

  float xvalue, yvalue =0;
  float EdepEffRadius=0;

  
  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);

    for (int j=0; j<x->size(); j++)
      {
	xvalue = x->at(j);
	yvalue = y->at(j);

	if (xvalue*xvalue + yvalue*yvalue < radius*radius)
	{
	  EdepEffRadius += EdepEff->at(j);
	}
      }
  }

  return EdepEffRadius;
  
}



float GetEdepEffTot(const char* filename)
{

  TFile* file = new TFile(filename);
  std::vector<float>* x=0;
  std::vector<float>* y=0;
  std::vector<float>* z=0;
  std::vector<float>* EdepEff=0;
  TTree *Tree = (TTree*)file->Get("IP");
  Tree->SetBranchAddress("PositionX", &x);
  Tree->SetBranchAddress("PositionY", &y);
  Tree->SetBranchAddress("PositionZ", &z);
  Tree->SetBranchAddress("DepositEff", &EdepEff);
  const int Entries = Tree->GetEntries();

  float xvalue, yvalue =0;
  float EdepEffTot=0;

  
  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);

    for (int j=0; j<x->size(); j++)
      {
	EdepEffTot += EdepEff->at(j);
      }
  }

  return EdepEffTot;
  
}
