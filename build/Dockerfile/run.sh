#!/bin/bash
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
xauth nlist :0 | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
DISPLAY_FLAGS="-v $XSOCK:$XSOCK -v $XAUTH:$XAUTH -e XAUTHORITY=$XAUTH"
FOLDER_FLAGS="-v $PWD/src:/home/src"
sudo docker run -ti $DISPLAY_FLAGS $FOLDER_FLAGS sandbox /bin/bash

