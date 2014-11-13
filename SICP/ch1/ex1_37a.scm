; 1-37 之迭代版本

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

(define fai
  (/ 1
     (cont-frac
       (lambda (i) 1.0)
       (lambda (i) 1.0)
       10)))

;(display fai)
