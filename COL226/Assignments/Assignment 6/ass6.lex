structure Tokens = Tokens

type pos = int
type svalue = Tokens.svalue
type ('a,'b) token = ('a,'b) Tokens.token
type lexresult= (svalue,pos) token

val pos = ref 1
fun eof () = Tokens.EOF(!pos,!pos)
fun error (e,l : int,_) = TextIO.output (TextIO.stdOut, String.concat[
	"line ", (Int.toString l), ": ", e, "\n"
      ])
fun atoi s = case Int.fromString s of SOME num => num | NONE => 0;
fun readReal s =case (Real.fromString s) of SOME r => r | NONE => 0.0;

%%
%header (functor CalcLexFun(structure Tokens: Calc_TOKENS));
caps=[A-Z];
small=[a-z];
alpha=[A-Za-z];
digit=[0-9];
ws = [\ \t];
%%
\n       							=> (pos := (!pos) + 1; lex());
{ws}+    							=> (lex());
{digit}+ 							=> (Tokens.INT((atoi yytext), !pos, !pos));
([1-9][0-9]*|0|[0]*[1-9][0-9]*) 	=> (Tokens.INT(atoi yytext,!pos,!pos));
([1-9][0-9]*[.][0-9]*[1-9]*|[0]*[.][0-9]*[1-9]|0.0) 
									=> (Tokens.REAL ((readReal yytext),!pos,!pos));
"false"  							=> (Tokens.BOOL(false,!pos,!pos));
"true"  							=> (Tokens.BOOL(true,!pos,!pos));
"->"  								=> (Tokens.GOESTO(!pos,!pos));
"fn"      							=> (Tokens.FN(!pos,!pos));
"="       							=> (Tokens.ASSIGN(!pos,!pos));
"=="      							=> (Tokens.EQUAL(!pos,!pos));
"!="      							=> (Tokens.NOTEQUAL(!pos,!pos));
"<"       							=> (Tokens.LESSERTHAN(!pos,!pos));
">"       							=> (Tokens.GREATERTHAN(!pos,!pos));
"let"     							=> (Tokens.LET(!pos,!pos));
"in"      							=> (Tokens.IN(!pos,!pos));
"local"   							=> (Tokens.LOCAL(!pos,!pos));
"end"     							=> (Tokens.END(!pos,!pos));
"if"      							=> (Tokens.IF(!pos,!pos));
"then"    							=> (Tokens.THEN(!pos,!pos));
"else"    							=> (Tokens.ELSE(!pos,!pos));
"fi"      							=> (Tokens.FI(!pos,!pos));
","       							=> (Tokens.COMMA(!pos,!pos));
"+"       							=> (Tokens.PLUS(!pos,!pos));
"-"       							=> (Tokens.SUB(!pos,!pos));
"*"       							=> (Tokens.MUL(!pos,!pos));
"/"       							=> (Tokens.DIV(!pos,!pos));
"("       							=> (Tokens.LPAREN(!pos,!pos));
")"       							=> (Tokens.RPAREN(!pos,!pos));
"or"      							=> (Tokens.OR(!pos,!pos));
"["									=> (Tokens.BOXLPAREN(!pos,!pos));
"]"									=> (Tokens.BOXRPAREN(!pos,!pos));
":"									=> (Tokens.COLON(!pos,!pos));
"and"      							=> (Tokens.AND(!pos,!pos));
";"       							=> (Tokens.SEMI(!pos,!pos));
"\."	 							=> (Tokens.DOT(!pos,!pos));
{alpha}+							=> (Tokens.IDEN(yytext,!pos,!pos));
"."		 							=> (error ("ignoring bad character "^yytext,!pos,!pos); lex());