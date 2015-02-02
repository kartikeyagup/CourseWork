datatype keyword = LET | IF | THEN | ELSE | END

datatype lexresult = NUM of int 						(*To fix*)
	| BOOLEAN of bool 									(*To fix *)
	| FLOAT of real 									(*TODO*)
	| STRING of string 									(*TODO*)
	| LPAREN 											(*TODO*)
	| RPAREN											(*TODO*)
	| ARITHMETIC 										(*TODO*)
	| COMPARATOR										(*TODO*)
	| CONNECTIVES										(*TODO*)
	| CONCAT											(*TODO*)
	| SUBSTR											(*TODO*)
	| IDENTIFIER of string 								(*TODO*)
	| KEYWORD of keyword 
	| COMMA
	| COLON
	| EOF

val error= fn x => TextIO.output(TextIO.stdOut,x ^ "\n")
val eof = fn () => EOF

%%
%structure Assignment1Lex
%%
(-[1-9][0-9]*|0|[1-9][0-9]*)	=> (NUM (Option.valOf(Int.fromString(yytext))));
"true"|"false"					=> (BOOLEAN (Option.valOf(Bool.fromString(yytext))));
","								=> (COMMA);
":"								=> (COLON);
"if"							=> (KEYWORD (IF));
"let"							=> (KEYWORD (LET));
"then"							=> (KEYWORD (THEN));
"else"							=> (KEYWORD (ELSE));
"end"							=> (KEYWORD (END));
.								=> (error ( "error dound" ) ; lex() );
