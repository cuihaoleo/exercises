(load "ex1_37a.scm")
(load "ex1_37b.scm")

(define (tan-cf-meta func x k)
  (func
    (lambda (i)
      (if (= i 1)
        x
        (- (* x x))))
    (lambda (i) (- (* 2 i) 1))
    k))

; 迭代版本
(define (tan-cf x k) (tan-cf-meta cont-frac x k))
; 递归版本
(define (tan-cf-recur x k) (tan-cf-meta cont-frac-recur x k))

