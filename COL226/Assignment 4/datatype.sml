signature PROGRAM =
	sig
		datatype Program = ProgList of Term list
		and Term = Term_Single of Query
				| Term_Conditional of Query*Query list
		and Query = Query_Oper of string*Data list
		and Data = Data_Var of string
				| Data_Cons of string
				| Data_Term of Term	
				| Data_List of Data list

end

structure Program :> PROGRAM = 
	struct
		datatype Program = ProgList of Term list
		and Term = Term_Single of Query
				| Term_Conditional of Query*Query list
		and Query = Query_Oper of string*Data list
		and Data = Data_Var of string
				| Data_Cons of string
				| Data_Term of Term
				| Data_List of Data list
end;