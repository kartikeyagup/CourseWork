Control.Print.printDepth := 100;
CM.make "sources.cm";
(*Calc.parse_string "abc+2+3;";*)

(*expr = Hello  , 23, 23.32, 45+32+3*)
(*term = Hello ; funsy (Hello, 23) *)
(*predsym = yo *)
(*pred = yo (Hello, 982.3)*)
(*fact= pred .*)
Calc.parse_string "yo;";
(*Calc.parse_string "yo (Hello, 982.3) .;"*)