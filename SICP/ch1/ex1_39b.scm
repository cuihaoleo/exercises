(define (cont-frac n d k)
  (define (go depth)
    (if (= depth k)
      (/ (n depth) (d depth))
      (/ (n depth)
         (+ (d depth)
            (go (+ depth 1))))))
  (go 1))

(define (tan-cf x k)
  (cont-frac
    (lambda (i)
      (if (= i 1)
        x
        (- (* x x))))
    (lambda (i) (- (* 2 i) 1))
    k))

(display "Built-in tan(10): ")
(display (tan 10.0))
(newline)

(display "My tan-cf(10): ")
(display (tan-cf 10.0 100))
(newline)
