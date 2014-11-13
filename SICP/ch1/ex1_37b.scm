; 1-37 之递归版本

(define (cont-frac-recur n d k)
  (define (go depth)
    (if (= depth k)
      (/ (n depth) (d depth))
      (/ (n depth)
         (+ (d depth)
            (go (+ depth 1))))))
  (go 1))

(define fai2
  (/ 1
     (cont-frac-recur
       (lambda (i) 1.0)
       (lambda (i) 1.0)
       10)))

;(display fai)
