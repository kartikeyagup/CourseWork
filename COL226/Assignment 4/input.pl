f(A,[A]).
f(L,[L|LY]).

a([kar,kg,kp]).

g([a,b,c,d],k).

edge(a,b). 
edge(a,g). 
edge(b,d). 
edge(c,d). 
edge(g,c). 
edge(g,f). 
edge(c,e). 
edge(e,d). 
path(X,X). 
path(X,Y) :- edge(X,Y).
path(X,Y) :- edge(X,Z), path(Z,Y). 

father(a,b).
sibling(b,d).
sibling(X,Y) :- father(Z,X),father(Z,Y).
parent(X,Y,Z) :- mother(X,Z),father(Y,Z). 
father(X,Y) :- father(X,Z),sibling(Z,Y).
parent(p,q,r).
;