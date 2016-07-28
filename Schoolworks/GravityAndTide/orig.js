 "use strict";

function reduceAngle(angle) {
    return angle - 360 * Math.floor(angle/360)
}

function radians(deg) {
    return deg / 180 * Math.PI;
}

function degrees(rad) {
    return rad / Math.PI * 180;
}

function sin(angle) {
    return Math.sin(radians(angle));
}

function cos(angle) {
    return Math.cos(radians(angle));
}

function range(n) {
   return Array.apply(null, Array(n)).map((_, i) => i);
}

function somethingExciting(pairs, func) {
    let sum = 0;
    if (func == null) {
        func = x => x;
    }
    for (let i=0; i<pairs.length; i++) {
        sum += func(pairs[i][0] * pairs[i][1]);
    }
    return func(sum);
}

function astronomyParameters(time) {
    let ms = time - (new Date("1899-12-31T12:00:00+0000"));
    let T = ms / 86400000 / 36525;

    let h = somethingExciting([
            [279.69668, 1],
            [36000.76892, T],
            [0.00030, T*T]], reduceAngle);
    let ps = somethingExciting([
            [281.22083, 1],
            [1.71902, T],
            [0.00045, T*T],
            [0.000003, T*T*T]], reduceAngle);
    let s = somethingExciting([
            [270.43659, 1],
            [481267.89057, T],
            [0.00198, T*T],
            [0.000002, T*T*T]], reduceAngle);
    let p = somethingExciting([
            [334.32956, 1],
            [4069.03403, T],
            [0.01032, T*T],
            [-0.000001, T*T*T]], reduceAngle);
    let N_ = somethingExciting([
            [259.18328, 1],
            [1934.14201, T],
            [5.00208, T*T],
            [0.000002, T*T*T]], reduceAngle);
    let N = -N_;
    return [time, T, h, ps, s, p, N];
}


function generateDoodson(magic, func, code, phase_correct, time, where) {
    let [a, b, c, d, e, f] = code.map(x => x-5);
    a += 5;

    let w = somethingExciting([
            [a, 14.4920521],
            [b, 0.5490165],
            [c, 0.0410686],
            [d, 0.0046418],
            [e, 0.0022064],
            [f, 0.0000020]]);

    let [_, T, h, ps, s, p, N] = astronomyParameters(time);
    let [phi, L] = where;

    let tau = (time % 86400000)*15/3600000 + h - s + L;
    let phase = somethingExciting([
                [phase_correct, 1],
                [a, tau], [b, s], [c, h],
                [d, p], [e, -N], [f, ps]], reduceAngle);

    return t => magic*func(phi)*cos(phase+w*t);
}

function square(x) {
    return x*x;
}

function doodsonMethod(time, where) {
    let [phi, L] = where;
    let C = 82.49;
    let d1 = phi => C*square(cos(phi)),
        d2 = phi => C*sin(phi*2);
    
    let factory = (a, b, c, d) => generateDoodson(a, b, c, d, time, where);
    let M2 = factory(0.90812, d1, [2,5,5,5,5,5], 180),
        S2 = factory(0.42358, d1, [2,7,3,5,5,5], 180),
        N2 = factory(0.17387, d1, [2,4,5,6,5,5], 180),
        K1 = factory(0.53050, d2, [1,6,5,5,5,5], -90),
        O1 = factory(0.37689, d2, [1,4,5,5,5,5], 90);

    return t => M2(t) + S2(t) + N2(t) + K1(t) + O1(t);
}

function astronomyMethod(orig_time, where) {
    let [phi, l] = where;

    return function func(delta_hour) {
        let d = new Date(orig_time.getTime() + delta_hour*3600000);
        let [_, t, h, ps, s, p, n] = astronomyParameters(d);

        let cm_rm = somethingExciting([
            [1, 1],
            [0.054501, cos(s-p)],
            [0.010025, cos(s-2*h+p)],
            [0.008249, cos(2*(s-h))],
            [0.002970, cos(2*(s-p))]]);
        let lmd_m = somethingExciting([
            [1, s],
            [degrees(0.109760), sin(s-p)],
            [degrees(0.022236), sin(s-2*h+p)],
            [degrees(0.011490), sin(2*(s-h))],
            [degrees(0.003728), sin(2*(s-p))]], reduceAngle)
        let beta_m = somethingExciting([
            [degrees(0.089504), sin(s-n)],
            [degrees(0.004897), sin(2*s-p-n)],
            [-degrees(0.004847), sin(p-n)],
            [degrees(0.003024), sin(s-2*h+n)]], reduceAngle)

        let cs_rs = somethingExciting([
            [1, 1],
            [0.016750, cos(h-ps)],
            [0.000280, cos(2*(h-ps))],
            [0.000005, cos(3*(h-ps))]]);
        let lmd_s = somethingExciting([
            [1, h],
            [degrees(0.016750), cos(h-ps)],
            [degrees(0.000280), cos(2*(h-ps))],
            [degrees(0.000005), cos(3*(h-ps))]], reduceAngle)

        let x = (d % 86400000)*15/3600000 + h + l - 180;
        let e = somethingExciting([
            [23.452294, 1],
            [-0.0130125, t],
            [-0.0000016, t*t],
            [0.0000005, t*t*t]], reduceAngle);

        let cos_zm = sin(phi) * (
                     sin(e)*sin(lmd_m)*cos(beta_m) +
                     cos(e)*sin(beta_m)) +
                 cos(phi) * (
                     cos(lmd_m)*cos(beta_m)*cos(x) +
                     sin(x) * (
                         cos(e)*sin(lmd_m)*cos(beta_m) +
                         -sin(e)*sin(beta_m)));
        let d_gm = 54.993 * Math.pow(cm_rm,3) * (1-3*square(cos_zm)) +
                1.369 * Math.pow(cm_rm,4) * (3*cos_zm - 5*Math.pow(cos_zm,3));

        let cos_zs = sin(phi) * sin(lmd_s)*sin(e) +
                 cos(phi) * (
                     cos(lmd_s)*cos(x) +
                     sin(lmd_s)*sin(x)*cos(e));
        let d_gs = 25.358 * Math.pow(cs_rs,3) * (1-3*Math.pow(cos_zs,2));

        return d_gm + d_gs
    };
}

function main() { 
    let time = new Date("2015-10-15T00:00:00+0800");
    let duration = 6*24;
    let where = [34.75, 113.63];

    let ra = range(duration);

    let f1 = doodsonMethod(time, where),
        f2 = astronomyMethod(time, where);

    let result1 = ra.map(f1),
        result2 = ra.map(f2);

    let trace1 = {
        x: range(result1.length),
        y: result1,
        name: 'Doodson',
        type: 'scatter'
    };
    let trace2 = {
        x: range(result2.length),
        y: result2,
        name: 'astro',
        type: 'scatter'
    };
    
    let tester = document.getElementById("tester");
    tester.innerHTML = '';
    Plotly.newPlot(tester, [trace1, trace2], { title: "Gravity tide!" });
}

document.addEventListener("DOMContentLoaded", event => main());
window.onresize = () => main();
