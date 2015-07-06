#!/bin/bash
SERVER_ALIAS=server_machine
SERVER_PORT=9000

FOLDER_FLAGS="-v $PWD/src:/home/src"

if [[ $1 == server ]]; then
    SERVER_PORTS_FLAGS="-p $SERVER_PORT:$SERVER_PORT --name sandbox_server"
    SERVER_ID=$(sudo docker ps -a | grep "sandbox_server" |  awk '{print $1}')
    if [[ ! -z "$SERVER_ID" ]]; then
        sudo docker stop $SERVER_ID
        sudo docker rm $SERVER_ID
    fi
    sudo docker run -ti $DISPLAY_FLAGS $FOLDER_FLAGS $SERVER_PORTS_FLAGS sandbox /bin/bash
elif [[ $1 == client ]]; then
    CLIENT_PORTS_FLAGS="--link sandbox_server:$SERVER_ALIAS"
    sudo docker run -ti $DISPLAY_FLAGS $FOLDER_FLAGS $CLIENT_PORTS_FLAGS sandbox /bin/bash
else
    echo "USAGE: ./run.sh (client|server)"
fi
