; scheme 的 remainder 是向零取整的余数还是向下取整的呢？
(define (gcd a b)
 (if (= b 0)
  a
  (gcd b (remainder a b))))

(define (make-rat n d)
 (let ((g (abs (gcd n d))))
  (if (>= d 0)
    (cons (/ n g) (/ d g))
    (cons (/ (- n) g) (/ (- d) g)))))

(display (make-rat 7 8))
(newline)
(display (make-rat -2 10))
(newline)
(display (make-rat -20 -10))
(newline)
(display (make-rat -5 10))
(newline)
