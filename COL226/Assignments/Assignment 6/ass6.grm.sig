signature Calc_TOKENS =
sig
type ('a,'b) token
type svalue
val SEMI:  'a * 'a -> (svalue,'a) token
val COLON:  'a * 'a -> (svalue,'a) token
val EOF:  'a * 'a -> (svalue,'a) token
val OR:  'a * 'a -> (svalue,'a) token
val RCURL:  'a * 'a -> (svalue,'a) token
val LCURL:  'a * 'a -> (svalue,'a) token
val AND:  'a * 'a -> (svalue,'a) token
val DOT:  'a * 'a -> (svalue,'a) token
val DIV:  'a * 'a -> (svalue,'a) token
val MUL:  'a * 'a -> (svalue,'a) token
val SUB:  'a * 'a -> (svalue,'a) token
val RPAREN:  'a * 'a -> (svalue,'a) token
val LPAREN:  'a * 'a -> (svalue,'a) token
val PLUS:  'a * 'a -> (svalue,'a) token
val COMMA:  'a * 'a -> (svalue,'a) token
val LOCAL:  'a * 'a -> (svalue,'a) token
val FI:  'a * 'a -> (svalue,'a) token
val THEN:  'a * 'a -> (svalue,'a) token
val ELSE:  'a * 'a -> (svalue,'a) token
val IF:  'a * 'a -> (svalue,'a) token
val END:  'a * 'a -> (svalue,'a) token
val LET:  'a * 'a -> (svalue,'a) token
val IN:  'a * 'a -> (svalue,'a) token
val GREATERTHAN:  'a * 'a -> (svalue,'a) token
val LESSERTHAN:  'a * 'a -> (svalue,'a) token
val NOTEQUAL:  'a * 'a -> (svalue,'a) token
val ASSIGN:  'a * 'a -> (svalue,'a) token
val EQUAL:  'a * 'a -> (svalue,'a) token
val FN:  'a * 'a -> (svalue,'a) token
val GOESTO:  'a * 'a -> (svalue,'a) token
val IDEN: (string) *  'a * 'a -> (svalue,'a) token
val VAR: (string) *  'a * 'a -> (svalue,'a) token
val BOOL: (bool) *  'a * 'a -> (svalue,'a) token
val REAL: (real) *  'a * 'a -> (svalue,'a) token
val INT: (int) *  'a * 'a -> (svalue,'a) token
end
signature Calc_LRVALS=
sig
structure Tokens : Calc_TOKENS
structure ParserData:PARSER_DATA
sharing type ParserData.Token.token = Tokens.token
sharing type ParserData.svalue = Tokens.svalue
end
