Control.Print.printDepth := 100;
CM.make "sources.cm";

datatype OpCode = Add
		|Sub 
		|Mul
		|Div
		|Or
		|And
		|Not 
		|Abs
		|Equal
		|NotEqual
		|Greater
		|Lesser
		|Load of answer

	and answer= ans_int of int
		|ans_real of real
		|ans_bool of bool
;

fun Compile(Absyn.Expr_int p) = [Load(ans_int p)]
	|Compile(Absyn.Expr_real p)= [Load(ans_real p)]
	|Compile(Absyn.Expr_bool p)= [Load(ans_bool p)]
	|Compile(Absyn.Expr_bin (Absyn.ADD, e1,e2)) = Compile(e1) @ Compile( e2) @ [Add]
	|Compile(Absyn.Expr_bin (Absyn.MUL, e1,e2)) = Compile(e1) @ Compile( e2) @ [Mul]
	|Compile(Absyn.Expr_bin (Absyn.DIV, e1,e2)) = Compile(e1) @ Compile( e2) @ [Div]
	|Compile(Absyn.Expr_bin (Absyn.SUB, e1,e2)) = Compile(e1) @ Compile( e2) @ [Sub]
	|Compile(Absyn.Expr_bin (Absyn.OR, e1,e2)) = Compile(e1) @ Compile( e2) @ [Or]
	|Compile(Absyn.Expr_bin (Absyn.AND, e1,e2)) = Compile(e1) @ Compile( e2) @ [And]
	|Compile(Absyn.Expr_bin (Absyn.EQUALTO, e1,e2)) = Compile(e1) @ Compile( e2) @ [Equal]
	|Compile(Absyn.Expr_bin (Absyn.NOTEQUAL, e1,e2)) = Compile(e1) @ Compile( e2) @ [NotEqual]
	|Compile(Absyn.Expr_bin (Absyn.GREATER, e1,e2)) = Compile(e1) @ Compile( e2) @ [Greater]
	|Compile(Absyn.Expr_bin (Absyn.LESSER, e1,e2)) = Compile(e1) @ Compile( e2) @ [Lesser]
	|Compile(Absyn.Expr_un (Absyn.NOT, e1)) = Compile(e1)@[Not]	
	|Compile(Absyn.Expr_un (Absyn.ABS, e1)) = Compile(e1)@[Abs]
;

fun GetExpressionList(Absyn.Program (p))=p

val e1= GetExpressionList( Calc.parse_string "3+4 .;");
Compile(hd(e1));
(*Calc.parse_string("apples(A) if oranges(B) , oran(C) .;");
Calc.parse_string "apples(O) if lol(Lol) , app(not (App)). ;";
Calc.parse_string "apples(A) if oranges(B) , oran(C) .;";
Calc.parse_string "app(true and false).;";
Calc.parse_string "app(A,B).;";
Calc.parse_string "app( 45/34 + 26 - 23.04 + 23.2E2 + 45 pow 5 ).;";
Calc.parse_string "app(Orange).;";
Calc.parse_string "app(Apples and Orange).;";
Calc.parse_string "app( not (Applies) ).;";*)