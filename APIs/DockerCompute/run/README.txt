#####################################
# SCANeRcompute Docker image running
#####################################

Using the SCANeRcompute docker image (see build/README.txt to build the image)

config    : folder that host the running configuration, will be mounted as docker volume to config/COMPUTE within the container
data      : folder that host the data (scenario and related data): will be mounted as docker volume to data/COMPUTE within the container
out       : results ouput folders, will be mounted as docker volume to /AVSimulation/OUT within the container
launch.sh : script for lauching the container

Copy wanted SCANeR configuration in "config" dir. (Please check before that the configuration is running on a standard installation)
Copy wanted SCANeR data in "data" dir.
start "launch.sh":
Launch the "launch.sh" script with release number as argument to run the image.
$ ./launch.sh XX 
get results within "out" folder.

The default setup is to launch all scenario of the COMPUTE configuration.
To customize behaviour, change the compute.sh script in the build folder and rebuild.

