#![feature(old_io)]
use std::old_io as io;

// simple hangman game, answer is "wikipedia"
fn main() {
    let word = "wikipedia";
    let mut round = 0;
    let mut mark = [false; 10];
    let mut fail_count = 0;

    loop {
        round += 1;
        println!("Round #{}, your guess: ", round);

        let input = io::stdin().read_char().ok().expect("Fail to read!");
        io::stdin().read_line().ok().expect("Fail to read!");

        let mut fail = true;
        let mut proc_count = 0;

        for (i,c) in word.chars().enumerate() {
            if c == input {
                mark[i] = true;
                fail = false;
            }
            print!("{}", if mark[i] {proc_count += 1; c} else {'_'});
        }
        println!("");

        if fail {
            fail_count += 1;
            
            if fail_count == 6 {
                println!("You die!");
                break;
            }

            println!("1 stroke added: {} to die.", 6 - fail_count);
        }

        if proc_count == word.len() {
            println!("You win!");
            break;
        }
    }
}

