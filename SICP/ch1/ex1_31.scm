(define (product term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter 
        (next a)
        (* 
          result
          (term a)))))
  (iter a 1.0))

(define (factorial n)
  (product
    (lambda (n) n)
    1
    (lambda (n) (+ n 1))
    n))

;(display (factorial 9))

