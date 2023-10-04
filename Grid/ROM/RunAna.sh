#!/bin/bash
#conda init bash
#conda activate CAP_CONDA
#echo Using CONDA environment $CAP_CONDA
echo The root version is:
echo `which root` 
#module load  pythia
#module load  gsl
TASKIX=$SLURM_ARRAY_TASK_ID
SEED=$(( SLURM_ARRAY_TASK_ID + SLURM_ARRAY_JOB_ID*100 ))
CAP_HISTOPATH=$CAP_WORKINGDIRECTORY_Output/$(printf "%02d/" $TASKIX )
echo "========================================================================================"
echo SLURM_ARRAY_TASK_ID is  $SLURM_ARRAY_TASK_ID
echo SLURM_ARRAY_JOB_ID is  $SLURM_ARRAY_JOB_ID
echo TASKIX is  $TASKIX
echo SEED is $SEED
echo NEVENTS is $CAP_NEVENTS
echo Will save histograms at $CAP_HISTOPATH
mkdir $CAP_HISTOPATH
echo "Calling root w/ RunAna"
echo "========================================================================================"
#root -b "$CAP_MACROS/RunAna.C("\"$CAP_PROJECTS/$CAP_JOB_CONFIGURATION\"","\"$CAP_HISTOPATH\"",$SEED,true,$CAP_NEVENTS,1,1)"
root -b "$CAP_MACROS/RunAna.C("\"$CAP_JOB_CONFIGURATION\"","\"$CAP_HISTOPATH\"",$SEED,true,$CAP_NEVENTS,1,1)"

