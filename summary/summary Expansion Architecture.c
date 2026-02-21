//! Expansion Architecture
/*
    ? what will we do ?
        ~ we will take a linkedlist from tokens
        // each token has :
            * type
            * value (string)
        $ we will edit ONLY the value field

    ? what is the meaning of expansion ?
        % replace $VAR with its value from env
        % replace $? with last exit status

    ? where does it happen ?
        ~ after lexer
        ~ before parser

    ? golden rules :
        ^ inside double quotes  : YES (expand)
        ^ without quotes        : YES (expand)
        ^ inside single quotes  : NO  (do NOT expand)

    ? how will it work ?
        ~ we walk through the string char by char
        ~ we track quote state :
            * in_single
            * in_double
        ~ when we see '$' AND we are NOT inside single quotes
            -> extract variable name
            -> get value from env
            -> append value to result
        ~ otherwise
            -> copy character as it is

    ? variable name rules :
        ~ must start with letter or '_'
        ~ can contain letters, digits, '_'
        ~ $? is a special case
        ~ if '$' is alone or invalid -> keep it as normal char

    ? edge cases :
        1) echo $USER
            -> echo <value_of_USER>

        2) echo "$USER"
            -> echo "<value_of_USER>"

        3) echo '$USER'
            -> echo '$USER'   (no expansion)

        4) echo $USER$HOME
            -> echo <value_of_USER><value_of_HOME>

        5) echo $
            -> echo $

        6) echo $NOTEXIST
            -> echo ""   (empty string)

        7) echo $?
            -> echo <last_exit_status>
*/
