signature PROGRAM =
	sig
		datatype Program = ProgList of Term list
		and Term = Term_real of real
				| Term_var of string
				| Term_int of int
				| Term_Oper of string*Term list
end

structure Program :> PROGRAM = 
	struct
		datatype Program = ProgList of Term list
		and Term = Term_real of real
				| Term_var of string
				| Term_int of int
				| Term_Oper of string*Term list
end;