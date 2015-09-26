(define (fringe tree)
 (if (list? tree)
  (if (null? tree)
   tree
   (append
    (fringe (car tree))
    (fringe (cdr tree))))
  (list tree)))

(define x (list (list 1 2) (list 3 4)))
(display (fringe x))
(newline)
(display (fringe (list x x)))
