
(define (sbphere r)
    "sphere '(x y z) r
    Defines a sphere from a center and radius"
    (lambda (x y z)
      (cond ((< z 0)
          (- (sqrt (+ (square x) (square y) (square z))) r))
          (#t .25)
          )))

(define (osphere r)
    "sphere '(x y z) r
    Defines a sphere from a center and radius"
    (lambda (x y z)
      (if
       (> x y)
       ; (> 3 0)
            (- (sqrt (+ (square (* 2 x)) (square y) (* 3 (square z)))) r)
            (- (sqrt (+ (square (* 2 x)) (square y) (* 3 (square z)))) r))
      ))

(define (pillow r)
    "sphere '(x y z) r
    Defines a sphere from a center and radius"
    (lambda (x y z)
      (- (sqrt (+
                (square x)
                (square y)
                (square (square z))
                )) r)))


(define (weird r)
  (lambda (x y z)
    1))

; what are some interesting shapes to...model? This shit is cool...


(ao-show "s2" (weird 5))
; (ao-show "s2" (pillow 1))
