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
                | Expr_string of string
    			| Expr_bool of bool
                | Expr_assign of string*expr
                | Expr_if of expr*expr*expr
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
                | Expr_list of expr list
                | Expr_function of (string list)*expr
                | Expr_assignpar of expr list
                | Expr_assignseq of expr*expr
                | Expr_LetInEnd of expr*expr
                | Expr_LocalInEnd of expr*expr
                | Expr_App of expr*expr
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
                | Expr_string of string
                | Expr_if of expr*expr*expr
    			| Expr_bool of bool
                | Expr_assign of string*expr
    			| Expr_un of unaryop*expr
    			| Expr_bin of binaryop*expr*expr
                | Expr_list of expr list
                | Expr_function of (string list)*expr
                | Expr_assignpar of expr list
                | Expr_assignseq of expr*expr
                | Expr_LetInEnd of expr*expr
                | Expr_LocalInEnd of expr*expr
                | Expr_App of expr*expr
    end