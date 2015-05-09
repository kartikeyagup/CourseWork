Control.Print.printDepth := 100;
CM.make "sources.cm";

signature Krivine = 
sig
	datatype Mach = Machine of Clo*St
and St= Stack of Clo list
and Clo = Closure of ((string*Clo) list)*Absyn.expr

	exception TypeMisMatch;
	exception InvalidOperation;
	exception LookupFail;
	exception InsufficientElements;
	exception BindError;

	val BindVals : (string list)*(Absyn.expr list)*((string*Clo) list) -> (string*Clo) list
	val Lookup : string*((string*Clo) list) -> Clo
	val NewMachine : Absyn.expr -> Mach
	val GetResult : Mach -> Absyn.expr
	val SingleStep : Mach -> Mach
	val MultiStep : Mach -> Mach
	val DoEveryThing : string -> Mach

end

fun GetExpression(Absyn.Program (p)) = hd(p);

structure K :> Krivine= 
struct

	datatype Mach = Machine of Clo*St
and St= Stack of Clo list
and Clo = Closure of ((string*Clo) list)*Absyn.expr

	exception TypeMisMatch;
	exception InvalidOperation;
	exception LookupFail;
	exception InsufficientElements;
	exception BindError;

	fun Slice(l,t,p)=if (List.length(p)=t) then p else Slice(tl(l),t,p@[hd(l)]);

	fun Slash(l1,l2)=
		let
			val length1 = List.length(l1)
			val length2 = List.length(l2)
		in
			Slice(l1,length1-length2,[])
		end
	;

	fun BindVals([],[],Gamma)=[]
		|BindVals(a::as1,b::bs,Gamma)=(a,Closure(Gamma,b))::BindVals(as1,bs,Gamma)
		|BindVals(_,_,_) = raise BindError
	;
	
	fun Lookup (s,[]) = raise LookupFail
		|Lookup(s,(l1,l2)::p)= if (String.compare(s,l1)=EQUAL) then l2 else Lookup(s,p)	
	;

	fun NewMachine(e) = Machine(Closure([],e),Stack([]))

	fun GetResult(Machine(Closure(e,p),_))=p;

	fun SingleStep(Machine(Closure(A,Absyn.Expr_int(p)),Stack([])))=
			Machine(Closure(A,Absyn.Expr_int(p)),Stack([]))
		|SingleStep(Machine(Closure(A,Absyn.Expr_real(p)),Stack([])))=
			Machine(Closure(A,Absyn.Expr_real(p)),Stack([]))
		|SingleStep(Machine(Closure(A,Absyn.Expr_bool(p)),Stack([])))=
			Machine(Closure(A,Absyn.Expr_bool(p)),Stack([]))
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.ADD,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case p1 of Absyn.Expr_int(l) => 
						(case p2 of Absyn.Expr_int(q) => Machine(Closure(A,Absyn.Expr_int(l+q)),Stack(st))
							| (_) => raise TypeMisMatch
						)
					| Absyn.Expr_real(l) => 
						(case p2 of Absyn.Expr_real(q) => Machine(Closure(A,Absyn.Expr_real(l+q)),Stack(st))
							| (_) => raise TypeMisMatch
						)
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.SUB,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_int(l-q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_real(l-q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.MUL,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_int(l*q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_real(l*q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.DIV,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_int(l div q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_real(l/q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.AND,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_bool(l),Absyn.Expr_bool(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l andalso q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.OR,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_bool(l),Absyn.Expr_bool(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l orelse q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_if(e1,e2,e3)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
			in
				case (p1) of (Absyn.Expr_bool(l)) => 
						if (l) then Machine(Closure(A,e2),Stack(st))
						else Machine(Closure(A,e3),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.EQUALTO,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l = q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(Real.==(l,q))),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.GREATER,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l > q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l>q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.LESSER,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l < q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l<q)),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_bin(Absyn.NOTEQUAL,e1,e2)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
				val p2=GetResult(MultiStep(Machine(Closure(A,e2),Stack([]))));
			in
				case (p1,p2) of (Absyn.Expr_int(l),Absyn.Expr_int(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(l <> q)),Stack(st))
					| (Absyn.Expr_real(l),Absyn.Expr_real(q)) => 
						Machine(Closure(A,Absyn.Expr_bool(Real.!=(l,q))),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_un(Absyn.NOT,e1)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
			in
				case (p1) of (Absyn.Expr_bool(l)) => 
						Machine(Closure(A,Absyn.Expr_bool(not(l))),Stack(st))
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_un(Absyn.ABS,e1)),Stack(st)))=
			let
				val p1=GetResult(MultiStep(Machine(Closure(A,e1),Stack([]))));
			in
				case (p1) of (Absyn.Expr_int(l)) => 
						Machine(Closure(A,Absyn.Expr_int(abs(l))),Stack(st))
					| (Absyn.Expr_real(l)) =>
						Machine(Closure(A,Absyn.Expr_real(abs(l))),Stack(st))	
					| (_) => raise TypeMisMatch
			end
		|SingleStep(Machine(Closure(A,Absyn.Expr_assign(l1,l2)),Stack(st)))=
			Machine(Closure( ((l1,Closure(A,l2))::A) ,Absyn.Expr_bool(true) ), Stack(st))
		(*Sequential definition*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_assignseq(p1,p2)),Stack(st) ))=
			let
				val Machine(Closure(p1,e),l) = MultiStep(Machine(Closure(A,p1),Stack([])))
				val Machine(Closure(p3,e4),stf) = MultiStep(Machine(Closure(p1,p2),Stack([])))
			in
				Machine(Closure(p3,e4),Stack(st))
			end
		(*Let in end*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_LetInEnd(l1,e1)),Stack(p)))=
			let
				val Machine(Closure(newcl,evaled),Stack(news)) = MultiStep(Machine(Closure(A,l1),Stack([])))
				val Machine(Closure(newcl1,evaled1),Stack(news1)) = MultiStep(Machine(Closure(newcl,e1),Stack([])))
			in
				Machine(Closure(A,evaled1),Stack(p))
			end
		(*variable lookup*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_string(y)),Stack(l)))=
			let
				val clsofans = Lookup(y,A);
				val Machine(Closure(ev1,ev2),Stack(p))= MultiStep(Machine(clsofans,Stack(l)));
			in
				Machine(Closure(A,ev2),Stack(p))
			end
		(*App*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_App(s,elist)),Stack(q)))=
			Machine(Closure(A,s),Stack( Closure(A,elist) ::q))
		(*Function call*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_function(slist,exp)),Stack([]))) =
			raise InsufficientElements
		|SingleStep(Machine(Closure(A,Absyn.Expr_function(slist,exp)),Stack(Closure(m1,Absyn.Expr_list(m2))::B))) =
			let
				val Binded = BindVals(slist,m2,m1);
			in
				Machine(Closure(Binded@A,exp),Stack(B))
			end
		(*Local in end *)
		|SingleStep(Machine(Closure(A,Absyn.Expr_LocalInEnd(e1,e2)),Stack(st)))=
			let
				val Machine(Closure(p1,p2),Stack(q1))= MultiStep(Machine(Closure(A,e1),Stack([])));
				val Machine(Closure(p3,p4),Stack(q2))= MultiStep(Machine(Closure(p1,e2),Stack([])));
			in
				Machine(Closure(Slash(p3,p1)@A,p4),Stack(st))
			end
		(*Parallel definition*)
		|SingleStep(Machine(Closure(A,Absyn.Expr_assignpar([])),Stack(st)))=
			Machine(Closure(A,Absyn.Expr_bool(true)),Stack(st))
		|SingleStep(Machine(Closure(A,Absyn.Expr_assignpar(l1::ls)),Stack(st)))=
			let
				val Machine(Closure(n1,n2),l) = MultiStep(Machine(Closure(A,l1),Stack([])))
			in
				Machine(Closure(n1,Absyn.Expr_assignpar(ls)),Stack(st))
			end
		(*Unknown expression*)
		|SingleStep(_)= raise InvalidOperation

	and MultiStep(Machine(Closure(A,Absyn.Expr_int(p)),Stack([]))) =
			Machine(Closure(A,Absyn.Expr_int(p)),Stack([]))
		|MultiStep(Machine(Closure(A,Absyn.Expr_real(p)),Stack([])))=
			Machine(Closure(A,Absyn.Expr_real(p)),Stack([]))
		|MultiStep(Machine(Closure(A,Absyn.Expr_bool(p)),Stack([])))=
			Machine(Closure(A,Absyn.Expr_bool(p)),Stack([]))
		|MultiStep(p)=MultiStep(SingleStep(p))
	;

	fun DoEveryThing(s)=
		MultiStep(NewMachine(GetExpression(Calc.parse_string(s))));
end


(*
Control.Print.printDepth  := 1000;
Control.Print.stringDepth := 1000;
Control.Print.printLength := 1000;
*)
(*2+3;*)

(*val q = Calc.parse_string ( " 3 . ; ");*)
(*val m=Calc.parse_string ( " let [ x= 50/0 , y= 8 ] in 7 end  . ;");*)

open K;

(*val parsed= Calc.parse_string "  let [ x= fn ( (p,q) , p-q+3) : y=8 ] in x(5,y) end . ;";*)
(*NewMachine(GetExpression(parsed));*)

(*val q=DoEveryThing( " if (true) then let [x= fn ( (p,q) , (p-q)+3) , y=8] in x(4,y) end else (4.5+3.4) fi . ;") ;*)
(*Calc.parse_string " let local a=3 in x=4 end in x+7 end  . ;";*)
(*DoEveryThing( " if (true) then let local a=3 in x=a end in x+7 end else (4.5+3.4) fi . ;") ;*)
(*val s4 = Calc.parse_string "let x:= fn(p)p+3 in let y:=fn(q,r)q(r) in y(x,7) end end .;";*)

DoEveryThing( "let x=50 in x+7 end . ;");
(*val e1= NewMachine(GetExpression(Calc.parse_string("let x=fn ( (p,q), (p-q)*40) in x(5,4) end . ;")));*)

val Machine(Closure(e12,p),q)= DoEveryThing("x=fn ( (p,q), (p-q)*40) . ;");
Machine(Closure(e12,GetExpression (Calc.parse_string("x(7,8) . ;"))) ,q);

(*Machine(Closure([],e),Stack([]))*)
(*SingleStep(e1);*)

(*DoEveryThing( " let [ x= fn ( (p) , p+3) : y=fn ((q,r), q(r) ) ] in y(x,10) end . ;");*)
DoEveryThing( " let local [ x=50 : z= 65] in y=x+z end in  3*y end . ;");
DoEveryThing( " let local [ x=50 , y=x+7] in z= x+y end in z*5 end . ;");