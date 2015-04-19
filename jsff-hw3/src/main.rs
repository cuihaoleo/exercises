#![feature(core)]

fn tixing_integrate <F:Fn(f64)->f64> (f:F, a:f64, b:f64, n:usize) -> f64 {
    let h = (b - a) / (n as f64);
    let acc:f64 = (1..n).map(|i| f(a + i as f64 * h)).sum();
    h * (acc + 0.5 * (f(a) + f(b)))
}

fn simpson_integrate <F:Fn(f64)->f64> (f:F, a:f64, b:f64, rn:usize) -> f64 {
    let n = rn + (rn & 1);
    let h = (b - a) / (n as f64);
    let acc:f64 = (0..n/2).map(|i| {
        let x = a + ((2 * i) as f64) * h;
        2.0 * f(x) + 4.0 * f(x+h)
    }).sum();
    (acc + f(b) - f(a)) * h / 3.0
}

macro_rules! check {
    ($f:expr) => {{
        let prec = (1 as f64).cos() - (5 as f64).cos();

        (0..13).map(|x|1<<x).fold(0.0, |pre:f64, k| { 
            let err = $f(|x:f64|x.sin(), 1.0, 5.0, k) - prec;
            let order = (pre.abs() / err.abs()).log10() / (2 as f64).log10();
            if order.is_infinite() {
                print!("N={:4}, {:<+19.12e}", k, err);
            }
            else {
                print!(", {:.4}\nN={:4}, {:<+19.12e}", order, k, err);
            }
            err
        });

        print!("\n");
    }};
}

fn main() {
    println!("梯形积分：");
    check!(tixing_integrate);
    println!("西姆松积分：");
    check!(simpson_integrate);
}

