- [Helpful command line commands](#helpful-command-line-commands)
  - [`export` -- hide working directory](#export----hide-working-directory)
  - [`more` -- reading text](#more----reading-text)
  - [`less` -- reading text conveniently](#less----reading-text-conveniently)
  - [`wc` -- word count](#wc----word-count)
  - [`grep` -- search for PATTERNS in each FILE](#grep----search-for-patterns-in-each-file)
  - [`|` -- translate input outputs](#----translate-input-outputs)
  - [`sleep N` -- do nothing for N seconds](#sleep-n----do-nothing-for-n-seconds)
  - [`yes` -- Infinitely output a line with all specified STRING(s), or 'y'.](#yes----infinitely-output-a-line-with-all-specified-strings-or-y)
  - [`head` -- print first 10 lines of input into standard output](#head----print-first-10-lines-of-input-into-standard-output)
  - [`2>` -- retranslate errors stream into file](#2----retranslate-errors-stream-into-file)


# Helpful command line commands

## `export` -- hide working directory

Usually command line looks like this:
```sh
user@system:/folder1/folder2/folder3/folder4$ # and here you type commands
```

To shorten this printing path use this:
```sh
export PS1='$ '
```
Instead of `$ `, you can type any text, even emoji

Now it looks just like this:
```sh
$ # here you type commands
```

You can always check working directory via `pwd`

Also before changing this prompt you can display current settings with `echo "$PS1"`, so you always can return previous formating:
```sh
-bash-5.1$echo "$PS1"
\s-\v\$
```

This command will make yellow dollar sign: 
```sh
export PS1='\e[0;33m$ \e[m'
```

For more customization:
1. https://askubuntu.com/questions/16728/hide-current-working-directory-in-terminal
2. https://www.cyberciti.biz/tips/howto-linux-unix-bash-shell-setup-prompt.html
3. https://www.cyberciti.biz/faq/bash-shell-change-the-color-of-my-shell-prompt-under-linux-or-unix/

## `more` -- reading text

```sh
more t.txt # read file t.txt line by line
# type 'h' for more commands
# type 'q' to quit more
# can't go backwards to read previous lines
```

## `less` -- reading text conveniently

```sh
less t.txt # more convenient program to read text
# type 'h' for less commands
# type 'q' to quit less
```

## `wc` -- word count

```sh
wc t.txt
  393  2095 25919 t.txt
  # 393 lines, 2095 words, 25919 bytes

wc t.txt -w # words
2095 t.txt

wc t.txt -l # lines
393 t.txt

wc t.txt -m # symbols
16072 t.txt
```

## `grep` -- search for PATTERNS in each FILE

Usage: grep [OPTION]... PATTERNS [FILE]...

Patterns are regular expressions

```sh
grep Romeo 100.txt.utf-8
# prints out all lines in the file "100.txt.utf-8" which contain string "Romeo"
```

## `|` -- translate input outputs

"Pipe" `|` translates **standard output** of program to the *left* into **standard input** of program to the *right*:
```sh
<program 1> | <program 2>
```

It can be done iteratively:
```sh
<program 1> | <program 2> | <program 3>
```

Usage example:

```sh
grep Romeo 100.txt.utf-8 | grep Juliet
# prints all lines which contain both "Romeo" and "Juliet"
```

```sh
grep Romeo 100.txt.utf-8 | grep Juliet | wc -l
# prints number of lines which contain both "Romeo" and "Juliet"
```

## `sleep N` -- do nothing for N seconds

```sh
sleep 1 # do nothing for 1 second
sleep 2 # do nothing for 2 seconds
sleep 3 # do nothing for 3 seconds
```

## `yes` -- Infinitely output a line with all specified STRING(s), or 'y'.

```sh
$ yes # result below
y
y
y
y
y
y
y
...
```

## `head` -- print first 10 lines of input into standard output

Usage: head [OPTION]... [FILE]...

Print the first 10 lines of each FILE to standard output.

With more than one FILE, precede each with a header giving the file name.

With no FILE, or when FILE is -, read standard input.

```sh
$ yes | head
y # 1
y # 2
y # 3
y # 4
y # 5
y # 6
y # 7
y # 8
y # 9
y # 10
$ 
# kernel killed programm 'yes' when there's no one left who could read it
```

## `2>` -- retranslate errors stream into file

```sh
$ grep Romeo 100.txt.utf-8 Juliet >Romeo.txt 2>errors.txt
$ ls
README.md  Romeo.txt  args  args.c  errors.txt  t.txt
$ cat Romeo.txt 
$ cat errors.txt 
grep: 100.txt.utf-8: No such file or directory
grep: Juliet: No such file or directory
$ 
```

Command `2>&1` retranslates error stream to the same file where standard output goes. So both errors and correct output of programs will be in the same file
```sh
$ grep Romeo 100.txt.utf-8 Juliet >Romeo.txt 2>&1
$ ls
README.md  Romeo.txt  args  args.c  errors.txt  t.txt
$ cat Romeo.txt
grep: 100.txt.utf-8: No such file or directory
grep: Juliet: No such file or directory
$ cat errors.txt 
grep: 100.txt.utf-8: No such file or directory
grep: Juliet: No such file or directory
$
```
