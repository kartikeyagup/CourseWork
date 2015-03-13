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
caps=[A-Z];
sm=[a-z];
digit=[0-9];
ws = [\ \t];
%%
\n       => (pos := (!pos) + 1; lex());
{ws}+    => (lex());
{digit}+ => (Tokens.CONSINT(Option.valOf(Int.fromString(yytext)), !pos, !pos));
{digit}+"\."{digit}+
		 => (Tokens.CONSREAL(Option.valOf(Real.fromString(yytext)),!pos,!pos));
{alpha}+ => (Tokens.IDEN(yytext,!pos,!pos));
";"		 => (Tokens.SEMI(!pos,!pos));
"("		 => (Tokens.LPAREN(!pos,!pos));
"," 	 => (Tokens.COMMA(!pos,!pos));
")"		 => (Tokens.RPAREN(!pos,!pos));
"\."	 => (Tokens.DOT(!pos,!pos));
"."      => (error ("ignoring bad character "^yytext,!pos,!pos); lex());