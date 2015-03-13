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
			if (sym1s=sym2s) then
				if (sym1i=sym2i) then  true
				else false
			else
				true
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
end

open SIGNATURE;

Control.Print.printDepth := 100;
CM.make "sources.cm";

fun CheckWellFormedTerm (Program.Term_real(x),term1) = true
	|CheckWellFormedTerm(Program.Term_var(x),term1) = true
	|CheckWellFormedTerm(Program.Term_int(x),term1) = true
	|CheckWellFormedTerm(Program.Term_Oper(stringop,terml),term1) = 
	(
		let
			 fun helperlist([],validsg)=true
			 	|helperlist(x::xs,validsg) = CheckWellFormedTerm(x,validsg) andalso helperlist(xs,validsg)
		in
			if (ExistsSymbol(stringop,term1)) then 
				if (List.length(terml)=GetArity(stringop,term1)) then
					helperlist(terml,term1)
				else
					false 
			else
				false
		end
	)
;

fun wff(Program.ProgList([]),Correctsig) = true
	|wff(Program.ProgList(x::xs),Correctsig) = CheckWellFormedTerm(x,Correctsig) andalso wff(Program.ProgList(xs),Correctsig)
;

signature Substitution = 
	sig
		datatype  Subs = SubsList of (string*Program.Term) list  

	val GetTermSubs				: string*Subs -> Program.Term
end

fun first(x,y) = x;
fun second(x,y) = y;

structure SUBS :> Substitution= 
struct
	datatype  Subs = SubsList of (string*Program.Term) list  
	
	fun GetTermSubs(x,SubsList[]) = Program.Term_var(x)
		| GetTermSubs(x,SubsList(m::ms)) = if (x=first(m)) then second(m) else GetTermSubs(x,SubsList(ms))  
end

open SUBS;

fun CheckEqual(Program.Term_var(x),Program.Term_var(y)) = (x=y)
	|CheckEqual(_,_) = false
;

fun subst(Program.Term_real(x),subslist) = Program.Term_real(x)
	|subst(Program.Term_int(x),subslist) = Program.Term_int(x)
	|subst(Program.Term_var(x),subslist) = 
	let
		val p = GetTermSubs(x,subslist)
	in
		if (CheckEqual(p,Program.Term_var(x))) then p
		else subst(p,subslist)
	end
	|subst(Program.Term_Oper(a,l),subslist) = 
	let
		fun helper([],subslist)=[]
			|helper(x::xs,subslist)=subst(x,subslist)::helper(xs,subslist) 	
	in
		Program.Term_Oper(a,helper(l,subslist))	
	end
;
fun Subst([],subs)= []
	|Subst((x::xs),subs) = subst(x,subs)::Subst(xs,subs);

fun CompleteSubstitution(Program.ProgList(l),subsc) = Program.ProgList(Subst(l,subsc)) 

exception FailUnify;

fun ContainsVar(s,Program.Term_real(a)) = false
	|ContainsVar(s,Program.Term_int(a)) = false
	|ContainsVar(s,Program.Term_var(a)) = (s=a)
	|ContainsVar(s,Program.Term_Oper(a,[]))= false
	|ContainsVar(s,Program.Term_Oper(a,x::xs)) = ContainsVar(s,x) orelse ContainsVar(a,Program.Term_Oper(a,xs))
;

fun UnifyTerms (Program.Term_real(x),Program.Term_real(a),unifier)=(if (Real.==(a,x)) then unifier else raise FailUnify) 
	|UnifyTerms(Program.Term_int(x),Program.Term_int(a),unifier) =(if (x=a) then unifier else raise FailUnify)  
	|UnifyTerms(Program.Term_var(x),Program.Term_var(y),SubsList(l))=(if (x=y) then SubsList(l) else SubsList(l@[(x,Program.Term_var(y))]))
	|UnifyTerms(Program.Term_var(x),Program.Term_int(y),SubsList(l))  = SubsList(l@[(x,Program.Term_int(y))])
	|UnifyTerms(Program.Term_var(x),Program.Term_real(y),SubsList(l)) = SubsList(l@[(x,Program.Term_real(y))])
	|UnifyTerms(Program.Term_int(y),Program.Term_var(x),SubsList(l))  = SubsList(l@[(x,Program.Term_int(y))])
	|UnifyTerms(Program.Term_real(y),Program.Term_var(x),SubsList(l)) = SubsList(l@[(x,Program.Term_real(y))])
	|UnifyTerms(Program.Term_var(x),Program.Term_Oper(y,yl),SubsList(l)) =
	(
	 	if (ContainsVar(x,Program.Term_Oper(y,yl))) then 
	 		raise FailUnify 
	 	else 
	 		SubsList(l@[(x,Program.Term_Oper(y,yl))])
	)
	|UnifyTerms(Program.Term_Oper(y,yl),Program.Term_var(x),unifier) = UnifyTerms(Program.Term_var(x),Program.Term_Oper(y,yl),unifier)
	|UnifyTerms(Program.Term_Oper(x,xl),Program.Term_Oper(y,yl),unifier) =
	(
		if (x=y) then
		(
			let
			 	fun unifyhelper([],[],u)=u
			 		|unifyhelper(k::ks,b::bs,u)=unifyhelper(ks,bs,UnifyTerms(subst(k,u),subst(b,u),u))
					|unifyhelper(_,_,u)=u
			in
				unifyhelper(xl,yl,unifier)
			end
		)
		else
			raise FailUnify
	)
	|UnifyTerms(_,_,_) = raise FailUnify
;

fun UnifyProg(Program.ProgList(m))=
	let
		fun UnifyProgHelper([],u)=u
			|UnifyProgHelper([x],u)=u
			|UnifyProgHelper(x::y::xys,u)= UnifyProgHelper(y::xys,UnifyTerms(subst(x,u),subst(y,u),u))
	in
		UnifyProgHelper(m,SubsList [])
	end
;

val s1= Symb("kg",2);
val s2= Symb("anu",2);
val s3= Symb("soccer",2);
val s4= Symb("faran",2);
val s5= Symb("kg",3);
val l1=SymbList [s1,s2,s3,s4,s5,s3];

CheckValidSig l1;

val e1=Calc.parse_string "sub(plus (3 ,plus (4,1) ),45.3);"
val c1= Symb("plus",2);
val c2= Symb("sub",2);
val c3= Symb("mult",3);
val corrects=SymbList [c1,c2,c3];
wff(e1,corrects);

val e2=Calc.parse_string "sub(plus (x ,plus (4,y) ),x);";
val dosubs=SubsList [("x",Program.Term_real(4.0))];
CompleteSubstitution(e2,dosubs);

val e3=Calc.parse_string "sub(x,y);";
val e4=Calc.parse_string "sub(add(sub(3,4),m),3);";

val Program.ProgList(l)=e3;
val Program.ProgList(m)=e4;
UnifyTerms(hd(l),hd(l),SubsList([]));
UnifyProg(e3);

val e5=Calc.parse_string "f(h(1,2),x) , f(y,h(x,2));";
(*UnifyProg(e5);*)
val e6=Calc.parse_string "f(h(1,y),x) , f(x,h(2,y));";
(*UnifyProg(e6);*)
val e7=Calc.parse_string "f(h(x,1),y) , f(z,h(2,x));";
UnifyProg(e7);
val e8=Calc.parse_string "f(h(1,x),h(x,2)) , f(h(1,2),h(z,x)); ";
UnifyProg(e8);
val e9=Calc.parse_string "f(x,x), f(y,1) ;";
val n=UnifyProg(e9);
CompleteSubstitution(e9,n);

(*val e10=Calc.parse_string "f(x,y) ;";*)
(*val newsubs=SubsList [("x",Program.Term_var("y")),("y",Program.Term_int(1))];*)
(*val n=CompleteSubstitution(e10,newsubs);*)
