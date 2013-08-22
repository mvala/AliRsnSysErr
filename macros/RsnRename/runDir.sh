#!/bin/bash

function DATA_20130106() {
  DIR_IN="/home/mvala/MVALA/Work/ALICE/Rsn_Phi/pp_2.76/2013-01-06/DATA_LHC11a_ESD"
  DIR_OUT="/home/mvala/00_RSN/alice/rsn/PHIKK/LHC11a/ESD_pass4_without_SDD/RSN_20130106/All/STD2010"
  for D in $(ls -1 $DIR_IN);do
    root -b -q -l 'RsnRename.C("'$DIR_IN'/'$D'/AnalysisResults.root","'$DIR_OUT/$D'")'
  done
}

function MC_20130411() {
  MC="LHC12f1a"
  MC="LHC12f1b"
  DIR_IN="/home/mvala/MVALA/Work/ALICE/Rsn_Phi/pp_2.76/2013-04-11/MC_$MC"
  DIR_OUT="/home/mvala/00_RSN/alice/rsn/PHIKK/$MC/ESD/RSN_20130411/All/STD2010"
  for D in $(ls -1 $DIR_IN);do
    root -b -q -l 'RsnRename.C("'$DIR_IN'/'$D'/AnalysisResults.root","'$DIR_OUT/$D'")'
  done

#   DIR_OUT="/home/mvala/00_RSN/alice/rsn/PHIKK/$MC/ESD/RSN_20130411/Runs"
#   for D in $(ls -1 $DIR_IN);do
#     for D2 in $(ls -1 $DIR_IN/$D);do
#       if [ -d $DIR_IN/$D/$D2 ];then
#         DOUT=$(echo $D2 | awk -F '_' '{print $3}')
#         root -b -q -l 'RsnRename.C("'$DIR_IN'/'$D'/'$D2'/AnalysisResults.root","'$DIR_OUT'/'$DOUT'/STD2010/'$D'")'
#       fi
#     done
#   done

}

function MC_20130219() {

# root 'RsnRename.C("/home/mvala/MVALA/Work/ALICE/Rsn_Phi/pp_2.76/2013-02-19/LHC12f1a/AnalysisResults.root","/home/mvala/00_RSN/alice/rsn/PHIKK/LHC12f1a/ESD/RSN_20130219/All/STD2010/00_DEFAULT")'
# root 'RsnRename.C("/home/mvala/MVALA/Work/ALICE/Rsn_Phi/pp_2.76/2013-02-19/LHC12f1b/AnalysisResults.root","/home/mvala/00_RSN/alice/rsn/PHIKK/LHC12f1b/ESD/RSN_20130219/All/STD2010/00_DEFAULT")'

# runs
  MC="LHC12f1a"
  MC="LHC12f1b"
  DIR_IN="/home/mvala/MVALA/Work/ALICE/Rsn_Phi/pp_2.76/2013-02-19/$MC/"
  DIR_OUT="/home/mvala/00_RSN/alice/rsn/PHIKK/$MC/ESD/RSN_20130219/Runs"
  for D in $(ls -1 $DIR_IN);do
    if [ -d $DIR_IN/$D ];then
      DOUT=$(echo $D | awk -F '_' '{print $3}')
      root -b -q -l 'RsnRename.C("'$DIR_IN'/'$D'/AnalysisResults.root","'$DIR_OUT'/'$DOUT'/STD2010")'
    fi
  done
}
