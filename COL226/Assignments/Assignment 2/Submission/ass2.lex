structure Tokens = Tokens

type pos = int
type svalue = Tokens.svalue
type ('a,'b) token = ('a,'b) Tokens.token
type lexresult= (svalue,pos) token

val pos = ref 0
fun eof () = Tokens.EOF(!pos,!pos)
fun error (e,l,_) = TextIO.output (TextIO.stdOut, String.concat[
	"line ", (Int.toString l), ": ", e, "\n"])

%%
%header (functor CalcLexFun(structure Tokens: Calc_TOKENS));
alpha=[A-Za-z];
digit=[0-9];
ws = [\ \t];
%%
\n       => (pos := (!pos) + 1; lex());
{ws}+    => (lex());
{digit}+ => (Tokens.CONSINT(Option.valOf(Int.fromString(yytext)), !pos, !pos));
{digit}+"\."{digit}+
		 => (Tokens.CONSREAL(Option.valOf(Real.fromString(yytext)),!pos,!pos));
"+"      => (Tokens.PLUS(!pos,!pos));
"*"      => (Tokens.MULT(!pos,!pos));
"-"		 => (Tokens.SUB(!pos,!pos));
"/"		 => (Tokens.DIV(!pos,!pos));
"%" 	 => (Tokens.MOD(!pos,!pos));
"and"	 => (Tokens.AND(!pos,!pos));
"or" 	 => (Tokens.OR(!pos,!pos));
"func"	 => (Tokens.FUNSY(!pos,!pos));
"," 	 => (Tokens.COMMA(!pos,!pos));
"not" 	 => (Tokens.NOT(!pos,!pos));
"abs" 	 => (Tokens.ABS(!pos,!pos));
"pow"	 => (Tokens.POW(!pos,!pos));
"="		 => (Tokens.EQUALTO(!pos,!pos));
"<>" 	 => (Tokens.NOTEQUAL(!pos,!pos));
">="	 => (Tokens.GREATEREQ(!pos,!pos));
"<="	 => (Tokens.LESSEREQ(!pos,!pos));
">"		 => (Tokens.GREATER(!pos,!pos));
"<"		 => (Tokens.LESSER(!pos,!pos));
"if"	 => (Tokens.IF(!pos,!pos));
"\." 	 => (Tokens.DOT(!pos,!pos));
"(" 	 => (Tokens.LPAREN(!pos,!pos));
")" 	 => (Tokens.RPAREN(!pos,!pos));
"true" 	 => (Tokens.BOOLEAN(true,!pos, !pos));
"false"  => (Tokens.BOOLEAN(false,!pos, !pos));
{alpha}+ => (Tokens.IDEN(yytext,!pos,!pos));
"."      => (error ("ignoring bad character "^yytext,!pos,!pos); lex());