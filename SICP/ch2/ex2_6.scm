; Church Number!
(define zero (lambda (f) (lambda (x) x)))
(define (add-1 n)
 (lambda (f) (lambda (x) (f ((n f) x)))))

;   0 = lambda f: lambda x: x
; inc = lambda n: lambda f: lambda x: f(n(f)(x))
;   1 = lambda f: lambda x: f(x)
;   2 = lambda f: lambda x: f(f(x))
;   + = lambda n, m: lambda f: lambda x: n(f)(m(f)(x))
(define (one) (lambda (f) (lambda (x) (f x))))
(define (two) (lambda (f) (lambda (x) (f (f x)))))
(define (plus n m)
 (lambda (f) (lambda (x) ((n f) ((m f) x)))))
