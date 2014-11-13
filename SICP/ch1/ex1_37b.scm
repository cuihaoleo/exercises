(define (cont-frac n d k)
  (define (go depth)
    (if (= depth k)
      (/ (n depth) (d depth))
      (/ (n depth)
         (+ (d depth)
            (go (+ depth 1))))))
  (go 1))

(define iaf
  (cont-frac
    (lambda (i) 1.0)
    (lambda (i) 1.0)
    10))

(display (/ 1 iaf))
