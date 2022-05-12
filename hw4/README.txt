NOTE: 
    before running srm/unrm/trash, define an environment variable called
    TRASH which is used as a global trash to keep track of the location of local
    trash cans. e.g. "~/.globaltrash"
    OPTIONAL: define an environment variable EVERY for the "every" program

C-interp
    when called through a soft link e.g. foo, compile foo.c and execute it with
    any given arguments. Any executables created will be removed afterwards.

build:
    running "make" will use the given Makefile to build all programs,
    to build a specific program, run "make [program]" e.g. make every

every
    USAGE: every [-N,M] [FILE]...
    prints M lines out of every N. 
    details on options can be found at https://www.ics.uci.edu/~wayne/courses/cs146/a4.txt

srm
    USAGE: srm FILE...
    Safely removes given files to the trashcan, if a file with same name and
    path already exists, the old file will be replaced. 

unrm
    USAGE: unrm FILE...
    Recovers given files from the trashcan. If given file(s) does not exist, 
    outputs an error and skip the non-existing file(s).

trash
    USAGE: trash
    Empties the trashcan, removes all files currently in the trashcan.
