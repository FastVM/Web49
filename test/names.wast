(module
    (func $fib (export "fib") (param $x i32) (result i32)
        (if (result i32) (i32.lt_s (local.get $x) (i32.const 2))
            (then
                (local.get $x))
            (else
                (i32.add
                    (call $fib (i32.sub (local.get $x) (i32.const 1)))
                    (call $fib (i32.sub (local.get $x) (i32.const 2))))))))

(assert_return (invoke "fib" (i32.const 0)) (i32.const 0))
(assert_return (invoke "fib" (i32.const 1)) (i32.const 1))
(assert_return (invoke "fib" (i32.const 2)) (i32.const 1))
(assert_return (invoke "fib" (i32.const 3)) (i32.const 2))
(assert_return (invoke "fib" (i32.const 4)) (i32.const 3))
(assert_return (invoke "fib" (i32.const 5)) (i32.const 5))
(assert_return (invoke "fib" (i32.const 6)) (i32.const 8))
(assert_return (invoke "fib" (i32.const 7)) (i32.const 13))
(assert_return (invoke "fib" (i32.const 8)) (i32.const 21))
(assert_return (invoke "fib" (i32.const 9)) (i32.const 34))
(assert_return (invoke "fib" (i32.const 10)) (i32.const 55))
(assert_return (invoke "fib" (i32.const 11)) (i32.const 89))
(assert_return (invoke "fib" (i32.const 12)) (i32.const 144))
(assert_return (invoke "fib" (i32.const 13)) (i32.const 233))
(assert_return (invoke "fib" (i32.const 14)) (i32.const 377))
(assert_return (invoke "fib" (i32.const 15)) (i32.const 610))