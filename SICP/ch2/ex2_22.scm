; 应该无法用迭代一遍实现不反序的列表映射
; 用 cons 形成的 list，只能 O(1) 地 prepend，不能 append
; 可能的解决方法是先用迭代操作逆序，再迭代 map？

(define (square n) (* n n))

(define (square-list-bad items)
 (define (iter things answer)
  (if (null? things)
      answer
      (iter (cdr things)
            (cons (square (car things))
                  answer))))
 (iter items '()))

(define (square-list-bad2 items)
 (define (iter things answer)
  (if (null? things)
      answer
      (iter (cdr things)
            (cons answer
                  (square (car things))))))
 (iter items '()))

(define li (list 1 2 3 4 5))
(display (square-list-bad li))
(newline)
(display (square-list-bad2 li))
