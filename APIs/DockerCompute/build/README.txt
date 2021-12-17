##################################
# SCANeRcompute Docker image
##################################

To build the SCANeRcompute image, put the wanted SCANeRstudio_2022.1rXX.tar.bz2 file in this folder.

If using AVSimulation license server, customize the "hasp_84230.ini" to match your environment.

Launch the script with release number of the source file as argument to build the image.
$ ./build.sh XX

The resulting image will be tagged: avsimulation/compute:2022.1rXX

Your image is ready. See the run/README.txt for launching

