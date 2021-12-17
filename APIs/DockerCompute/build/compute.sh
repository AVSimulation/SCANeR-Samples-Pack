#!/bin/bash

source setenv.sh SCANeRstudio_2022/

# Enable blocking socket for Non real-time (usage of OFFLINESCHEDULER)
export STUDIO_BLOCKING_SOCKET=1

# Scenarios execution
SCANeRcompute -m -a -s /DATA/OUT $*


