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