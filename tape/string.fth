INCLUDE char
INCLUDE array

: ." ( "<chars>" --  ) 
  '"' parse type
;

: S>STR ( n -- str n )
  >str . str>
;

: U>STR ( u -- str n )
  >str u. str> 
;

: F>STR ( f -- str n )
  >str f. str> 
;
