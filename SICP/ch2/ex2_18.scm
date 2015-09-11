(define (reverse li)
 (define (iter remain ret)
  (if (null? remain)
   ret
   (iter (cdr remain) (cons (car remain) ret))))
 (iter li '()))

(display (reverse (list 1 2 3 4 5)))
