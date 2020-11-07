# A base docker image with all the requirements of the ajit-toolchain

FROM ubuntu:16.04

ENV AJIT_HOME /home/ajit/ajit-toolchain

COPY setup_ajit_base.sh $AJIT_HOME/

RUN bash $AJIT_HOME/setup_ajit_base.sh

COPY docker_cmd.sh $AJIT_HOME/
CMD bash $AJIT_HOME/docker_cmd.sh
