datatype keyword = LET | IF | THEN | ELSE | END
datatype substr = SINGLE of int | BOUNDED of int*int
datatype operator= ADD| MUL | SUB | POW | DIV | MOD | ABS
datatype boolean = AND | OR | NOT
datatype compare = LESSTHAN| EQUALTO | LESSTHANEQUAL | GREATERTHANEQUAL | GREATERTHAN |NOTEQUAL
datatype lexresult = NUM of int
	| BOOLEAN of bool
	| FLOAT of real
	| STRING of string
	| LPAREN
	| RPAREN
	| ARITHMETIC of operator
	| COMPARATOR of compare
	| CONNECTIVES of boolean
	| CONCAT
	| SUBSTR of substr
	| IDENTIFIER of string
	| KEYWORD of keyword
	| COMMA
	| COLON
	| EOF

val error		= fn x 	=> TextIO.output(TextIO.stdOut,x ^ "\n")
val eof 		= fn () => EOF;
fun getlim(x)   = if (hd(x)= #".") then 0 else 1 + getlim(tl(x));
val splitter 	= fn x 	=> let val lim = getlim (explode(x))  in  (Option.valOf(Int.fromString(String.substring(x,1,lim-1))),Option.valOf(Int.fromString(String.substring(x,lim+2,String.size(x)-lim-3)))) end;

%%
%structure Assignment1Lex
%%
("~"[1-9][0-9]*|0|[1-9][0-9]*)"\."([0-9]*[1-9]|0)("E"("~"[1-9][0-9]*|0|[1-9][0-9]*))?		
																				=> (FLOAT (Option.valOf(Real.fromString(yytext))));
("~"[1-9][0-9]*|0|[1-9][0-9]*)													=> (NUM (Option.valOf(Int.fromString(yytext))));
["\""][^"\""]*["\""]															=> (STRING (String.substring(yytext,1,size(yytext)-2)));
("~0"|"~"?0[0-9]+)																=> (error ("Bad token int: " ^yytext) ; lex());
[0-9"\.""~"]+"E"("~"?0[0-9]+|"~0")?												=> (error ("Bad token real right: " ^yytext) ; lex());	
("~0"|"~"?0[0-9]+)?("\."[0-9"~"]*)?("E"["~"0-9]*)?								=> (error ("Bad token real left l: " ^yytext) ; lex());
[0-9"~"]*"\."?("~"[0-9]*|"~"?0[0-9]*|[0-9]*[1-9][0]*)*("E"["~"0-9]*)?			=> (error ("Bad token real left r: " ^yytext) ; lex());
"true"|"false"																	=> (BOOLEAN (Option.valOf(Bool.fromString(yytext))));
"and"																			=> (CONNECTIVES (AND));
"or"																			=> (CONNECTIVES (OR));
"not"																			=> (CONNECTIVES (NOT));
","																				=> (COMMA);
":"																				=> (COLON);
"("																				=> (LPAREN);
")"																				=> (RPAREN);
"/"																				=> (ARITHMETIC (DIV));
"%"																				=> (ARITHMETIC (MOD));
"*"																				=> (ARITHMETIC (MUL));
"abs"																			=> (ARITHMETIC (ABS));
"pow"																			=> (ARITHMETIC (POW));
"-"																				=> (ARITHMETIC (SUB));
"+"																				=> (ARITHMETIC (ADD));
"\^"																			=> (CONCAT);
"<>"																			=> (COMPARATOR (NOTEQUAL));
"<="																			=> (COMPARATOR (LESSTHANEQUAL));
">="																			=> (COMPARATOR (GREATERTHANEQUAL));
"<>"																			=> (COMPARATOR (NOTEQUAL));
">"																				=> (COMPARATOR (GREATERTHAN));
"<"																				=> (COMPARATOR (LESSTHAN));
"="																				=> (COMPARATOR (EQUALTO));
"\["[0-9]+"...\]"																=> (SUBSTR (SINGLE(Option.valOf(Int.fromString(String.substring(yytext,1, String.size(yytext) -3))))));
"\["[0-9]+".."[0-9]+"\]"														=> (SUBSTR (BOUNDED(splitter yytext)));
"if"																			=> (KEYWORD (IF));
"let"																			=> (KEYWORD (LET));
"then"																			=> (KEYWORD (THEN));
"else"																			=> (KEYWORD (ELSE));
"end"																			=> (KEYWORD (END));
[a-z|A-Z][a-z|0-9|A-Z|\'|\_]*													=> (IDENTIFIER (yytext));
[\ \t\n]																		=> (lex());
.																				=> (error ( "error found at " ^ yytext ) ; lex() );