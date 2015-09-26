(define li1 (list 1 3 (list 5 7) 9))
(define li2 (list (list 7)))
(define li3 (list 1
             (list 2
              (list 3
               (list 4
                (list 5
                 (list 6 7)))))))

(display (car (cdr (car (cdr (cdr li1))))))
(newline)
(display (car (car li2)))
(newline)
(define (second-of li) (car (cdr li)))
(display (second-of
          (second-of
           (second-of
            (second-of
             (second-of
              (second-of li3)))))))
