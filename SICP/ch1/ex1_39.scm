(define (cont-frac n d k)
  (define (go depth ans)
    (if (= depth 0)
      ans
      (go
        (- depth 1)
        (/ (n depth) (+ (d depth) ans)))))
  (go
    (- k 1)
    (/ (n k) (d k))))

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

