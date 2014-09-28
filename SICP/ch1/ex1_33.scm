(define (filtered-accumulate combiner null-value term a next b filtered)
  (define (iter a result)
    (if (> a b)
      result
      (iter 
        (next a)
        (if (filtered a)
          result
          (combiner
            result
            (term a))))))
  (iter a null-value))

(define (accumulate combiner null-value term a next b)
  (filtered-accumulate combiner null-value term a next b (lambda (x) #f)))

(define (product term a next b)
  (accumulate * 1.0 term a next b))

(define (factorial n)
  (product
    (lambda (n) n)
    1
    (lambda (n) (+ n 1))
    n))

(display (factorial 9))

(define (prime? n)
  (define (loop i)
    (if (> i (quotient n 2))
      #t
      (if (= 0 (remainder n i))
        #f
        (loop (+ i 1)))))
  (loop 2))

(define (prime-sum a b)
  (filtered-accumulate
    +
    0
    (lambda (n) n)
    a
    (lambda (n) (+ n 1))
    b
    (lambda (n) (not (prime? n)))))

(newline)
(display (prime-sum 2 10))
(newline)
