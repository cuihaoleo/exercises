(load "ex1_37a.scm")

(define (calculate-e k)
  (define (d i)
    (if (= (remainder i 3) 2)
      (* 2.0 (+ 1 (quotient i 3)))
      1.0))
  (+ 2 (cont-frac (lambda (x) 1.0) d k)))

