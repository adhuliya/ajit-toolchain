# remove temporary files from the build
# expects $AJIT_HOME env variable to be set properly.


source $AJIT_HOME/ajit_env;

# rm -rf $AJIT_HOME/buildroot_src;
# rm -rf $AJIT_HOME/build/development;
# 
# for x in $AJIT_HOME/build/buildroot-2014.08/*; do
#   if [[ "$x" != "output" ]]; then
#     rm -Rf "$x";
#   fi
# done
# 
# for x in $AJIT_HOME/build/buildroot-2014.08/output/*; do
#   if [[ "$x" != "host" ]]; then
#     rm -Rf "$x";
#   fi
# done

