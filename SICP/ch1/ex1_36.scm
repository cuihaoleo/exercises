(define tolerance 0.000001)

(define (fixed-point-show-proc f first-guess)
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

; I comment the example to supress output when loaded.
;(define x
;  (fixed-point-show-proc
;    (lambda (x)
;      (/ (log 1000) (log x)))
;   2.0))
