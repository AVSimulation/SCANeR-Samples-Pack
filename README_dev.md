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
git checkout -t origin/main
```
This gets the latest working version of the Samples-Pack

### Configuration.cfg

Configuration paths have to be added manually in `%STUDIO_PATH%/Configurations.cfg`
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
Now the Samples Pack can be used normally

## 3. Publish a modification

### First time setup

The Git user name must be set up at least once before commiting.
```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```

### Get the latest version

Before starting to work, make sure that you have the latest version of the Samples Pack.
```
git checkout -t origin/main
```

### Create your branch

Then, create a local branch to start working.
```
git checkout -b GA_Fix_Headlights_Framerate
```
No hard naming convention here, but consider including the following information in the branch name:
* author: Your initials
* type: "fix" or "improve" or "new"
* task: If a related Jira task exists, write the ID
* sample: Name of the modified sample
* subject: One or two words to describe the modification
This will help reviewers to keep track of pending modifications.

### Modify

You can perform the modifications on your local copy of the Samples Pack.
 
Commit as mush as you want on your local branch.
* Check the list of modified files
```
git status
```
This also list all SCANeR files that are not in the Samples Pack. Ignore them and only look for yours.
* Include new, modified or deleted files to your commit with
```
git add path/to/my/file
```
* Save the changes in your current local branch
```
git commit -m "Replaced Simulink block"
```
Parameter "-m" is the commit message that will help the reviewers.

### Push

When you finished doing the modification and the Samples Pack works, push the branch to the GitHub server.
```
git push origin GA_Fix_Headlights_Framerate
```
* "origin" points to the GitHub repository
* after "/" is the name of your branch

### Request merge

You can request your modification to be released ("Pull request") in the public version of Samples Pack.
A reviewer will check the modification and perform the release.

* Go to the list of branches of the GitHub repository: https://github.com/AVSGuillaume/Samples-Pack/branches
You should see your branch in the list.
![Your branches](doc/assets/Your%20branches.png)
* Select `New pull request`
* Add details that will help the reviewer
* Finish with `Create pull request`

The other devs are notified.
A reviewer will be designated to validate the modification.

## 4. Review a modification

The reviewer is not the same person who did the modification.

Current Pull Requests can be see on this page: https://github.com/AVSGuillaume/Samples-Pack/pulls.

When you are the reviewer:
* Select the Pull Request to review in order to see the details
* Tab "Files changed" gives an overview of modifications. All samples whose files have been touched must be tested.
* Tab "Conversation" allows for tracked discussion between modification dev and reviewer.

### Test

Get your local copy of the Samples Pack to include the modifications to review.
```
git checkout -t origin/GA_Fix_Headlights_Framerate
```
Run the Samples according to their respective manual.

### Merge

Use the Pull Request page to take action according to your result.
(https://github.com/AVSGuillaume/Samples-Pack/pulls)

* If anything is suspicious
    * Use the "Conversation" tab to scold the modification dev.
    * When the modification is done (by the dev or the reviewer), committed and pushed on the same branch, restart the review process.
* If all is good, validate with button `Merge pull request` then `Confirm merge`

### Publish

The modification is now available on the branch "main".
The working branch has been automatically deleted.

Samples Pack devs who want to update with the latest modification must checkout "main" again:
```
git checkout -t origin/main
```

The public copy of the Samples Pack should be updated manually:
* Get to the home page of the GitHub repo. https://github.com/AVSGuillaume/Samples-Pack/
* Download the ZIP with button `Code > Download ZIP`
* Replace the archive `stockage.avsimulation.com/Evaluation/2021/SCANeRstudio_SamplesPack.zip` via FTP
* If they were modified, replace the PDF files of the Samples Pack Manual in `stockage.avsimulation.com/Evaluation/2021/`
