; it works!
(define (mycons x y)
 (lambda (m) (m x y)))

(define (mycar z)
 (z (lambda (p q) p)))

(define (mycdr z)
 (z (lambda (p q) q)))

(define tuple (mycons 1 2))
(display (mycar tuple))
(newline)
(display (mycdr tuple))
