#![feature(io)]

use std::io;
use std::io::BufRead;
use std::iter;

// 打印一个三角
fn main() {
    let mut input = String::new();

    let cin = io::stdin();

    println!("Input number of rows: ");
    cin.lock().read_line(&mut input).ok().expect("failed to read");

    let n = input.trim().parse().ok().expect("ohh");

    for i in 1 .. n+1 {
        println!("{}", iter::repeat('*').take(i).collect::<String>());
    }
}
