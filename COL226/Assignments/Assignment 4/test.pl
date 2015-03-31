edge(a,b).
edge(a,c).
reachable(A,B):-edge(A,C), edge(C,B).
