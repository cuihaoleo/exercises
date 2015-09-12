(define (my-for-each f li)
 (cond ((not (null? li)) (f (car li)) (my-for-each f (cdr li)))))

(define li (list "a" "b" "c" "d"))
(my-for-each display li)
