# A base docker image with all the requirements of the ajit-toolchain

FROM ubuntu:16.04

ENV AJIT /home/ajit
ENV AJIT_HOME /home/ajit/ajit-toolchain

COPY setup_ajit_base.sh $AJIT/

RUN bash $AJIT/setup_ajit_base.sh

COPY docker_cmd.sh $AJIT/
CMD bash $AJIT/docker_cmd.sh
