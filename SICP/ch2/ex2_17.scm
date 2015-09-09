(define (last-pair li)
 (if (null? (cdr li))
  li
  (last-pair (cdr li))))

(display (last-pair (list 1 2 4 8 16)))
