CC = g++
CFLAGS = -Wall -c -g -fpermissive 

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I. -I.. -I$(ROOTSYS)/include  -I../interface/   -I../../CommonTools/ -I../../CommonTools/interface/ -I$(ROOFIT_INCLUDE)/ -I$(CMSSW_BASE)/src # -I$(CMSSW_BASE)/src/NanoUVCommonTools  

ROOTSYS ?= ERROR_RootSysIsNotDefined

ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`

EXTRALIBS := -L$(ROOTSYS)/lib -lRooFit -lTMVA -lRooFitCore -lHtml -lMathCore -lGenVector -lMinuit -lTreePlayer -L$(ROOFIT_LIBDIR)/ 



SglBkgAnalysis: Signal_Analysis.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SglBkgAnalysis Signal_Analysis.cpp BParkTools.o  BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



BkgSides: Bkg_sidebands.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o BkgSides Bkg_sidebands.cpp BParkTools.o  BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



ElectronEff: ElectronEff.cpp BParkTools.o BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o ElectronEff ElectronEff.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


ElectronEff_old: newElectronPFefficiency.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o ElectronEff_old newElectronPFefficiency.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



ElectronBkg: Electron_background.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o ElectronBkg Electron_background.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



SkimMC: skimmed_ntuple.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimMC skimmed_ntuple.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


SkimProbe: MuProbeTriplets.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimProbe MuProbeTriplets.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

SkimData_bkg: Skim_eleback.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimData_bkg Skim_eleback.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



SkimDataPF: data_skimming.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimDataPF data_skimming.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

SkimData: Skimmer.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimData Skimmer.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

SkimData2: Skimmer2criteria.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimData2 Skimmer2criteria.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

SkimStd: Skim_stdCut.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o SkimStd Skim_stdCut.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


BkgAnalysis: Background_analysis.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o BkgAnalysis Background_analysis.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

Fake_plots: fake_plots.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o Fake_plots fake_plots.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


ROCStudies: ROCs.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o ROCStudies ROCs.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)



FitPeak: fit_peak.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o FitPeak fit_peak.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG)

Skim_valid: 4mu_skim.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o Skim_valid 4mu_skim.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG)


Categories: categories.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o Categories categories.cpp BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

Categorized_analysis: categ_analysis.cpp BParkTools.o BCategorizedClass.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o Categorized_analysis categ_analysis.cpp BParkTools.o BCategorizedClass.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


PFMvaId_mB: Cut_onSignal.cpp BParkTools.o SelectedBClass.o SingleBClass.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o PFMvaId_mB Cut_onSignal.cpp SelectedBClass.o SingleBClass.o BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


ROC_sidebands: ROC_sidebands.cpp BParkTools.o SingleBClass.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o ROC_sidebands ROC_sidebands.cpp SingleBClass.o BParkTools.o BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


PF_bkg: Bkg_selector.cpp BParkTools.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o PF_bkg Bkg_selector.cpp BParkTools.o BminiMCTree.o BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

PF_sig: Signal_selector.cpp BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -o PF_sig Signal_selector.cpp  BElectronsClass.o BCategorizedClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)


BParkTools.o: ../../newElectronPF/src/BParkTools.cc BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o
	$(CC) -Wall $(INCLUDES) -c  ../../newElectronPF/src/BParkTools.cc BElectronsClass.o BElectronsClassMC.o BGElectronClass.o BSignalElectronClass.o BNanoClass.o $(ROOTFLAG) $(EXTRALIBS)

BElectronsClass.o: ../../newElectronPF/src/BElectronsClass.cc
	$(CC) -Wall $(INCLUDES) -c ../../newElectronPF/src/BElectronsClass.cc $(ROOTFLAG) $(EXTRALIBS)

SingleBClass.o: ../../newElectronPF/src/SingleBClass.cc
	$(CC) -Wall $(INCLUDES) -c ../../newElectronPF/src/SingleBClass.cc $(ROOTFLAG) $(EXTRALIBS)

SelectedBClass.o: ../../newElectronPF/src/SelectedBClass.cc
	$(CC) -Wall $(INCLUDES) -c ../../newElectronPF/src/SelectedBClass.cc $(ROOTFLAG) $(EXTRALIBS)

BElectronsClassMC.o: ../../newElectronPF/src/BElectronsClassMC.cc
	$(CC) -Wall $(INCLUDES) -c  ../../newElectronPF/src/BElectronsClassMC.cc $(ROOTFLAG) $(EXTRALIBS)

BGElectronClass.o: ../../newElectronPF/src/BGElectronClass.cc
	$(CC) -Wall $(INCLUDES) -c ../../newElectronPF/src/BGElectronClass.cc $(ROOTFLAG) $(EXTRALIBS)

BSignalElectronClass.o: ../../newElectronPF/src/BSignalElectronClass.cc
	$(CC) -Wall $(INCLUDES) -c  ../../newElectronPF/src/BSignalElectronClass.cc $(ROOTFLAG) $(EXTRALIBS)

BminiMCTree.o: ../src/BminiMCTree.cc
	$(CC) -Wall $(INCLUDES) -c ../src/BminiMCTree.cc $(ROOTFLAG) $(EXTRALIBS)

BNanoClass.o: ../src/BNanoClass.cc
	$(CC) -Wall $(INCLUDES) -c ../src/BNanoClass.cc $(ROOTFLAG) $(EXTRALIBS)
BCategorizedClass.o: ../../newElectronPF/src/BCategorizedClass.cc
	$(CC) -Wall $(INCLUDES) -c ../../newElectronPF/src/BCategorizedClass.cc $(ROOTFLAG) $(EXTRALIBS)
clean:
	rm *.o BParkTools.o
