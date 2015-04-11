hastype(_Gamma,X,T):-integer(X), T=[int].
hastype(_Gamma,X,T):-float(X), T=[real].
hastype(_Gamma,true,T):-T=[bool].
hastype(_Gamma,false,T):-T=[bool].
hastype(_Gamma,unit,T):-T=[].
%Put in strings, product, records, functions

hastype(Gamma,A+B,T):-hastype(Gamma,A,[int]),hastype(Gamma,B,[int]),T=[int].
hastype(Gamma,A+B,T):-hastype(Gamma,A,[real]),hastype(Gamma,B,[real]),T=[real].

hastype(Gamma,A-B,T):-hastype(Gamma,A,[int]),hastype(Gamma,B,[int]),T=[int].
hastype(Gamma,A-B,T):-hastype(Gamma,A,[real]),hastype(Gamma,B,[real]),T=[real].

hastype(Gamma,A*B,T):-hastype(Gamma,A,[int]),hastype(Gamma,B,[int]),T=[int].
hastype(Gamma,A*B,T):-hastype(Gamma,A,[real]),hastype(Gamma,B,[real]),T=[real].

hastype(Gamma,A/B,T):-hastype(Gamma,A,[int]),hastype(Gamma,B,[int]),T=[int].
hastype(Gamma,A/B,T):-hastype(Gamma,A,[real]),hastype(Gamma,B,[real]),T=[real].

hastype(Gamma,A&B,T):-hastype(Gamma,A,[bool]),hastype(Gamma,B,[bool]),T=[bool].
hastype(Gamma,A|B,T):-hastype(Gamma,A,[bool]),hastype(Gamma,B,[bool]),T=[bool].
% variables, constants, strings, if then else, tuple, lambda, functions,
% let and local 
% sequential and parallel bindings

