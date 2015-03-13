Control.Print.printDepth := 100;
CM.make "sources.cm";
(*Calc.parse_string "abc+2+3;";*)

(*expr = Hello  , 23, 23.32, 45+32+3*)
(*term = Hello ; funsy (Hello, 23) *)
(*predsym = yo *)
(*pred = yo (Hello, 982.3)*)
(*fact= pred .*)
(*Calc.parse_string "yo;";*)
Calc.parse_string "f ( A, B) .;";
Calc.parse_string("apples(A) if oranges(B) , oran(C) .;");
Calc.parse_string "apples(O) if lol(Lol) , app(not (App)). ;";
Calc.parse_string "apples(A) if oranges(B) , oran(C) .;";
Calc.parse_string "app(true and false).;";
Calc.parse_string "app(A,B).;";
Calc.parse_string "app( 45/34 + 26 - 23.04 + 23.2E2 + 45 pow 5 ).;";
Calc.parse_string "app(Orange).;";
Calc.parse_string "app(Apples and Orange).;";
Calc.parse_string "app( not (Applies) ).;";