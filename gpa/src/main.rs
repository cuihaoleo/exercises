#![feature(io)]
#![feature(old_io)]

use std::io;
use std::io::BufRead;

fn get_gpa (score: u8) -> Result<f32, &'static str> {
    return match score {
         0...59 => Ok(0.0),
             60 => Ok(1.0),
        61...63 => Ok(1.3),
        64...67 => Ok(1.7),
        68...71 => Ok(2.0),
        72...74 => Ok(2.3),
        75...77 => Ok(2.7),
        78...81 => Ok(3.0),
        82...84 => Ok(3.3),
        85...89 => Ok(3.7),
        90...95 => Ok(4.0),
        96...100 => Ok(4.7),
        _ => Err("invalid score")
    }
}

fn main() {
    let mut input = String::new();

    let cin = io::stdin();

    print!("Input number your score: ");
    std::old_io::stdio::flush();

    cin.lock().read_line(&mut input).ok().expect("failed to read");

    let n = input.trim().parse::<u8>().ok().expect("invalid score");
    let gpa_result = get_gpa(n);

    match gpa_result {
        Ok(gpa) => { println!("Your GPA is {}!", gpa); },
        Err(e) => { println!("Error: {}", e); }
    }
}

