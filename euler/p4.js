// nodejs

var max = 0

for (var i=100; i<1000; i++) {
    for (var j=100; j<1000; j++) {
        var n = i*j + '';
        var rev = n.split('').reverse().join('');
        if (n==rev) {
            if (+n > max) {
                max = +n
            }
        }
    }
}

console.log(max);

