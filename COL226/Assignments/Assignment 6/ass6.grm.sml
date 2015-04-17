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
\\001\000\001\000\007\000\002\000\006\000\003\000\005\000\000\000\
\\001\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\028\000\010\000\029\000\009\000\030\000\008\000\000\000\
\\001\000\031\000\000\000\032\000\000\000\000\000\
\\031\000\000\000\
\\032\000\001\000\007\000\002\000\006\000\003\000\005\000\000\000\
\\033\000\000\000\
\\034\000\000\000\
\\035\000\000\000\
\\036\000\000\000\
\\037\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\038\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\039\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\040\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\041\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\042\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\043\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\044\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\045\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\\046\000\008\000\018\000\010\000\017\000\011\000\016\000\012\000\015\000\
\\022\000\014\000\025\000\013\000\026\000\012\000\027\000\011\000\
\\029\000\009\000\030\000\008\000\000\000\
\"
val actionRowNumbers =
"\000\000\003\000\001\000\008\000\
\\007\000\006\000\000\000\000\000\
\\004\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\
\\000\000\014\000\013\000\005\000\
\\011\000\010\000\012\000\009\000\
\\017\000\018\000\016\000\015\000\
\\002\000"
val gotoT =
"\
\\001\000\028\000\002\000\002\000\003\000\001\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\017\000\000\000\
\\002\000\018\000\000\000\
\\002\000\002\000\003\000\019\000\000\000\
\\002\000\020\000\000\000\
\\002\000\021\000\000\000\
\\002\000\022\000\000\000\
\\002\000\023\000\000\000\
\\002\000\024\000\000\000\
\\002\000\025\000\000\000\
\\002\000\026\000\000\000\
\\002\000\027\000\000\000\
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
val numstates = 29
val numrules = 16
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
 | INT of unit ->  (int) | EXPRLIST of unit ->  (Absyn.expr list)
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
 $$ (T 26))::
(nil
,nil
 $$ (T 24))::
nil
val noShift = 
fn (T 30) => true | _ => false
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
  | (T 26) => "DIV"
  | (T 27) => "DOT"
  | (T 28) => "AND"
  | (T 29) => "OR"
  | (T 30) => "EOF"
  | (T 31) => "SEMI"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms : term list = nil
 $$ (T 31) $$ (T 30) $$ (T 29) $$ (T 28) $$ (T 27) $$ (T 26) $$ (T 25)
 $$ (T 24) $$ (T 23) $$ (T 22) $$ (T 21) $$ (T 20) $$ (T 19) $$ (T 18)
 $$ (T 17) $$ (T 16) $$ (T 15) $$ (T 14) $$ (T 13) $$ (T 12) $$ (T 11)
 $$ (T 10) $$ (T 9) $$ (T 8) $$ (T 7) $$ (T 6) $$ (T 5)end
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
|  ( 4, ( ( _, ( MlyValue.REAL REAL1, REAL1left, REAL1right)) :: 
rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (REAL
 as REAL1) = REAL1 ()
 in (Absyn.Expr_real REAL)
end)
 in ( LrTable.NT 1, ( result, REAL1left, REAL1right), rest671)
end
|  ( 5, ( ( _, ( MlyValue.BOOL BOOL1, BOOL1left, BOOL1right)) :: 
rest671)) => let val  result = MlyValue.EXPR (fn _ => let val  (BOOL
 as BOOL1) = BOOL1 ()
 in (Absyn.Expr_bool (BOOL))
end)
 in ( LrTable.NT 1, ( result, BOOL1left, BOOL1right), rest671)
end
|  ( 6, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.ADD, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 7, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.MUL, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 8, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.DIV, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 9, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.SUB, EXPR1, EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 10, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.AND,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 11, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.OR,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 12, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.EQUALTO,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 13, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.NOTEQUAL,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 14, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.GREATER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
end
|  ( 15, ( ( _, ( MlyValue.EXPR EXPR2, _, EXPR2right)) :: _ :: ( _, ( 
MlyValue.EXPR EXPR1, EXPR1left, _)) :: rest671)) => let val  result = 
MlyValue.EXPR (fn _ => let val  EXPR1 = EXPR1 ()
 val  EXPR2 = EXPR2 ()
 in (Absyn.Expr_bin (Absyn.LESSER,EXPR1,EXPR2))
end)
 in ( LrTable.NT 1, ( result, EXPR1left, EXPR2right), rest671)
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
fun DIV (p1,p2) = Token.TOKEN (ParserData.LrTable.T 26,(
ParserData.MlyValue.VOID,p1,p2))
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 27,(
ParserData.MlyValue.VOID,p1,p2))
fun AND (p1,p2) = Token.TOKEN (ParserData.LrTable.T 28,(
ParserData.MlyValue.VOID,p1,p2))
fun OR (p1,p2) = Token.TOKEN (ParserData.LrTable.T 29,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 30,(
ParserData.MlyValue.VOID,p1,p2))
fun SEMI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 31,(
ParserData.MlyValue.VOID,p1,p2))
end
end
