open TextIO;
use "Assignment1.lex.sml";
open Assignment1Lex;
open UserDeclarations;
val lexer = makeLexer( fn n => valOf(inputLine( stdIn ) ));
(*val lexer = makeLexer( fn n => valOf(inputLine( TextIO.openIn("pokemon.txt") ) ));*)
lexer();