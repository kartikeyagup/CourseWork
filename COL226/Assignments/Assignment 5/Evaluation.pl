lookup([],_X,_T):-fail.
lookup([(A,T)|_GS],A,T).
lookup([_|GS],P,T):-lookup(GS,P,T).


calculates(_TGamma,X,X):-integer(X).
calculates(_TGamma,X,X):-float(X).
calculates(_TGamma,true,true).
calculates(_TGamma,false,false).
calculates(_TGamma,true,true).
calculates(_TGamma,unit,unit).
calculates(_TGamma,str(P),str(P)).
calculates(TGamma,var(X),L):-lookup(TGamma,var(X),L).

calculates(TGamma,E1+E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1+L2.
calculates(TGamma,E1-E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1-L2.
calculates(TGamma,E1*E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1*L2.
calculates(TGamma,E1/E2,L):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2),L is L1/L2.

calculates(TGamma,(E1,E2),(L1,L2)):-calculates(TGamma,E1,L1),calculates(TGamma,E2,L2).

calculates(TGamma,ifthenelse( A, B, C), T):- ( calculates(TGamma,A,true) -> calculates(TGamma,B,T);calculates(TGamma,C,T)).

