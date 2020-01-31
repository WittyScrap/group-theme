# Generic computer-y game

Game where you play as an antivirus fighting a virus on a computer, whilst a different player uses the computer to guide the antivirus player.
Antivuris player is VR.

VR player alias: Antivirus<br>
2D player alias: User

## Details

* Emissive and dark constrast as a general theme
* Cute/innocent looking viruses turning into monsters?
* RAM page swaps = rooms swapping in and out
* Virus that jumps on you if you don't kill it quickly enough and forces you to write some code before a time expires
* ~~Coop?~~
* Asymmetric multiplayer: person at computer that knows where everything is and player that can take action.
* Different weapons for different viruses using colour codes
* RGB RAINBOW GUN
* User provides Antivirus with different weapons on request
* Unlimited bullets
* Weapon cooldown: CPU usage full
* Drawbacks TBD
* More actions for User

## This repository
Instructions on how to use and maintain the repository

### Download the project for the first time
* Head over to the GitHub desktop download page (https://desktop.github.com/)
* Download GitHub desktop, open it, login with your GitHub account when prompted
* Select File -> Clone repository
* If you cannot locate the `group-theme` repository from the GitHub repositories list, click on URL
* Write `WittyScrap/group-theme` in the URL field
* Select the local path in which you wish to store the UE4 project
* Clone the repository
* Change the current branch from master to the most appropriate for whichever task you will perform
* Head into the project directory and open the .uproject file from there, alternatively start UE4 (v4.22.3) and locate the project from the open menu within it

The following steps _may not_ be necessary, but should be followed anyway just for safety.

* In the Unreal editor, select the Source Control menu from the toolbar
* Select "Connect to source control"
* Select GitHub, enter https://github.com/WittyScrap/group-theme.git in the URL field

### Commit a change you have made locally
Before a change gets synchronized back to this repository, it will be made into a local "commit". Commits are simply a list of changes that you have made to the project locally.<br>
To check in changes locally:

* In the Unreal editor, select the Source Control menu from the toolbar
* Select the Submit to source control option
* Enter a message describing what changes you have made
* Submit

### Pushing your recent local commits to the online repository
Committing locally does not alter this online repository, to do so:

* Open GitHub desktop
* Ensure the Current Repository is set to be the correct one
* Select the Publish changes option on the toolbar
* If any merge conflicts ensue, they will need to be discussed

### Refresh your local repository with any new changes in the remote repository
From within GitHub desktop, select Repository -> Pull
