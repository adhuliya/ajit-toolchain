# A docker image with ajit-toolchain

# This Dockerfile is copied from `$AJIT_HOME/docker/ajit_build_dev` 
# to `$AJIT_HOME/` folder.

# The toolchain is built after building the docker image.
# Once the build completes the docker container is
# ready to use from `/home/ajit` directory with user ajit.

# After running the docker image read: `/home/ajit/README.md`
# see ./docker/ajit_base/Dockerfile
FROM ajit_base_20.04:1.0

ARG uid
ARG gid
ARG user
ARG group

RUN ln -s /usr/bin/python3 /usr/bin/python3.6
RUN groupadd -g ${gid} ${group}
RUN cat /etc/group
RUN useradd -u ${uid} -g ${gid} -m -d /home/ajit -s /bin/bash ${user}
RUN cat /etc/group
RUN cat /etc/passwd

# No work is done while building the image in development
# version. The building has to be initiated manually inside
# the docker container.

# Run a startup script to keep the container alive.
# Not copying docker_cmd.sh in $AJIT_HOME as the toolchain
# will be mounted there.

COPY ./docker_cmd.sh $AJIT/
CMD bash $AJIT/docker_cmd.sh

