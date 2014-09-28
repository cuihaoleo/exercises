(define (accumulate combiner null-value term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter 
        (next a)
        (combiner 
          result
          (term a)))))
  (iter a null-value))

(define (product term a next b)
  (accumulate * 1.0 term a next b))

(define (factorial n)
  (product
    (lambda (n) n)
    1
    (lambda (n) (+ n 1))
    n))

(display (factorial 9))

