/* 计算方法作业1：计算 Sum(1/(k*(k+x))), k from 1 to +inf
 * 并行计算版本 */

#![feature(core)]
#![feature(slice_patterns)]
use std::f64;
use std::sync::mpsc;
use std::thread;

fn psi (x: f64) -> f64 {
    (1..1000000).map(|ki| {
        let k = ki as f64;
        1.0/(k*(k+x))
    }).sum()
}

fn main() {
    let xlist = [0.0, 0.5, 1.0, f64::consts::SQRT_2, 10.0, 100.0, 300.0];
    let (tx, rx) = mpsc::channel();

    for &x in xlist.iter() {
        let tx = tx.clone();
        thread::spawn(move || tx.send([x, psi(x)]).unwrap());
    }

    for _ in 0..xlist.len() {
        let [x, psi] = rx.recv().unwrap();
        println!("{:6.2} , {:16.12e}", x, psi);
    }
}

