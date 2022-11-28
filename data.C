/* For the assignment we have to make graphs of eta phi and transverse momentum with the number of particles on the y-axis to see the corresponding graphs remove the comments from the eta phi and transverse momentum depending on the graph we need and also changing the multiplicity that we required .*/

#include<math.h>

void data(){

TFile *file=new TFile("hist1.root");/*to import the root file from the server*/
  TTree *pytree = (TTree*)file->Get("pytree100");/*change the multiplicity in the bracket that is for different classes of pytree020,pytree2040,...........pytree100.*/
  Int_t events = pytree->GetEntries();/*to get number of events*/

 const Int_t max=90000;//to introduce a constant defining the limit of an array//
   
  Int_t ntrack = 0;//defining variable and arrays to store the values from the actual data//
  Double_t pT[max];
  Double_t eta[max];
  Double_t phi[max];

  pytree->SetBranchAddress("eta",&eta);  
  pytree->SetBranchAddress("phi",&phi);
  pytree->SetBranchAddress("pT",&pT);
  pytree->SetBranchAddress("ntrack",&ntrack);

  TCanvas *canvas=new TCanvas();

  
 
//We are  creating histograms in the following steps.//

  TH1D *phitoward = new TH1D("phi towards","Phi Towards",200,-5, 5);
  TH1D *pttoward = new TH1D("pT towards","pT Towards",1000,0,100);
  TH1D *etatoward = new TH1D("eta towards","Eta Towards",200,-5, 5);
  TH1D *phiaway = new TH1D("phi away","Phi Away",200,-5, 5);
  TH1D *ptaway = new TH1D("pT away","pT Away",1000,0,100);
  TH1D *etaaway = new TH1D("eta away","Eta Away",200,-5, 5);
  TH1D *etatransverse = new TH1D("eta transverse","Eta Tansverse",200,-5, 5);
  TH1D *phitransverse = new TH1D("phi transverse","Phi Tansverse",200,-5, 5);  
  TH1D *pttransverse = new TH1D("pT transverse","pT Tansverse",1000,0,100);
  
  
  

  
//In the following step we are looping across entries//
Int_t leadparticle;				
for(Int_t k=0; k<events; k++)   
	{  							

	pytree->GetEntry(k);//storing the data of kth entry//
	Int_t ntrks = ntrack;
        

	leadparticle = 0;
//finding the index of lead particle
	for(Int_t i=0; i<ntrks; i++) {
		if(pT[leadparticle]<pT[i]) leadparticle=i;
	}
//dividing the particles in three regions and storing the data by filling in the histograms.//

	for(Int_t i=0; i<ntrks; i++) 
	{
	  if(TMath::Abs(phi[leadparticle]-phi[i])<TMath::Pi()/3){  //condition for towards region //
        pttoward->Fill(pT[i]);
        etatoward->Fill(eta[i]);
        phitoward->Fill(phi[i]);}
	  else if(TMath::Abs(phi[leadparticle]-phi[i])>2*TMath::Pi()/3){ //condition for away region//
        ptaway->Fill(pT[i]);
        etaaway->Fill(eta[i]);
        phiaway->Fill(phi[i]);}
	  else { //rest will go in transverse region//
        pttransverse->Fill(pT[i]);
        etatransverse->Fill(eta[i]);
        phitransverse->Fill(phi[i]);}
	}}
//In the following step we are merging all  three graphs in the same graph//

THStack *pts = new THStack("pt","pT");
THStack *etas = new THStack("eta","eta");
THStack *phis = new THStack("phi","phi");


etas->Add(etaaway);
etas->Add(etatoward);
etas->Add(etatransverse);

etas->Draw();
//using the default function of giving colour to histogram in root//
 
etatoward->SetLineColor(18);
etaaway->SetLineColor(12);
etatransverse->SetLineColor(8);

//as of now the code will draw the graph for the variable eta//

//remove the comments to get the graph of the variable needed //

/*
phis->Add(phitoward);
phis->Add(phiaway);
phis->Add(phitransverse);

phis->Draw();
phitoward->SetLineColor(18);
phiaway->SetLineColor(12);
phitransverse->SetLineColor(8);*/

/*
pts->Add(pttoward);
pts->Add(ptaway);
pts->Add(pttransverse);

pts->SetMinimum(0.0);
pts->Draw();
pttoward->SetLineColor(18);
ptaway->SetLineColor(12);
pttransverse->SetLineColor(8);*/


canvas->BuildLegend();


}

