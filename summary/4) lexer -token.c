//! Lexer / Token Types – Design Notes
/*
    ~ Why do we need Token Types?
        * Because the lexer does NOT understand the meaning of commands.
        * It only classifies input into categories:
                % this is a WORD
                % this is an OPERATOR
                % this is a PIPE
                % this is a REDIRECTION

        * Which means:
            # type  = identity of the token
            # value = raw textual data

    ~ How do we define the scope?
        $ Supported tokens:
            ? WORD
                * Any textual data
                * Whether written inside quotes or not
            ? Operators
                |   PIPE
                <   REDIRECT_IN
                >   REDIRECT_OUT
                <<  HEREDOC
                >>  REDIRECT_APPEND

    ~ Notes:
        % Quotes affect HOW we read characters,
          but they do NOT change the token type.

    ~ Why enum instead of #define?
        # enum advantages:
            * Clear and readable
            * Easy to debug
            * Type-safe
        % Used across:
            $ Lexer
            $ Parser
            $ Token debugging / printing
*/


//! main structure : t_token
/*
    ? what is t_token ?
        ~ it is the direct output of the lexer
        ~ the lexer reads a raw input string (char *input)
        ~ and converts it into a sequence of tokens
        ~ each token represents a single syntactic unit
          understood only by its appearance, not its meaning

    ? notes :
        # value :
            * stores the text after removing quotes
            * but before any expansion (env, wildcard, etc.)

        # TOKEN_WORD :
            $ may represent :
                * a command name
                * an argument
                * a file name
            $ note :
                * the lexer does NOT distinguish between them

        # quotes :
            $ there is no token type for quotes
            $ quotes only affect how characters are read
*/
