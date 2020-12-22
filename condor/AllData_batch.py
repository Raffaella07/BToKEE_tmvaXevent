import os
import string 
letter ='ABCD'


def makefile(part, let, dir):
	filename = "skim_part.%d_%s_%d.condor"%(part,let,dir)
	file = open(filename,"w")
	file.write("universe 	      = vanilla\n")
	file.write("executable            = /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/BToKEE_tmvaXevent/condor/submit.sh\n")
	file.write("arguments             = ./PF_bkg /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/BToKEE_tmvaXevent/samples/data/ParkingBPH%d_Run2018%s_part%d_000%d.txt $(ProcId) 1 /eos/home-r/ratramon/BToKEE_bdtsamples/LargeBkg_PFPF/%d_%s_%d/skimmedNANO_BPark_data_$(ProcId)_2020Jan2016.root\n"%(part, let, part, dir,part,let,dir))
	file.write("output                = /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/newElectronPF/condor/output/SkimDataB_%d%s%d.$(ProcId).out\n"%(part,let,dir))		
	file.write("error                 = /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/newElectronPF/condor/error/SkimDataB_%d%s%d.$(ProcId).err\n"%(part,let,dir))		
	file.write("log                   = /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/macros/newElectronPF/condor/log/SkimDataB_%d%s%d.$(ProcId).log\n"%(part,let,dir))	
	file.write("\n")
	file.write("request_memory        = 2000 \n")
	file.write("+MaxRuntime           = 244000\n")
	file.write("queue 1000\n")
	file.close()



	

#if not os.path.isdir("/eos/home-r/ratramon/BToKEE_IPsigPF"):
#	os.mkdir("/eos/home-r/ratramon/BToKEE_IPsigPF")

for i in range(1,4):
	for j in letter:
		if j in ('A', 'B','C'):
			for k in range(0,1):
				makefile(i,j,k)
				print("%d %s %d"%(i,j,k))
				if not os.path.isdir("/eos/home-r/ratramon/BToKEE_bdtsamples/LargeBkg/"):
					os.mkdir("/eos/home-r/ratramon/BToKEE_bdtsamples/LargeBkg/")
	
		elif j == 'D' :
			for k in range(6):
				makefile(i,j,k)
				print("%d %s %d"%(i,j,k))
				if not os.path.isdir("/eos/home-r/ratramon/BToKEE_bdtsamples/LargeBkg_PFPF/%d_%s_%d/"%(i,j,k)):
					os.mkdir("/eos/home-r/ratramon/BToKEE_bdtsamples/LargeBkg_PFPF/%d_%s_%d/"%(i,j,k))

