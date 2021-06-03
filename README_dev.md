# Samples-Pack Developper’s Manual

## 1. Prerequisites

### GitHub Account

For now, the repository is private.
An account using your company email (avsimulation.fr) is required.  
Send a request to guichet@avsimulation.fr.

### Git client

Any Git client is good to use, but the instructions are given here for the "official" client found on git-scm.com.

Get the Git client here : https://git-scm.com/download/win  
Install with default settings (Git Bash is required, Git GUI is good to have)

### Git basics

This manual is meant to be self sufficient.  
If you are interested, check the Git basics here:  https://git-scm.com/doc

### SCANeR studio 2021.1

A valid installation of SCANeR studio 2021.1 is required.

## 2. First time installation

### Set up the Git local repo

* Open folder `%STUDIO_PATH%/SCANeRstudio_2021`
* `Right click > Git Bash here`
* In the Git Bash console, run the following commands
```
git init
git remote add origin https://github.com/AVSGuillaume/Samples-Pack.git
git fetch
```
* When prompted, login to GitHub with the account linked to your company e-mail.
* Once fetching is finished, run the following command in the Git Bash console
```
git checkout -b 2021.2 origin/2021.2
```
This creates a new local branch "2021.2" that with upstream "origin/2021.2"
Now your working tree has the latest version of the Samples Pack files.

### configuration.cfg

Configuration paths still needs to be added manually in `%STUDIO_PATH%/configurations.cfg`
```
SAMPLE_2021_ADAS = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_ADAS
SAMPLE_2021_ADAS_LKA_ACC = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_ADAS_LKA_ACC
SAMPLE_2021_CAMERACAPTURE = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_CAMERACAPTURE
SAMPLE_2021_CARMAKER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_CARMAKER
SAMPLE_2021_DATAEXCHANGE = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_DATAEXCHANGE
SAMPLE_2021_FMI = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_FMI
SAMPLE_2021_HEADLIGHTS = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_HEADLIGHTS
SAMPLE_2021_HEADLIGHTS_HPC = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_HEADLIGHTS_HPC  
SAMPLE_2021_LATERAL_CTRL = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_LATERAL_CTRL
SAMPLE_2021_LONGI_CTRL = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_LONGI_CTRL
SAMPLE_2021_PIXEL_LIGHTING = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_PIXEL_LIGHTING
SAMPLE_2021_SCENARIO_IMPORTER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_SCENARIO_IMPORTER
SAMPLE_2021_VEHICLE_PLAYER = ${STUDIO_PATH}/SCANeRstudio_2021/config/SAMPLE_VEHICLE_PLAYER
```
Now the Samples Pack can be used normally

### Set your Git credentials

The Git user name must be set up at least once before commiting.
```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```
Now the remote repository can accept your future modifications.

### Ignore SCANeR installation files

By default, Git lists all files. This includes SCANeR studio installed files that are not related to the Samples Pack.  
Try to do ```git status``` and you will see the very long list. It is difficult to find the relevant modification of Samples Pack files in the middle of it.

In order to ignore these files from now on, add all of these file to your local exclude list.  
(Do this only when you don't have uncommitted Samples Pack changes, or they will be added to the exclude list.)
```
git ls-files --others --exclude-standard = .git/info/exclude
```
Git will stop mentionning these files. They will remain untouched.

Over time, if you work and create files that are not related to the Samples Pack (e.g.: test configuration), run the command again to update your exclude list.

## 3. Publish a modification

### Get the latest version

Before starting to work, make sure that you have the latest version of the Samples Pack.  
(Make sure that you are on a working branch with a valid uplink.)
```
git fetch
git pull
```
This gets the last modifications from the remote, and applies it to your working branch.

### Start working

You can perform the modifications on your local copy of the Samples Pack.
 
Commit changes on your working branch.
* Check the list of modified files
```
git status
```
* Include new, modified or deleted files to your commit with
```
git add path/to/my/file
```
* Save the changes in your current local branch
```
git commit -m "Replaced Simulink block"
```
Parameter "-m" is the commit message that helps everyone know what you did.

### Push

When you finished doing the modification and the Samples Pack works, push the branch to the GitHub server.
```
git push
```
If you get an error (rejected), see next section.

### Merge

If it has been some time since you started working, it is possible that someone else in the team modified the Samples Pack in the mean time.

You need to merge the modifications locally before sending. First, get the remote modifications.
```
git pull
```
* If everything goes well, there is no error message. Set a merge commit message when prompter.
* If there are conflicts, follow the guidelines to resolve file by file:
https://akshayranganath.github.io/Git-Pull-Handling-Merge-Conflict/  
Once all is ready, create the merge commit
```
git commit -m "Merging"
```

Finally, send again
```
git push
```
