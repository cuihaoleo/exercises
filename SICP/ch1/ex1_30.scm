; 求和函数（尾递归）
(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter 
        (next a)
        (+ 
          result
          (term a)))))
  (iter a 0))

; 计算立方和
(define (cube x) (* x x x))
(define (sum-cubes a b)
  (define (inc n) (+ n 1))
  (sum cube a inc b))

; pi
(define (pi-sum a b)
  (define (pi-term x)
    (/ 1.0 (* x (+ x 2))))
  (define (pi-next x)
    (+ x 4))
  (sum pi-term a pi-next b))

(define pi (* 8 (pi-sum 1 10000)))
(display pi)

