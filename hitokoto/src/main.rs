#![feature(rustc_private)]
#![feature(core)]
#![feature(io)]

extern crate serialize;
extern crate hyper;

use std::io::Read;
use serialize::json;

use hyper::Client;
use hyper::header::Connection;
use hyper::header::ConnectionOption;

#[derive(Decodable)]
#[allow(dead_code)]
struct Koto {
    hitokoto: String,
    cat: String,
    author: String,
    source: String,
    like: i32,
    date: String,
    catname: String,
    id: i64
}

fn main() {
    let mut client = Client::new();

    let mut res = client.get("http://api.hitokoto.us/rand")
        .header(Connection(vec![ConnectionOption::Close]))
        .send().unwrap();

    let mut body = String::new();
    res.read_to_string(&mut body).unwrap();

    let koto: Koto = json::decode(body.as_slice()).unwrap();
    print!("{}", koto.hitokoto.trim());

    let src = koto.source.as_slice().trim();
    if src.len() > 0 {
        println!(" --{}", src);
    }
    else {
        println!("");
    }
}
