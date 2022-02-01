# Samples-Pack Contributor's manual

Thank you for checking the SCANeR Sample Pack.

This project includes turn-key examples for various use cases of [**SCANeR**](https://www.avsimulation.com/scaner-catalog/).  
Use it for evaluation, inspiration, starter for your own projects.

> _**Get a [free SCANeR Trial here](https://www.avsimulation.com/free-download/), including all features to use the samples.**_

## Introduction

AVSimulation encourages **collaboration**. The SCANeR Samples Pack is open source, and open to your contributions.

* **Step 1. Copy:** Recover the Samples Pack to your own Github account ("fork").  
  _Use it on your computer for evaluation, inspiration, starter for your own projects._
  
* **Step 2. Work:** Make modifications: improvements, new samples.  
  _Track your changes on your own Github repository, branches._
  
* **Step 3. Publish:** Publish your work on AVSimulation's official repository ("pull request").  
  _AVSimulation approves and your modification is published, available for all._

### Pre-requisites

* SCANeR 2022  
  _Get a free Trial version here: [AVSimulation Free Downloads](https://www.avsimulation.com/free-download/)_
* A [GitHub](https://github.com/login) Account
* A Git client  
  _Here is a Git client : https://git-scm.com/download/win_  
  _Install with default settings (Git Bash is required, Git GUI is nice to have)_
* Git basics  
  _Feeling rusty with Git? Review the Git basics here:  https://git-scm.com/doc_

## Step 1. Copy the Samples Pack

### 1.1. Recover ("fork") the Git repository

This repository is open to forks.

* Go to the [SCANeR Samples Pack repository home](https://github.com/AVSimulation/SCANeR-Samples-Pack/)
* Click on the `Fork` button in the top right corner.
* Confirm the Fork and let Github copy the files to your repository.

_Now you have your own copy of the projects in the Samples Pack._ 👍

### 1.2. Set LOCAL_STUDIO_PATH

> The Samples Pack goes in folder `%LOCAL_STUDIO_PATH%/SCANeR-Samples-Pack-2022/`.

`LOCAL_STUDIO_PATH` is an _environment variable_, like `%STUDIO_PATH%`.  
(Details in the User Manual: `1.5.4.7.5. Set LOCAL_STUDIO_PATH variable`)

* Create a new folder (e.g.: `D:/SCANeR_data/`).
* Find in Windows: "Edit environment variables for your account"
* Add the environment variable "LOCAL_STUDIO_PATH" with full absolute path to your folder (e.g.: "D:\SCANeR_data").

### 1.3. Download ("clone") your Git repository

* Open the directory `%LOCAL_STUDIO_PATH%/`
* `Right click > Git Bash here`
* Clone your repository:
```
git clone https://github.com/<NAME>/SCANeR-Samples-Pack.git SCANeR-Samples-Pack-2022
```
  Where `<NAME>` is your Github account.  
* When prompted, login to GitHub with the account linked to your company e-mail.
* *Downloading takes a few seconds.*
* Go inside the new local repository :
```
cd SCANeR-Samples-Pack-2022
```

### 1.4. Git hooks for configuration.cfg

[Hooks](https://git-scm.com/docs/githooks) are bash scripts that are executed along with a Git command.

* Enable the hooks provided in this repository:
```
git config core.hooksPath "./samples-pack-utils/hooks/"
```

> In the folder `samples-pack-utils/` there is a hook script to auto-update `configuration.cfg` everytime `git checkout` is called.  

Now, SCANeR detects new samples automatically at the next start.

### 1.5. Update the working tree

```
git checkout 2022
```
Now the working tree (i.e. files in `%LOCAL_STUDIO_PATH%/SCANeR-Samples-Pack-2022`) are matching the remote branch.

_The Samples Pack is ready to use in SCANeR._ 👍

Check out the [SCANeR Quick Starts](https://avsimulation.github.io/SCANeR-Quick-Starts/) for a guide of each sample.

### 1.6. Prepare for contribution

The remote repository will need to know who makes a contribution.
```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```

## Step 2. Work

### 2.1. Before modifying, get the latest files

* On your github repository home, click `Fetch upstream` to recover changes from AVSimulation's repository.
* On your local repository, recover the latest changes from your github repository.  
```
git fetch
git pull
```

### 2.2. Start working

You can perform the modifications on your local copy of the Samples Pack.

* Check the list of modified files
```
git status
```
* Include new, modified or deleted files to your commit with
```
git add path/to/the/file
```
* Save the changes in your current local branch
```
git commit -m "Replaced some Simulink block"
```
Parameter "-m" is the commit message that helps everyone know what you did.

### 2.3. Push

When you finished doing the modification and the Samples Pack works, push the branch to the GitHub server.
```
git push
```
> If you get rejected at this stage, hold on and check [merge conflict resolution](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging) 💪.

## Step 3. Publish

When your work is ready, send it to the official AVSimulation repository.  
Your work will be visible to all, and AVSimulation takes care of the migration to new versions.

* On your Github repository home, select the branch that you want to publish.
* Click `Contribute` > `Open pull request`.
* Left member (destination):
  * base repository: `AVSimulation/SCANeR-Samples-Pack`
  * base: `2022`
* Right member (origin): Your repository, and the branch to publish.
* Make sure to fill-in the title and describe your improvement, addition in the comment field.
  It will make it easier for AVSimulation to understand and approve the change.
* `Create pull request`

**Thanks a lot for your contribution** 😎

Now AVSimulation will review the modification.  
After the pull request is approved, your modification is available to all.

## Get help

* [SCANeR **Quick Starts**](https://avsimulation.github.io/SCANeR-Quick-Starts/)
* [**Getting Started** with SCANeR on YouTube](https://www.youtube.com/playlist?list=PLkaKWDRLGrSacxV-4e-EmGLGHbr-w09_5)
* [How to? on YouTube](https://www.youtube.com/playlist?list=PLkaKWDRLGrSb2HZM76aeAaXoH0r06xwtl)
* [**Online events** every months](https://www.avsimulation.com/events/)
* [Past workshops on YouTube](https://www.youtube.com/playlist?list=PLkaKWDRLGrSZ5XdPTTLlDqJBXSDZy1U9Q)
* [**Contact us**](https://www.avsimulation.com/contact-us/)
