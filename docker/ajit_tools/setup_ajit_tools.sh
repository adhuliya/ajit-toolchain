# remove temporary files from the build

export TEST_ENV="hello";

rm -rf $AJIT_HOME/buildroot_src;
rm -rf $AJIT_HOME/build/development;

for x in $AJIT_HOME/build/buildroot-2014.08/*; do
  if [[ "$x" != "output" ]]; then
    rm -Rf "$x";
  fi
done

for x in $AJIT_HOME/build/buildroot-2014.08/output/*; do
  if [[ "$x" != "host" ]]; then
    rm -Rf "$x";
  fi
done

