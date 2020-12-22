#!/bin/bash
export SCRAM_ARCH=slc7_amd64_gcc700
cd /afs/cern.ch/user/r/ratramon/Bparking/CMSSW_10_2_15/src/
eval `scramv1 runtime -sh`
echo $PWD
cd macros/BToKEE_tmvaXevent/analysis
echo $PWD
$1 $2 $3 $4 $5 $6

