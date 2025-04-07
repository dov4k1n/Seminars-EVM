- [Download folder from this repository](#download-folder-from-this-repository)
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
  - [Pull](#pull)
- [Vim](#vim)
  - [Style](#style)
  - [Modes](#modes)
  - [Navigation](#navigation)
  - [Text editing](#text-editing)
  - [Search and replace](#search-and-replace)
  - [Save and Exit](#save-and-exit)

# Download folder from this repository
https://download-directory.github.io/

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
<program> >file.txt          # write standard output of <program> into file.txt
<program> <file.txt          # use file.txt as standard input for <program>


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
git branch -M main         # rename current branch into "main"
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

## Pull
Fetch from remote
```sh
git pull origin
git pull --no-commit origin # fetch and merge without creating new commit
```

# Vim

> vim – Vi Improved, a programmer's text editor
> 
> It can be used to edit all kinds of plain text. It is especially useful for editing programs
>
> Source: man vim

To learn Vim run `vimtutor` command in Terminal. (30 min)

## Style

To style vim create or edit file named `.vimrc` in your home directory.

Basic configuration commands:
```vim
syntax on             " enable syntax highlighting for various languages
set expandtab         " replace tabs with spaces
set tabstop=4         " tab size in spaces
set softtabstop=4     " backspace size in spaces (for tabs)
set shiftwidth=4      " shift size in spaces (`>>` command)
set cindent           " auto indentation for C language
set number            " display line numbers
set relativenumber    " relative numeration of lines
set cursorline        " highlight current line
set t_Co=256          " display in 256 colors mode, if your terminal supports it

colorscheme elflord   " use 'elflord' colorscheme
```

To view available colorschemes, run the following command inside Vim:
```vim
:colorscheme <Tab>
```

## Modes

Vim works in several modes:
*  Normal Mode: for navigation and commands.
*  Insert Mode: for text editing.
*  Visual Mode: for text selection.
* Command Mode: for executing commands.

**Switching between modes**:
* `i` -- enter Insert Mode (before cursor).
* `a` -- enter Insert Mode (after cursor).
* `o` -- enter Insert Mode (on a new line).
* `v` -- enter Visual Mode.
* `:` -- enter Command Mode.
* `Esc` -- return to Normal Mode.

## Navigation

Effective navigation is a key for fast work with Vim.

**Basic navigation**:
* `h` -- left.
* `l` -- right.
* `j` -- down.
* `k` -- up.

Hint: `h` is on the left, `l` is on the right, `j` looks like down arrow.

**File navigation**:
* Press  `G`  to move you to the bottom of the file.
* Type  `gg`  to move you to the top of the file.
* Hold `Ctrl` key and press `g` to show your location in the file and the file status.
* Type the number of a line and then press `G` to move you to that line.

**Quick transitions**:
* `0` -- to the beginning of the line.
* `$` -- to the end of the line.
* `w` -- to the next word.
* `b` -- to the previous word.
* `e` -- to the end of the current word.
* `Ctrl` + `f` -- page down.
* `Ctrl` + `b` -- page up.

## Text editing

**Delete**:
* `x` -- delete symbol under the cursor.
* `dd` -- delete line.
* `dw` -- delete word.
* `d$` -- delete till the end of line.
* `d0` -- delete till the start of line.
* `d2w` -- delete 2 words after cursor.
* `d3w` -- delete 3 words after cursor. And so on.

**Undo**:
* `u` -- undo last commands.
* `Ctrl` + `r` -- redo last commands (undo the undos).

**Copy and paste**:
* `yy` -- copy line.
* `yw` -- copy word.
* `p` -- paste after cursor.
* `P` -- paste before cursor.

**Replace and Change**:
* `rx` -- replace character at the cursor with 'x'.
* `ce` -- change until the end of word.
* `cc` -- change until the end of line.
* `~` -- change the register of a character at the cursor.
* `.` -- repeat last action.
* `>>` -- shift line right.
* `<<` -- shift line left.

**Copy, Paste and Move multiple lines**:
* Enter Visual Mode (`:v`).
* Select lines (`j` or `k`).
* Press `y` to copy or `d` to cut.
* Press `p` to paste after cursor or `P` to paste before cursor.

## Search and replace

**Search**:
* `/text` -- find "text" (`n` move to next occurence, `N` move to previous).
* `:noh` -- to disable highlighting.

**Replace**:
* `:s/old/new` -- replace first occurence of "old" into "new" on current line.
* `:s/old/new/g` -- replace all occurences of "old" into "new" on current line.
* `:%s/old/new/g` -- replace all occurences in entire file.
* `:%s/old/new/gc` -- same, but with confirmation of each replace.

## Save and Exit

* `:w` -- save file.
* `:q` -- exit vim.
* `:wq` or `ZZ` -- save and exit vim.
* `q!` -- exit without save.

