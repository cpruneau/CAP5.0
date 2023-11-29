#################################################################################
#
# .zshrc
#
#################################################################################
echo "  "
echo "  "
echo "========================================================================================"
echo "  "
echo " Running SetupPythiaLinks.sh"
echo "  "
echo "========================================================================================"
module load pythia
module load cmake
module load root
##################################################
# Load modules and setup
##################################################
echo "========================================================"
echo " Setting up PYTHIA8 "
echo "========================================================"
export PYTHIA8="/wsu/el7/gnu7/pythia/8.303/"
export PYTHIA8_DIR="$MyOpt/Pythia/pythia8307"
export PYTHIA8_INCLUDE_DIR="$PYTHIA8/include/Pythia8/"
export PYTHIA8_LIBRARIES="$PYTHIA8/lib"
export LIBPATH=$LIBPATH:$PYTHIA8_LIBRARIES
echo   "Selected PYTHIA version: "
echo   $PYTHIA8
echo   $PYTHIA8_DIR
echo   $PYTHIA8_INCLUDE_DIR
echo   $PYTHIA8_LIBRARIES
echo " "
echo "========================================================"
echo " Done with Setting up PYTHIA8"
echo "========================================================"
echo " "
echo " "


##################################################
# Configure AliBuild  
##################################################
export ALIBUILD_WORK_DIR="$HOME/alice/sw"
eval "`alienv shell-helper`"





