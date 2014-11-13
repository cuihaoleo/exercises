(define tolerance 0.000001)

(define (fixed-point f first-guess)
  (define (close-enough? a b)
    (< (abs (- a b)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(define fai
  (fixed-point
    (lambda (x)
      (+ 1.0 (/ 1.0 x)))
    1.0))

(display fai)
(newline)
