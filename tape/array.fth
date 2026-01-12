(* Size Multipliers *)

: CHARS ( n -- n )
  #1 * ;

: CELLS ( n -- n )
  cell * ;


: INTS ( n -- n )
  int * ;

: FLOATS ( n -- n )
  float * ;


(* Address Helpers *)

: +@ ( a n -- n )
  + @ ;

: +! ( n a n -- )
  + ! ;

: +F@ ( a n -- f )
  + F@ ;

: +F! ( f a n -- )
  + F! ;