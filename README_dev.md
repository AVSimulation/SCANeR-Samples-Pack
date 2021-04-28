# Samples-Pack Developper’s Manual

## 1. Prerequisites
### 1.1. GitHub Account
An account using your company email (avsimulation.fr) is required.
Upon request, AVSimulation sends you an e-mail invitation to join the repo.

### 1.2. Install Git
Get the Git Client here : https://git-scm.com/download/win
Install with default settings (Git Bash is required, Git GUI is good to have)

### 1.3. SCANeR Studio 2021.1
A valid installation of SCANeR Studio 2021.1r34 or above is required.

## 2. First time installation
### 2.1. Set up the Git local repo
* Open folder `%STUDIO_PATH%/SCANeRstudio_2021`
* `Right click > Git Bash here`
* In the Git Bash console, run the following commands
```
git init
git remote add origin https://github.com/AVSGuillaume/Samples-Pack.git
git fetch
```
* Login to GitHub is required
Use the GitHub account linked to your company e-mail.
* Once logged in, run the following command in the Git Bash console
```
git checkout -t origin/main
```
This gets the latest working version of the Samples-Pack
Result should be
```
remote: Enumerating objects: 666, done.
remote: Counting objects: 100% (15/15), done.
remote: Compressing objects: 100% (12/12), done.
remote: Total 666 (delta 3), reused 12 (delta 3), pack-reused 651
Receiving objects: 100% (666/666), 59.40 MiB | 4.23 MiB/s, done.
Resolving deltas: 100% (234/234), done.
From https://github.com/AVSGuillaume/Samples-Pack
 * [new branch]      main       -> origin/main
 * [new branch]      master     -> origin/master
 * [new tag]         v1.0       -> v1.0
```
### 2.2. Configuration.cfg
Configuration paths have to be added manually in %STUDIO_PATH%/Configurations.cfg
```
SAMPLE_2021_ADAS = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_ADAS
SAMPLE_2021_ADAS_LKA_ACC = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_ADAS_LKA_ACC
SAMPLE_2021_CAMERACAPTURE = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_CAMERACAPTURE
SAMPLE_2021_CARMAKER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_CARMAKER
SAMPLE_2021_DATAEXCHANGE = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_DATAEXCHANGE
SAMPLE_2021_FMI = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_FMI
SAMPLE_2021_HEADLIGHTS = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_HEADLIGHTS
SAMPLE_2021_LATERAL_CTRL = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_LATERAL_CTRL
SAMPLE_2021_LONGI_CTRL = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_LONGI_CTRL
SAMPLE_2021_PIXEL_LIGHTING = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_PIXEL_LIGHTING
SAMPLE_2021_SCENARIO_IMPORTER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_SCENARIO_IMPORTER
SAMPLE_2021_VEHICLE_PLAYER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_VEHICLE_PLAYER
```
## 3. Work with Samples-Pack on Git


	
