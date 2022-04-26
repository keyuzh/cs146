NOTE: 
    before running any command below, define an environment variable called
    TRASH as the directory for trashcan. e.g. "~/.trash"

srm(1)
    USAGE: srm [OPTION]... [FILE]...

    Safely removes given files to the trashcan, if a file with same name and
    path already exists, the old file will be replaced. 
    If any option is specified, command uses rm(1) with the given options and 
    recovery will not be possible.

unrm(1)
    USAGE: unrm FILE...
    Recovers given files from the trashcan. If given file(s) does not exist, 
    outputs an error and skip the non-existing file(s).

lsrm(1)
    USAGE: lsrm
    Lists all files that is currently in the trashcan in a "ls -l" manner.

durm(1)
    USAGE: durm
    Displays the current size of trashcan.

trash(1)
    USAGE: trash
    Empties the trashcan, removes all files currently in the trashcan.
