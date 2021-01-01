
# important env variables
export BUILDROOT_DIR_NAME=buildroot-2014.08
export RELATIVE_BIN_DIR_PATH=$BUILDROOT_DIR_NAME/output/host/usr/bin;
export ABS_BIN_DIR_PATH="`pwd`/$RELATIVE_BIN_DIR_PATH";
export PATH=$ABS_BIN_DIR_PATH:$PATH;

cd "`pwd`/from_ajit_repo";
source exports.sh;
cd -;
