(module
    (func (export "no_nest") (param $x i32) (result i32)
        local.get $x
        if (result i32)
            i32.const 1
        else
            i32.const 0
        end)
    (func (export "full_nest") (param $x i32) (result i32)
        (if (result i32) (local.get $x)
            (then
                (i32.const 1))
            (else
                (i32.const 0)))))

(assert_return (invoke "no_nest" (i32.const 0)) (i32.const 0))
(assert_return (invoke "no_nest" (i32.const 1)) (i32.const 1))
(assert_return (invoke "no_nest" (i32.const 2)) (i32.const 1))

(assert_return (invoke "full_nest" (i32.const 0)) (i32.const 0))
(assert_return (invoke "full_nest" (i32.const 1)) (i32.const 1))
(assert_return (invoke "full_nest" (i32.const 2)) (i32.const 1))