#!/bin/sh
#
# add current user and user's primary group
#
groupadd -g $GGID $GGROUP
useradd  -u $GUID -s $GSHELL -c $GUSERNAME -g $GGID -M -d $GHOME $GUSERNAME
usermod  -a -G sudo $GUSERNAME
su -l $GUSERNAME    # become the current user and start a shell
export PATH=$PATH:$HOME/bin
#/bin/bash           # another root shell
