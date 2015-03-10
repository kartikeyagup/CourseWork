signature ABSYN =
  sig
    datatype node = LEAFS of string | LEAFI of int | NODE of string * node list
  end

structure Absyn :> ABSYN =
   struct
      datatype node = LEAFS of string | LEAFI of int | NODE of string * node list
   end