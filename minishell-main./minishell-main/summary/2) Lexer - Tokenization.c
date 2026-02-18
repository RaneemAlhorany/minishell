//! Lexer / Tokenization

/*
? Purpose:
~ Convert raw user input into a sequence of tokens
~ This is purely a lexical analysis step

? General Idea:
    % Given the input:
        echo "hello world" | cat >> out.txt

    % The lexer produces:
        WORD("echo")
        WORD("hello world")
        PIPE(|)
        WORD("cat")
        REDIRECT_APPEND(>>)
        WORD("out.txt")

    ^ Notes:
        ~ No parsing logic
        ~ No execution
        ~ No syntax validation
        ~ Only splitting input into meaningful tokens

? What the Lexer DOES:
    * Reads input character by character
    * Groups characters into tokens
    * Detects operators and special symbols
    * Handles quotes as grouping mechanisms

? What the Lexer DOES NOT do:
    * Does NOT execute commands
    * Does NOT build command structures
    * Does NOT check logical correctness
    * Does NOT care about command semantics

? Scope:
    $ Supported token types:
        * WORD
        * PIPE            |
        * REDIRECT_IN     <
        * REDIRECT_OUT    >
        * HEREDOC         <<
        * REDIRECT_APPEND >>

    $ Supported syntax elements:
        * Spaces (used as token separators)
        * Single quotes   '...'
        * Double quotes   "..."

? Quotes Handling (Lexer Responsibility):
    * Quotes define token boundaries
    * Content inside quotes becomes ONE token
    * Quotes themselves are not part of the token value
    * No environment expansion here (done later)

    Examples:
        echo "hello world"   -> WORD("hello world")
        echo 'hello $USER'  -> WORD("hello $USER")

? Important Rule:
    ~ Lexer stops at token creation
    ~ Any structural meaning is deferred to the parser


*/
