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
\\001\000\001\000\006\000\000\000\
\\001\000\001\000\018\000\002\000\017\000\010\000\016\000\000\000\
\\001\000\003\000\020\000\000\000\
\\001\000\004\000\010\000\000\000\
\\001\000\005\000\030\000\011\000\029\000\012\000\028\000\000\000\
\\001\000\007\000\022\000\000\000\
\\001\000\008\000\000\000\009\000\000\000\000\000\
\\001\000\011\000\027\000\000\000\
\\001\000\011\000\034\000\000\000\
\\036\000\000\000\
\\037\000\001\000\006\000\000\000\
\\038\000\000\000\
\\039\000\000\000\
\\040\000\000\000\
\\041\000\003\000\008\000\006\000\007\000\000\000\
\\042\000\005\000\019\000\000\000\
\\043\000\000\000\
\\044\000\000\000\
\\045\000\005\000\021\000\000\000\
\\046\000\000\000\
\\047\000\004\000\010\000\000\000\
\\048\000\000\000\
\\049\000\000\000\
\\050\000\000\000\
\\051\000\000\000\
\\052\000\000\000\
\\053\000\005\000\030\000\000\000\
\\054\000\000\000\
\"
val actionRowNumbers =
"\000\000\014\000\009\000\010\000\
\\003\000\000\000\012\000\011\000\
\\001\000\015\000\002\000\018\000\
\\005\000\022\000\001\000\021\000\
\\020\000\000\000\013\000\001\000\
\\017\000\007\000\004\000\016\000\
\\019\000\025\000\001\000\023\000\
\\001\000\008\000\027\000\026\000\
\\024\000\006\000"
val gotoT =
"\
\\001\000\033\000\002\000\003\000\003\000\002\000\005\000\001\000\000\000\
\\000\000\
\\000\000\
\\002\000\003\000\003\000\007\000\005\000\001\000\000\000\
\\000\000\
\\004\000\010\000\005\000\009\000\000\000\
\\000\000\
\\000\000\
\\002\000\013\000\005\000\001\000\006\000\012\000\007\000\011\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\013\000\005\000\001\000\007\000\022\000\008\000\021\000\000\000\
\\000\000\
\\000\000\
\\004\000\023\000\005\000\009\000\000\000\
\\000\000\
\\002\000\013\000\005\000\001\000\006\000\024\000\007\000\011\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\013\000\005\000\001\000\007\000\029\000\000\000\
\\000\000\
\\002\000\013\000\005\000\001\000\007\000\031\000\008\000\030\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\"
val numstates = 34
val numrules = 19
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
 | VAR of unit ->  (string) | IDEN of unit ->  (string)
 | DATALIST of unit ->  (Program.Data)
 | DATA of unit ->  (Program.Data)
 | STRINGLIST of unit ->  (Program.Data list)
 | QUERY of unit ->  (Program.Query)
 | BODY of unit ->  (Program.Query list)
 | TERMLIST of unit ->  (Program.Term list)
 | TERM of unit ->  (Program.Term)
 | PROG of unit ->  (Program.Program)
end
type svalue = MlyValue.svalue
type result = Program.Program
end
structure EC=
struct
open LrTable
infix 5 $$
fun x $$ y = y::x
val is_keyword =
fn _ => false
val preferred_change : (term list * term list) list = 
nil
val noShift = 
fn (T 7) => true | _ => false
val showTerminal =
fn (T 0) => "IDEN"
  | (T 1) => "VAR"
  | (T 2) => "DOT"
  | (T 3) => "LPAREN"
  | (T 4) => "COMMA"
  | (T 5) => "IF"
  | (T 6) => "RPAREN"
  | (T 7) => "EOF"
  | (T 8) => "SEMI"
  | (T 9) => "LBOXPAREN"
  | (T 10) => "RBOXPAREN"
  | (T 11) => "SEPARATOR"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms : term list = nil
 $$ (T 11) $$ (T 10) $$ (T 9) $$ (T 8) $$ (T 7) $$ (T 6) $$ (T 5) $$ 
(T 4) $$ (T 3) $$ (T 2)end
structure Actions =
struct 
exception mlyAction of int
local open Header in
val actions = 
fn (i392,defaultPos,stack,
    (()):arg) =>
case (i392,stack)
of  ( 0, ( ( _, ( MlyValue.TERMLIST TERMLIST1, TERMLIST1left, 
TERMLIST1right)) :: rest671)) => let val  result = MlyValue.PROG (fn _
 => let val  (TERMLIST as TERMLIST1) = TERMLIST1 ()
 in (Program.ProgList TERMLIST)
end)
 in ( LrTable.NT 0, ( result, TERMLIST1left, TERMLIST1right), rest671)

end
|  ( 1, ( ( _, ( MlyValue.TERM TERM1, TERM1left, TERM1right)) :: 
rest671)) => let val  result = MlyValue.TERMLIST (fn _ => let val  (
TERM as TERM1) = TERM1 ()
 in ([TERM])
end)
 in ( LrTable.NT 2, ( result, TERM1left, TERM1right), rest671)
end
|  ( 2, ( ( _, ( MlyValue.TERMLIST TERMLIST1, _, TERMLIST1right)) :: (
 _, ( MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let val  
result = MlyValue.TERMLIST (fn _ => let val  (TERM as TERM1) = TERM1
 ()
 val  (TERMLIST as TERMLIST1) = TERMLIST1 ()
 in ([TERM]@TERMLIST)
end)
 in ( LrTable.NT 2, ( result, TERM1left, TERMLIST1right), rest671)
end
|  ( 3, ( ( _, ( _, _, DOT1right)) :: ( _, ( MlyValue.QUERY QUERY1, 
QUERY1left, _)) :: rest671)) => let val  result = MlyValue.TERM (fn _
 => let val  (QUERY as QUERY1) = QUERY1 ()
 in (Program.Term_Single QUERY)
end)
 in ( LrTable.NT 1, ( result, QUERY1left, DOT1right), rest671)
end
|  ( 4, ( ( _, ( _, _, DOT1right)) :: ( _, ( MlyValue.BODY BODY1, _, _
)) :: _ :: ( _, ( MlyValue.QUERY QUERY1, QUERY1left, _)) :: rest671))
 => let val  result = MlyValue.TERM (fn _ => let val  (QUERY as QUERY1
) = QUERY1 ()
 val  (BODY as BODY1) = BODY1 ()
 in (Program.Term_Conditional (QUERY, BODY))
end)
 in ( LrTable.NT 1, ( result, QUERY1left, DOT1right), rest671)
end
|  ( 5, ( ( _, ( MlyValue.QUERY QUERY1, QUERY1left, QUERY1right)) :: 
rest671)) => let val  result = MlyValue.TERM (fn _ => let val  (QUERY
 as QUERY1) = QUERY1 ()
 in (Program.Term_Single QUERY)
end)
 in ( LrTable.NT 1, ( result, QUERY1left, QUERY1right), rest671)
end
|  ( 6, ( ( _, ( MlyValue.QUERY QUERY1, QUERY1left, QUERY1right)) :: 
rest671)) => let val  result = MlyValue.BODY (fn _ => let val  (QUERY
 as QUERY1) = QUERY1 ()
 in ([QUERY])
end)
 in ( LrTable.NT 3, ( result, QUERY1left, QUERY1right), rest671)
end
|  ( 7, ( ( _, ( MlyValue.BODY BODY1, _, BODY1right)) :: _ :: ( _, ( 
MlyValue.QUERY QUERY1, QUERY1left, _)) :: rest671)) => let val  result
 = MlyValue.BODY (fn _ => let val  (QUERY as QUERY1) = QUERY1 ()
 val  (BODY as BODY1) = BODY1 ()
 in ([QUERY]@BODY)
end)
 in ( LrTable.NT 3, ( result, QUERY1left, BODY1right), rest671)
end
|  ( 8, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.STRINGLIST 
STRINGLIST1, _, _)) :: _ :: ( _, ( MlyValue.IDEN IDEN1, IDEN1left, _))
 :: rest671)) => let val  result = MlyValue.QUERY (fn _ => let val  (
IDEN as IDEN1) = IDEN1 ()
 val  (STRINGLIST as STRINGLIST1) = STRINGLIST1 ()
 in (Program.Query_Oper(IDEN,STRINGLIST))
end)
 in ( LrTable.NT 4, ( result, IDEN1left, RPAREN1right), rest671)
end
|  ( 9, ( ( _, ( MlyValue.DATA DATA1, DATA1left, DATA1right)) :: 
rest671)) => let val  result = MlyValue.STRINGLIST (fn _ => let val  (
DATA as DATA1) = DATA1 ()
 in ([DATA])
end)
 in ( LrTable.NT 5, ( result, DATA1left, DATA1right), rest671)
end
|  ( 10, ( ( _, ( MlyValue.STRINGLIST STRINGLIST1, _, STRINGLIST1right
)) :: _ :: ( _, ( MlyValue.DATA DATA1, DATA1left, _)) :: rest671)) =>
 let val  result = MlyValue.STRINGLIST (fn _ => let val  (DATA as 
DATA1) = DATA1 ()
 val  (STRINGLIST as STRINGLIST1) = STRINGLIST1 ()
 in ([DATA]@STRINGLIST)
end)
 in ( LrTable.NT 5, ( result, DATA1left, STRINGLIST1right), rest671)

end
|  ( 11, ( ( _, ( MlyValue.IDEN IDEN1, IDEN1left, IDEN1right)) :: 
rest671)) => let val  result = MlyValue.DATA (fn _ => let val  (IDEN
 as IDEN1) = IDEN1 ()
 in (Program.Data_Cons IDEN)
end)
 in ( LrTable.NT 6, ( result, IDEN1left, IDEN1right), rest671)
end
|  ( 12, ( ( _, ( MlyValue.VAR VAR1, VAR1left, VAR1right)) :: rest671)
) => let val  result = MlyValue.DATA (fn _ => let val  (VAR as VAR1) =
 VAR1 ()
 in (Program.Data_Var VAR)
end)
 in ( LrTable.NT 6, ( result, VAR1left, VAR1right), rest671)
end
|  ( 13, ( ( _, ( MlyValue.TERM TERM1, TERM1left, TERM1right)) :: 
rest671)) => let val  result = MlyValue.DATA (fn _ => let val  (TERM
 as TERM1) = TERM1 ()
 in (Program.Data_Term TERM)
end)
 in ( LrTable.NT 6, ( result, TERM1left, TERM1right), rest671)
end
|  ( 14, ( ( _, ( _, _, RBOXPAREN1right)) :: ( _, ( MlyValue.DATA 
DATA1, _, _)) :: ( _, ( _, LBOXPAREN1left, _)) :: rest671)) => let
 val  result = MlyValue.DATA (fn _ => let val  (DATA as DATA1) = DATA1
 ()
 in (Program.Data_List[DATA])
end)
 in ( LrTable.NT 6, ( result, LBOXPAREN1left, RBOXPAREN1right), 
rest671)
end
|  ( 15, ( ( _, ( _, _, RBOXPAREN1right)) :: ( _, ( MlyValue.DATA 
DATA2, _, _)) :: _ :: ( _, ( MlyValue.DATA DATA1, _, _)) :: ( _, ( _, 
LBOXPAREN1left, _)) :: rest671)) => let val  result = MlyValue.DATA
 (fn _ => let val  DATA1 = DATA1 ()
 val  DATA2 = DATA2 ()
 in (Program.Data_List[DATA1,Program.Data_List [DATA2]])
end)
 in ( LrTable.NT 6, ( result, LBOXPAREN1left, RBOXPAREN1right), 
rest671)
end
|  ( 16, ( ( _, ( _, _, RBOXPAREN1right)) :: ( _, ( MlyValue.DATALIST 
DATALIST1, _, _)) :: ( _, ( _, LBOXPAREN1left, _)) :: rest671)) => let
 val  result = MlyValue.DATA (fn _ => let val  (DATALIST as DATALIST1)
 = DATALIST1 ()
 in (DATALIST)
end)
 in ( LrTable.NT 6, ( result, LBOXPAREN1left, RBOXPAREN1right), 
rest671)
end
|  ( 17, ( ( _, ( MlyValue.DATA DATA1, DATA1left, DATA1right)) :: 
rest671)) => let val  result = MlyValue.DATALIST (fn _ => let val  (
DATA as DATA1) = DATA1 ()
 in (Program.Data_List [DATA])
end)
 in ( LrTable.NT 7, ( result, DATA1left, DATA1right), rest671)
end
|  ( 18, ( ( _, ( MlyValue.DATALIST DATALIST1, _, DATALIST1right)) ::
 _ :: ( _, ( MlyValue.DATA DATA1, DATA1left, _)) :: rest671)) => let
 val  result = MlyValue.DATALIST (fn _ => let val  (DATA as DATA1) = 
DATA1 ()
 val  (DATALIST as DATALIST1) = DATALIST1 ()
 in (Program.Data_List [DATA,DATALIST])
end)
 in ( LrTable.NT 7, ( result, DATA1left, DATALIST1right), rest671)
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
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 2,(
ParserData.MlyValue.VOID,p1,p2))
fun LPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 3,(
ParserData.MlyValue.VOID,p1,p2))
fun COMMA (p1,p2) = Token.TOKEN (ParserData.LrTable.T 4,(
ParserData.MlyValue.VOID,p1,p2))
fun IF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 5,(
ParserData.MlyValue.VOID,p1,p2))
fun RPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 6,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 7,(
ParserData.MlyValue.VOID,p1,p2))
fun SEMI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 8,(
ParserData.MlyValue.VOID,p1,p2))
fun LBOXPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 9,(
ParserData.MlyValue.VOID,p1,p2))
fun RBOXPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 10,(
ParserData.MlyValue.VOID,p1,p2))
fun SEPARATOR (p1,p2) = Token.TOKEN (ParserData.LrTable.T 11,(
ParserData.MlyValue.VOID,p1,p2))
end
end
