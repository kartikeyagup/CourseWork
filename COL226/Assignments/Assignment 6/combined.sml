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
		|RetFromLet
		|RetFromLoc
		|Ret
		|DumpVal
		|PopDump
		|Greater
		|Lesser
		|IfThenElse
		|Bind of string
		|Load of answer
		|Clos of (string list)*(OpCode list)

	and answer= ans_int of int
		|ans_real of real
		|ans_bool of bool
		|ans_str of string
		|ans_cls of (string list)*()
;

fun Compile(Absyn.Expr_int p) = [Load(ans_int p)]
	|Compile(Absyn.Expr_string p) = [Load(ans_str p)]
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
	|Compile(Absyn.Expr_if(e1,e2,e3)) = Compile(e1)@Compile(e2)@Compile(e3)@[IfThenElse]
	|Compile(Absyn.Expr_assign(s,e)) = Compile(e)@[Bind(s)]
	|Compile(Absyn.Expr_list ([])) = []
	|Compile(Absyn.Expr_list (x::xs)) = Compile(x)@Compile(Absyn.Expr_list xs)
	|Compile(Absyn.Expr_function(l,m)) = [Clos(l,Compile(m))]
	|Compile(Absyn.Expr_assignpar(p)) = Compile(Absyn.Expr_list(p))
	|Compile(Absyn.Expr_assignseq(e1,e2)) = Compile(e1)@Compile(e2)
	|Compile(Absyn.Expr_LetInEnd(e1,e2)) = [DumpVal]@Compile(e1)@Compile(e2)@[RetFromLet]
	|Compile(Absyn.Expr_LocalInEnd(e1,e2)) = [DumpVal]@Compile(e1)@[DumpVal]@Compile(e2)@[RetFromLoc]
;

fun CompileAll([])=[]
	|CompileAll(x::xs)=Compile(x)@CompileAll(xs)
;

fun GetExpressionList(Absyn.Program (p))=p


signature SECD = 
sig
	datatype St = Stack of answer list
and
		Env = Environment of (string*answer) list
and 
	Cont = Control of OpCode list 
and 
	Dum = Dump of (St*Env*Cont) list
and 
	SECDMachine = Machine of St*Env*Cont*Dum

	exception ArithmeticTypeMisMatch;
	exception InsufficientElements;
	exception BooleanTypeMisMatch;
	exception ComparasionTypeMisMatch;
	exception IfThenTypeMismatch;
	exception LookupFail;
	exception UnknownOpcode;

	val NewMachine : OpCode list -> SECDMachine
	val PushCompileList : SECDMachine*OpCode list -> SECDMachine
	val Lookup : string*Env -> answer
	val RunSingleInstruction : SECDMachine -> SECDMachine
	val RunAllInstructions : SECDMachine -> answer list
	val DoEveryThing: string -> answer list
end

structure Secd :> SECD= 
struct
	datatype St = Stack of answer list
and
		Env = Environment of (string*answer) list
and 
	Cont = Control of OpCode list 
and 
	Dum = Dump of (St*Env*Cont) list
and 
	SECDMachine = Machine of St*Env*Cont*Dum

	exception ArithmeticTypeMisMatch;
	exception InsufficientElements;	
	exception BooleanTypeMisMatch;
	exception ComparasionTypeMisMatch;
	exception IfThenTypeMismatch;
	exception LookupFail;
	exception UnknownOpcode;

	fun NewMachine(l)=Machine(Stack([]),Environment([]),Control(l),Dump([]));

	fun PushCompileList(Machine(A,B,C,D),L)= Machine(A,B,Control(L),D);

	fun Lookup(x,Environment([])) = raise LookupFail
		|Lookup(x,Environment((y,p)::ys)) = if (x=y) then p else Lookup(x,Environment(ys))
	;

	
	fun Slice(l,t,p)=if (List.length(p)=t) then p else Slice(tl(l),t,p@[hd(l)]);

	fun Slash(l1,l2)=
		let
			val length1 = List.length(l1)
			val length2 = List.length(l2)
		in
			Slice(l1,length1-length2,[])
		end
	;

	fun RunSingleInstruction(Machine(A,B,Control([]),D)) = Machine(A,B,Control([]),D)
		(*Variable lookup*)
		|RunSingleInstruction(Machine(Stack(A),B,Control((Load(ans_str(x))::C)),D)) = 
			Machine(Stack(Lookup(x,B)::A),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(A),B,Control((Load x)::C),D)) = Machine(Stack(x::A),B,Control(C),D)
		(*Addition*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Add :: C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Add :: C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::ans_int(xs)::l),B,Control(Add::C),D)) = 
		 	Machine(Stack(ans_int(x+xs)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::ans_real(xs)::l),B,Control(Add::C),D)) = 
			Machine(Stack(ans_real(x+xs)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Add::C),D)) = raise ArithmeticTypeMisMatch
		(*Subtraction*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Sub::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Sub::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::ans_int(xs)::l),B,Control(Sub::C),D)) = 
		 	Machine(Stack(ans_int(xs-x)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::ans_real(xs)::l),B,Control(Sub::C),D)) = 
		 	Machine(Stack(ans_real(xs-x)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Sub::C),D)) = raise ArithmeticTypeMisMatch
		(*Multiplication*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Mul :: C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Mul :: C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::ans_int(xs)::l),B,Control(Mul::C),D)) = 
		 	Machine(Stack(ans_int(x*xs)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::ans_real(xs)::l),B,Control(Mul::C),D)) = 
			Machine(Stack(ans_real(x*xs)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Mul::C),D)) = raise ArithmeticTypeMisMatch
		(*Division*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Div::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Div::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::ans_int(xs)::l),B,Control(Div::C),D)) = 
		 	Machine(Stack(ans_int(xs div x)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::ans_real(xs)::l),B,Control(Div::C),D)) = 
		 	Machine(Stack(ans_real(xs/x)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Div::C),D)) = raise ArithmeticTypeMisMatch
		(*Or*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Or::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Or::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_bool(x)::ans_bool(y)::xs),B,Control(Or::C),D)) =
			Machine(Stack(ans_bool(x orelse y)::xs),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Or::C),D)) = raise BooleanTypeMisMatch
		(*And*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(And::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(And::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_bool(x)::ans_bool(y)::xs),B,Control(And::C),D)) =
			Machine(Stack(ans_bool(x andalso y)::xs),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(And::C),D)) = raise BooleanTypeMisMatch
		(*Not*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Not::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_bool(x)::S),B,Control(Not::C),D))=
			Machine(Stack(ans_bool(not(x))::S),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Not::C),D))=raise BooleanTypeMisMatch
		(*Absolute*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Abs::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::S),B,Control(Abs::C),D))=
			Machine(Stack(ans_int(abs(x))::S),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::S),B,Control(Abs::C),D))=
			Machine(Stack(ans_real(abs(x))::S),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Abs::C),D))=raise BooleanTypeMisMatch
		(*Equality*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(Equal::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack([x]),B,Control(Equal::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(ans_int(x)::ans_int(xs)::l),B,Control(Equal::C),D)) = 
		 	Machine(Stack(ans_bool(xs=x)::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(ans_real(x)::ans_real(xs)::l),B,Control(Equal::C),D)) = 
		 	Machine(Stack(ans_bool(Real.==(x,xs))::l),B,Control(C),D)
		|RunSingleInstruction(Machine(Stack(_),B,Control(Equal::C),D)) = raise ComparasionTypeMisMatch
		(*If then else*)
		|RunSingleInstruction(Machine(Stack([]),B,Control(IfThenElse::C),D))=raise InsufficientElements		
		|RunSingleInstruction(Machine(Stack([x]),B,Control(IfThenElse::C),D))=raise InsufficientElements		
		|RunSingleInstruction(Machine(Stack([x,y]),B,Control(IfThenElse::C),D))=raise InsufficientElements		
		|RunSingleInstruction(Machine(Stack(x::y::ans_bool(true)::ys),B,Control(IfThenElse::C),D))=
			Machine(Stack(y::ys),B,Control(C),D)		
		|RunSingleInstruction(Machine(Stack(x::y::ans_bool(false)::ys),B,Control(IfThenElse::C),D))=	
			Machine(Stack(x::ys),B,Control(C),D)		
		|RunSingleInstruction(Machine(_,P,Control(IfThenElse::C),D))= raise IfThenTypeMismatch
		(*Bind*)
		|RunSingleInstruction(Machine(Stack([]),P,Control(Bind(p)::C),D)) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(x::xs),Environment(K),Control(Bind(p)::C),D)) = 
			Machine(Stack(xs),Environment((p,x)::K),Control(C),D)
		(*Ret*)
		|RunSingleInstruction(Machine(A,B,Control(Ret::l),Dump([])))= raise InsufficientElements
		|RunSingleInstruction(Machine(A,B,Control(Ret::l),Dump((e1,e2,e3)::xs)))= Machine(e1,e2,e3,Dump(xs))
		(*Dump*)
		|RunSingleInstruction(Machine(A,B,Control(DumpVal::l),Dump(D)))= Machine(A,B,Control(l),Dump((A,B,Control(l))::D))
		(*Return from let*)
		|RunSingleInstruction(Machine(Stack(x::xs),B,Control(RetFromLet::Q),Dump((Stack(e1),e2,e3)::es)))=
			Machine(Stack(x::xs),e2,Control(Q),Dump(es))
		|RunSingleInstruction(Machine(_,_,Control(RetFromLet::p),_))= raise InsufficientElements
		(*Return from local*)
		|RunSingleInstruction(Machine(Stack(x),B,Control(RetFromLoc::C),Dump([]))) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(x),B,Control(RetFromLoc::C),Dump([p]))) = raise InsufficientElements
		|RunSingleInstruction(Machine(Stack(x),Environment(B),Control(RetFromLoc::C),Dump((p1,Environment(p2),p3)::(q1,Environment(q2),q3)::L))) =
			Machine(Stack(x),Environment(Slash(B,p2)@q2),Control(C),Dump(L))
		|RunSingleInstruction(Machine(_,_,_,_))= raise UnknownOpcode;
	;

	fun RunAllInstructions(Machine(Stack(A),B,Control([]),D))=A
		|RunAllInstructions(M)=RunAllInstructions(RunSingleInstruction(M))
	;

	fun DoEveryThing(s) = RunAllInstructions(NewMachine(CompileAll(GetExpressionList(Calc.parse_string(s)))));
end
;

Control.Print.printDepth  := 1000;
Control.Print.stringDepth := 1000;
Control.Print.printLength := 1000;

(*val e1= GetExpressionList( Calc.parse_string "3+4 .;");*)
(*CompileAll(e1);*)

(*GetExpressionList( Calc.parse_string " x=5 . x+7 . 3+4 . 5*7 . 8-4 . 5/4 . if true then 4*9 else 3+6 fi . ;");*)
Secd.DoEveryThing(" x=5 . y=7 . z=10 .  x*y*z  . let x=50 in x+7 end . x*10 . 5*7 . 8-4 . 5/4 . if true then 4*9 else 3+6 fi . ;");
Secd.DoEveryThing( "let x=50 in x+7 end . ;");
Secd.DoEveryThing( "local x=50 in y=x+7 end . 3*y . ;");