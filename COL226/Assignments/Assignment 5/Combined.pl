%% Helper function
lookup([],_X,_T):-fail.
lookup([(A,T)|_GS],A,T).
lookup([_|GS],P,T):-lookup(GS,P,T).

append([],L,L).
append([X|XS],YS,[X|L]):-append(XS,YS,L).

bind([],[],[]).
bind([X|XS],[Y|YS],[(X,Y)|L2]):-bind(XS,YS,L2).

%% Base cases
hastype(_Gamma,X,T):-integer(X), T=int.
hastype(_Gamma,X,T):-float(X), T=real.
hastype(_Gamma,str(_X),T):-T=string.
hastype(_Gamma,true,T):-T=bool.
hastype(_Gamma,false,T):-T=bool.
hastype(_Gamma,unit,T):-T=unit.
hastype(Gamma,var(X),T):-lookup(Gamma,var(X),T).

%% Records
hastype(Gamma,(A,B),(T1,T2)):-hastype(Gamma,A,T1),hastype(Gamma,B,T2).
hastype(_Gamma,[],[]).
hastype(Gamma,[A|B],[T1|T2]):-hastype(Gamma,A,T1),hastype(Gamma,B,T2).

%% Functions
hastype(Gamma,lambda(X,E),arrow(T1,T2)):-hastype([(X,T1)|Gamma],E,T2).
hastype(Gamma,app(E1,E2),T2):- hastype(Gamma,E1,arrow(T1,T2)),hastype(Gamma,E2,T1).

%% Algebraic operations
hastype(Gamma,A+B,T):-hastype(Gamma,A,int),hastype(Gamma,B,int),T=int.
hastype(Gamma,A+B,T):-hastype(Gamma,A,real),hastype(Gamma,B,real),T=real.

hastype(Gamma,A-B,T):-hastype(Gamma,A,int),hastype(Gamma,B,int),T=int.
hastype(Gamma,A-B,T):-hastype(Gamma,A,real),hastype(Gamma,B,real),T=real.

hastype(Gamma,A*B,T):-hastype(Gamma,A,int),hastype(Gamma,B,int),T=int.
hastype(Gamma,A*B,T):-hastype(Gamma,A,real),hastype(Gamma,B,real),T=real.

hastype(Gamma,div(A,B),T):-hastype(Gamma,A,int),hastype(Gamma,B,int),T=int.
hastype(Gamma,A/B,T):-hastype(Gamma,A,real),hastype(Gamma,B,real),T=real.
hastype(Gamma,mod(A,B),T):-hastype(Gamma,A,int),hastype(Gamma,B,int),T=int.
hastype(Gamma,abs(X),T):-hastype(Gamma,X,T).

hastype(Gamma,A*B,T):-hastype(Gamma,A,bool),hastype(Gamma,B,bool),T=bool.
hastype(Gamma,A+B,T):-hastype(Gamma,A,bool),hastype(Gamma,B,bool),T=bool.
hastype(Gamma,conc(A,B),string):-hastype(Gamma,A,string),hastype(Gamma,B,string).
hastype(Gamma,subst(A,B,C),string):-hastype(Gamma,A,string),hastype(Gamma,B,int),hastype(Gamma,C,int).

hastype(Gamma,A>B,bool):-hastype(Gamma,A,int),hastype(Gamma,B,int).
hastype(Gamma,A=B,bool):-hastype(Gamma,A,int),hastype(Gamma,B,int).
hastype(Gamma,A<B,bool):-hastype(Gamma,A,int),hastype(Gamma,B,int).

hastype(Gamma,A>B,bool):-hastype(Gamma,A,real),hastype(Gamma,B,real).
hastype(Gamma,A=B,bool):-hastype(Gamma,A,real),hastype(Gamma,B,real).
hastype(Gamma,A<B,bool):-hastype(Gamma,A,real),hastype(Gamma,B,real).

hastype(Gamma,letInEnd(D,E),T):-typeelab(Gamma,D,P),append(Gamma,P,Ap),hastype(Ap,E,T).
hastype(Gamma,ifthenelse( A, B, C), T):- hastype(Gamma,A,bool),hastype(Gamma,B,T),hastype(Gamma,C,T).

typeelab(Gamma,assign(var(X),E),[(var(X),T)]):-hastype(Gamma,E,T).
typeelab(Gamma,sequential(D1,D2),T):-append(L1,L2,T),typeelab(Gamma,D1,L1),append(Gamma,L1,GammaX),typeelab(GammaX,D2,L2).
typeelab(Gamma,parallel(D1,D2),T):-typeelab(Gamma,D1,L1),typeelab(Gamma,D2,L2),append(L1,L2,T).
typeelab(Gamma,localinend(D1,D2),T2):-typeelab(Gamma,D1,T1),append(Gamma,T1,Appended),typeelab(Appended,D2,T2).

calculates(_TGamma,X,X):-integer(X).
calculates(_TGamma,X,X):-float(X).
calculates(_TGamma,true,true).
calculates(_TGamma,false,false).
calculates(_TGamma,true,true).
calculates(_TGamma,unit,unit).
calculates(_TGamma,str(P),P).
calculates(TGamma,var(X),L):-lookup(TGamma,var(X),L).
calculates(_Gamma,[],[]).
calculates(Gamma,[A|B],[T1|T2]):-calculates(Gamma,A,T1),calculates(Gamma,B,T2).
calculates(Gamma,(A,B),(T1,T2)):-calculates(Gamma,A,T1),calculates(Gamma,B,T2).

calculates(TGamma,E1/E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1/L2.
calculates(TGamma,E1*E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1*L2.
calculates(TGamma,E1+E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1+L2.
calculates(TGamma,E1-E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1-L2.
calculates(TGamma,E1=E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),(L1=:=L2 -> L = true; L= false).
calculates(TGamma,E1>E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),(L1>L2 -> L = true; L= false).
calculates(TGamma,E1<E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),(L1<L2 -> L = true; L= false).
calculates(TGamma,and(E1,E2),L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),(L=L1,L2).
calculates(TGamma,or(E1,E2),L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),(L=L1;L2).
calculates(TGamma,not(E),L):-calculates(TGamma,E,L1),(L1 -> L = false; L= true).
calculates(_TGamma,abs(E),L):-L is abs(E).
calculates(TGamma,div(E1,E2),L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1 div L2.
calculates(TGamma,mod(E1,E2),L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1 mod L2.
calculates(TGamma,conc(A,B),L):-calculates(TGamma,A,L1),calculates(TGamma,B,L2),string_concat(L1,L2,L).

calculates(TGamma,(E1,E2),(L1,L2)):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2).

calculates(TGamma,ifthenelse( A, B, C), T):- ( calculates(TGamma,A,true) -> calculates(TGamma,B,T);calculates(TGamma,C,T)).
calculates(Gamma,letInEnd(D,E),T):-typeelab_calc(Gamma,D,P),append(Gamma,P,Ap),calculates(Ap,E,T).

calculates(Gamma,lambda(X,E),cls(Gamma,lambda(X,E))).
calculates(Gamma,app(E1,E2),T):-calculates(Gamma,E1,cls(A,lambda(B,C))),calculates(Gamma,E2,Ans),bind(B,Ans,Binded), append(A,Binded,L),calculates(L,C,T).

typeelab_calc(Gamma,assign(var(X),E),[(var(X),T)]):-calculates(Gamma,E,T).
typeelab_calc(Gamma,sequential(D1,D2),T):-append(L1,L2,T),typeelab_calc(Gamma,D1,L1),append(Gamma,L1,GammaX),typeelab_calc(GammaX,D2,L2).
typeelab_calc(Gamma,parallel(D1,D2),T):-typeelab_calc(Gamma,D1,L1),typeelab_calc(Gamma,D2,L2),append(L1,L2,T).
typeelab_calc(Gamma,localinend(D1,D2),T2):-typeelab_calc(Gamma,D1,T1),append(Gamma,T1,Appended),typeelab_calc(Appended,D2,T2).

%% Subject Reduction
subjectreduction(Capital,Small,X):-hastype(Capital,X,T),calculates(Small,X,P),hastype(Capital,P,T).

%% calculates([],lambda([var(x),var(y)],var(x)*var(y) +5),T).
%% calculates([(var(z),5)],app(lambda([var(x),var(y)],var(x)*var(y)*var(z) +5),[3,4]),T).
%% calculates(P,letInEnd(localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),var(a)+var(b)),T).
%% typeelab([],localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),T)
%% calculates([(z,num(4))] , letinend( define(x, lambda(tuple([y,z]) , plus(y,z))) , apply(x , tuple([num(2),num(5)]))) , O).
%% calculates([],letInEnd(sequential(assign(var(x),4),assign(var(y),7)),var(x)+4-var(y)),T).
%% hastyp([],localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),T)
%% hastype(P,letInEnd(localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),var(a)+var(b)),T).






