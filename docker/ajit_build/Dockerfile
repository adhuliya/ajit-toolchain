# A docker image with ajit-toolchain

# This Dockerfile is copied from `$AJIT_HOME/docker/ajit_build` 
# to `$AJIT_HOME/` folder.

# The toolchain is built while building the docker image.
# Once the build completes the docker container is
# ready to use from `/home/ajit` directory with user ajit.

# After running the docker image read: `/home/ajit/README.md`
# see ./docker/ajit_base/Dockerfile
FROM ajit_base:1.0

# copy buildroot and related modules and build
COPY buildroot_src $AJIT_HOME/buildroot_src
WORKDIR $AJIT_HOME

COPY ahir_release $AJIT_HOME/ahir_release
COPY simulators   $AJIT_HOME/simulators
COPY tools        $AJIT_HOME/tools
COPY scripts      $AJIT_HOME/scripts
COPY examples     $AJIT_HOME/examples

COPY ./docker/ajit_build/setup_ajit_build.sh $AJIT_HOME/
RUN bash ./setup_ajit_build.sh

COPY ./docker/ajit_build/ajit_env $AJIT_HOME/

COPY ./docker/ajit_build/docker_cmd.sh $AJIT_HOME/
CMD bash ./docker_cmd.sh


