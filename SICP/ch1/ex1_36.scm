(define tolerance 0.000001)

(define (fixed-point f first-guess)
  (define (close-enough? a b)
    (< (abs (- a b)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (display next)
      (newline)
      (if (close-enough? guess next)
        next
        (try next))))
  (display first-guess)
  (newline)
  (try first-guess))

(define x
  (fixed-point
    (lambda (x)
      (/ (log 1000) (log x)))
    2.0))

(display "ANSWER: ")
(display x)
(newline)
