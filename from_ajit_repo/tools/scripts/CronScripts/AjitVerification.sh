#!/bin/bash

# Script to run the verification tests on the latest processor implementations
# both C and Aa. Using crontab, this script can be scheduled to run at specific time everyday.

# Written by Titto Thomas

source /home/titto/Cron/cron.sh

# Update AHIR first
cd $AHIR_RELEASE/../
git fetch --all
git reset --hard origin/master
./build.sh

# get the location of the script
SCRIPT_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_HOME/../AjitRepoV2/

# update the repo
git fetch --all
git reset --hard origin/master

# Ajit repo home location
REPO_HOME="$SCRIPT_HOME/../AjitRepoV2/"
# Navigate to the Ajit repo
cd $REPO_HOME
source exports.sh

# Clean all the previous builds
scons -c
./clean.sh
cd processor/Aa_v2/cpu
./clean.sh

cd ../../../

# Build the C model
scons
./build.sh

echo "Building the Aa model.."
# Build the Aa model
#cd processor/Aa_v2/cpu
#./build.sh
echo "Finished building the Aa model.."

# Run the verification tests
cd $SCRIPT_HOME
validation_outer.py -C -t 50 -j 1 $REPO_HOME/processor/verification/
validation_outer.py -A -t 1000 -j 1 $REPO_HOME/processor/verification/


# Analyze the log files and generate mail content
./AjitVerificationMail.py VerificationMail.txt


# Bundle all the logs files together
log_folder="ajit_log_$(date +%d-%m-%Y)"
mkdir $log_folder
mv src*.* $log_folder
mv val*.* $log_folder

zip -r $log_folder.zip $log_folder

# send the email with all details
php email.php VerificationMail.txt $log_folder.zip tittoambadan@gmail.com
php email.php VerificationMail.txt $log_folder.zip madhav@ee.iitb.ac.in
php email.php VerificationMail.txt $log_folder.zip getashfa@gmail.com
php email.php VerificationMail.txt $log_folder.zip mailtopiyushsoni9@gmail.com

# clean up
rm -rf $log_folder
rm VerificationMail.txt
rm $log_folder.zip

# Clean all the current builds done by this script
validation_outer.py -c $REPO_HOME/processor/verification/
cd $REPO_HOME
scons -c
#./build.sh
#cd processor/Aa_v2/cpu
./clean.sh
#cd tests
#scons -c

#cd $SCRIPT_HOME/../
#rm -rf AjitRepoV2/
exit
