- [Download folder from this repository](#download-folder-from-this-repository)
- [C++ Development Tools](#c-development-tools)
- [Linux command line commands](#linux-command-line-commands)
- [Git](#git)
  - [Init](#init)
  - [Add](#add)
  - [Status](#status)
  - [Commit](#commit)
  - [Branch](#branch)
  - [Merge](#merge)
  - [Log](#log)
  - [Reflog](#reflog)
  - [Reset](#reset)
  - [Remote](#remote)
  - [Push](#push)

# Download folder from this repository
https://download-directory.github.io/

# C++ Development Tools

https://drive.google.com/file/d/1JvYzauQq9o8i2dl23Gt-dIwsiKp8U1-X/view?usp=drive_link

# Linux command line commands

You can add the `--help` flag to all commands to learn how to write them correctly and what else they can do.

```sh
clear      # clear command line


history    # display the history list
history 5  # display last 5 commands
history N  # display last N commands


ls                  # list files inside current folder
ls folder           # list files inside 'folder'
ls folder/subfolder # list files inside 'folder/subfolder'


pwd                 # print working directory
cd                  # change directory
cd folder           # go to 'folder'
cd folder/subfolder # go to 'folder/subfolder'
cd ..               # go to previous folder


touch               # create empty file
touch file.txt      # create empty file called 'file.txt'
touch main.c        # create empty file called 'main.c'


echo                         # Write arguments to the standard output.
echo hello                   # Write "hello" to the standard output
help echo                    # Get info about 'echo' command
echo "hello world" >file.txt # create file.txt and write "hello world" inside it  


cat                    # concatenate to standart output
cat file.txt           # print the content of 'file.txt'
cat file.txt file2.txt # print the contents of 'file.txt' and 'file2.txt' concatenated


mkdir                  # make directory
mkdir folder           # make directory called 'folder'
mkdir folder/subfolder # make directory called 'subfolder' inside 'folder'


rm          # remove file(s)
rm file.txt # remove file called 'file.txt'
rmdir       # remove directory(ies), if empty


vim          # open text editor "vim"
vim file.txt # open 'file.txt' in vim
vim main.c   # open 'main.c' in vim
INSERT       # keyboard button to start typing into file
ESC          # keyboard button to stop typing into file
:q           # exit vim
:q!          # exit vim without saving changes
:w           # save changes in current file
:w file2.txt # save changes in a new file called 'file2.txt' if it doesn't exist yet
:wq          # save changes and exit vim
```

# Git
Git is a *Version Control System (VCS)* - a program for facilitating work with changing information

You can learn it directly in the command line by typing `git --help` or `git <command> --help`, where instead of *\<command\>* is the name of the command you want to learn

You can also google and read Wikipedia or Stack Overflow on a specific problem you want to solve

## Init
Create an empty Git repository or reinitialize an existing one
```sh
git init         # initialize
git init -b main # initialize and rename current branch from 'master' into 'main'
```
## Add
Add file contents to the index
```sh
git add file.txt # start tracking file.txt
git add .        # start tracking all files
```
## Status
```sh
git status # show the working tree status
```
## Commit
Record changes to the repository
```sh
git commit -m "first commit"
```

## Branch
List, create or switch branches
```sh
git branch                 # list all branches and view current branch
git branch <branch name>   # create new branch
git checkout <branch name> # switch to branch
git switch <branch name>   # switch to branch
```

## Merge
Join two or more development histories together
```sh
git merge <branch 1> <branch 2>
```

## Log
View commit logs
```sh
git log
```

## Reflog
View reflog (git changes)
```sh
git reflog
```

## Reset
Reset current HEAD to the specified state
```sh
git reset --hard dc1ff05 # example
```

## Remote
```sh
git remote add origin https://github.com/dov4k1n/Seminars-EVM.git
```

## Push
Update remote
```sh
git push -u origin main
git push -u origin <branch name>
```