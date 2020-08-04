#lang racket/base
(require racket/runtime-path
         ffi/unsafe
         ffi/unsafe/define)

(provide
 tty-restore!
 tty-raw!)

(define-runtime-path tty-raw "tty-raw.dylib")
(define-ffi-definer define-tty-raw (ffi-lib tty-raw))

(define-tty-raw ttyraw (_fun -> _int))
(define-tty-raw ttyrestore (_fun -> _int))

(define (tty-restore!)
  (unless (zero? (ttyrestore))
    (error 'tty-restore!)))

(define (tty-raw!)
  (unless (zero? (ttyraw))
    (error 'tty-raw!)))
