lookup([],_X,_T):-fail.
lookup([(A,T)|_GS],A,T).
lookup([_|GS],P,T):-lookup(GS,P,T).

append([],L,L).
append([X|XS],YS,[X|L]):-append(XS,YS,L).

bind([],[],[]).
bind([X|XS],[Y|YS],[(X,Y)|L2]):-bind(XS,YS,L2).

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
calculates(Gamma,letInEnd(D,E),T):-typeelab(Gamma,D,P),append(Gamma,P,Ap),calculates(Ap,E,T).

calculates(Gamma,lambda(X,E),cls(Gamma,lambda(X,E))).
calculates(Gamma,app(E1,E2),T):-calculates(Gamma,E1,cls(A,lambda(B,C))),calculates(Gamma,E2,Ans),bind(B,Ans,Binded), append(A,Binded,L),calculates(L,C,T).

typeelab(Gamma,assign(var(X),E),[(var(X),T)]):-calculates(Gamma,E,T).
typeelab(Gamma,sequential(D1,D2),T):-append(L1,L2,T),typeelab(Gamma,D1,L1),append(Gamma,L1,GammaX),typeelab(GammaX,D2,L2).
typeelab(Gamma,parallel(D1,D2),T):-typeelab(Gamma,D1,L1),typeelab(Gamma,D2,L2),append(L1,L2,T).
typeelab(Gamma,localinend(D1,D2),T2):-typeelab(Gamma,D1,T1),append(Gamma,T1,Appended),typeelab(Appended,D2,T2).



%% calculates([],lambda([var(x),var(y)],var(x)*var(y) +5),T).
%% calculates([(var(z),5)],app(lambda([var(x),var(y)],var(x)*var(y)*var(z) +5),[3,4]),T).
%% calculates(P,letInEnd(localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),var(a)+var(b)),T).
%% typeelab([],localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),T)
%% calculates([(z,num(4))] , letinend( define(x, lambda(tuple([y,z]) , plus(y,z))) , apply(x , tuple([num(2),num(5)]))) , O).
%% calculates([],letInEnd(sequential(assign(var(x),4),assign(var(y),7)),var(x)+4-var(y)),T).
%% hastyp([],localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),T)
%% hastype(P,letInEnd(localinend(sequential(assign(var(x),3),assign(var(y),4)),sequential(assign(var(a),var(x)),assign(var(b),var(y)))),var(a)+var(b)),T).