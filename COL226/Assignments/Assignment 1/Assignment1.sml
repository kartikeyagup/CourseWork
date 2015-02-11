open TextIO;
use "Assignment1.lex.sml";
open Assignment1Lex;
open UserDeclarations;

val inp:string = TextIO.input(openIn("input.txt"))

val a= ref 0;

fun calculatex(n) =
	if (!a=0) 
		then 
		( 
				(a := !a +1);
				 inp
		)
	else 
		""
;

val lexer = makeLexer(calculatex);

fun getlistoftokens()= 
	let 
		val p:lexresult = lexer();
	in 
		case p of
			EOF => [p]
			| _ => [p] @ getlistoftokens()
	end;

getlistoftokens();