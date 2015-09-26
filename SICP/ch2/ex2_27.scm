(define (deep-reverse li)
 (define (iter remain ret)
  (if (null? remain)
   ret
   (iter
    (cdr remain)
    (cons
     (let ((this (car remain)))
      (if (list? this)
       (iter this '())
       this))
     ret))))
 (iter li '()))

(display (deep-reverse (list (list 1 2) (list 3 4 (list 5 6 7)))))
