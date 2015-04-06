signature Signature = 
	sig
		datatype Symbol = Symb of string*int
		and SymbolList = SymbList of Symbol list

	val GetString 			: Symbol -> string
	val GetIntArity			: Symbol -> int
	val GetListOfSymbols	: SymbolList -> Symbol list
	val CheckValidSig 		: SymbolList -> bool
	val CheckValidSym 		: Symbol*Symbol -> bool
	val CheckValidSymList	: Symbol*SymbolList -> bool
	val ExistsSymbol 		: string*SymbolList -> bool
	val GetArity			: string*SymbolList -> int
	val check_sig			: SymbolList -> bool
end

structure SIGNATURE:>Signature = 
	struct
		datatype Symbol = Symb of string*int
		and SymbolList = SymbList of Symbol list
		
	fun GetString(x:Symbol) =
		let
			val Symb(a,b) = x
		in
			a
		end

	fun GetIntArity(x:Symbol) =
		let
			val Symb(a,b) = x
		in
			b
		end

	fun GetListOfSymbols(x:SymbolList) =
		let
			val SymbList(l) = x
		in
			l
		end

	fun CheckValidSym(x:Symbol, y:Symbol) =
		let
			val Symb(sym1s,sym1i) = x
			val Symb(sym2s,sym2i) = y
		in
			if (sym1i>0 andalso sym2i>0) then 
				if (sym1s=sym2s) then
					if (sym1i=sym2i) then  true
					else false
				else
					true
			else
				false
		end

	fun CheckValidSymList(inpsym:Symbol,y:SymbolList) =
		let
			val SymbList(symlist) = y
			
			fun helper(sym1,[]) = true
				|helper(sym1,x::xs) = CheckValidSym(sym1,x) andalso helper(sym1,xs)
		in
			helper(inpsym,symlist)
		end

	fun CheckValidSig(x:SymbolList) =
		let
			val SymbList(listofsymb) = x

			fun helper2([])=true
				|helper2(y::ys) = CheckValidSymList(y,SymbList ys) andalso helper2(ys)
		in
			helper2(listofsymb)
		end

	fun ExistsSymbol(s1,slist)=
		let
			fun helper(s1,[])=false
				|helper(s1,x::xs)= (s1=GetString(x)) orelse helper(s1,xs)
		in
			helper(s1,GetListOfSymbols(slist))
		end

	fun GetArity (s1,y:SymbolList) =
		let
			fun helper_arr(s1,[]) = 0
				|helper_arr(s1,x::xs) = if (s1=GetString(x)) then GetIntArity(x) else GetArity(s1,SymbList(xs))
		in
			helper_arr(s1,GetListOfSymbols(y))
		end

	fun check_sig(x)= CheckValidSig(x);
end

open SIGNATURE;

Control.Print.printDepth := 1000;
Control.Print.stringDepth := 1000;
Control.Print.printLength := 1000;


CM.make "sources.cm";


fun CheckWellFormedQuery(Program.Query_Oper(stringop,terml),term1) = 
	if (ExistsSymbol(stringop,term1)) then
			(List.length(terml)=GetArity(stringop,term1))
	else
		false
;

fun CheckWellFormedTerm (Program.Term_Single(x),term1)= CheckWellFormedQuery(x,term1)
	| CheckWellFormedTerm (Program.Term_Conditional(x,y),term1)=
	(
		let
			fun helperlist([],validsg)=true
				| helperlist(x::xs,validsg)= CheckWellFormedQuery(x,validsg) andalso helperlist(xs,validsg);
		in
			CheckWellFormedQuery(x,term1) andalso helperlist(y,term1)
		end
	)
;

fun wff_h(Program.ProgList([]),Correctsig) = true
	|wff_h(Program.ProgList(x::xs),Correctsig) = CheckWellFormedTerm(x,Correctsig) andalso wff_h(Program.ProgList(xs),Correctsig)
;

exception Invalid_sig;

fun wff(x,y)= if (check_sig(y)) then wff_h(Program.ProgList(x),y) else raise Invalid_sig;


signature Substitution = 
	sig
		datatype  Subs = SubsList of (string*Program.Data) list  

	val GetTermSubs				: string*Subs -> Program.Data
end

fun first(x,y) = x;
fun second(x,y) = y;

structure SUBS :> Substitution= 
struct
	datatype  Subs = SubsList of (string*Program.Data) list  
	
	fun GetTermSubs(x,SubsList[]) = Program.Data_Var(x)
		| GetTermSubs(x,SubsList(m::ms)) = if (x=first(m)) then second(m) else GetTermSubs(x,SubsList(ms))  
end

open SUBS;

fun CheckEqual(Program.Data_Var(x),Program.Data_Var(y)) = (x=y)
	|CheckEqual(_,_) = false
;


fun subst_data(Program.Data_Var(x),subslist) = GetTermSubs(x,subslist)
	|subst_data(Program.Data_Cons(x),subslist) = Program.Data_Cons(x)
	|subst_data(Program.Data_Term(x),subslist) = let val Program.Term_Single(p)= x in Program.Data_Term(Program.Term_Single(subst_query(p,subslist))) end
	|subst_data(Program.Data_List(x),subslist) =
		let
			fun helperlist(Program.Data_List([x]),subslist) = Program.Data_List([subst_data(x,subslist)])
				|helperlist(Program.Data_List([x,y]),subslist) = Program.Data_List([subst_data(x,subslist),subst_data(y,subslist)])
		in
			(helperlist(Program.Data_List(x),subslist))
		end

and subst_query(Program.Query_Oper(x,datlist),subslist) =
	let
		fun helper([],subslist)=[]
			|helper(x::xs,subslist)=subst_data(x,subslist)::helper(xs,subslist);
		;
	in
		Program.Query_Oper(x,helper(datlist,subslist))
	end
;

fun subst(Program.Term_Single(x),subslist) = Program.Term_Single(subst_query(x,subslist))
	| subst(Program.Term_Conditional(x,y),subslist)= 
	let
		fun helper([],subslist)=[]
			|helper(x::xs,subslist)=subst_query(x,subslist)::helper(xs,subslist) 	
	in
		Program.Term_Conditional(subst_query(x,subslist),helper(y,subslist))	
	end
;

fun Subst([],subs)= []
	|Subst((x::xs),subs) = subst(x,subs)::Subst(xs,subs);

fun CompleteSubstitution(Program.ProgList(l),subsc) = Program.ProgList(Subst(l,subsc)) 

exception FailUnify;

fun ContainsVar_Data(x,Program.Data_Var(y)) = (x=y)
	|ContainsVar_Data(x,Program.Data_Term(y)) = ContainsVar_Term(x,y)
	|ContainsVar_Data(x,Program.Data_List(l)) = 
		let
			fun listhelper(x,Program.Data_List([k]))= ContainsVar_Data(x,k)
				|listhelper(x,Program.Data_List([a,b])) = ContainsVar_Data(x,a) orelse ContainsVar_Data(x,b)
		in
			listhelper(x,Program.Data_List(l))
		end
	|ContainsVar_Data(x,_) = false

and ContainsVar_Query(x,Program.Query_Oper(a,b))=
	let
		fun helper(x,[])= false
			|helper(x,l::ls)= ContainsVar_Data(x,l) orelse helper(x,ls)
	in
		helper(x,b)
	end


and ContainsVar_Term(x,Program.Term_Single(a))= ContainsVar_Query(x,a)
	|ContainsVar_Term(x,Program.Term_Conditional(a,b))=
		let
			fun helperterm(x,[])=false
				|helperterm(x,l::ls)=ContainsVar_Query(x,l) orelse helperterm(x,ls)
		in
			ContainsVar_Query(x,a) orelse helperterm(x,b)
		end
;

fun UnifyTerms(Program.Term_Single(x),Program.Term_Single(y),l)= UnifyQueries(x,y,l)
	|UnifyTerms(_,_,l)=(false,l)

and UnifyData(Program.Data_Var(x),Program.Data_Var(y),SubsList(unifier))= if (x=y) then (true,SubsList(unifier)) else (true,SubsList((x,Program.Data_Var(y))::unifier))
	|UnifyData(Program.Data_Cons(x),Program.Data_Cons(y),l)= if (x=y) then (true,l) else (false,l)
	|UnifyData(Program.Data_Var(x),Program.Data_Cons(y),SubsList(l)) = (true,SubsList((x,Program.Data_Cons(y))::l))
	|UnifyData(Program.Data_Cons(y),Program.Data_Var(x),SubsList(l)) = (true,SubsList((x,Program.Data_Cons(y))::l))
	|UnifyData(Program.Data_Cons(y),Program.Data_Term(x),l) = (false,l)
	|UnifyData(Program.Data_Term(x),Program.Data_Cons(y),l) = (false,l)
	|UnifyData(Program.Data_Var(x),Program.Data_Term(p),SubsList(l)) = 
		if ContainsVar_Term(x,p) then (false, SubsList(l))
		else (true, SubsList((x,Program.Data_Term(p))::l))
	|UnifyData(Program.Data_Term(p),Program.Data_Var(x),SubsList(l)) = 
		if ContainsVar_Term(x,p) then (false, SubsList(l))
		else (true, SubsList((x,Program.Data_Term(p))::l))
	|UnifyData(Program.Data_Term(p),Program.Data_Term(q),SubsList(l)) = UnifyTerms(p,q,SubsList(l))
	|UnifyData(Program.Data_Cons(x),Program.Data_List(p),l)= if (List.length(p)=1) then UnifyData(Program.Data_Cons(x),hd(p),l) else (false,l)
	|UnifyData(Program.Data_List(p),Program.Data_Cons(x),l)= if (List.length(p)=1) then UnifyData(Program.Data_Cons(x),hd(p),l) else (false,l)
	|UnifyData(Program.Data_Term(p),Program.Data_List(x),l)= if (List.length(x)=1) then UnifyData(Program.Data_Term(p),hd(x),l) else (false,l)
	|UnifyData(Program.Data_List(x),Program.Data_Term(p),l)= if (List.length(x)=1) then UnifyData(Program.Data_Term(p),hd(x),l) else (false,l)
	|UnifyData(Program.Data_Var(x),Program.Data_List(m),SubsList(l))=
		if ContainsVar_Data(x,Program.Data_List(m)) then (false,SubsList(l))
		else (true,SubsList((x,Program.Data_List(m))::l ))
	|UnifyData(Program.Data_List(m),Program.Data_Var(x),SubsList(l))=
		if ContainsVar_Data(x,Program.Data_List(m)) then (false,SubsList(l))
		else (true,SubsList((x,Program.Data_List(m))::l ))
	|UnifyData(Program.Data_List([a]),Program.Data_List([b]),SubsList(l))=
		let
			val (res,SubsList(unified)) = UnifyData(a,b,SubsList [])
		in
			if res then (true, SubsList(unified@l))
			else (false, SubsList(l))
		end
	|UnifyData(Program.Data_List([Program.Data_Var(a)]),Program.Data_List([b,c]),SubsList(l))=
		UnifyData(Program.Data_Var(a),Program.Data_List([b,c]),SubsList(l))
	|UnifyData(Program.Data_List([b,c]),Program.Data_List([Program.Data_Var(a)]),SubsList(l))=
		UnifyData(Program.Data_Var(a),Program.Data_List([b,c]),SubsList(l))
	|UnifyData(Program.Data_List([a,b]),Program.Data_List([c,d]),SubsList(l))=
		let
			val (res1,SubsList(l1)) = UnifyData(a,c,SubsList [])
			val (res2,SubsList(l2)) = UnifyData(b,d,SubsList [])
		in
			if (res1 andalso res2) then (true, SubsList(l1 @l2 @ l))
			else (false,SubsList(l))
		end
	| UnifyData(Program.Data_List(a),Program.Data_List(b),l) = (false, l)


and UnifyQueries(Program.Query_Oper(s1,d1),Program.Query_Oper(s2,d2),SubsList(l))=
	if (s1=s2) then 
		let
			fun UnifyHelper([],[],SubsList(l)) = (true,SubsList(l))
				| UnifyHelper(x::xs,y::ys,SubsList(l))= 
				let
					val name = UnifyData(subst_data(x,SubsList(l)),subst_data(y,SubsList(l)),SubsList(l))
				in
					if first(name) then UnifyHelper(xs,ys,second(name))
					else (false, SubsList(l))
				end
		in
			UnifyHelper(d1,d2,SubsList(l))
		end
	else (false,SubsList(l))
;

fun Unify(x,y)=UnifyQueries(x,y,SubsList([]));

fun MakeList(l) =
	let
		val Program.ProgList(p) = Calc.parse_string(l);
	in
		p
	end
;

fun GetQueryList(l)=
	let
		val tlist = MakeList(l);
		fun helper([])=[]
			|helper(Program.Term_Single(x)::xs) = x::helper(xs)
			|helper(Program.Term_Conditional(x)::xs)=helper(xs)
		;
	in
		helper(tlist)
	end
;

fun GetConditionsList(l)=
	let
		val tlist = MakeList(l);
		fun helper([])=[]
			|helper(Program.Term_Single(x)::xs) = helper(xs)
			|helper(Program.Term_Conditional(x)::xs)=x::helper(xs)
		;
	in
		helper(tlist)
	end
;



fun GetQuery(l)=
	let
		val p = GetQueryList(l)
	in
		List.nth(p,0)
	end
;

fun CheckQueryWithFact(l,[]) = false
	|CheckQueryWithFact(l,x::xs) = if (first(Unify(l,x))) then true else CheckQueryWithFact(l,xs)
;

fun ReturnAnswers(l,[],ans) = ans 
	|ReturnAnswers(l,x::xs,ans) = if (first(Unify(l,x))) then ReturnAnswers(l,xs,(second(Unify(l,x))::ans)) else ReturnAnswers(l,xs,ans)
;

fun PrettyPrintData(Program.Data_Var(x))= print x
	|PrettyPrintData(Program.Data_Cons(y)) = print y
;

fun PrettyPrintQuery(Program.Query_Oper(x,ls))=
	(
		let
			fun helpers([]) = (print "\n")
				|helpers(x::xs)= (PrettyPrintData(x); print "\t" ; helpers(xs))
			;
		in
			(print x; print "\t" ; helpers(ls) ; print "\n")
		end
	)
;
fun compose(SubsList(a),SubsList(b))= SubsList(a@b);


fun CheckQueryRetAns(l,[],mlist,ans)=ans
	|CheckQueryRetAns(l,Program.Term_Single(a)::ls,mlist,ans)= 
		if first(Unify(l,a)) then CheckQueryRetAns(l,ls,mlist,(second(Unify(l,a)))::ans)
		else CheckQueryRetAns(l,ls,mlist,ans)
	|CheckQueryRetAns(l,(Program.Term_Conditional(a,b))::ls,mlist,ans)=
	(
		if (first(Unify(l,a))) then
			let
				(* query list* term list * subst -> subst list  *)
				fun listiterator([],plist,a1) = [a1]
					|listiterator(x::xs,plist,a1) = 
						let
							val applied= subst_query(x,a1);
							val answerappl = CheckQueryRetAns(applied,plist,plist,[]);

							(* query list * subst list * term list * subst * subst lis0t -> subst list  *)
							fun helper(xs,[],proglist,prevans,p)=p
								|helper(xs,a::ls,proglist,prevans,p)= helper(xs,ls,proglist,prevans,listiterator(xs,proglist,compose(prevans,a))@p)
						in
							helper(xs,answerappl,plist,a1,[])
						end
			in
				CheckQueryRetAns(l,ls,mlist,listiterator(b,mlist,second(Unify(l,a)))@ans)
			end
		else 
			CheckQueryRetAns(l,ls,mlist,ans)
	)
;

datatype Answer = 
	Answer_Bool of bool 
	| Answer_Subs of Subs list
;

fun GetVarsList([],p)=p
	|GetVarsList(Program.Data_Var(x)::l,p)=GetVarsList(l,x::p)
	|GetVarsList(Program.Data_Cons(x)::l,p)=GetVarsList(l,p)
	|GetVarsList(Program.Data_Term(x)::l,p)=
		let
			val Program.Term_Single(y) = x
		in
			GetVarsList(l, GetVarQ(y)@p)
		end
	|GetVarsList(Program.Data_List([x])::l,p) = GetVarsList(l,GetVarsList([x],[])@p)
	|GetVarsList(Program.Data_List([x,y])::l,p) = GetVarsList(l,GetVarsList([x],[])@GetVarsList([y],[])@p)



and GetVarQ(Program.Query_Oper(a,b))= GetVarsList(b,[]);

fun CheckEqual(x,Program.Data_Var(y)) = (x=y)
	|CheckEqual(x,Program.Data_Cons(y)) = (x=y)
	|CheckEqual(_,_) = false
;

fun RemoveWrapper(Program.Data_Cons(x))= x
	|RemoveWrapper(Program.Data_Var(x))= x(*
	|RemoveWrapper(Program.Data_Term(x))= x
	|RemoveWrapper(Program.Data_List(x))= x*)
;

fun ReturnSubsVal(x,l)=
	let
		val ans = GetTermSubs(x,l);
	in
		if CheckEqual(x,ans) then ans
		else ReturnSubsVal(RemoveWrapper(ans),l)
	end
;

fun ReturnFinalValues([],l,a)=SubsList(a)
	|ReturnFinalValues(x::xs,l,a)=ReturnFinalValues(xs,l,(x,ReturnSubsVal(x,l))::a)
;

fun ReplaceVarslist(varlist,[])=[]
	|ReplaceVarslist(varlist,x::xs)=ReturnFinalValues(varlist,x,[])::ReplaceVarslist(varlist,xs)
;

fun DoQuery(x,p)= 
	let
		val execans=CheckQueryRetAns(x,p,p,[]);
		val varlist = GetVarQ(x);
	in
		if List.length(varlist)=0 then Answer_Bool(List.length(execans)>0)
		else if (List.length(execans)=0) then Answer_Bool(false)
		(*else Answer_Subs(ReplaceVarslist(varlist,execans))*)
		else Answer_Subs(execans)
	end
;

fun DoQueries([],p)=[]
	|DoQueries(x::xs,p)=DoQuery(x,p)::DoQueries(xs,p)
;

use "SymbolList.sml";

exception InvalidInput;
exception InvalidQueries;

val interpreted = MakeList(TextIO.input(TextIO.openIn("input.pl")));
val queries = GetQueryList(TextIO.input(TextIO.openIn("query.pl")));

if (wff (interpreted,l1)) then 
	if wff(MakeList(TextIO.input(TextIO.openIn("query.pl"))),l1) then DoQueries(queries,interpreted)
	else raise InvalidQueries
else raise InvalidInput;