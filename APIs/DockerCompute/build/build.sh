#!/bin/bash

# Check arguments
if [ -z "$1" ]
  then
    echo "build.sh: Missing release number argument."
    echo "build.sh: Usage: $0 <Release Number>"
    exit 1
fi

RELEASE=$1

# Build dir
BUILD_DIR=`dirname "$(readlink -f "$0")"`

# Check SCANeRstudio archive presence
if [ ! -f  $BUILD_DIR/SCANeRstudio_2022.1-r$RELEASE.tar.bz2 ]; then
    echo "build.sh: Error Source SCANeRstudio_2022.1-r$RELEASE.tar.bz2 not found"
    exit 2
fi

# Build the image
docker build -t avsimulation/compute:2022.1r$RELEASE --build-arg RELEASE=$RELEASE .

if [ $? -eq 0 ]
then
  echo ""
  echo "build.sh: =============================="
  echo "build.sh: Successfully created docker image with tag: avsimulation/compute:2022.1r$RELEASE"
fi

