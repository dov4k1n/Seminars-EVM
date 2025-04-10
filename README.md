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
  - [Multiple Windows](#multiple-windows)
  - [Multiple Tabs](#multiple-tabs)
  - [File System Explorer](#file-system-explorer)
  - [History](#history)
  - [Help](#help)
  - [Save and Exit](#save-and-exit)

# Download folder from this repository
https://download-directory.github.io/

# Linux command line commands

You can add the `--help` flag to all commands to learn how to write them  
correctly and what else they can do.

```sh
clear                 # clear command line


history               # display the history list
history 5             # display last 5 commands
history N             # display last N commands


ls                    # list files inside current folder
ls folder             # list files inside 'folder'
ls folder/subfolder   # list files inside 'folder/subfolder'


pwd                   # print working directory
cd                    # change directory
cd folder             # go to 'folder'
cd folder/subfolder   # go to 'folder/subfolder'
cd ..                 # go to previous folder


touch                 # create empty file
touch file.txt        # create empty file called 'file.txt'
touch main.c          # create empty file called 'main.c'


echo                  # Write arguments to the standard output.
echo hello            # Write "hello" to the standard output
help echo             # Get info about 'echo' command
echo "hi" >file.txt   # create file.txt and write "hi" inside it
<program> >file.txt   # write standard output of <program> into file.txt
<program> <file.txt   # use file.txt as standard input for <program>


cat                   # concatenate to standart output
cat file.txt          # print content of 'file.txt'
cat a.txt b.txt       # print contents of 'a.txt' and 'b.txt' concatenated


mkdir                 # make directory
mkdir dir             # make directory called 'dir'
mkdir dir/subdir      # make directory called 'subdir' inside 'dir'


rm                    # remove file(s)
rm file.txt           # remove file called 'file.txt'
rmdir                 # remove directory(ies), if empty
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
set number            " display line numbers
set colorcolumn=80    " colorize 80th column
set list              " display hidden characters (end of line, tab, etc.)

set expandtab         " replace tabs with spaces
set tabstop=4         " tab size in spaces
set softtabstop=4     " backspace size in spaces (for tabs)
set shiftwidth=4      " shift size in spaces (`>>` command)

set cindent           " auto indentation for C language

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
* `i` -- enter Insert Mode (**before** cursor).
* `a` -- enter Insert Mode (**after** cursor).
* `o` -- enter Insert Mode (on a new line **under** cursor).
* `I` -- enter Insert Mode (at the **beginning** of line).
* `A` -- enter Insert Mode (at the **end** of line).
* `O` -- enter Insert Mode (on a new line **above** cursor).
* `v` -- enter Visual Mode.
* `:` -- enter Command Mode.
* `Esc` -- return to Normal Mode.


## Navigation

Effective navigation is the key to fast work with Vim.

**Basic navigation**:
* `h` -- left.
* `l` -- right.
* `j` -- down.
* `k` -- up.

Hint: `h` is on the left, `l` is on the right, `j` looks like down arrow.

**View**:
* `zz` -- **center** current line.
* `:set so=999` -- keep cursor **centered on scroll**.
* `Ctrl` + `e` -- move **screen up** one step.
* `Ctrl` + `y` -- move **screen down** one step.
* `Ctrl` + `u` -- move screen & cursor up 1/2 page.
* `Ctrl` + `d` -- move screen & cursor down 1/2 page.
* `zt` -- move current line to the top of the screen.
* `zb` -- move current line to the bottom of the screen.
* `Ctrl` + `f` -- **page down**.
* `Ctrl` + `b` -- **page up**.

**File navigation**:
* `gg` -- move to the **top** of the file.
* `G` -- move to the **bottom** of the file.
* `number` + `G` -- move to line `number`.
* `Ctrl` + `g` -- show file status.

**Quick transitions**:
* `0` -- start of line.
* `$` -- end of line.
* `^` -- first word of line.
* `w` -- next start of word.
* `e` -- next end of word.
* `b` -- previous start of word.
* `W` -- next start of word (whitespace-delimeted).
* `E` -- next end of word (whitespace-delimeted).
* `B` -- previous start of word (whitespace-delimeted).


## Text editing

**Delete**:
* `x` -- delete character at cursor.
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
1. Enter Visual Mode (`:v`).
2. Select lines (`j` or `k`).
3. Press `y` to copy or `d` to cut.
4. Press `p` to paste after cursor or `P` to paste before cursor.


## Search and replace

**Search**:
* `/text` -- find "text" (`n` move to next occurence, `N` move to previous).
* `:noh` -- to disable highlighting.

**Replace**:
* `:s/old/new` -- replace first occurence of "old" into "new" on current line.
* `:s/old/new/g` -- replace all occurences of "old" into "new" on current line.
* `:%s/old/new/g` -- replace all occurences in entire file.
* `:%s/old/new/gc` -- same, but with confirmation of each replace.


## Multiple Windows

**Split**:
* `:split` or `Ctrl` + `w` + `s` -- split horizontally.
* `:vsplit` or `Ctrl` + `w` + `v` -- split vertically.
* `:hide` -- close current window.
* `:only` -- keep only this window open.

**Move**:
* `Ctrl` + `w` + `arrow` -- move cursor at window.
* `Ctrl` + `w` + `Ctrl` + `w` -- move cursor to another window cyclic.

**Resize**:
* `Ctrl` + `w` + `+` -- **increase height** of window.
* `Ctrl` + `w` + `>` -- **increase width** of window.
* `Ctrl` + `w` + `-` -- **reduce height** of window.
* `Ctrl` + `w` + `<` -- **reduce width** of window.
* `num` + above -- increase/reduce by `num`.
* `Ctrl` + `w` + `_` -- expand horizontally.
* `Ctrl` + `w` + `|` -- expand vertically.
* `Ctrl` + `w` + `=` -- make all equal size.

**Other files**:
* `:e filename` -- edit another file in current window.
* `:split filename` -- split horizontally and load another file.
* `:vsplit filename` -- split vertically and load another file.
* `:ls` -- show current buffers (opened files history).
* `:b 2` -- open buffer #2 in current window.


## Multiple Tabs

**Open**:
* `vim -p file1 file2 file3` -- open each file in separate tabs.
* `:tabedit` or `:tabe filename` -- open file in a new tab.
* `:tabclose` or `:tabc` -- close current tab.
* `:tabonly` or `:tabo` -- close all other tabs.
* `Ctrl` + `w` + `T` -- open current split window in new tab.

**Move**:
* `gt` -- next tab.
* `gT` -- prior tab.
* `:tabfirst` -- jump to first tab.
* `:tablast` -- jump to last tab.
* `num` + `gt` -- open tab `num`.
* `:tabmove num` -- move current tab to position `num`.
* `:tabmove` -- move current tab to the end.

**Search**:
* `:tabfind filename` -- search and open file in new tab.
* `:tabs` -- view summary of open tabs.

**Refactor**:
* `tabdo %s/foo/bar/g` -- replace "foo" into "bar" in all open tabs.


## File System Explorer

* `:Sex` -- split & explore current file's directory :-)
* `:Vex` -- vertical split & explore.
* `:Tex` -- tab & explore.
* `:Ex` -- explore.


## History

* `:history` -- show history of commands.


## Help

* `:help` -- open vim's main help file.
* `:help <command>` -- open help on a specific command.


## Save and Exit

* `:w` -- save file.
* `:q` -- exit vim.
* `:wq` or `ZZ` -- save and exit vim.
* `:q!` -- exit without save.
* `:w a.txt` -- save in a new file 'a.txt', if it does not exist yet.
