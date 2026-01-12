: BUFFER: ( u "<name>" -- ; -- addr )
(* a-addr is the address of the space reserved by BUFFER: when it defined name. 
 * The program is responsible for initializing the contents. 
 *)
  CREATE ALLOT ;