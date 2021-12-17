#!/bin/bash

# Check arguments
if [ -z "$1" ]
  then
    echo "launch.sh: Missing release number argument."
    echo "launch.sh: Usage: $0 <Release Number>"
    exit 1
fi

RELEASE=$1

# Build dir
DIR=`dirname "$(readlink -f "sample")"`

# Run the docker container
docker run --gpus all \
--rm \
-u $(id -u ${USER}):$(id -g ${USER}) \
-v $DIR/sample/:/DATA/IN \
-v $DIR/out:/DATA/OUT \
-it avsimulation/compute:2022.1r$RELEASE 

# For debugging or testing with command line use the following command
#docker run --gpus all \
#--rm \
#-u $(id -u ${USER}):$(id -g ${USER}) \
#-v $DIR/sample/:/DATA/IN \
#-v $DIR/out:/DATA/OUT \
#-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY \
#--entrypoint "/bin/bash" \
#-it avsimulation/compute:2022.1r17
#
