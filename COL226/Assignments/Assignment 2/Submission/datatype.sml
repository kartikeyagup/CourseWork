signature ABSYN =
	sig
    	datatype program = Program of dec list
    and dec 	= Decfact of fact
    			| Decrule of rule
    and fact 	= FACT of pred 
    and pred 	= PRED of predsymbol* term list
    and rule 	= RULE of head*body
    and head 	= HEAD of pred
    and body 	= BODY of pred list
    and predsymbol = PREDS of string
    and term 	= Term_expr of expr
    			| Term_fsymbol of term list
    and binaryop = ADD
    			| SUB
    			| MUL
    			| DIV
    			| MOD
    			| AND
    			| OR
    			| POW
    			| EQUALTO
    			| NOTEQUAL
    			| GREATER
    			| LESSER
    			| LESSEREQ
    			| GREATEREQ
    and unaryop = NOT 
    			| ABS
    and expr 	= Expr_var of string
    			| Expr_int of int
    			| Expr_real of real
    			| Expr_bool of bool
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
  end

structure Absyn :> ABSYN =
   struct
datatype program = Program of dec list
    and dec 	= Decfact of fact
    			| Decrule of rule
    and fact 	= FACT of pred 
    and pred 	= PRED of predsymbol* term list
    and rule 	= RULE of head*body
    and head 	= HEAD of pred
    and body 	= BODY of pred list
    and predsymbol = PREDS of string
    and term 	= Term_expr of expr
    			| Term_fsymbol of term list
    and binaryop = ADD
    			| SUB
    			| MUL
    			| DIV
    			| MOD
    			| AND
    			| OR
    			| POW
    			| EQUALTO
    			| NOTEQUAL
    			| GREATER
    			| LESSER
    			| LESSEREQ
    			| GREATEREQ
    and unaryop = NOT 
    			| ABS
    and expr 	= Expr_var of string
    			| Expr_int of int
    			| Expr_real of real
    			| Expr_bool of bool
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
    end