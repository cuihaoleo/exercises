extern crate rustc_serialize;
extern crate hyper;

use std::io::Read;
use rustc_serialize::json;

use hyper::Client;
use hyper::header::Connection;

#[derive(RustcDecodable, RustcEncodable)]
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
    let client = Client::new();

    let mut res = client.get("http://api.hitokoto.us/rand")
        .header(Connection::close())
        .send().unwrap();

    let mut body = String::new();
    res.read_to_string(&mut body).unwrap();

    let koto: Koto = json::decode(&body).unwrap();
    print!("{}", koto.hitokoto.trim());

    let src = koto.source.trim();
    if src.len() > 0 {
        println!(" --{}", src);
    }
    else {
        println!("");
    }
}
