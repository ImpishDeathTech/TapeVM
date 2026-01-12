

: fizz-buzz ( n -- )
  #0 DO
    I #15 % 0= IF 
      c" Fizz Buzz" type cr
    ELSE I #5 % 0= IF 
      c" Buzz" type cr
    ELSE I #3 % 0= IF 
      c" Fizz" type cr
    ELSE 
      I . cr
    THEN: #3
  LOOP
;

&100 fizz-buzz
bye