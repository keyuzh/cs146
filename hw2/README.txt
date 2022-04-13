2)  cx(1)
    USAGE: cx FILE...
    Adds the "x" permission to the given files. That is, the execute permission 
    for files; and query/cd permission for directories.

    How it works: It simply calls "chmod +x" to all given arguments

3)  nf(1)
    USAGE: nf
    Counts the number of files in the current directory

    How it works: It calls "ls -1" which displays every file in the current 
    directory, one per line, without headings. Then pipe the output to wc(1) to
    count then number of lines.

4)  lss(1)
    USAGE: lss
    List all the file in currect directory in decreasing size order.

    How it works: It simply calls "ls -lS", then pipe its output to tail(1)
    with argument "-n +2" to get rid of first line of "total xxx"
    
5)  whoson(1)
    USAGE: whoson
    Display a sorted list of unique undergrads logged in the current machine,
    that is, students with multiple terminal instances are only displayed once.

    How it works:
    First, we use users(1) to get list of currently logged in users.
    Then use the output as the argument for groups(1) to get the groups that 
    each user is in.
    Then pipe the output to grep(1) to filter only the undergrads. 
    Then pipe output to cut(1) to cut the list of groups and only leave 
    usernames. 
    Then use sort(1) with option -u to sort the usernames and remove duplicates.
    Finally, echo(1) the output so everything is on one line.

6)  howmany(1)
    USAGE: howmany
    Display number of unique undergrads logged in the current machine,
    that is, students with multiple terminal instances are only counted once.

    How it works: calls whoson(1) and use wc(1) to count the number of usernames
    displayed.

7)  valid(1)
    USAGE: valid STRING
    Shows whether the given STRING is a valid shell variable name.

    How it works: We knows that shell variable name must begin with an 
    alphabetic charater or underscore('_'), followed by any number of 
    alphanumeric charaters or underscores. Therefore, we use grep(1) to match 
    the given string with a regular expression which defines this rule.

8)  prargs(1)
    USAGE: prargs [ARGUMENT]...
    Displays a numbered list of arguments.

    How it works: It uses a for loop to loop through the arguments.
    In each iteration, uses printf(1) to format the output as specified.
    