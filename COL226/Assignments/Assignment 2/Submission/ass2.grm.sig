signature Calc_TOKENS =
sig
type ('a,'b) token
type svalue
val SEMI:  'a * 'a -> (svalue,'a) token
val EOF:  'a * 'a -> (svalue,'a) token
val RPAREN:  'a * 'a -> (svalue,'a) token
val LPAREN:  'a * 'a -> (svalue,'a) token
val DOT:  'a * 'a -> (svalue,'a) token
val IF:  'a * 'a -> (svalue,'a) token
val LESSEREQ:  'a * 'a -> (svalue,'a) token
val GREATEREQ:  'a * 'a -> (svalue,'a) token
val LESSER:  'a * 'a -> (svalue,'a) token
val GREATER:  'a * 'a -> (svalue,'a) token
val NOTEQUAL:  'a * 'a -> (svalue,'a) token
val EQUALTO:  'a * 'a -> (svalue,'a) token
val POW:  'a * 'a -> (svalue,'a) token
val ABS:  'a * 'a -> (svalue,'a) token
val MOD:  'a * 'a -> (svalue,'a) token
val DIV:  'a * 'a -> (svalue,'a) token
val SUB:  'a * 'a -> (svalue,'a) token
val MULT:  'a * 'a -> (svalue,'a) token
val PLUS:  'a * 'a -> (svalue,'a) token
val NOT:  'a * 'a -> (svalue,'a) token
val COMMA:  'a * 'a -> (svalue,'a) token
val FUNSY:  'a * 'a -> (svalue,'a) token
val OR:  'a * 'a -> (svalue,'a) token
val AND:  'a * 'a -> (svalue,'a) token
val BOOLEAN: (bool) *  'a * 'a -> (svalue,'a) token
val CONSREAL: (real) *  'a * 'a -> (svalue,'a) token
val CONSINT: (int) *  'a * 'a -> (svalue,'a) token
val VAR: (string) *  'a * 'a -> (svalue,'a) token
val IDEN: (string) *  'a * 'a -> (svalue,'a) token
end
signature Calc_LRVALS=
sig
structure Tokens : Calc_TOKENS
structure ParserData:PARSER_DATA
sharing type ParserData.Token.token = Tokens.token
sharing type ParserData.svalue = Tokens.svalue
end
