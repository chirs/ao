(define (square i) (* i i))

(define (mandelbrot depth)
  (lambda (x y z)
    (let recurse ((real 0) (imag 0) (i depth))
      (if (> i 0)
        (recurse (+ (- (square real) (square imag)) x)
                 (+ (* 2 real imag) y)
                 (- i 1))
        (+ (square real) (square imag) -4)))))


(define (mandelbrot depth)
  (lambda (x y z)
    (let recurse ((real 0) (imag 0) (i depth))
      (if (> i 0)
        (recurse (+ (- (square real) (square imag)) x)
                 (+ (* 2 real imag) y)
                 (- i 1))
        (+ (square real) (square imag) -4)))))


(define (mandelbrot-shell depth)
  (difference
   (mandelbrot (- depth 3))
   (mandelbrot depth)
   )
  )

(define (mandelsphere depth)
  (intersection 
   (mandelbrot depth)
   ; (sphere '(0 0 0 ) 2)
   (cube '(-2 -2 0) '(2 2 2))
   )
  )



; what is i doing?
; why can't I redefine z in here?
; that let is doing assignment, right?

(define (mandelbulb depth factor)
  (lambda (x y z)
    (let recurse ((real 0) (imag 0) (i depth))
      (if (> i 0)
        (recurse (+ (- (square real) (square imag)) x)
                 (+ (* factor real imag) y)
                 (- i 1))
            (+ (square real) (square imag) -4)

        ))))
  



;(ao-show "mandelbrot" (mandelbrot 15))
(ao-show "mandelbrot" (mandelsphere 10))
