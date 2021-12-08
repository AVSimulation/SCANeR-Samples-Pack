# Samples-Pack Developper’s Manual

## 1. Prerequisites

* SCANeR studio 2022

* GitHub Account

An account using your company email (avsimulation.fr) is required.  
Send a request to guichet@avsimulation.fr.

* Git client

Any Git client is good to use. The instructions are given here for the "official" client found on git-scm.com.

Get the Git client here : https://git-scm.com/download/win  
Install with default settings (Git Bash is required, Git GUI is nice to have)

* Git basics

This manual should be self sufficient.  
For more, check the Git basics here:  https://git-scm.com/doc

## 2. First time installation

### Set up LOCAL_STUDIO_PATH

`LOCAL_STUDIO_PATH` is an environment variable like `STUDIO_PATH`.  
It allows the user to define an arbitrary directory for SCANeR's user data and configurations.  
Details in the SCANeR studio user manual: `1.5.4.7.5. Set LOCAL_STUDIO_PATH variable`.

> The Samples Pack goes into `%LOCAL_STUDIO_PATH%/SCANeR-Samples-Pack-2022/`

* In windows, create a folder anywhere (e.g.: `D:/SCANeR_data/`).
* Find `Edit the system environment variables` or `Edit environment variables for your account`
* Add the environment variable `LOCAL_STUDIO_PATH` with full absolute path to your folder (e.g.: `D:\SCANeR_data`).

### Set up the Git local repo

* Open directory `%LOCAL_STUDIO_PATH%`
* `Right click > Git Bash here`
* Clone the repository:
```
git clone https://github.com/AVSimulation/SCANeR-Samples-Pack.git SCANeR-Samples-Pack-2022
```
* When prompted, login to GitHub with the account linked to your company e-mail.
* *Downloading can take a few minutes.*
* Update your local working tree:
```
cd SCANeR-Samples-Pack-2022
git checkout 2022
```

### Git hook for configuration.cfg

```
git config core.hooksPath "./samples-pack-utils/hooks/"
```
Now every time you checkout a branch, the Samples Pack configuration paths will be automatically be added to `%STUDIO_PATH%/configurations.cfg`  

### Prepare for contribution

The remote repository will need to know who makes a contribution.
```
git config --global user.email "name.surname@avsimulation.fr"
git config --global user.name "Name Surname"
```

## 3. Publish a modification

### Before modifying, get the latest files

Make sure that you are on a working branch (e.g. `2022`) with a valid uplink (e.g. `origin/2022`).
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
git commit -m "Replaced some Simulink block"
```
Parameter "-m" is the commit message that helps everyone know what you did.

### Push

When you finished doing the modification and the Samples Pack works, push the branch to the GitHub server.
```
git push
```
If you get rejected, see next section.

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

### Diff tool

The diff tool helps visualize the current modifications.

* Install [Meld](https://meldmerge.org/) or [WinMerge](https://winmerge.org/)
* Apply in Git Bash (once and for all)
  * For Meld
  ```
  git config --global diff.tool meld
  git config --global difftool.meld.path "C:\Program Files (x86)\Meld\Meld.exe"
  git config --global difftool.prompt false

  git config --global merge.tool meld
  git config --global mergetool.meld.path "C:\Program Files (x86)\Meld\Meld.exe"
  git config --global mergetool.prompt false
  ```
  * For WinMerge
  ```
  git config --global diff.tool winmerge 
  git config --global difftool.winmerge.path 'C:\Program Files (x86)\WinMerge\WinMergeU.exe'
  git config --global difftool.prompt false

  git config --global merge.tool winmerge 
  git config --global mergetool.winmerge.path 'C:\Program Files (x86)\WinMerge\WinMergeU.exe'
  git config --global mergetool.prompt false
  ```

Now check your pending modifications ...
```
git difftool --dir-diff
```
... or the difference between two commits or branches
```
git difftool --dir-diff 2022 2021.2
```

## 4. Release (obsolete - to be updated)

The [SCANeR User Guides](https://avsguichet.github.io/Samples-Pack/) website links to the latest release of the Samples Pack.

* Prepare the ZIP
  * Go to the [latest commit on GitHub](../../tree/2022)
  * Download as a ZIP: `Code` > `Download as ZIP`  
  The ZIP includes a root folder `Samples-Pack-2022` that we don't want.
  * Create a new ZIP with `APIs/`, `bin/`, `config/` etc... at the root  
  Name of the new ZIP: `Samples-Pack-<latest major SCANeR release>r<Samples Pack sub-version>` (e.g. `Samples-Pack-2022r1`)
* ~~Create a Release on GitHub~~
  * ~~Go to the [repository releases page](../../releases)~~
  * ~~Button `Draft a new release`~~
    * ~~Target = `<latest major SCANeR release>` (e.g. `2022`)~~
    * ~~Tag = `<latest major SCANeR release>r<Samples Pack sub-version>` (e.g. `2022r1`)~~
    * ~~Title = `Samples Pack <Samples Pack version>` (e.g. `Samples Pack 2022r1`)~~
    * ~~Description of changes included in this release (optional)~~
    * ~~Attach binaries = Drag & drop the new ZIP in the "Attach binaries" area~~
  * ~~Button `Publish release`~~
* Send the ZIP to the FTP server `stockage.scanersimulation.com` using FileZilla
  * `(root)/Evaluation/2022/Samples-Pack-2022.zip`
* Update the link
  * Go to the SCANeR Guides repository and [edit `_config.yml`](../../../SCANeR-User-Guides/edit/Published/_config.yml).
  * Change the `zip_url:` path to the newly uploaded ZIP URL
