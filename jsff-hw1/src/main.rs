/* 计算方法作业1：计算 Sum(1/(k*(k+x))), k from 1 to +inf */

#![feature(core)]
use std::iter::AdditiveIterator;
use std::f64;

fn psi (x: f64) -> f64 {
    (1..1000000).map(|ki| {
        let k = ki as f64;
        1.0/(k*(k+x))
    }).sum()
}

fn main() {
    let xlist = [0.0, 0.5, 1.0, f64::consts::SQRT2, 10.0, 100.0, 300.0];
    for &x in xlist.iter() {
        println!("{:6.2} , {:16.12e}", x, psi(x));
    }
}

