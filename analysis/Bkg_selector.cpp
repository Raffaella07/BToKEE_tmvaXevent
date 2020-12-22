#include "../interface/BParkTools.h"
#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <utility>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <unistd.h>
#include <dirent.h>
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TFile.h"
#include "TAxis.h"
#include "TTree.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TString.h"
#include "TLorentzVector.h"

#define MUON_MASS 0.10565837
#define B_MASS  5.27925


void rankedIdxes(std::vector<float>* unsorted, std::vector<float>* sorted, std::vector<int>* all_idx, std::vector<int>* indx ){

	int d, j,counter=0;

	std::sort(sorted->begin(), sorted->end(),std::greater<float>());
	for (int d=0; d < sorted->size(); d++){
		for (int j =0; j<all_idx->size();j++){

			if (unsorted->at(j)==sorted->at(d)){
				counter++;
				indx->push_back(all_idx->at(j));
				if (counter == sorted->size())break;

			}
		}
				//if (counter == sorted->size())break;

	}





}

int main(int argc, char **argv){

	//--grab and initialize trees
	std::string inputfile = argv[1];
	int input_idx= std::atoi(argv[2]);
	int set= std::atoi(argv[3]);
	std::cout << "input idx " << input_idx <<  std::endl;
	//initialize input chain
	TChain* chain= new TChain("Events");
	std::ifstream infile;
	infile.open(inputfile.c_str());	
	bool isMC;
	if(infile.fail()) // checks to see if file opended 
	{ 
		std::cout << "error" << std::endl; 
		return 1; // no point continuing if the file didn't open...
	}
	std::cout << "Loading input from /eos/cms/store/group/cmst3/group/bpark/BParkingNANO_2020Jan16/" << std::endl;
	int counter =0; 
	std::string line;
	while(std::getline(infile, line)) // reads file to end of *file*, not line
	{ 	bool temp;
		if (counter ==0)
		{
			//	infile >> temp; // read first column number
			isMC = atoi(line.c_str()); //first line of file contains flag for mc/data 
			std::cout << isMC << std::endl;
		}

		else{
			//	infile >> file; // read first column number
			if (counter < input_idx+1 ){
			std::ifstream file(line.c_str());
			
			bool good=false;	
			if (counter > 0 && counter < 900)do{
				good = file.good();
				

				}while(!good);
				if(good) chain->Add(line.c_str());
				std::cout << line << std::endl;
//			break;
			}
		}
		counter++;


	}
	if (isMC)std::cout <<" analyzing Montecarlo dataset: " << inputfile << std::endl;
	else std::cout <<"analyzing dataset: " << inputfile << std::endl;
	std::cout << "loaded file number " << counter << " as input:  " << line  << std::endl;

	chdir(" /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/newElectronPF/analysis");
	TFile* outfile = TFile::Open(argv[4],"RECREATE");
	std::cout <<  outfile << std::endl;
	TTree SkimTree("Tree", "A skimmed tree containing one selected nBToKEE event");


	BNanoClass evt;
	evt.Init(chain);

	//Event variables
	int entry, event,category;
	float prescale, weight;
	int iHLT_Mu12_IP6, iHLT_Mu9_IP6;

	//BToKEE fitted variables 
	bool BToKEE_isMC;

	float BToKEE_cos2D,BToKEE_eta   ,BToKEE_fit_cos2D,BToKEE_fit_eta   ,BToKEE_fit_k_eta,BToKEE_fit_k_phi,
	       BToKEE_fit_k_pt ,BToKEE_fit_l1_eta,BToKEE_fit_l1_phi,BToKEE_fit_l1_pt ,BToKEE_fit_l2_eta,BToKEE_fit_l2_phi,BToKEE_fit_l2_pt,BToKEE_fit_mass  ,BToKEE_fit_massErr,BToKEE_fit_phi  ,BToKEE_fit_pt,
	       BToKEE_l_xy   ,BToKEE_l_xy_unc,BToKEE_l_xy_sig,BToKEE_mass   ,BToKEE_maxDR ,BToKEE_minDR  ,BToKEE_mllErr_llfit,BToKEE_mll_fullfit,BToKEE_mll_llfit  ,BToKEE_mll_raw,BToKEE_phi  ,BToKEE_pt, BToKEE_ptN,BToKEE_svprob,
	       BToKEE_vtx_ex,BToKEE_vtx_ey,BToKEE_vtx_ez,BToKEE_vtx_x,BToKEE_vtx_y  ,BToKEE_vtx_z;  
	int  BToKEE_charge,BToKEE_pdgId, signal;
	//Reco collections variables:
	//Kinematics
	float BToKEE_l1_pt,BToKEE_l2_pt,BToKEE_l1_ptN,BToKEE_l2_ptN,BToKEE_l1_eta,BToKEE_l2_eta,BToKEE_l1_phi,BToKEE_l2_phi, BToKEE_k_pt, BToKEE_k_ptN, BToKEE_k_eta, BToKEE_k_phi,BToKEE_l1_charge,BToKEE_l2_charge,BToKEE_k_charge;

	//isolation
	float BToKEE_iso04, BToKEE_l1_iso04, BToKEE_l2_iso04,BToKEE_k_iso04;

	//displacement
	float BToKEE_l1_dxySig, BToKEE_l2_dxySig,BToKEE_k_dxySig,BToKEE_DeltaZ;

	//pt imbalance
	float BToKEE_ptImb;

	
	//electrons categories flags & Ids
	bool  BToKEE_l1_isPF, BToKEE_l2_isPF,BToKEE_l1_isLowPt, BToKEE_l2_isLowPt, BToKEE_l1_isPFoverlap, BToKEE_l2_isPFoverlap;
	float BToKEE_l2_pfmvaId,BToKEE_l1_pfmvaId,BToKEE_l1_mvaId, BToKEE_l2_mvaId;

	//Gen level decay products
//	float GenPart_l1_pt, GenPart_l1_eta, GenPart_l1_phi, GenPart_l1_charge, GenPart_l2_pt, GenPart_l2_eta, GenPart_l2_phi, GenPart_l2_charge, GenPart_k_pt, GenPart_k_eta, GenPart_k_phi, GenPart_k_charge;


	int nSaved = 1;
	//variables per event

	SkimTree.Branch("entry", &entry);
	SkimTree.Branch("event", &event);
	SkimTree.Branch("category", &category);
	SkimTree.Branch("nSaved", &nSaved);
	SkimTree.Branch("HLT_Mu12_IP6", &iHLT_Mu12_IP6, "iHLT_Mu12_IP6/I");
	SkimTree.Branch("HLT_Mu9_IP6", &iHLT_Mu9_IP6, "iHLT_Mu9_IP6/I");

	//BToKEE variables

	SkimTree.Branch("BToKEE_cos2D",  &BToKEE_cos2D);
	SkimTree.Branch("BToKEE_eta", &BToKEE_eta);
	SkimTree.Branch("BToKEE_fit_cos2D", &BToKEE_fit_cos2D);
	SkimTree.Branch("BToKEE_fit_eta",  &BToKEE_fit_eta);
	SkimTree.Branch("BToKEE_fit_k_eta", &BToKEE_fit_k_eta);
	SkimTree.Branch("BToKEE_fit_k_phi",  &BToKEE_fit_k_phi);
	SkimTree.Branch("BToKEE_fit_k_pt",  &BToKEE_fit_k_pt);
	SkimTree.Branch("BToKEE_fit_l1_eta", &BToKEE_fit_l1_eta);
	SkimTree.Branch("BToKEE_fit_l1_phi", &BToKEE_fit_l1_phi);
	SkimTree.Branch("BToKEE_fit_l1_pt", &BToKEE_fit_l1_pt);
	SkimTree.Branch("BToKEE_fit_l2_eta", &BToKEE_fit_l2_eta);
	SkimTree.Branch("BToKEE_fit_l2_phi", &BToKEE_fit_l2_phi);
	SkimTree.Branch("BToKEE_fit_l2_pt", &BToKEE_fit_l2_pt);
	SkimTree.Branch("BToKEE_fit_mass", &BToKEE_fit_mass);
	SkimTree.Branch("BToKEE_fit_massErr", &BToKEE_fit_massErr);
	SkimTree.Branch("BToKEE_fit_phi", &BToKEE_fit_phi);
	SkimTree.Branch("BToKEE_fit_pt", &BToKEE_fit_pt);
	SkimTree.Branch("BToKEE_l_xy", &BToKEE_l_xy);
	SkimTree.Branch("BToKEE_l_xy_unc", &BToKEE_l_xy_unc);
	SkimTree.Branch("BToKEE_l_xy_sig", &BToKEE_l_xy_sig);
	SkimTree.Branch("BToKEE_iso04", &BToKEE_iso04);
	SkimTree.Branch("BToKEE_mass", &BToKEE_mass);
	SkimTree.Branch("BToKEE_ptImb", &BToKEE_ptImb);
	SkimTree.Branch("BToKEE_maxDR" , &BToKEE_maxDR );
	SkimTree.Branch("BToKEE_minDR" , &BToKEE_minDR );
	SkimTree.Branch("BToKEE_mllErr_llfit" , &BToKEE_mllErr_llfit );
	SkimTree.Branch("BToKEE_mll_fullfit" ,  &BToKEE_mll_fullfit );
	SkimTree.Branch("BToKEE_mll_llfit" , &BToKEE_mll_llfit );
	SkimTree.Branch("BToKEE_mll_raw" , &BToKEE_mll_raw );
	SkimTree.Branch("BToKEE_phi" , &BToKEE_phi );
	SkimTree.Branch("BToKEE_pt" , &BToKEE_pt );
	SkimTree.Branch("BToKEE_ptN" , &BToKEE_ptN );
	SkimTree.Branch("BToKEE_svprob" , &BToKEE_svprob );
	SkimTree.Branch("BToKEE_vtx_ex" , &BToKEE_vtx_ex );
	SkimTree.Branch("BToKEE_vtx_ey" ,  &BToKEE_vtx_ey );
	SkimTree.Branch("BToKEE_vtx_ez" , &BToKEE_vtx_ez );
	SkimTree.Branch("BToKEE_vtx_x" , &BToKEE_vtx_x );
	SkimTree.Branch("BToKEE_vtx_y" , &BToKEE_vtx_y );
	SkimTree.Branch("BToKEE_vtx_z" , &BToKEE_vtx_z );
	SkimTree.Branch("BToKEE_charge" ,  &BToKEE_charge );
	SkimTree.Branch("BToKEE_l1_charge" ,  &BToKEE_l1_charge);
	SkimTree.Branch("BToKEE_l2_charge" ,  &BToKEE_l2_charge);
	SkimTree.Branch("BToKEE_k_charge" ,  &BToKEE_k_charge);
	SkimTree.Branch("BToKEE_l1_pt" , &BToKEE_l1_pt );
	SkimTree.Branch("BToKEE_l2_pt" , &BToKEE_l2_pt );
	SkimTree.Branch("BToKEE_l1_ptN" , &BToKEE_l1_ptN );
	SkimTree.Branch("BToKEE_l2_ptN" , &BToKEE_l2_ptN );
	SkimTree.Branch("BToKEE_l1_eta" , &BToKEE_l1_eta );
	SkimTree.Branch("BToKEE_l2_eta" , &BToKEE_l2_eta );
	SkimTree.Branch("BToKEE_l1_phi" , &BToKEE_l1_phi );
	SkimTree.Branch("BToKEE_l2_phi" , &BToKEE_l2_phi );
	SkimTree.Branch("BToKEE_l1_isPF" , &BToKEE_l1_isPF );
	SkimTree.Branch("BToKEE_l2_isPF" , &BToKEE_l2_isPF );
	SkimTree.Branch("BToKEE_l1_pfmvaId" , &BToKEE_l1_pfmvaId );
	SkimTree.Branch("BToKEE_l2_pfmvaId" , &BToKEE_l2_pfmvaId );
	SkimTree.Branch("BToKEE_l1_isLowPt" , &BToKEE_l1_isLowPt );
	SkimTree.Branch("BToKEE_l2_isLowPt" , &BToKEE_l2_isLowPt );
	SkimTree.Branch("BToKEE_l1_mvaId" , &BToKEE_l1_mvaId );
	SkimTree.Branch("BToKEE_l2_mvaId" , &BToKEE_l2_mvaId );
	SkimTree.Branch("BToKEE_l1_isPFoverlap" , &BToKEE_l1_isPFoverlap );
	SkimTree.Branch("BToKEE_l2_isPfoverlap" , &BToKEE_l2_isPFoverlap );
	SkimTree.Branch("BToKEE_l1_iso04", &BToKEE_l1_iso04);
	SkimTree.Branch("BToKEE_l2_iso04", &BToKEE_l2_iso04);
	SkimTree.Branch("BToKEE_l1_dxySig", &BToKEE_l1_dxySig);
	SkimTree.Branch("BToKEE_l2_dxySig", &BToKEE_l2_dxySig);
	SkimTree.Branch("BToKEE_k_pt" , &BToKEE_k_pt );
	SkimTree.Branch("BToKEE_k_ptN" , &BToKEE_k_ptN );
	SkimTree.Branch("BToKEE_k_eta" , &BToKEE_k_eta );
	SkimTree.Branch("BToKEE_k_phi" , &BToKEE_k_phi );
	SkimTree.Branch("BToKEE_k_iso04", &BToKEE_k_iso04);
	SkimTree.Branch("BToKEE_k_dxySig", &BToKEE_k_dxySig);
	SkimTree.Branch("BToKEE_pdgId" , &BToKEE_pdgId );
	SkimTree.Branch("BToKEE_DeltaZ" , &BToKEE_DeltaZ );
	SkimTree.Branch("weight" , &weight );
	SkimTree.Branch("prescale" , &prescale );
	SkimTree.Branch("signal" , &signal );
//	SkimTree.Branch("BToKEE_isMC" , &BToKEE_isMC , "BToKEE_isMC[nSaved]/O");

/*	if (isMC){ // decay products @ gen level

		SkimTree.Branch("GenPart_l1_pt" , &GenPart_l1_pt , "GenPart_l1_pt[nSaved]/F");
		SkimTree.Branch("GenPart_l1_eta" , &GenPart_l1_eta , "GenPart_l1_eta[nSaved]/F");
		SkimTree.Branch("GenPart_l1_phi" , &GenPart_l1_phi , "GenPart_l1_phi[nSaved]/F");
		SkimTree.Branch("GenPart_l1_charge" , &GenPart_l1_charge , "GenPart_l1_charge[nSaved]/I");
		SkimTree.Branch("GenPart_l2_pt" , &GenPart_l2_pt , "GenPart_l2_pt[nSaved]/F");
		SkimTree.Branch("GenPart_l2_eta" , &GenPart_l2_eta , "GenPart_l2_eta[nSaved]/F");
		SkimTree.Branch("GenPart_l2_phi" , &GenPart_l2_phi , "GenPart_l2_phi[nSaved]/F");
		SkimTree.Branch("GenPart_l2_charge" , &GenPart_l2_charge , "GenPart_l2_charge[nSaved]/I");
		SkimTree.Branch("GenPart_k_pt" , &GenPart_k_pt , "GenPart_k_pt[nSaved]/F");
		SkimTree.Branch("GenPart_k_eta" , &GenPart_k_eta , "GenPart_k_eta[nSaved]/F");
		SkimTree.Branch("GenPart_k_phi" , &GenPart_k_phi , "GenPart_k_phi[nSaved]/F");
		SkimTree.Branch("GenPart_k_charge" , &GenPart_k_charge , "GenPart_k_charge[nSaved]/I");

	}*/


	int i;

	std::cout <<"N entries " << evt.fChain->GetEntries() << std::endl;  // input check

	for(i=0;i<evt.fChain->GetEntries();i++){

		if (i%10000==0)std::cout << "On entry " << i  << std::endl;  // loop proceeding ok


		evt.fChain->GetEntry(i);


	//	if (!evt.HLT_Mu12_IP6 && !evt.HLT_Mu9_IP6) continue; // Trigger paths to be satisfied
		
		std::vector<float> B_sel_disc1;
		std::vector<float> B_sel_cat;
		std::vector<float> B_sel_disc2;
		std::vector<int> B_sel_Idx;
		if (evt.nBToKEE>600) continue;
		int cat =0;
	//	for (int cat =0; cat < 3;cat++){// looping onto event categories 

			for (int j = 0; j<evt.nBToKEE;j++){
				bool cat1, cat2, cat3;	
				if (set==1){
					cat1 = (!evt.Electron_isPF[evt.BToKEE_l1Idx[j]] || !evt.Electron_isPF[evt.BToKEE_l2Idx[j]]);
					cat2 = ((evt.Electron_isPF[evt.BToKEE_l1Idx[j]] && evt.Electron_isPF[evt.BToKEE_l2Idx[j]]) || (evt.Electron_isLowPt[evt.BToKEE_l1Idx[j]] && evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]]));
					cat3 = (!evt.Electron_isLowPt[evt.BToKEE_l1Idx[j]] || !evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]]);
				
				}else{
					cat1 = evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]];
					cat2 = !evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]] ||  evt.Electron_mvaId[evt.BToKEE_l2Idx[j]]<2;
					cat3 = !evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]] ||  evt.Electron_mvaId[evt.BToKEE_l2Idx[j]]>2;

				}			

				

				if (cat ==0 && cat1 )continue; // PF-PF

				else if (cat ==1 && cat2 )continue; // PF-lowPt
				if (cat ==2 && cat3 )continue; // lowPt-lowPt



				//defining selections 


				bool ele1_convveto = evt.Electron_convVeto[evt.BToKEE_l1Idx[j]];     
				bool ele2_convveto = evt.Electron_convVeto[evt.BToKEE_l2Idx[j]];     
				bool vtxFitSel =  evt.BToKEE_mass[j]>5.45/* || evt.BToKEE_mass[j]<4.8 && evt.BToKEE_fit_pt[j]>3 && evt.BToKEE_l_xy[j]/evt.BToKEE_l_xy_unc[j]>6 && evt.BToKEE_svprob[j]>0.1 &&evt. BToKEE_fit_cos2D[j]>0.99*/;
				bool ele1Sel = ele1_convveto /*&& evt.BToKEE_fit_l1_pt[j]>0.5 && fabs(evt.BToKEE_fit_l1_eta[j])<2.4 && evt.Electron_isPF[evt.BToKEE_l1Idx[j]]*/;  
				bool ele2Sel = ele2_convveto/* && evt.BToKEE_fit_l2_pt[j]>0.5 && fabs(evt.BToKEE_fit_l2_eta[j])<2.4 && evt.Electron_isPF[evt.BToKEE_l2Idx[j]]*/;  
				bool kSel = evt.BToKEE_fit_k_pt[j]>0.8 && fabs(evt.BToKEE_fit_k_eta[j])<2.4; 
	

				if (/* kSel &&*/ ele1Sel && ele2Sel){ // decay products selection

					if (vtxFitSel){ // whole event selection
				
						if (cat==0 && evt.Electron_isLowPt[evt.BToKEE_l2Idx[j]]) std::cout  << "condition not satisfied" << std::endl;
						B_sel_disc1.push_back(evt.Electron_pt[evt.BToKEE_l1Idx[j]]+evt.Electron_pt[evt.BToKEE_l2Idx[j]]+evt.ProbeTracks_pt[evt.BToKEE_kIdx[j]]); // pushing back whichever variable to perform ranking of B candidates and choose the best candidate to be saved
						B_sel_disc2.push_back(evt.BToKEE_l_xy[j]/evt.BToKEE_l_xy_unc[j]); // pushing back whichever variable to perform ranking of B candidates and choose the best candidate to be saved
						B_sel_Idx.push_back(j); // pushing back the reco B  index 
						B_sel_cat.push_back(cat);//pushing back the event category
			}	
					}
					}
		
		//}

//		std::cout << "array size " << B_sel_disc1.size() << std::endl; 
		std::vector<int> idx[2];
		if(B_sel_Idx.size()>0){ // this loop can be changed to fit the selection criteria needed for skimming

			double temp=-99; 
			std::vector<float> categories[3][2];
			for (int j =0; j<B_sel_Idx.size();j++){
				//	std::cout << "category " << B_sel_cat.at(j) << std::endl; 
				if (B_sel_cat.at(j)==0 && evt.Electron_isLowPt[evt.BToKEE_l2Idx[B_sel_Idx.at(j)]]) std::cout  << "condition not satisfied" << std::endl;

				//Diving the events passing selection in categories
				/*		std::cout << "lowpt lowpt? " << evt.Electron_isLowPt[evt.BToKEE_l1Idx[B_sel_Idx.at(j)]] << "  " << evt.Electron_isLowPt[evt.BToKEE_l2Idx[B_sel_Idx.at(j)]] << std::endl;
						std::cout << "Pf Pf? " << evt.Electron_isPF[evt.BToKEE_l1Idx[B_sel_Idx.at(j)]] << "  " << evt.Electron_isPF[evt.BToKEE_l2Idx[B_sel_Idx.at(j)]] << std::endl;
						std::cout << "__________single selected B : index  " << B_sel_Idx.at(j) << "probV : " << evt.BToKEE_l_xy[B_sel_Idx.at(j)]/evt.BToKEE_l_xy_unc[B_sel_Idx.at(j)] << std::endl; 
						*/		
							if (B_sel_cat.at(j)==0){
									categories[0][0].push_back(B_sel_disc1.at(j));
									categories[0][1].push_back(B_sel_disc2.at(j));
									}
									else if (B_sel_cat.at(j)==1){
									categories[1][0].push_back(B_sel_disc1.at(j));
									categories[1][1].push_back(B_sel_disc2.at(j));
									}
									else if (B_sel_cat.at(j)==2){
									categories[2][0].push_back(B_sel_disc1.at(j));
									categories[2][1].push_back(B_sel_disc2.at(j));
									}
				//if (i==40859)std::cout << "category " << B_sel_cat.at(j) << std::endl; 
				
			}
			//	if (i == 40859)std::cout << " idx size " << idx.size() << std::endl;
			category =0;
			rankedIdxes(&B_sel_disc1, &categories[0][0], &B_sel_Idx,  &idx[0] ); // fills idx vector with the indexes from the reco B in the first category ranked with the choosen criterium
			rankedIdxes(&B_sel_disc2, &categories[0][1], &B_sel_Idx,  &idx[1] ); // fills idx vector with the indexes from the reco B in the first category ranked with the choosen criterium

			
			//	f (i == 40859)std::cout << " categories 1 size " << categories[1].size() << std::endl;
			//	if (i == 40859)std::cout << " idx size " << idx.size() << std::endl;
			if (idx[0].size()+idx[1].size()==0 && categories[1][0].size()+categories[0][0].size()>0){ // if the first category is empty, does the same in the second

			category = 1;
			//	if (i== 40859) std::cout << "first category matches " << categories[0].size() << "1 " << categories[1].size() << std::endl;
			if (categories[0][0].size()==0)rankedIdxes(&B_sel_disc1, &categories[1][0], &B_sel_Idx,  &idx[0] );
			if (categories[0][1].size()==0)rankedIdxes(&B_sel_disc2, &categories[1][1], &B_sel_Idx,  &idx[1] );

			}
			//	if (i == 40859)std::cout << " categories 1 size " << categories[1].size() << std::endl;
			//	if (i == 40859)std::cout << " idx size " << idx.size() << std::endl;
			if(idx[0].size()+idx[1].size()==0 && categories[2][0].size()+categories[2][1].size()>0){ // if the first and second categories are empty, does the same on the third
			category =2;
			//	std::cout << " in last if " << std::endl;
			if (categories[0][0].size()==0 && categories[1][0].size()==0)rankedIdxes(&B_sel_disc1, &categories[2][0], &B_sel_Idx,  &idx[0] );
			if (categories[0][1].size()==0 && categories[1][1].size()==0)rankedIdxes(&B_sel_disc2, &categories[2][1], &B_sel_Idx,  &idx[1] );

			}



		}
		std::vector<int> idx_c,idx_check;
		int size1,size2;			
  //       	std::cout << " idx size 1 " << idx[1].size() << std::endl;
		if(idx[0].size()!=0){
			if (idx[0].size()>3) size1 =3;
			else size1 =idx[0].size();
			for(int h =0; h<size1;h++){
				idx_check.push_back(idx[0].at(h));
			}

			if (idx[1].size()>3) size2 =3;
			else size2 =idx[1].size();
			for(int x =0; x<size2;x++){
				//			std::cout << " idx  " << x << std::endl;
				bool there=false;
				for (int l = 0; l< size1;l++){
					if (idx[1].at(x)==idx_check.at(l)) there = true;

					//					std::cout << " indexess " << idx_check.at(l) <<  " " << idx[1].at(x) << std::endl;
				}
				if(!there)idx_check.push_back(idx[1].at(x));
			}

			int size;
			if (idx_check.size() < 6 ) size = idx_check.size(); // set the size of the saved array of B candidates to the actual number of reco B in the highest category found not empty
			else size =6; // if more than 3 reco B are found, saves the first six
	//		std::cout << "array size " << size << std::endl;
			for (int k =0; k< idx_check.size();k++){

			if (category ==0  && evt.Electron_isLowPt[evt.BToKEE_l2Idx[idx_check.at(k)]]) continue;
			nSaved = 1;
			entry = i;
			event = evt.event;
			prescale = 1;
			weight = 1;
			signal = 0;
			iHLT_Mu12_IP6 = evt.HLT_Mu12_IP6;
			iHLT_Mu9_IP6 = evt.HLT_Mu9_IP6;


			//save arrays of reco B selected

		//	if(i==40859)	std::cout << "__________________________________________________________________________single selected B : index  " << idx << "probV : " << evt.BToKEE_l_xy[idx_check.at(k)]/evt.BToKEE_l_xy_unc[idx_check.at(k)] << std::endl; 	
				
				BToKEE_cos2D=evt.BToKEE_cos2D[idx_check.at(k)];   //[nBToKEE]
				BToKEE_eta=evt.BToKEE_eta[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_eta=evt.BToKEE_fit_eta[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_k_eta=evt.BToKEE_fit_k_eta[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_k_phi=evt.BToKEE_fit_k_phi[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_k_pt=evt.BToKEE_fit_k_pt[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l1_eta=evt.BToKEE_fit_l1_eta[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l1_phi=evt.BToKEE_fit_l1_phi[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l1_pt=evt.BToKEE_fit_l1_pt[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l2_eta=evt.BToKEE_fit_l2_eta[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l2_phi=evt.BToKEE_fit_l2_phi[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_l2_pt=evt.BToKEE_fit_l2_pt[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_mass=evt.BToKEE_fit_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_massErr=evt.BToKEE_fit_massErr[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_phi=evt.BToKEE_fit_phi[idx_check.at(k)];   //[nBToKEE]
				BToKEE_fit_pt=evt.BToKEE_fit_pt[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l_xy=evt.BToKEE_l_xy[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l_xy_unc=evt.BToKEE_l_xy_unc[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l_xy_sig=evt.BToKEE_l_xy[idx_check.at(k)]/evt.BToKEE_l_xy_unc[idx_check.at(k)];   //[nBToKEE]
				BToKEE_iso04=evt.BToKEE_b_iso04[idx_check.at(k)];   //[nBToKEE]
				BToKEE_mass=evt.BToKEE_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_maxDR=evt.BToKEE_maxDR[idx_check.at(k)];   //[nBToKEE]
				BToKEE_minDR=evt.BToKEE_minDR[idx_check.at(k)];   //[nBToKEE]
				BToKEE_mllErr_llfit=evt.BToKEE_mllErr_llfit[idx_check.at(k)];   //[nBToKEE]
				BToKEE_mll_fullfit=evt.BToKEE_mll_fullfit[idx_check.at(k)];   //[nBToKEE]
				BToKEE_mll_llfit=evt.BToKEE_mll_llfit[idx_check.at(k)];   //[nBToKEE]
				BToKEE_mll_raw=evt.BToKEE_mll_raw[idx_check.at(k)];   //[nBToKEE]
				BToKEE_phi=evt.BToKEE_phi[idx_check.at(k)];   //[nBToKEE]
				BToKEE_pt=evt.BToKEE_pt[idx_check.at(k)];   //[nBToKEE]
				BToKEE_ptN=evt.BToKEE_pt[idx_check.at(k)]/evt.BToKEE_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_svprob=evt.BToKEE_svprob[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_ex=evt.BToKEE_vtx_ex[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_ey=evt.BToKEE_vtx_ey[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_ez=evt.BToKEE_vtx_ez[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_x=evt.BToKEE_vtx_x[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_y=evt.BToKEE_vtx_y[idx_check.at(k)];   //[nBToKEE]
				BToKEE_vtx_z=evt.BToKEE_vtx_z[idx_check.at(k)];   //[nBToKEE]
				BToKEE_charge=evt.BToKEE_charge[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l1_charge=evt.Electron_charge[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_charge=evt.Electron_charge[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_k_charge = evt.ProbeTracks_charge[evt.BToKEE_kIdx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_DeltaZ=evt.BToKEE_vtx_z[idx_check.at(k)]-evt.PV_z;   //[nBToKEE]

				BToKEE_k_pt=evt.ProbeTracks_pt[evt.BToKEE_kIdx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_k_dxySig=evt.ProbeTracks_dxyS[evt.BToKEE_kIdx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_k_ptN=evt.ProbeTracks_pt[evt.BToKEE_kIdx[idx_check.at(k)]]/evt.BToKEE_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_k_eta=evt.ProbeTracks_eta[evt.BToKEE_kIdx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_k_phi=evt.ProbeTracks_phi[evt.BToKEE_kIdx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_k_iso04=evt.BToKEE_k_iso04[idx_check.at(k)];   //[nBToKEE]

				BToKEE_l1_pt=evt.Electron_pt[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_dxySig=evt.Electron_dxy[evt.BToKEE_l1Idx[idx_check.at(k)]]/evt.Electron_dxyErr[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_pt=evt.Electron_pt[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_dxySig=evt.Electron_dxy[evt.BToKEE_l2Idx[idx_check.at(k)]]/evt.Electron_dxyErr[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_ptN=evt.Electron_pt[evt.BToKEE_l1Idx[idx_check.at(k)]]/evt.BToKEE_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l2_ptN=evt.Electron_pt[evt.BToKEE_l2Idx[idx_check.at(k)]]/evt.BToKEE_mass[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l1_eta=evt.Electron_eta[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_eta=evt.Electron_eta[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_phi=evt.Electron_phi[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_phi=evt.Electron_phi[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_pfmvaId=evt.Electron_pfmvaId[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_pfmvaId=evt.Electron_pfmvaId[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_isPF=evt.Electron_isPF[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_isPF=evt.Electron_isPF[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_isLowPt=evt.Electron_isLowPt[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_isLowPt=evt.Electron_isLowPt[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_mvaId=evt.Electron_mvaId[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l2_mvaId=evt.Electron_mvaId[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE]
				BToKEE_l1_isPFoverlap=evt.Electron_isPFoverlap[evt.BToKEE_l1Idx[idx_check.at(k)]];   //[nBToKEE]  flag checking if the LowPt electron is reconstructed also as PF
				BToKEE_l2_isPFoverlap=evt.Electron_isPFoverlap[evt.BToKEE_l2Idx[idx_check.at(k)]];   //[nBToKEE] flag checking if the LowPt electron is reconstructed also as PF
				BToKEE_l1_iso04=evt.BToKEE_l1_iso04[idx_check.at(k)];   //[nBToKEE]
				BToKEE_l2_iso04=evt.BToKEE_l2_iso04[idx_check.at(k)];   //[nBToKEE]

				TVector3 l1_p,l2_p,r,k_p, pair_proj,k_proj;
				l1_p.SetPtEtaPhi(BToKEE_l1_pt,BToKEE_l1_eta,BToKEE_l1_phi);
				l2_p.SetPtEtaPhi(BToKEE_l2_pt,BToKEE_l2_eta,BToKEE_l2_phi);
				k_p.SetPtEtaPhi(BToKEE_k_pt,BToKEE_k_eta,BToKEE_k_phi);
				r.SetXYZ(evt.BToKEE_vtx_x[idx_check.at(k)]-evt.PV_x,evt.BToKEE_vtx_y[idx_check.at(k)]-evt.PV_y,evt.BToKEE_vtx_z[idx_check.at(k)]-evt.PV_z);

				pair_proj = r.Cross(l1_p+l2_p);
				k_proj = r.Cross(k_p);

				BToKEE_ptImb = pair_proj.Mag()/k_proj.Mag();





				SkimTree.Fill();

	}






	
               } 
		


	}
	
	outfile->Write();
	outfile->Close();
	return 0;
}
