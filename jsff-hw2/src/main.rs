#![feature(unboxed_closures)]
#![feature(core)]

use std::iter::AdditiveIterator;
use std::num::Float;
use std::f64::consts::FRAC_PI_2;

#[derive(Clone)]
struct Point(f64, f64);

struct LagrangeBlah {
    level: usize,
    li_factors: Vec<f64>,
    points: Vec<Point>
}

impl LagrangeBlah {
    fn new (points: &Vec<Point>) -> LagrangeBlah {
        let n = points.len();
        let li_factors = (0..n).map(
                |i| 1.0 / (0..i).chain(i+1..n)
                                .fold(1.0, |a, j| a*(points[i].0-points[j].0))
            ).collect::<Vec<f64>>();

        LagrangeBlah{
            level: n,
            li_factors: li_factors,
            points: points.clone()
        }
    }

    fn new_from_fn <F, Iter> (f: &F, xlist: Iter) -> LagrangeBlah 
            where F: Fn(f64)->f64, Iter: Iterator<Item=f64> {
        let points = xlist.map(|x| Point(x, f(x)))
                          .collect::<Vec<Point>>();
        LagrangeBlah::new(&points)
    }
}

impl Fn<(f64, )> for LagrangeBlah {
    type Output = f64;
    extern "rust-call" fn call (&self, args: (f64,)) -> f64 {
        let (x, ) = args;
        let x_diffs = self.points.iter()
                                 .map(|&Point(xi, _)| x - xi)
                                 .collect::<Vec<f64>>();
        let li = |i| (0..i).chain(i+1..self.level)
                           .fold(self.li_factors[i], |a, i| a * x_diffs[i]);

        self.points.iter()
                   .enumerate()
                   .map(|(i, &Point(_,y))| li(i) * y)
                   .sum()
    }
}

fn check_max_delta <F, G, Iter> (f: &F, g: &G, xlist: Iter) -> f64
        where F: Fn(f64)->f64,
              G: Fn(f64)->f64,
              Iter: Iterator<Item=f64> {
    xlist.map(|x|(f(x)-g(x)).abs())
         .fold(0.0, |a, x| if a>=x {a} else {x})
}

fn worker <F: Fn(usize,usize)->f64> (x_getter: F) {
    let f = |x:f64| 1.0 / (1.0 + x * x);
    let test_x_list:Vec<f64> = (0..501).map(|i| -5.0 + (i as f64) / 50.0)
                                       .collect::<Vec<f64>>();

    for &n in [5, 10, 20, 40].iter() {
        let lag = LagrangeBlah::new_from_fn(&f,
                    (0..n+1).map(|i| x_getter(n, i))
                  );
        let delta = check_max_delta(&lag, &f, test_x_list.iter().map(|&x|x));
        println!("N={} , {}", n, delta);
    }
}

fn main() {
    println!("第1组节点误差：");
    worker(|n, i| -5.0 + 10.0 * (i as f64) / (n as f64));
    println!("第2组节点误差：");
    worker(|n, i| (FRAC_PI_2*(2.0*(i as f64)+1.0)/(n as f64+1.0)).cos()*5.0);
}

