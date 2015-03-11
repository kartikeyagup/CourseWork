functor CalcLrValsFun(structure Token : TOKEN)
 : sig structure ParserData : PARSER_DATA
       structure Tokens : Calc_TOKENS
   end
 = 
struct
structure ParserData=
struct
structure Header = 
struct

end
structure LrTable = Token.LrTable
structure Token = Token
local open LrTable in 
val table=let val actionRows =
"\
\\001\000\001\000\010\000\000\000\
\\001\000\002\000\024\000\003\000\023\000\004\000\022\000\005\000\021\000\
\\008\000\020\000\010\000\019\000\016\000\018\000\000\000\
\\001\000\002\000\024\000\003\000\023\000\004\000\022\000\005\000\021\000\
\\010\000\019\000\016\000\018\000\000\000\
\\001\000\006\000\042\000\007\000\041\000\011\000\040\000\012\000\039\000\
\\013\000\038\000\014\000\037\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\027\000\068\000\000\000\
\\001\000\006\000\042\000\007\000\041\000\011\000\040\000\012\000\039\000\
\\013\000\038\000\014\000\037\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\027\000\069\000\000\000\
\\001\000\024\000\012\000\000\000\
\\001\000\025\000\047\000\000\000\
\\001\000\026\000\011\000\000\000\
\\001\000\026\000\044\000\000\000\
\\001\000\026\000\045\000\000\000\
\\001\000\026\000\046\000\000\000\
\\001\000\027\000\028\000\000\000\
\\001\000\027\000\070\000\000\000\
\\001\000\028\000\000\000\029\000\000\000\000\000\
\\072\000\000\000\
\\073\000\000\000\
\\074\000\000\000\
\\075\000\001\000\010\000\000\000\
\\076\000\000\000\
\\077\000\000\000\
\\078\000\000\000\
\\079\000\000\000\
\\080\000\025\000\013\000\000\000\
\\081\000\000\000\
\\082\000\009\000\048\000\000\000\
\\083\000\000\000\
\\084\000\000\000\
\\085\000\006\000\042\000\007\000\041\000\011\000\040\000\012\000\039\000\
\\013\000\038\000\014\000\037\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\086\000\000\000\
\\087\000\009\000\043\000\000\000\
\\088\000\000\000\
\\089\000\000\000\
\\090\000\000\000\
\\091\000\000\000\
\\092\000\000\000\
\\093\000\006\000\042\000\007\000\041\000\012\000\039\000\014\000\037\000\
\\015\000\036\000\017\000\035\000\018\000\034\000\019\000\033\000\
\\020\000\032\000\021\000\031\000\022\000\030\000\023\000\029\000\000\000\
\\094\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\095\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\096\000\006\000\042\000\007\000\041\000\012\000\039\000\014\000\037\000\
\\015\000\036\000\017\000\035\000\018\000\034\000\019\000\033\000\
\\020\000\032\000\021\000\031\000\022\000\030\000\023\000\029\000\000\000\
\\097\000\006\000\042\000\007\000\041\000\011\000\040\000\012\000\039\000\
\\013\000\038\000\014\000\037\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\098\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\099\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\100\000\006\000\042\000\007\000\041\000\011\000\040\000\012\000\039\000\
\\013\000\038\000\014\000\037\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\101\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\102\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\103\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\104\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\105\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\106\000\006\000\042\000\007\000\041\000\015\000\036\000\017\000\035\000\
\\018\000\034\000\019\000\033\000\020\000\032\000\021\000\031\000\
\\022\000\030\000\023\000\029\000\000\000\
\\107\000\000\000\
\\108\000\000\000\
\"
val actionRowNumbers =
"\000\000\014\000\007\000\005\000\
\\016\000\022\000\015\000\017\000\
\\026\000\001\000\000\000\019\000\
\\018\000\011\000\027\000\029\000\
\\008\000\009\000\010\000\034\000\
\\032\000\031\000\033\000\023\000\
\\006\000\024\000\020\000\002\000\
\\002\000\002\000\002\000\002\000\
\\002\000\002\000\002\000\002\000\
\\002\000\002\000\002\000\002\000\
\\002\000\001\000\002\000\002\000\
\\001\000\021\000\000\000\048\000\
\\047\000\046\000\045\000\044\000\
\\043\000\042\000\039\000\037\000\
\\038\000\036\000\035\000\041\000\
\\040\000\030\000\003\000\004\000\
\\012\000\025\000\050\000\049\000\
\\028\000\013\000"
val gotoT =
"\
\\001\000\069\000\002\000\007\000\003\000\006\000\004\000\005\000\
\\005\000\004\000\006\000\003\000\008\000\002\000\015\000\001\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\007\000\003\000\006\000\004\000\005\000\005\000\004\000\
\\006\000\003\000\008\000\002\000\015\000\012\000\000\000\
\\000\000\
\\009\000\015\000\012\000\014\000\013\000\013\000\000\000\
\\004\000\025\000\007\000\024\000\008\000\002\000\014\000\023\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\012\000\047\000\000\000\
\\012\000\048\000\000\000\
\\012\000\049\000\000\000\
\\012\000\050\000\000\000\
\\012\000\051\000\000\000\
\\012\000\052\000\000\000\
\\012\000\053\000\000\000\
\\012\000\054\000\000\000\
\\012\000\055\000\000\000\
\\012\000\056\000\000\000\
\\012\000\057\000\000\000\
\\012\000\058\000\000\000\
\\012\000\059\000\000\000\
\\012\000\060\000\000\000\
\\009\000\015\000\012\000\014\000\013\000\061\000\000\000\
\\012\000\062\000\000\000\
\\012\000\063\000\000\000\
\\009\000\015\000\012\000\014\000\013\000\064\000\000\000\
\\000\000\
\\004\000\025\000\008\000\002\000\014\000\065\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\"
val numstates = 70
val numrules = 37
val s = ref "" and index = ref 0
val string_to_int = fn () => 
let val i = !index
in index := i+2; Char.ord(String.sub(!s,i)) + Char.ord(String.sub(!s,i+1)) * 256
end
val string_to_list = fn s' =>
    let val len = String.size s'
        fun f () =
           if !index < len then string_to_int() :: f()
           else nil
   in index := 0; s := s'; f ()
   end
val string_to_pairlist = fn (conv_key,conv_entry) =>
     let fun f () =
         case string_to_int()
         of 0 => EMPTY
          | n => PAIR(conv_key (n-1),conv_entry (string_to_int()),f())
     in f
     end
val string_to_pairlist_default = fn (conv_key,conv_entry) =>
    let val conv_row = string_to_pairlist(conv_key,conv_entry)
    in fn () =>
       let val default = conv_entry(string_to_int())
           val row = conv_row()
       in (row,default)
       end
   end
val string_to_table = fn (convert_row,s') =>
    let val len = String.size s'
        fun f ()=
           if !index < len then convert_row() :: f()
           else nil
     in (s := s'; index := 0; f ())
     end
local
  val memo = Array.array(numstates+numrules,ERROR)
  val _ =let fun g i=(Array.update(memo,i,REDUCE(i-numstates)); g(i+1))
       fun f i =
            if i=numstates then g i
            else (Array.update(memo,i,SHIFT (STATE i)); f (i+1))
          in f 0 handle General.Subscript => ()
          end
in
val entry_to_action = fn 0 => ACCEPT | 1 => ERROR | j => Array.sub(memo,(j-2))
end
val gotoT=Array.fromList(string_to_table(string_to_pairlist(NT,STATE),gotoT))
val actionRows=string_to_table(string_to_pairlist_default(T,entry_to_action),actionRows)
val actionRowNumbers = string_to_list actionRowNumbers
val actionT = let val actionRowLookUp=
let val a=Array.fromList(actionRows) in fn i=>Array.sub(a,i) end
in Array.fromList(List.map actionRowLookUp actionRowNumbers)
end
in LrTable.mkLrTable {actions=actionT,gotos=gotoT,numRules=numrules,
numStates=numstates,initialState=STATE 0}
end
end
local open Header in
type pos = int
type arg = unit
structure MlyValue = 
struct
datatype svalue = VOID | ntVOID of unit ->  unit
 | BOOLEAN of unit ->  (bool) | CONSREAL of unit ->  (real)
 | CONSINT of unit ->  (int) | VAR of unit ->  (string)
 | IDEN of unit ->  (string) | DECLLIST of unit ->  (Absyn.dec list)
 | PREDLIST of unit ->  (Absyn.pred list)
 | TERMLIST of unit ->  (Absyn.term list)
 | EXPR of unit ->  (Absyn.expr) | UNARYOP of unit ->  (Absyn.unaryop)
 | BINARYOP of unit ->  (Absyn.binaryop)
 | TERM of unit ->  (Absyn.term)
 | PREDSYM of unit ->  (Absyn.predsymbol)
 | BODY of unit ->  (Absyn.body) | HEAD of unit ->  (Absyn.head)
 | RULE of unit ->  (Absyn.rule) | PRED of unit ->  (Absyn.pred)
 | FACT of unit ->  (Absyn.fact) | DECL of unit ->  (Absyn.dec)
 | PROG of unit ->  (Absyn.program)
end
type svalue = MlyValue.svalue
type result = Absyn.program
end
structure EC=
struct
open LrTable
infix 5 $$
fun x $$ y = y::x
val is_keyword =
fn _ => false
val preferred_change : (term list * term list) list = 
(nil
,nil
 $$ (T 10))::
(nil
,nil
 $$ (T 11))::
(nil
,nil
 $$ (T 13))::
(nil
,nil
 $$ (T 12))::
nil
val noShift = 
fn (T 27) => true | _ => false
val showTerminal =
fn (T 0) => "IDEN"
  | (T 1) => "VAR"
  | (T 2) => "CONSINT"
  | (T 3) => "CONSREAL"
  | (T 4) => "BOOLEAN"
  | (T 5) => "AND"
  | (T 6) => "OR"
  | (T 7) => "FUNSY"
  | (T 8) => "COMMA"
  | (T 9) => "NOT"
  | (T 10) => "PLUS"
  | (T 11) => "MULT"
  | (T 12) => "SUB"
  | (T 13) => "DIV"
  | (T 14) => "MOD"
  | (T 15) => "ABS"
  | (T 16) => "POW"
  | (T 17) => "EQUALTO"
  | (T 18) => "NOTEQUAL"
  | (T 19) => "GREATER"
  | (T 20) => "LESSER"
  | (T 21) => "GREATEREQ"
  | (T 22) => "LESSEREQ"
  | (T 23) => "IF"
  | (T 24) => "DOT"
  | (T 25) => "LPAREN"
  | (T 26) => "RPAREN"
  | (T 27) => "EOF"
  | (T 28) => "SEMI"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms : term list = nil
 $$ (T 28) $$ (T 27) $$ (T 26) $$ (T 25) $$ (T 24) $$ (T 23) $$ (T 22)
 $$ (T 21) $$ (T 20) $$ (T 19) $$ (T 18) $$ (T 17) $$ (T 16) $$ (T 15)
 $$ (T 14) $$ (T 13) $$ (T 12) $$ (T 11) $$ (T 10) $$ (T 9) $$ (T 8)
 $$ (T 7) $$ (T 6) $$ (T 5)end
structure Actions =
struct 
exception mlyAction of int
local open Header in
val actions = 
fn (i392,defaultPos,stack,
    (()):arg) =>
case (i392,stack)
of  ( 0, ( ( _, ( MlyValue.DECLLIST DECLLIST1, DECLLIST1left, 
DECLLIST1right)) :: rest671)) => let val  result = MlyValue.PROG (fn _
 => let val  (DECLLIST as DECLLIST1) = DECLLIST1 ()
 in (Absyn.Program DECLLIST)
end)
 in ( LrTable.NT 0, ( result, DECLLIST1left, DECLLIST1right), rest671)

end
|  ( 1, ( ( _, ( MlyValue.FACT FACT1, FACT1left, FACT1right)) :: 
rest671)) => let val  result = MlyValue.DECL (fn _ => let val  (FACT
 as FACT1) = FACT1 ()
 in (Absyn.Decfact FACT)
end)
 in ( LrTable.NT 1, ( result, FACT1left, FACT1right), rest671)
end
|  ( 2, ( ( _, ( MlyValue.RULE RULE1, RULE1left, RULE1right)) :: 
rest671)) => let val  result = MlyValue.DECL (fn _ => let val  (RULE
 as RULE1) = RULE1 ()
 in (Absyn.Decrule RULE)
end)
 in ( LrTable.NT 1, ( result, RULE1left, RULE1right), rest671)
end
|  ( 3, ( ( _, ( MlyValue.DECL DECL1, DECL1left, DECL1right)) :: 
rest671)) => let val  result = MlyValue.DECLLIST (fn _ => let val  (
DECL as DECL1) = DECL1 ()
 in ([DECL])
end)
 in ( LrTable.NT 14, ( result, DECL1left, DECL1right), rest671)
end
|  ( 4, ( ( _, ( MlyValue.DECLLIST DECLLIST1, _, DECLLIST1right)) :: (
 _, ( MlyValue.DECL DECL1, DECL1left, _)) :: rest671)) => let val  
result = MlyValue.DECLLIST (fn _ => let val  (DECL as DECL1) = DECL1
 ()
 val  (DECLLIST as DECLLIST1) = DECLLIST1 ()
 in ([DECL]@DECLLIST)
end)
 in ( LrTable.NT 14, ( result, DECL1left, DECLLIST1right), rest671)

end
|  ( 5, ( ( _, ( _, _, DOT1right)) :: ( _, ( MlyValue.PRED PRED1, 
PRED1left, _)) :: rest671)) => let val  result = MlyValue.FACT (fn _
 => let val  (PRED as PRED1) = PRED1 ()
 in (Absyn.FACT(PRED))
end)
 in ( LrTable.NT 2, ( result, PRED1left, DOT1right), rest671)
end
|  ( 6, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.TERMLIST 
TERMLIST1, _, _)) :: _ :: ( _, ( MlyValue.PREDSYM PREDSYM1, 
PREDSYM1left, _)) :: rest671)) => let val  result = MlyValue.PRED (fn
 _ => let val  (PREDSYM as PREDSYM1) = PREDSYM1 ()
 val  (TERMLIST as TERMLIST1) = TERMLIST1 ()
 in (Absyn.PRED (PREDSYM,TERMLIST))
end)
 in ( LrTable.NT 3, ( result, PREDSYM1left, RPAREN1right), rest671)

end
|  ( 7, ( ( _, ( _, _, DOT1right)) :: ( _, ( MlyValue.BODY BODY1, _, _
)) :: _ :: ( _, ( MlyValue.HEAD HEAD1, HEAD1left, _)) :: rest671)) =>
 let val  result = MlyValue.RULE (fn _ => let val  (HEAD as HEAD1) = 
HEAD1 ()
 val  (BODY as BODY1) = BODY1 ()
 in (Absyn.RULE (HEAD,BODY))
end)
 in ( LrTable.NT 4, ( result, HEAD1left, DOT1right), rest671)
end
|  ( 8, ( ( _, ( MlyValue.PRED PRED1, PRED1left, PRED1right)) :: 
rest671)) => let val  result = MlyValue.HEAD (fn _ => let val  (PRED
 as PRED1) = PRED1 ()
 in (Absyn.HEAD PRED)
end)
 in ( LrTable.NT 5, ( result, PRED1left, PRED1right), rest671)
end
|  ( 9, ( ( _, ( MlyValue.PREDLIST PREDLIST1, PREDLIST1left, 
PREDLIST1right)) :: rest671)) => let val  result = MlyValue.BODY (fn _
 => let val  (PREDLIST as PREDLIST1) = PREDLIST1 ()
 in (Absyn.BODY PREDLIST)
end)
 in ( LrTable.NT 6, ( result, PREDLIST1left, PREDLIST1right), rest671)

end
|  ( 10, ( ( _, ( MlyValue.PRED PRED1, PRED1left, PRED1right)) :: 
rest671)) => let val  result = MlyValue.PREDLIST (fn _ => let val  (
PRED as PRED1) = PRED1 ()
 in ([PRED])
end)
 in ( LrTable.NT 13, ( result, PRED1left, PRED1right), rest671)
end
|  ( 11, ( ( _, ( MlyValue.PREDLIST PREDLIST1, _, PREDLIST1right)) ::
 _ :: ( _, ( MlyValue.PRED PRED1, PRED1left, _)) :: rest671)) => let
 val  result = MlyValue.PREDLIST (fn _ => let val  (PRED as PRED1) = 
PRED1 ()
 val  (PREDLIST as PREDLIST1) = PREDLIST1 ()
 in ([PRED]@PREDLIST)
end)
 in ( LrTable.NT 13, ( result, PRED1left, PREDLIST1right), rest671)

end
|  ( 12, ( ( _, ( MlyValue.IDEN IDEN1, IDEN1left, IDEN1right)) :: 
rest671)) => let val  result = MlyValue.PREDSYM (fn _ => let val  (
IDEN as IDEN1) = IDEN1 ()
 in (Absyn.PREDS IDEN)
end)
 in ( LrTable.NT 7, ( result, IDEN1left, IDEN1right), rest671)
end
|  ( 13, ( ( _, ( MlyValue.EXPR EXPR1, EXPR1left, EXPR1right)) :: 
rest671)) => let val  result = MlyValue.TERM (fn _ => let val  (EXPR
 as EXPR1) = EXPR1 ()
 in (Absyn.Term_expr EXPR)
end)
 in ( LrTable.NT 8, ( result, EXPR1left, EXPR1right), rest671)
end
|  ( 14, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.TERMLIST 
TERMLIST1, _, _)) :: _ :: ( _, ( _, FUNSY1left, _)) :: rest671)) =>
 let val  result = MlyValue.TERM (fn _ => let val  (TERMLIST as 
TERMLIST1) = TERMLIST1 ()
 in (Absyn.Term_fsymbol TERMLIST)
end)
 in ( LrTable.NT 8, ( result, FUNSY1left, RPAREN1right), rest671)
end
|  ( 15, ( ( _, ( MlyValue.TERM TERM1, TERM1left, TERM1right)) :: 
rest671)) => let val  result = MlyValue.TERMLIST (fn _ => let val  (
TERM as TERM1) = TERM1 ()
 in ([TERM])
end)
 in ( LrTable.NT 12, ( result, TERM1left, TERM1right), rest671)
end
|  ( 16, ( ( _, ( MlyValue.TERMLIST TERMLIST1, _, TERMLIST1right)) ::
 _ :: ( _, ( MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let
 val  result = MlyValue.TERMLIST (fn _ => let val  (TERM as TERM1) = 
TERM1 ()
 val  (TERMLIST as TERMLIST1) = TERMLIST1 ()
 in ([TERM] @TERMLIST)
end)
 in ( LrTable.NT 12, ( result, TERM1left, TERMLIST1right), rest671)

end
|  ( 17, ( ( _, ( MlyValue.CONSINT CONSINT1, CONSINT1left, 
CONSINT1right)) :: rest671)) => let val  result = MlyValue.EXPR (fn _
 => let val  (CONSINT as CONSINT1) = CONSINT1 ()
 in (Absyn.Expr_int CONSINT)
end)
 in ( LrTable.NT 11, ( result, CONSINT1left, CONSINT1right), rest671)

end
|  ( 18, ( ( _, ( MlyValue.CONSREAL CONSREAL1, CONSREAL1left, 
CONSREAL1right)) :: rest671)) => let val  result = MlyValue.EXPR (fn _
 => let val  (CONSREAL as CONSREAL1) = CONSREAL1 ()
 in (Absyn.Expr_real CONSREAL)
end)
 in ( LrTable.NT 11, ( result, CONSREAL1left, CONSREAL1right), rest671
)
end
|  ( 19, ( ( _, ( MlyValue.VAR VAR1, VAR1left, VAR1right)) :: rest671)
) => let val  result = MlyValue.EXPR (fn _ => let val  (VAR as VAR1) =
 VAR1 ()
 in (Absyn.Expr_var (VAR))
end)
 in ( LrTable.NT 11, ( result, VAR1left, VAR1right), rest671)
end
|  ( 20, ( ( _, ( MlyValue.BOOLEAN BOOLEAN1, BOOLEAN1left, 
BOOLEAN1right)) :: rest671)) => let val  result = MlyValue.EXPR (fn _
 => let val  (BOOLEAN as BOOLEAN1) = BOOLEAN1 ()
 in (Absyn.Expr_bool (BOOLEAN))
end)
 in ( LrTable.NT 11, ( result, BOOLEAN1left, BOOLEAN1right), rest671)

end
|  ( 21, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.ADD, EXPR1, EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 22, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.MUL, EXPR1, EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 23, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.DIV, EXPR1, EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 24, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.SUB, EXPR1, EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 25, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.MOD,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 26, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.AND,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 27, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.OR,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 28, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.POW,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 29, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.EQUALTO,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 30, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.NOTEQUAL,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 31, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.GREATER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 32, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.LESSER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 33, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.GREATEREQ,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 34, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.LESSEREQ,EXPR1,EXPR2))
end)
 in ( LrTable.NT 11, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 35, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.EXPR EXPR1,
 _, _)) :: _ :: ( _, ( _, NOT1left, _)) :: rest671)) => let val  
result = MlyValue.EXPR (fn _ => let val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_un  (Absyn.NOT,EXPR))
end)
 in ( LrTable.NT 11, ( result, NOT1left, RPAREN1right), rest671)
end
|  ( 36, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.EXPR EXPR1,
 _, _)) :: _ :: ( _, ( _, ABS1left, _)) :: rest671)) => let val  
result = MlyValue.EXPR (fn _ => let val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_un  (Absyn.ABS,EXPR))
end)
 in ( LrTable.NT 11, ( result, ABS1left, RPAREN1right), rest671)
end
| _ => raise (mlyAction i392)
end
val void = MlyValue.VOID
val extract = fn a => (fn MlyValue.PROG x => x
| _ => let exception ParseInternal
	in raise ParseInternal end) a ()
end
end
structure Tokens : Calc_TOKENS =
struct
type svalue = ParserData.svalue
type ('a,'b) token = ('a,'b) Token.token
fun IDEN (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 0,(
ParserData.MlyValue.IDEN (fn () => i),p1,p2))
fun VAR (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 1,(
ParserData.MlyValue.VAR (fn () => i),p1,p2))
fun CONSINT (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 2,(
ParserData.MlyValue.CONSINT (fn () => i),p1,p2))
fun CONSREAL (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 3,(
ParserData.MlyValue.CONSREAL (fn () => i),p1,p2))
fun BOOLEAN (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 4,(
ParserData.MlyValue.BOOLEAN (fn () => i),p1,p2))
fun AND (p1,p2) = Token.TOKEN (ParserData.LrTable.T 5,(
ParserData.MlyValue.VOID,p1,p2))
fun OR (p1,p2) = Token.TOKEN (ParserData.LrTable.T 6,(
ParserData.MlyValue.VOID,p1,p2))
fun FUNSY (p1,p2) = Token.TOKEN (ParserData.LrTable.T 7,(
ParserData.MlyValue.VOID,p1,p2))
fun COMMA (p1,p2) = Token.TOKEN (ParserData.LrTable.T 8,(
ParserData.MlyValue.VOID,p1,p2))
fun NOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 9,(
ParserData.MlyValue.VOID,p1,p2))
fun PLUS (p1,p2) = Token.TOKEN (ParserData.LrTable.T 10,(
ParserData.MlyValue.VOID,p1,p2))
fun MULT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 11,(
ParserData.MlyValue.VOID,p1,p2))
fun SUB (p1,p2) = Token.TOKEN (ParserData.LrTable.T 12,(
ParserData.MlyValue.VOID,p1,p2))
fun DIV (p1,p2) = Token.TOKEN (ParserData.LrTable.T 13,(
ParserData.MlyValue.VOID,p1,p2))
fun MOD (p1,p2) = Token.TOKEN (ParserData.LrTable.T 14,(
ParserData.MlyValue.VOID,p1,p2))
fun ABS (p1,p2) = Token.TOKEN (ParserData.LrTable.T 15,(
ParserData.MlyValue.VOID,p1,p2))
fun POW (p1,p2) = Token.TOKEN (ParserData.LrTable.T 16,(
ParserData.MlyValue.VOID,p1,p2))
fun EQUALTO (p1,p2) = Token.TOKEN (ParserData.LrTable.T 17,(
ParserData.MlyValue.VOID,p1,p2))
fun NOTEQUAL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 18,(
ParserData.MlyValue.VOID,p1,p2))
fun GREATER (p1,p2) = Token.TOKEN (ParserData.LrTable.T 19,(
ParserData.MlyValue.VOID,p1,p2))
fun LESSER (p1,p2) = Token.TOKEN (ParserData.LrTable.T 20,(
ParserData.MlyValue.VOID,p1,p2))
fun GREATEREQ (p1,p2) = Token.TOKEN (ParserData.LrTable.T 21,(
ParserData.MlyValue.VOID,p1,p2))
fun LESSEREQ (p1,p2) = Token.TOKEN (ParserData.LrTable.T 22,(
ParserData.MlyValue.VOID,p1,p2))
fun IF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 23,(
ParserData.MlyValue.VOID,p1,p2))
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 24,(
ParserData.MlyValue.VOID,p1,p2))
fun LPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 25,(
ParserData.MlyValue.VOID,p1,p2))
fun RPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 26,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 27,(
ParserData.MlyValue.VOID,p1,p2))
fun SEMI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 28,(
ParserData.MlyValue.VOID,p1,p2))
end
end
