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

### SCANeR studio 2021.2

A valid installation of SCANeR studio 2021.2 is required.

## 2. First time installation

### Set up the Git local repo

* Open directory `%STUDIO_PATH%/SCANeRstudio_2021`
* `Right click > Git Bash here`
* In the Git Bash console, run the following commands:
```
git init
git remote add origin https://github.com/AVSGuichet/Samples-Pack.git
git fetch
```
* When prompted, login to GitHub with the account linked to your company e-mail.
* Fetching takes some time.

The local git repo is now up to date, but no branch is applied to your SCANeR studio installation yet.

### Set your Git credentials

```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```
Now the remote repository can accept your future modifications.

### Git hook for configuration.cfg

```
git config core.hooksPath "./samples-pack-utils/hooks/"
```
Now every time you checkout a branch, the Samples Pack configuration paths will be automatically be added to `%STUDIO_PATH%/configurations.cfg`  

### Ignore SCANeR installation files

By default, Git lists all files. This includes SCANeR studio installed files that are not related to the Samples Pack.  
Try to do ```git status``` and you will see the very long list. It is difficult to find the relevant modification of Samples Pack files in the middle of it.

In order to ignore these files from now on, add all of these file to your local exclude list.  
(Do this only when you don't have uncommitted Samples Pack changes, or they will be added to the exclude list.)
```
git ls-files --others --exclude-standard >> .git/info/exclude
```
Git will stop mentionning these files. They will remain untouched.

Over time, if you work and create files that are not related to the Samples Pack (e.g.: test configuration), run the command again to update your exclude list.

### Deploy the Samples Pack files

```
git checkout -b 2021.2 origin/2021.2
```
This creates a new local branch `2021.2` that with uplink `origin/2021.2`
Now your SCANeR studio installation has the latest version of the Samples Pack files.

## 3. Publish a modification

### Get the latest version

Make sure that you are on a working branch (e.g. `2021.2`) with a valid uplink (e.g. `origin/2021.2`).
```
git fetch
git pull
```
Now your SCANeR studio installation has the latest Samples Pack files.

### Start working

You can perform the modifications on your local copy of the Samples Pack.

Commit changes on your working branch as often as necessary.

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

## 4. Release

The [SCANeR User Guides](https://avsguichet.github.io/Samples-Pack/) website links to the latest release of the Samples Pack.

* Prepare the ZIP
  * Go to the [latest commit on GitHub](../../tree/2021.2)
  * Download as a ZIP: `Code` > `Download as ZIP`  
  The ZIP includes a root folder `Samples-Pack-2021.2` that we don't want.
  * Create a new ZIP with `APIs/`, `bin/`, `config/` etc... at the root  
  Name of the new ZIP: `Samples-Pack-<latest major SCANeR release>r<Samples Pack sub-version>` (e.g. `Samples-Pack-2021.2r1`)
* Create a Release on GitHub
  * Go to the [repository releases page](../../releases)
  * Button `Draft a new release`
    * Target = `<latest major SCANeR release>` (e.g. `2021.2`)
    * Tag = `<latest major SCANeR release>r<Samples Pack sub-version>` (e.g. `2021.2r1`)
    * Title = `Samples Pack <Samples Pack version>` (e.g. `Samples Pack 2021.2r1`)
    * Description of changes included in this release (optional)
    * Attach binaries = Drag & drop the new ZIP in the "Attach binaries" area
  * Button `Publish release`
* Update the link
  * Go to the SCANeR Guides repository and [edit `_config.yml`](../../../SCANeR-User-Guides/edit/Published/_config.yml).
  * Change the `zip_url:` path to the newly uploaded ZIP URL
