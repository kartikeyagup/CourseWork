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
\\001\000\001\000\014\000\002\000\013\000\003\000\012\000\005\000\011\000\
\\007\000\010\000\014\000\009\000\016\000\008\000\020\000\007\000\
\\023\000\006\000\027\000\005\000\000\000\
\\001\000\001\000\014\000\002\000\013\000\003\000\012\000\005\000\036\000\
\\007\000\010\000\014\000\009\000\016\000\008\000\020\000\007\000\
\\023\000\006\000\027\000\035\000\000\000\
\\001\000\005\000\031\000\027\000\030\000\000\000\
\\001\000\005\000\076\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\013\000\114\000\021\000\114\000\022\000\021\000\025\000\020\000\
\\026\000\019\000\028\000\114\000\029\000\018\000\031\000\016\000\
\\034\000\015\000\036\000\125\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\013\000\060\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\015\000\083\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\015\000\084\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\017\000\082\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\018\000\058\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\019\000\091\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\024\000\053\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\024\000\093\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\030\000\017\000\031\000\016\000\034\000\015\000\000\000\
\\001\000\009\000\057\000\000\000\
\\001\000\013\000\054\000\000\000\
\\001\000\013\000\059\000\000\000\
\\001\000\015\000\078\000\000\000\
\\001\000\021\000\089\000\000\000\
\\001\000\023\000\037\000\000\000\
\\001\000\023\000\062\000\000\000\
\\001\000\024\000\077\000\000\000\
\\001\000\024\000\085\000\000\000\
\\001\000\028\000\051\000\000\000\
\\001\000\028\000\067\000\000\000\
\\001\000\028\000\087\000\000\000\
\\001\000\035\000\000\000\037\000\000\000\000\000\
\\095\000\000\000\
\\096\000\001\000\014\000\002\000\013\000\003\000\012\000\005\000\011\000\
\\007\000\010\000\014\000\009\000\016\000\008\000\020\000\007\000\
\\023\000\006\000\027\000\005\000\000\000\
\\097\000\000\000\
\\098\000\000\000\
\\099\000\009\000\039\000\023\000\038\000\000\000\
\\099\000\009\000\061\000\023\000\038\000\000\000\
\\100\000\000\000\
\\101\000\000\000\
\\102\000\000\000\
\\103\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\104\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\105\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\106\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\107\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\108\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\109\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\110\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\111\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\112\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\113\000\000\000\
\\114\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\115\000\000\000\
\\116\000\000\000\
\\117\000\000\000\
\\118\000\000\000\
\\119\000\000\000\
\\120\000\000\000\
\\121\000\021\000\086\000\000\000\
\\122\000\000\000\
\\123\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\021\000\052\000\022\000\021\000\025\000\020\000\026\000\019\000\
\\029\000\018\000\031\000\016\000\034\000\015\000\000\000\
\\124\000\000\000\
\\125\000\008\000\025\000\010\000\024\000\011\000\023\000\012\000\022\000\
\\022\000\021\000\025\000\020\000\026\000\019\000\029\000\018\000\
\\031\000\016\000\034\000\015\000\000\000\
\\126\000\000\000\
\\127\000\000\000\
\\128\000\021\000\069\000\036\000\068\000\000\000\
\\128\000\036\000\068\000\000\000\
\\129\000\000\000\
\"
val actionRowNumbers =
"\000\000\027\000\013\000\000\000\
\\000\000\002\000\000\000\001\000\
\\019\000\031\000\034\000\033\000\
\\030\000\000\000\000\000\028\000\
\\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\
\\023\000\056\000\011\000\015\000\
\\002\000\014\000\009\000\016\000\
\\005\000\001\000\032\000\020\000\
\\000\000\000\000\041\000\040\000\
\\029\000\038\000\037\000\039\000\
\\036\000\044\000\045\000\043\000\
\\042\000\049\000\000\000\035\000\
\\002\000\024\000\061\000\000\000\
\\000\000\000\000\000\000\000\000\
\\003\000\021\000\047\000\057\000\
\\017\000\059\000\002\000\002\000\
\\058\000\008\000\006\000\007\000\
\\004\000\022\000\054\000\052\000\
\\050\000\063\000\062\000\025\000\
\\000\000\051\000\053\000\018\000\
\\003\000\060\000\010\000\000\000\
\\055\000\046\000\012\000\048\000\
\\026\000"
val gotoT =
"\
\\001\000\092\000\002\000\002\000\003\000\001\000\000\000\
\\000\000\
\\000\000\
\\002\000\025\000\004\000\024\000\000\000\
\\002\000\026\000\000\000\
\\006\000\027\000\000\000\
\\002\000\030\000\000\000\
\\002\000\032\000\006\000\031\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\038\000\000\000\
\\002\000\039\000\000\000\
\\002\000\002\000\003\000\040\000\000\000\
\\002\000\041\000\000\000\
\\002\000\042\000\000\000\
\\002\000\043\000\000\000\
\\002\000\044\000\000\000\
\\002\000\045\000\000\000\
\\002\000\046\000\000\000\
\\002\000\047\000\000\000\
\\002\000\048\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\006\000\054\000\007\000\053\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\025\000\004\000\024\000\006\000\054\000\007\000\053\000\000\000\
\\000\000\
\\000\000\
\\002\000\025\000\004\000\061\000\000\000\
\\002\000\062\000\000\000\
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
\\002\000\025\000\004\000\063\000\000\000\
\\000\000\
\\006\000\064\000\000\000\
\\000\000\
\\000\000\
\\002\000\068\000\000\000\
\\002\000\069\000\000\000\
\\002\000\070\000\000\000\
\\002\000\071\000\000\000\
\\002\000\072\000\000\000\
\\005\000\073\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\006\000\078\000\007\000\077\000\000\000\
\\006\000\079\000\000\000\
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
\\002\000\086\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\005\000\088\000\000\000\
\\000\000\
\\000\000\
\\002\000\090\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\"
val numstates = 93
val numrules = 35
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
 | IDEN of unit ->  (string) | VAR of unit ->  (string)
 | BOOL of unit ->  (bool) | REAL of unit ->  (real)
 | INT of unit ->  (int) | DEFNLIST of unit ->  (Absyn.expr list)
 | DEFN of unit ->  (Absyn.expr)
 | STRINGLIST of unit ->  (string list)
 | EXPRLISTC of unit ->  (Absyn.expr list)
 | EXPRLIST of unit ->  (Absyn.expr list)
 | EXPR of unit ->  (Absyn.expr) | PROG of unit ->  (Absyn.program)
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
 $$ (T 21))::
(nil
,nil
 $$ (T 25))::
(nil
,nil
 $$ (T 28))::
(nil
,nil
 $$ (T 24))::
nil
val noShift = 
fn (T 34) => true | (T 36) => true | _ => false
val showTerminal =
fn (T 0) => "INT"
  | (T 1) => "REAL"
  | (T 2) => "BOOL"
  | (T 3) => "VAR"
  | (T 4) => "IDEN"
  | (T 5) => "GOESTO"
  | (T 6) => "FN"
  | (T 7) => "EQUAL"
  | (T 8) => "ASSIGN"
  | (T 9) => "NOTEQUAL"
  | (T 10) => "LESSERTHAN"
  | (T 11) => "GREATERTHAN"
  | (T 12) => "IN"
  | (T 13) => "LET"
  | (T 14) => "END"
  | (T 15) => "IF"
  | (T 16) => "ELSE"
  | (T 17) => "THEN"
  | (T 18) => "FI"
  | (T 19) => "LOCAL"
  | (T 20) => "COMMA"
  | (T 21) => "PLUS"
  | (T 22) => "LPAREN"
  | (T 23) => "RPAREN"
  | (T 24) => "SUB"
  | (T 25) => "MUL"
  | (T 26) => "BOXLPAREN"
  | (T 27) => "BOXRPAREN"
  | (T 28) => "DIV"
  | (T 29) => "DOT"
  | (T 30) => "AND"
  | (T 31) => "LCURL"
  | (T 32) => "RCURL"
  | (T 33) => "OR"
  | (T 34) => "EOF"
  | (T 35) => "COLON"
  | (T 36) => "SEMI"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms : term list = nil
 $$ (T 36) $$ (T 35) $$ (T 34) $$ (T 33) $$ (T 32) $$ (T 31) $$ (T 30)
 $$ (T 29) $$ (T 28) $$ (T 27) $$ (T 26) $$ (T 25) $$ (T 24) $$ (T 23)
 $$ (T 22) $$ (T 21) $$ (T 20) $$ (T 19) $$ (T 18) $$ (T 17) $$ (T 16)
 $$ (T 15) $$ (T 14) $$ (T 13) $$ (T 12) $$ (T 11) $$ (T 10) $$ (T 9)
 $$ (T 8) $$ (T 7) $$ (T 6) $$ (T 5)end
structure Actions =
struct 
exception mlyAction of int
local open Header in
val actions = 
fn (i392,defaultPos,stack,
    (()):arg) =>
case (i392,stack)
of  ( 0, ( ( _, ( MlyValue.EXPRLIST EXPRLIST1, EXPRLIST1left, 
EXPRLIST1right)) :: rest671)) => let val  result = MlyValue.PROG (fn _
 => let val  (EXPRLIST as EXPRLIST1) = EXPRLIST1 ()
 in (Absyn.Program EXPRLIST)
end)
 in ( LrTable.NT 0, ( result, EXPRLIST1left, EXPRLIST1right), rest671)

end
|  ( 1, ( ( _, ( _, _, DOT1right)) :: ( _, ( MlyValue.EXPR EXPR1, 
EXPR1left, _)) :: rest671)) => let val  result = MlyValue.EXPRLIST (fn
 _ => let val  (EXPR as EXPR1) = EXPR1 ()
 in ([EXPR])
end)
 in ( LrTable.NT 2, ( result, EXPR1left, DOT1right), rest671)
end
|  ( 2, ( ( _, ( MlyValue.EXPRLIST EXPRLIST1, _, EXPRLIST1right)) :: _
 :: ( _, ( MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let
 val  result = MlyValue.EXPRLIST (fn _ => let val  (EXPR as EXPR1) = 
EXPR1 ()
 val  (EXPRLIST as EXPRLIST1) = EXPRLIST1 ()
 in ([EXPR]@EXPRLIST)
end)
 in ( LrTable.NT 2, ( result, EXPR1left, EXPRLIST1right), rest671)
end
|  ( 3, ( ( _, ( MlyValue.INT INT1, INT1left, INT1right)) :: rest671))
 => let val  result = MlyValue.EXPR (fn _ => let val  (INT as INT1) = 
INT1 ()
 in (Absyn.Expr_int INT)
end)
 in ( LrTable.NT 1, ( result, INT1left, INT1right), rest671)
end
|  ( 4, ( ( _, ( MlyValue.IDEN IDEN1, IDEN1left, IDEN1right)) :: 
rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (IDEN
 as IDEN1) = IDEN1 ()
 in (Absyn.Expr_string IDEN)
end)
 in ( LrTable.NT 1, ( result, IDEN1left, IDEN1right), rest671)
end
|  ( 5, ( ( _, ( MlyValue.REAL REAL1, REAL1left, REAL1right)) :: 
rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (REAL
 as REAL1) = REAL1 ()
 in (Absyn.Expr_real REAL)
end)
 in ( LrTable.NT 1, ( result, REAL1left, REAL1right), rest671)
end
|  ( 6, ( ( _, ( MlyValue.BOOL BOOL1, BOOL1left, BOOL1right)) :: 
rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (BOOL
 as BOOL1) = BOOL1 ()
 in (Absyn.Expr_bool (BOOL))
end)
 in ( LrTable.NT 1, ( result, BOOL1left, BOOL1right), rest671)
end
|  ( 7, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.EXPR EXPR1, _
, _)) :: ( _, ( _, LPAREN1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  (EXPR as EXPR1) = EXPR1 ()
 in (EXPR)
end)
 in ( LrTable.NT 1, ( result, LPAREN1left, RPAREN1right), rest671)
end
|  ( 8, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.ADD, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 9, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.MUL, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 10, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.DIV, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 11, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.SUB, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 12, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.AND,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 13, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.OR,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 14, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.EQUALTO,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 15, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.NOTEQUAL,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 16, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.GREATER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 17, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.LESSER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 18, ( ( _, ( _, _, FI1right)) :: ( _, ( MlyValue.EXPR EXPR3, _, _
)) :: _ :: ( _, ( MlyValue.EXPR EXPR2, _, _)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, _, _)) :: ( _, ( _, IF1left, _)) :: rest671)) =>
 let val  result = MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 val  EXPR3 = EXPR3 ()
 in (Absyn.Expr_if(EXPR1,EXPR2,EXPR3))
end)
 in ( LrTable.NT 1, ( result, IF1left, FI1right), rest671)
end
|  ( 19, ( ( _, ( MlyValue.EXPR EXPR1, _, EXPR1right)) :: _ :: ( _, ( 
MlyValue.IDEN IDEN1, IDEN1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  (IDEN as IDEN1) = IDEN1 ()
 val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_assign (IDEN,EXPR))
end)
 in ( LrTable.NT 1, ( result, IDEN1left, EXPR1right), rest671)
end
|  ( 20, ( ( _, ( _, _, RPAREN2right)) :: ( _, ( MlyValue.EXPR EXPR1,
 _, _)) :: _ :: _ :: ( _, ( MlyValue.STRINGLIST STRINGLIST1, _, _)) ::
 _ :: _ :: ( _, ( _, FN1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  (STRINGLIST as STRINGLIST1) = 
STRINGLIST1 ()
 val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_function (STRINGLIST, EXPR))
end)
 in ( LrTable.NT 1, ( result, FN1left, RPAREN2right), rest671)
end
|  ( 21, ( ( _, ( _, _, BOXRPAREN1right)) :: ( _, ( MlyValue.EXPRLISTC
 EXPRLISTC1, _, _)) :: ( _, ( _, BOXLPAREN1left, _)) :: rest671)) =>
 let val  result = MlyValue.EXPR (fn _ => let val  (EXPRLISTC as 
EXPRLISTC1) = EXPRLISTC1 ()
 in (Absyn.Expr_list EXPRLISTC)
end)
 in ( LrTable.NT 1, ( result, BOXLPAREN1left, BOXRPAREN1right), 
rest671)
end
|  ( 22, ( ( _, ( _, _, END1right)) :: ( _, ( MlyValue.DEFN DEFN2, _,
 _)) :: _ :: ( _, ( MlyValue.DEFN DEFN1, _, _)) :: ( _, ( _, 
LOCAL1left, _)) :: rest671)) => let val  result = MlyValue.EXPR (fn _
 => let val  DEFN1 = DEFN1 ()
 val  DEFN2 = DEFN2 ()
 in (Absyn.Expr_LocalInEnd(DEFN1,DEFN2))
end)
 in ( LrTable.NT 1, ( result, LOCAL1left, END1right), rest671)
end
|  ( 23, ( ( _, ( _, _, END1right)) :: ( _, ( MlyValue.EXPR EXPR1, _,
 _)) :: _ :: ( _, ( MlyValue.DEFN DEFN1, _, _)) :: ( _, ( _, LET1left,
 _)) :: rest671)) => let val  result = MlyValue.EXPR (fn _ => let val 
 (DEFN as DEFN1) = DEFN1 ()
 val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_LetInEnd(DEFN,EXPR))
end)
 in ( LrTable.NT 1, ( result, LET1left, END1right), rest671)
end
|  ( 24, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.EXPRLISTC 
EXPRLISTC1, _, _)) :: _ :: ( _, ( MlyValue.IDEN IDEN1, IDEN1left, _))
 :: rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (
IDEN as IDEN1) = IDEN1 ()
 val  (EXPRLISTC as EXPRLISTC1) = EXPRLISTC1 ()
 in (Absyn.Expr_App(Absyn.Expr_string IDEN,Absyn.Expr_list(EXPRLISTC))
)
end)
 in ( LrTable.NT 1, ( result, IDEN1left, RPAREN1right), rest671)
end
|  ( 25, ( ( _, ( _, _, END1right)) :: ( _, ( MlyValue.EXPR EXPR2, _,
 _)) :: _ :: ( _, ( MlyValue.EXPR EXPR1, _, _)) :: ( _, ( _, LET1left,
 _)) :: rest671)) => let val  result = MlyValue.EXPR (fn _ => let val 
 EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_LetInEnd(EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, LET1left, END1right), rest671)
end
|  ( 26, ( ( _, ( MlyValue.IDEN IDEN1, IDEN1left, IDEN1right)) :: 
rest671)) => let val  result = MlyValue.STRINGLIST (fn _ => let val  (
IDEN as IDEN1) = IDEN1 ()
 in ([IDEN])
end)
 in ( LrTable.NT 4, ( result, IDEN1left, IDEN1right), rest671)
end
|  ( 27, ( ( _, ( MlyValue.STRINGLIST STRINGLIST1, _, STRINGLIST1right
)) :: _ :: ( _, ( MlyValue.IDEN IDEN1, IDEN1left, _)) :: rest671)) =>
 let val  result = MlyValue.STRINGLIST (fn _ => let val  (IDEN as 
IDEN1) = IDEN1 ()
 val  (STRINGLIST as STRINGLIST1) = STRINGLIST1 ()
 in (IDEN::STRINGLIST)
end)
 in ( LrTable.NT 4, ( result, IDEN1left, STRINGLIST1right), rest671)

end
|  ( 28, ( ( _, ( MlyValue.EXPR EXPR1, EXPR1left, EXPR1right)) :: 
rest671)) => let val  result = MlyValue.EXPRLISTC (fn _ => let val  (
EXPR as EXPR1) = EXPR1 ()
 in ([EXPR])
end)
 in ( LrTable.NT 3, ( result, EXPR1left, EXPR1right), rest671)
end
|  ( 29, ( ( _, ( MlyValue.EXPRLISTC EXPRLISTC1, _, EXPRLISTC1right))
 :: _ :: ( _, ( MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) =>
 let val  result = MlyValue.EXPRLISTC (fn _ => let val  (EXPR as EXPR1
) = EXPR1 ()
 val  (EXPRLISTC as EXPRLISTC1) = EXPRLISTC1 ()
 in (EXPR::EXPRLISTC)
end)
 in ( LrTable.NT 3, ( result, EXPR1left, EXPRLISTC1right), rest671)

end
|  ( 30, ( ( _, ( MlyValue.EXPR EXPR1, _, EXPR1right)) :: _ :: ( _, ( 
MlyValue.IDEN IDEN1, IDEN1left, _)) :: rest671)) => let val  result = 
MlyValue.DEFN (fn _ => let val  (IDEN as IDEN1) = IDEN1 ()
 val  (EXPR as EXPR1) = EXPR1 ()
 in (Absyn.Expr_assign (IDEN,EXPR))
end)
 in ( LrTable.NT 5, ( result, IDEN1left, EXPR1right), rest671)
end
|  ( 31, ( ( _, ( _, _, BOXRPAREN1right)) :: ( _, ( MlyValue.DEFNLIST 
DEFNLIST1, _, _)) :: ( _, ( _, BOXLPAREN1left, _)) :: rest671)) => let
 val  result = MlyValue.DEFN (fn _ => let val  (DEFNLIST as DEFNLIST1)
 = DEFNLIST1 ()
 in (Absyn.Expr_assignpar (DEFNLIST))
end)
 in ( LrTable.NT 5, ( result, BOXLPAREN1left, BOXRPAREN1right), 
rest671)
end
|  ( 32, ( ( _, ( _, _, BOXRPAREN1right)) :: ( _, ( MlyValue.DEFN 
DEFN2, _, _)) :: _ :: ( _, ( MlyValue.DEFN DEFN1, _, _)) :: ( _, ( _, 
BOXLPAREN1left, _)) :: rest671)) => let val  result = MlyValue.DEFN
 (fn _ => let val  DEFN1 = DEFN1 ()
 val  DEFN2 = DEFN2 ()
 in (Absyn.Expr_assignseq (DEFN1,DEFN2))
end)
 in ( LrTable.NT 5, ( result, BOXLPAREN1left, BOXRPAREN1right), 
rest671)
end
|  ( 33, ( ( _, ( MlyValue.DEFN DEFN1, DEFN1left, DEFN1right)) :: 
rest671)) => let val  result = MlyValue.DEFNLIST (fn _ => let val  (
DEFN as DEFN1) = DEFN1 ()
 in ([DEFN])
end)
 in ( LrTable.NT 6, ( result, DEFN1left, DEFN1right), rest671)
end
|  ( 34, ( ( _, ( MlyValue.DEFNLIST DEFNLIST1, _, DEFNLIST1right)) ::
 _ :: ( _, ( MlyValue.DEFN DEFN1, DEFN1left, _)) :: rest671)) => let
 val  result = MlyValue.DEFNLIST (fn _ => let val  (DEFN as DEFN1) = 
DEFN1 ()
 val  (DEFNLIST as DEFNLIST1) = DEFNLIST1 ()
 in (DEFN::DEFNLIST)
end)
 in ( LrTable.NT 6, ( result, DEFN1left, DEFNLIST1right), rest671)
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
fun INT (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 0,(
ParserData.MlyValue.INT (fn () => i),p1,p2))
fun REAL (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 1,(
ParserData.MlyValue.REAL (fn () => i),p1,p2))
fun BOOL (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 2,(
ParserData.MlyValue.BOOL (fn () => i),p1,p2))
fun VAR (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 3,(
ParserData.MlyValue.VAR (fn () => i),p1,p2))
fun IDEN (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 4,(
ParserData.MlyValue.IDEN (fn () => i),p1,p2))
fun GOESTO (p1,p2) = Token.TOKEN (ParserData.LrTable.T 5,(
ParserData.MlyValue.VOID,p1,p2))
fun FN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 6,(
ParserData.MlyValue.VOID,p1,p2))
fun EQUAL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 7,(
ParserData.MlyValue.VOID,p1,p2))
fun ASSIGN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 8,(
ParserData.MlyValue.VOID,p1,p2))
fun NOTEQUAL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 9,(
ParserData.MlyValue.VOID,p1,p2))
fun LESSERTHAN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 10,(
ParserData.MlyValue.VOID,p1,p2))
fun GREATERTHAN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 11,(
ParserData.MlyValue.VOID,p1,p2))
fun IN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 12,(
ParserData.MlyValue.VOID,p1,p2))
fun LET (p1,p2) = Token.TOKEN (ParserData.LrTable.T 13,(
ParserData.MlyValue.VOID,p1,p2))
fun END (p1,p2) = Token.TOKEN (ParserData.LrTable.T 14,(
ParserData.MlyValue.VOID,p1,p2))
fun IF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 15,(
ParserData.MlyValue.VOID,p1,p2))
fun ELSE (p1,p2) = Token.TOKEN (ParserData.LrTable.T 16,(
ParserData.MlyValue.VOID,p1,p2))
fun THEN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 17,(
ParserData.MlyValue.VOID,p1,p2))
fun FI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 18,(
ParserData.MlyValue.VOID,p1,p2))
fun LOCAL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 19,(
ParserData.MlyValue.VOID,p1,p2))
fun COMMA (p1,p2) = Token.TOKEN (ParserData.LrTable.T 20,(
ParserData.MlyValue.VOID,p1,p2))
fun PLUS (p1,p2) = Token.TOKEN (ParserData.LrTable.T 21,(
ParserData.MlyValue.VOID,p1,p2))
fun LPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 22,(
ParserData.MlyValue.VOID,p1,p2))
fun RPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 23,(
ParserData.MlyValue.VOID,p1,p2))
fun SUB (p1,p2) = Token.TOKEN (ParserData.LrTable.T 24,(
ParserData.MlyValue.VOID,p1,p2))
fun MUL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 25,(
ParserData.MlyValue.VOID,p1,p2))
fun BOXLPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 26,(
ParserData.MlyValue.VOID,p1,p2))
fun BOXRPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 27,(
ParserData.MlyValue.VOID,p1,p2))
fun DIV (p1,p2) = Token.TOKEN (ParserData.LrTable.T 28,(
ParserData.MlyValue.VOID,p1,p2))
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 29,(
ParserData.MlyValue.VOID,p1,p2))
fun AND (p1,p2) = Token.TOKEN (ParserData.LrTable.T 30,(
ParserData.MlyValue.VOID,p1,p2))
fun LCURL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 31,(
ParserData.MlyValue.VOID,p1,p2))
fun RCURL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 32,(
ParserData.MlyValue.VOID,p1,p2))
fun OR (p1,p2) = Token.TOKEN (ParserData.LrTable.T 33,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 34,(
ParserData.MlyValue.VOID,p1,p2))
fun COLON (p1,p2) = Token.TOKEN (ParserData.LrTable.T 35,(
ParserData.MlyValue.VOID,p1,p2))
fun SEMI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 36,(
ParserData.MlyValue.VOID,p1,p2))
end
end
