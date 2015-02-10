datatype lexresult = DIV | EOF | EOS | ID of string | LPAREN | NUM of int | PLUS | PRINT | RPAREN | SUB | TIMES

val linenum = ref 1
val error = fn x => TextIO.output(TextIO.stdOut,x ^ "\n")
val eof = fn () => EOF

%%
%structure CalcLex

%%
[\ \t] => (lex());
"/"   => (DIV);
";"   => (EOS);
"("   => (LPAREN);
[0-9]+ => (NUM (revfold (fn(a,r)=>ord(a)-ord(#"0")+10*r) (explode yytext) 0));
")"   => (RPAREN);
"+"   => (PLUS);
[A-Za-z]+ => (if yytext="print" then PRINT else ID yytext);
"-" => (SUB);
"*" => (TIMES);
. => (error ("calc: ignoring bad character " ^yytext); lex());