signature ABSYN =
	sig
    	datatype program = Program of expr list
    and binaryop = ADD
    			| SUB
    			| MUL
    			| DIV
    			| AND
    			| OR
    			| EQUALTO
    			| NOTEQUAL
    			| GREATER
    			| LESSER
    and unaryop = NOT 
    			| ABS
    and expr 	= Expr_int of int
    			| Expr_real of real
    			| Expr_bool of bool
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
  end

structure Absyn :> ABSYN =
   struct
datatype program = Program of expr list
    and binaryop = ADD
    			| SUB
    			| MUL
    			| DIV
    			| AND
    			| OR
    			| EQUALTO
    			| NOTEQUAL
    			| GREATER
    			| LESSER
    and unaryop = NOT 
    			| ABS
    and expr 	= Expr_int of int
    			| Expr_real of real
    			| Expr_bool of bool
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
    end