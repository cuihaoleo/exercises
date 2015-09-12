(define (same-parity first . rest)
 (if (even? first)
  (cons first (filter even? rest))
  (cons first (filter odd? rest))))
