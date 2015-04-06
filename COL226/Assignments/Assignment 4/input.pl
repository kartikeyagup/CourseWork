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

father(ga,a)
father(a,b).
father(a,c).
father(a,d).
wife(e,a).
mother(X,Y) :- father(Z,Y), wife(X,Z).
grandfather(M,N) :- father(M,L), father(L,N).
;