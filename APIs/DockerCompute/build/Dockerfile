FROM  nvidia/opengl:1.0-glvnd-devel-ubuntu20.04
MAINTAINER AVSimulation <guillaume.millet@avsimulation.fr>

ARG SCANER_MINOR_VERSION=1
ARG SCANER_MAJOR_VERSION=2022
ARG SCANER_VERSION=$SCANER_MAJOR_VERSION.$SCANER_MINOR_VERSION

ARG RELEASE
# Test madatory argument
RUN : "${RELEASE:?Build argument RELEASE needs to be set and non-empty.}"

# Install needed packages
RUN apt-get update

ENV DEBIAN_FRONTEND="noninteractive" 
ENV TZ="Europe/Paris"

RUN apt-get install -y vim lsb-base lsb-release swig libxerces-c3.2 libtinyxml2.6.2v5 libopenal1 libgdal26 libqt5xml5 libegl1 libqt5script5 libqt5multimediawidgets5 freeglut3 libxqilla6v5 libsdl2-2.0-0 libfftw3-3 libpython2.7 libglew2.1 libpython3.8 libqt5quick5 libqwt-qt5-6 libproj15 libbullet2.88 libpocofoundation62 libpoconet62 libpocojson62 libboost-python1.71 libboost-regex1.71 libboost-chrono1.71 libboost1.71 libboost-system1.71 libogg0 libvorbis0a libmatio9 libpcap0.8 libexif12 libprotobuf17 libglu1-mesa libopengl0 libopencv-core4.2 libopencv-highgui4.2 libopencv-imgcodecs4.2 libopencv-imgproc4.2 libpcrecpp0v5
# clean downloaded packages
RUN apt-get clean

# Install SCANeRstudio
ADD SCANeRstudio_$SCANER_VERSION-r$RELEASE.tar.bz2 /
RUN chmod +x /AVSimulation/setenv.sh

# No Server X and multiple GPU
RUN mv /AVSimulation/SCANeRstudio_$SCANER_MAJOR_VERSION/bin/Linux/ubuntu/20.04/lib/external/libosgViewer.so.162 /AVSimulation/SCANeRstudio_$SCANER_MAJOR_VERSION/bin/Linux/ubuntu/20.04/lib/external/libosgViewerX11.so.162
RUN ln -s /AVSimulation/SCANeRstudio_$SCANER_MAJOR_VERSION/bin/Linux/ubuntu/20.04/lib/external/libosgViewerEGL.so.162 /AVSimulation/SCANeRstudio_$SCANER_MAJOR_VERSION/bin/Linux/ubuntu/20.04/lib/external/libosgViewer.so.162

# Prepare configuration
# Configuration is named COMPUTE and is mount from outside container with volumes
RUN mv /AVSimulation/configurations_default-$SCANER_MAJOR_VERSION.cfg /AVSimulation/configurations.cfg
RUN mkdir /DATA
RUN mkdir /DATA/IN
RUN mkdir /DATA/OUT
ENV LOCAL_STUDIO_PATH="/DATA/IN"

# Configure licence (For AVSimulation licensing, edit the hasp_84230.ini for your setup before building)
RUN mkdir /root/.hasplm
COPY hasp_84230.ini /root/.hasplm/
# Create a link at root if docker is launched with "normal" user
RUN mkdir /.hasplm
COPY hasp_84230.ini /.hasplm/
RUN chmod a+rx -R /.hasplm

# Run
COPY compute.sh /AVSimulation/

# Allow run as "normal user"
RUN chmod a+rx /AVSimulation/compute.sh
RUN chmod -R a+rx /DATA/IN
RUN chmod -R a+rwx /DATA/OUT

# Go
WORKDIR /AVSimulation
ENTRYPOINT ["bash", "compute.sh"]
