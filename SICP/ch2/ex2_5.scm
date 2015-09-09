(define (pow x n)
 (if (= n 0)
  1
  (* x (pow x (- n 1)))))

(define (crazycons a b)
 (* (pow 2 a) (pow 3 b)))

(define (crazycar n)
 (define (iter n)
  (if (and (even? n) (> n 0))
   (+ 1 (iter (/ n 2)))
   0))
 (iter n))

(define (crazycdr n)
 (define (iter n)
  (if (and (= (remainder n 3) 0) (> n 0))
   (+ 1 (iter (/ n 3)))
   0))
 (iter n))

(define tuple (crazycons 10 2))
(display (crazycar tuple))
(newline)
(display (crazycdr tuple))
