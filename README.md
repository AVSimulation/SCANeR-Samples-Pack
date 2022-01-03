# Samples-Pack Contributor's manual

Thank you for checking out the SCANeR Sample Pack.

This project includes **turn-key examples** for different use cases of SCANeR studio. Use it for evaluation, inspiration, starter for your own projects.

> **Get a [free SCANeR studio Trial here](https://www.avsimulation.com/free-download/), including all features to use the samples.**

Please check the procedure below to get started with using and contributing to the Samples Pack

# 1. Introduction

## 1.1. Principle

AVSimulation encourages **collaboration**. The SCANeR Samples Pack is open source, and open to your contributions.

The process is as follow:
1. Copy the Samples Pack to your own Github account. ("fork")
2. Use and make modifications: improvements, new samples. Publish under your own account.
3. Suggest the modification into the official AVSimulation repository. ("pull request")
4. AVSimulation approves; your modification is published and available for all.

## 1.2. Pre-requisites

* SCANeR studio 2022

* GitHub Account

* Git client

Any Git client is good to use.

Here is a Git client : https://git-scm.com/download/win  
Install with default settings (Git Bash is required, Git GUI is nice to have)

* Git basics

Feeling rusty with Git ? Review the Git basics here:  https://git-scm.com/doc

## 2. First time installation

## 2.1. Copy ("fork") the Git repository

This repository is open to forks.

* Go to the [SCANeR Samples Pack repository home](https://github.com/AVSimulation/SCANeR-Samples-Pack/)
* Click on the `Fork` button in the top right corner.
* Confirm the Fork and let Github copy the files to your repository.

_Now you have your own copy of the projects in the Samples Pack._ 👍

## 2.2. Set LOCAL_STUDIO_PATH

> The Samples Pack goes in folder `%LOCAL_STUDIO_PATH%/SCANeR-Samples-Pack-2022/`.

`LOCAL_STUDIO_PATH` is an _environment variable_, like `%STUDIO_PATH%`.  
(Details in the User Manual: `1.5.4.7.5. Set LOCAL_STUDIO_PATH variable`)

* In Windows, create a folder (e.g.: `D:/SCANeR_data/`).
* Find "Edit environment variables for your account"
* Add the environment variable "LOCAL_STUDIO_PATH" with full absolute path to your folder (e.g.: "D:\SCANeR_data").

### 2.3. Download ("clone") your Git repository

* Open the directory `%LOCAL_STUDIO_PATH%/`
* `Right click > Git Bash here`
* Clone your repository:
```
git clone https://github.com/<NAME>/SCANeR-Samples-Pack.git SCANeR-Samples-Pack-2022
```
  Where `<NAME>` is your Github account.  
* When prompted, login to GitHub with the account linked to your company e-mail.
* *Downloading takes a few minutes.*
* Go intside the new local repository
```
cd SCANeR-Samples-Pack-2022
```

### 2.4. Git hooks for configuration.cfg

[Hooks](https://git-scm.com/docs/githooks) are bash scripts that are executed with a Git command.  
In the folder `samples-pack-utils/` there is a hook script to auto-update `configuration.cfg` everytime `git checkout` is called.  
```
git config core.hooksPath "./samples-pack-utils/hooks/"
```
That way, SCANeR detects new samples automatically at the next start.

### 2.5. Update the working tree

```
git checkout 2022
```
Now the working tree (i.e. files in `%LOCAL_STUDIO_PATH%/SCANeR-Samples-Pack-2022`) are matching the remote branch.

_The Samples Pack is ready to use in SCANeR._ 👍

### 2.6. Prepare for contribution

The remote repository will need to know who makes a contribution.
```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```

# 3. Modify & contribute

(TBD)
