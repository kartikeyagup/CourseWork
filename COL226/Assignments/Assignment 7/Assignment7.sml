structure A = 
struct
	datatype Procedure = cons of string*(string list)*(string list)*(Procedure list)*int*string

	datatype Frame = fr of Procedure*((string*int) list)*(int);

	fun GetName(cons(A,_,_,_,_,_))=A;

	fun GetLevel(cons(A,B,C,D,E,F))=E;

	fun MakeStringList([])=[]
		|MakeStringList(cons(A,B,C,D,E,F)::l)=A::MakeStringList(l)
	;

	fun GetChildrenList([],a)=[]
		|GetChildrenList(cons(A,B,C,D,E,F)::l,a)=
			if (A=a) then MakeStringList(D)
			else GetChildrenList(l,a)
	;


	fun GetVars(cons(A,B,C,D,E,F))=C@B;

	exception NotFound;

	fun SearchInList([],p)=raise NotFound
		|SearchInList(cons(A,B,C,D,E,F)::l,p)= if A=p then cons(A,B,C,D,E,F) else SearchInList(l,p)
	;

	fun CallableList(proclist,cons(A,B,C,D,E,F))=
		if (E=0) then []
		else 
			let
				val parent=SearchInList(proclist,F);
				val answer=GetChildrenList(proclist,F);
			in
				if GetLevel(parent)=0 then answer@[GetName(parent)]
				else answer@CallableList(proclist,parent)
			end

	fun AllCallable(proclist,cons(A,B,C,D,E,F))=MakeStringList(D)@CallableList(proclist,cons(A,B,C,D,E,F))
	
	fun GetBindingForVar(x,[])=raise NotFound
		|GetBindingForVar(x,(y,s)::ys)= if x=y then s else GetBindingForVar(x,ys)
	;

	fun GetBindgingList([],p)=[]
		|GetBindgingList(a::as1,p)=
			let
				val boundval = GetBindingForVar(a,p)
			in
				(a,boundval)::GetBindgingList(as1,p)
			end
	;

	fun GetVarValForFrame(fr(p,q,r))=GetBindgingList(GetVars(p),q);

	fun GetVarVals(cstk,ind)=
		let
			val reqframe = List.nth(cstk,ind)
		in
			GetVarValForFrame(reqframe)
		end

	fun VisibleVars(cstk,reglist)=
		let
			val currentproc = List.nth(cstk,length(cstk)-1);
		in
			if (hd(reglist)= ~1) then []
			else GetVarVals(cstk,hd(reglist))@VisibleVars(cstk,tl(reglist))
		end

	fun GetEnv(fr(a,b,c))=b

	fun GetLevelFr(fr(cons(A,B,C,D,E,F),G,H))=E

	fun VisibleVars2(cstk,reglist)=
		if hd(reglist)= ~1 then []
		else if (hd(reglist)>GetLevelFr(hd(List.rev(cstk)))) then []
		else GetEnv(List.nth(cstk,hd(reglist)))@VisibleVars2(cstk,tl(reglist))

	fun VisibleVars3(cstk,reglist,indexval,limitval)=
		if (indexval>limitval) then []
		else GetEnv(List.nth(cstk,List.nth(reglist,indexval)))@VisibleVars3(cstk,reglist,indexval+1,limitval)
	;


	fun CheckVarExists(a,[])=false
		|CheckVarExists(a,b::bs)=if (a=b) then true else CheckVarExists(a,bs)

	fun VarPresent(x,[])=false
		|VarPresent(x,(a,b)::ls)=if (x=a) then true else VarPresent(x,ls)
	;

	(*fun LocateVar(x,fr(cons(A,B,C,D,E,F),b,c))=CheckVarExists(x,B) orelse CheckVarExists(x,C)*)

	fun LocateVar(x,fr(cons(A,B,C,D,E,F),b,c))=VarPresent(x,b)
	
	fun GetNumEntries([])=0
		|GetNumEntries(a::ls)= if (a= ~1) then ~1 else 1+ GetNumEntries(ls)
	;

	fun helperlocator(stack,reglist,indexto,varent)=
		let
			val consideredf = List.nth(stack,List.nth(reglist,indexto))
		in
			if indexto<0 then ~1
			else if LocateVar(varent,consideredf) then indexto
			else helperlocator(stack,reglist,indexto-1,varent)
		end

	fun LocateIndexFromReg(stack,reglist,varent)=
		let
			val numtogoto=GetNumEntries(reglist)
		in
			helperlocator(stack,reglist,numtogoto,varent)
		end

	fun ChangeEnvironment(L,[],x,valx)=L 
		|ChangeEnvironment(L,(a1,a2)::bs,x,valx)=
			if (a1=x) then ChangeEnvironment(L@[(a1,valx)],bs,x,valx)
			else ChangeEnvironment(L@[(a1,a2)],bs,x,valx)
	;

	fun ChangeVariableInFrame(fr(A,B,C),(x,valx))=fr(A,ChangeEnvironment([],B,x,valx),C)

	fun ListSetNth(l,n,p)=List.take(l,n) @ [p] @ List.drop(l,n+1);

	fun ReplaceVariables(stack : Frame list ,reglist : int list,varent : string ,newval : int)=
		let
			(*val print1= print("starting\n");*)
			val location = LocateIndexFromReg(stack,reglist,varent)
			(*val printed= (print("location obtained\t");print(Int.toString(location));print("\n"));*)
			val replacedframe = ChangeVariableInFrame( List.nth(stack,List.nth(reglist,location)) , (varent,newval) )
		in
			(ListSetNth(stack,List.nth(reglist,location),replacedframe),reglist)
		end

	fun ShowList([])=print("\n")
		|ShowList((a,b)::c)=(print(a);print(" : "); print (Int.toString(b)); print("\t"); ShowList(c))
	;

	fun containsl((a,b),[])=false
		|containsl((a,b),(x1,x2)::xs)= if (a=x1) then true else containsl((a,b),xs)
	;


	fun filterlist([],l)=l
		|filterlist(x::xs,l)= if containsl(x,l) then filterlist(xs,l) else filterlist(xs,x::l)
	;

	fun ListAllVariables(stack,reglist)=
		let
			val vislist = VisibleVars(List.rev(stack),reglist);
		in
			ShowList(vislist)
			(*ShowList(filterlist(vislist,[]))*)
		end
	;

	fun FilteredVisibleVars(stack,reglist)=
		let
			val answer1 = VisibleVars2(stack,reglist)
		in
			ShowList(filterlist(List.rev(answer1),[] ))
		end

	fun FilteredVisibleVars2(stack,reglist)=
		let
			val answer1 = VisibleVars3(stack,reglist,0,GetLevelFr(hd(List.rev(stack))))
		in
			ShowList(filterlist(List.rev(answer1),[] ))
		end



	fun lookupfunction([],f)=raise NotFound
		|lookupfunction(cons(A,B,C,D,E,F)::ls,f)= if (A=f) then (cons(A,B,C,D,E,F),B) else lookupfunction(ls,f)
	;

	fun BindVals([],[])=[]
		|BindVals(a::as1,b::bs)=(a,b)::BindVals(as1,bs)
	;

	fun initlocal(cons(A,B,[],D,E,F))=[]
		|initlocal(cons(A,B,x::xs,D,E,F))=(x,0)::initlocal(cons(A,B,xs,D,E,F))
	;

	fun existsinlist(a,[])=false
		|existsinlist(a,b::bs)=if a=b then true else existsinlist(a,bs)
	;

	fun existsinlist2(a,[])=false
		|existsinlist2(a,(b,c)::d)=if (a=b) then true else existsinlist2(a,d)
	;

	fun GetProc(fr(a,b,c))=a

	fun findandcheckfunc(ftocall,[],l)=false
		|findandcheckfunc(ftocall,cons(alpha,b,_,_,_,_)::pq,l) =
			 if (ftocall=alpha) then (length(b)=length(l)) else findandcheckfunc(ftocall,pq,l)
	;

	fun CheckCallable(stack:Frame list,reglist: int list,proclist: Procedure list,ftocall:string,valuelist:int list)=
		let
			val functionsc = AllCallable(proclist,GetProc(hd(List.rev(stack))))
		in
			if existsinlist(ftocall,functionsc) then
				findandcheckfunc(ftocall,proclist,valuelist)
			else false
		end
	;

	fun CheckModifieable(stack,reglist,proclist,vartomod:string,valueto:int)=
		let
			val variablesc = VisibleVars(stack,reglist)
		in
			existsinlist2(vartomod,variablesc)
		end
	;

	fun CallFunction(stack,reglist,proclist,ftocall,valuelist)=
		let
			val namelist = lookupfunction(proclist,ftocall)
			val bounded = BindVals(#2namelist,valuelist)
			val initialesd= initlocal(#1namelist);
			val newfr = fr(#1namelist,initialesd@bounded,List.nth(reglist,GetLevel(#1namelist)))
			val modreglist = ListSetNth(reglist,GetLevel(#1namelist),List.length(stack))
		in
			(stack@[newfr],modreglist)
		end
	;

	fun ReturnFromFunction(stack,proclist,reglist)=
		let
			val fr(A,B,C) = hd(List.rev(stack))
			val newregs = ListSetNth(reglist,GetLevel(A),C)
		in
			if (List.length(stack)=1) then (stack,reglist)
			else (List.rev(tl(List.rev(stack))),newregs)
		end
	;
 
end 
open A;

fun droplastchar(s)=String.implode(List.rev(tl(List.rev(String.explode(s)))))

fun printlist([])=print("\n")
	|printlist(a::xs)=(print(a);print("\t");printlist(xs))
;

fun getposition([])=0
	|getposition(x::xs)=if (x= #" ") then 0 else 1+ getposition(xs)
;

fun getintfromlist(l)=
	let
		val posofbreak = getposition(l)
	in
		if length(l)=0 then []
		else if (length(l)=posofbreak) then [String.implode(l)]
		else String.implode(List.take(l,posofbreak))::getintfromlist(List.drop(l,posofbreak+1))
	end
;

val a=String.explode("34 46 75");
getposition(String.explode("34"));
(*List.drop(a,it+1);*)
getintfromlist(String.explode("34 46 75"));



fun checkvalidint(a)=
	let
		val p = Int.fromString(a)
	in
		case p of SOME x=> true
			| NONE => false
	end

fun CheckAllTrue([])=true
	|CheckAllTrue(x::xs)=x andalso CheckAllTrue(xs)
;

fun checkifvalidinput(l)=
	let
		val splitted = getintfromlist(String.explode(l))
		val mapped = List.map checkvalidint splitted
	in
		CheckAllTrue(mapped)
	end

fun convertint(a)=valOf(Int.fromString(a))

fun GetIntList(l)=
	let
		val splitted = getintfromlist(String.explode(l))
	in
		List.map convertint splitted
	end

fun ShowStack([])=print("\n")
	|ShowStack(fr(cons(a,b,c,d,e,f),B,C)::ms)=(print(a);print("\t");ShowStack(ms))
;

fun removemain([])=[]
	|removemain(a::bs)= if (a="main") then removemain(bs) else a::removemain(bs)
;

fun callablefunctions(proclist,fr(A,B,C))= printlist(removemain(AllCallable(proclist,A)));

fun environment(startstack: Frame list,startdis: int list,proclist: Procedure list)=
	let
		val instructions = print("Enter choice: \n 1) Show state of variables \n 2) Show Callable Functions \n 3) Return \n 4) Change value of variable \n 5) Call a function \n 6) Show Stack \n e) Exit\n")
		val input = valOf(TextIO.inputLine(TextIO.stdIn));
	in
		if (input="e\n") then print ("Exiting\n")
		else if (input="1\n") then (FilteredVisibleVars2(startstack,startdis);environment(startstack,startdis,proclist))
		else if (input="2\n") then 
			(callablefunctions(proclist,hd(List.rev(startstack)));environment(startstack,startdis,proclist))
		else if (input="3\n") then 
			let
				val returnedname = ReturnFromFunction(startstack,proclist,startdis)
			in
				(print("Returned successfully\n");environment(#1returnedname,#2returnedname,proclist))
			end
		else if (input="4\n") then
			let
				val printdata = print("Enter Variable to be changed\n");
				val varentered = droplastchar(valOf(TextIO.inputLine(TextIO.stdIn)));
				val printdata = print("Enter Integer Value to be assigned\n");
				val intentered = droplastchar(valOf(TextIO.inputLine(TextIO.stdIn)));
			in
				if (checkvalidint(intentered) andalso CheckModifieable(startstack,startdis,proclist,varentered,1)) then
					let
						val (p,q) = ReplaceVariables(startstack,startdis,varentered,convertint(intentered))
					in
						(print("Data modified successfully\n");environment(p,q,proclist))
					end
				else
					(print("Cannot change value\n");environment(startstack,startdis,proclist))
			end
		else if (input="5\n") then 
			let
				val printdata = print("Enter Function to be called\n");
				val varentered = droplastchar(valOf(TextIO.inputLine(TextIO.stdIn)));
				val printdata = print("Enter list of inputs to give (Integer Value)\n");
				val intlistentered = droplastchar(valOf(TextIO.inputLine(TextIO.stdIn)));
			in
				if (checkifvalidinput(intlistentered)) then
					if CheckCallable(startstack,startdis,proclist,varentered,GetIntList(intlistentered)) then 
						let
							val (p,q) = CallFunction(startstack,startdis,proclist,varentered,GetIntList(intlistentered))
						in
							(print("Function Called Successfully\n");environment(p,q,proclist))
						end
					else
						(print("Incorrect function call\n");environment(startstack,startdis,proclist))
				else 
					(print ("Invalid int list\n");environment(startstack,startdis,proclist))
			end
		else if (input="6\n") then
			(ShowStack(startstack);environment(startstack,startdis,proclist))
		else (print("Incorrect input\n");environment(startstack,startdis,proclist))
	end
;


Control.Print.printDepth := 100;

val V=cons("V",["x1","y1"],[],[],3,"R");
val R=cons("R",["x3","y4"],["x4","y3"],[V],2,"P");
val S=cons("S",["x2","y2"],["x3","y1"],[],2,"P");
val P=cons("P",["x1","y1"],["x2","y2"],[R,S],1,"main");
val W=cons("W",["x4","y2"],["x1"],[],3,"T");
val T=cons("T",["x1","y3"],["x3","y1"],[W],2,"Q");
val U=cons("U",["x3","y2"],["x1","y4"],[],2,"Q");
val Q=cons("Q",["x2","y3"],["x1","y4"],[T,U],1,"main");
val main=cons("main",[],["x1","x2","x3","x4"],[P,Q],0,"null");
val allprocedures=[main,P,Q,R,V,S,T,W,U];

val frmain= fr(main,initlocal(main),0);
val reglist=[0,~1,~1,~1];

(*CheckCallable([frmain],reglist,allprocedures,"P",[5,6]);*)
(*CallableList(allprocedures,GetProc(hd(List.rev([frmain]))));*)

environment([frmain],reglist,allprocedures);

(*val (a,b)=CallFunction([frmain],reglist,allprocedures,"Q",[34,101]);
FilteredVisibleVars(a,b);
val (c,d)=CallFunction(a,b,allprocedures,"U",[900,100]);
FilteredVisibleVars(c,d);
val (e,f)=CallFunction(c,d,allprocedures,"P",[1,2]);
FilteredVisibleVars(e,f);*)
(*
val (e,f)=ReplaceVariables(c,d,"x1",32);
FilteredVisibleVars(e,f);*)
(*ListSetNth([1,2,3,4,5],3,7);