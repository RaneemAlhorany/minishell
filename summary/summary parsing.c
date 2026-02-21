//!  first step i will de ->
/*
    ? convert the (Token List) into (Simple Command Object)
    ? without support the pipes

    what i will build in this step:
     ~ 1) stracts 
        🔹 Redirection Struct
        🔹 Command Struct
     ~ 2) test :
     ls -la > file.txt
        args[0] = ls
        args[1] = -la
        args[2] = NULL

        redirs:
            type = >
            file = file.txt

*/


Left-Associative tree