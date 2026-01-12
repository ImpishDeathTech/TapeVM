(* Size Multipliers *)

: CHAR+ 
  #1 + ;

: CHARS ( n -- n )
  #1 * ;

: CELL+ 
  cell + ;

: CELLS ( n -- n )
  cell * ;

: INTS ( n -- n )
  int * ;

: FLOATS ( n -- n )
  float * ;


(* Address Helpers *)

: +@ ( a n -- n )
  cells + @ ;

: +! ( n a n -- )
  cells + ! ;

: +F@ ( a n -- f )
  + F@ ;

: +F! ( f a n -- )
  + F! ;