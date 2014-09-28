(define (f g)
  (g 2))

(define (square x) (* x x))
(display (f square))
(display (f (lambda (z) (* z (+ z 1)))))

; this cause an error
(f f)

