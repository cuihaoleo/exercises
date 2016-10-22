/* 
 * How to compile and run: 
 * Get compiler from: http://www.rust-lang.org/
 * or play online: https://play.rust-lang.org/
 */

fn tixing_integrate <F:Fn(f64)->f64> (f:F, a:f64, b:f64, n:usize) -> f64 {
    let h = (b - a) / (n as f64);
    let acc:f64 = (1..n).fold(0.0, |sm, i| sm + f(a + i as f64 * h));
    h * (acc + 0.5 * (f(a) + f(b)))
}

fn simpson_integrate <F:Fn(f64)->f64> (f:F, a:f64, b:f64, rn:usize) -> f64 {
    let n = rn + (rn & 1);
    let h = (b - a) / (n as f64);
    let acc:f64 = (0..n/2).fold(0.0, |sm, i| {
        let x = a + ((2 * i) as f64) * h;
        2.0 * f(x) + 4.0 * f(x+h) + sm
    });
    (acc + f(b) - f(a)) * h / 3.0
}

macro_rules! check {
    ($f:expr) => {{
        let prec = (1 as f64).cos() - (5 as f64).cos();
        let max_k = 13;

        (0..max_k+1).fold(0.0, |pre:f64, k| { 
            let n = 1 << k;
            let err = $f(|x:f64|x.sin(), 1.0, 5.0, n) - prec;
            let order = (pre.abs() / err.abs()).log10() / (2 as f64).log10();

            if !order.is_infinite() { print!(", {:.6}\n", order); }
            if k < max_k { print!("N={:4}, {:<+19.12e}", n, err); }

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

