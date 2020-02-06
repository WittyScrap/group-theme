# Suicidal Hero

A game about a robot built by two evil scientists with the intention of *destroying the planet*. The robot overhearing their evil plans decides to not want to be a part of it, and decides to dedicate his efforts entirely to preventing their tests on your abilities to perform tasks from succeding, by finding every possible way to die in every single Test Chamber. *The goal of the game is to complete the given test chambers by killing yourself in every single Chamber*. Finishing the Test Chambers "correctly", by finishing the tasks as indicated by the evil scientists, is possible; but will yield a bad ending.

## Details:
* The game view will be a Perspective/Orthoghonal 3D top-down view, with the ability to pan and rotate the camera around entire levels.
* Levels can be completed successfully (by dying) or unsuccessfully (by winning).
* The main character is a Robot.
* The setting will be a testing chamber/lab room and adequate props.
* Ways of death will be limited, but there will be tricks that will require some thinking to be resolved.
  1. For example, a trampoline over an otherwise obvious drop-to-your-death spot that needs to be moved somehow.
  2. Or an anti-gravity section that can be exploited by shooting yourself up to the roof.

-------------------------------

# How to use this repository

There have been a few changes to the way this repository needs to be handled to function correctly.<br/>
The details for this have been listed below.

## First set-up

1. Head over to the [GitHub Desktop](https://desktop.github.com/) download page.
2. Download GitHub Desktop, install it, and log in using your GitHub credentials.
3. Under File, select Clone repository.
4. Select WittyScrap/group-theme from the repositories list.
5. Clone the repository in a directory of your choice (or just leave it to the default value).
6. In the "Current branch" dropdown, select the branch that is most appropriate for your needs. Please make sure that you only use your assigned branch. After switching branches a small loading sequence may happen where the new assets are fetched, allow for that to finish.
7. Head over to where the repository has been cloned, locate the .uproject file and open it (MAKE SURE YOU SELECT UE 4.22.3).
8. You will be prompted to rebuild the project, it will notify you that the project may have been built using a different version of the engine, this is not the case: it simply cannot find the compiled C++ classes that were introduced in the project. Allow the engine to rebuild the project.
9. The project will now be open, and can be used as normal.

## Checking-out (AKA. What to do to synchronise your project with this online repository)

Note: you do not need to do this if you have just finished the First set-up.

1. Close any instance of the UE4 editor.
2. Open GitHub Desktop.
3. In the Changes tab on the right-hand side of the window, check if there are any pending changes.
  * If there are:
    1. Type a message in the Summary/Description fields.
    2. Click on Commit <your-branch-name>
4. Click on Repository, then on Pull.
5. Wait for any changes to your remote to be received.
6. You may now open the UE4 editor once again, provided no merge conflicts happened.
  
## Checking-in (AKA. What to do to push all your work and changes to this online repository)

1. Open GitHub Desktop.
2. Select the Changes tab on the right-hand side of the window.
3. Type a message in the Summary/Description fields.
4. Click on Commit <your-branch-name>.
5. Click on Repository, then on Pull.
6. Wait for any changes to your remote to be received.
7. Click on Repository, then on Push.
8. Wait for your commits to be uploaded.
