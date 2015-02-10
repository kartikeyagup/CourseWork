open TextIO;
use "math.lex.sml";
open CalcLex;
open UserDeclarations;
val lexer = makeLexer( fn n => valOf(inputLine( stdIn ) ));