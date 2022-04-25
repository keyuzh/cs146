lss(1)
    USAGE: lss [OPTION]... [FILE]...

    Outputs a "ls -l" listing of files, sorted by decreasing byte count.
    It accepts the same options as ls(1), with a few exceptions below.

    -C, -x
        Not accepted, those options requres the output files to be listed by 
        columns.
    -R, --recursive
        Not accepted, sorting by file size cannot work with recursive option
