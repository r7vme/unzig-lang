fn foo() i32 {
    return 1;
}

fn main() i32 {
    var x: i32 = foo();
    var y: i32 = 123 + (1 * x);
    y = 1;
    return 0;
}
