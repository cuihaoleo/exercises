"use strict";

var _slicedToArray = (function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; })();

function reduceAngle(angle) {
    return angle - 360 * Math.floor(angle / 360);
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
    return Array.apply(null, Array(n)).map(function (_, i) {
        return i;
    });
}

function somethingExciting(pairs, func) {
    var sum = 0;
    if (func == null) {
        func = function (x) {
            return x;
        };
    }
    for (var i = 0; i < pairs.length; i++) {
        sum += func(pairs[i][0] * pairs[i][1]);
    }
    return func(sum);
}

function astronomyParameters(time) {
    var ms = time - new Date("1899-12-31T12:00:00+0000");
    var T = ms / 86400000 / 36525;

    var h = somethingExciting([[279.69668, 1], [36000.76892, T], [0.00030, T * T]], reduceAngle);
    var ps = somethingExciting([[281.22083, 1], [1.71902, T], [0.00045, T * T], [0.000003, T * T * T]], reduceAngle);
    var s = somethingExciting([[270.43659, 1], [481267.89057, T], [0.00198, T * T], [0.000002, T * T * T]], reduceAngle);
    var p = somethingExciting([[334.32956, 1], [4069.03403, T], [0.01032, T * T], [-0.000001, T * T * T]], reduceAngle);
    var N_ = somethingExciting([[259.18328, 1], [1934.14201, T], [5.00208, T * T], [0.000002, T * T * T]], reduceAngle);
    var N = -N_;
    return [time, T, h, ps, s, p, N];
}

function generateDoodson(magic, func, code, phase_correct, time, where) {
    var _code$map = code.map(function (x) {
        return x - 5;
    });

    var _code$map2 = _slicedToArray(_code$map, 6);

    var a = _code$map2[0];
    var b = _code$map2[1];
    var c = _code$map2[2];
    var d = _code$map2[3];
    var e = _code$map2[4];
    var f = _code$map2[5];

    a += 5;

    var w = somethingExciting([[a, 14.4920521], [b, 0.5490165], [c, 0.0410686], [d, 0.0046418], [e, 0.0022064], [f, 0.0000020]]);

    var _astronomyParameters = astronomyParameters(time);

    var _astronomyParameters2 = _slicedToArray(_astronomyParameters, 7);

    var _ = _astronomyParameters2[0];
    var T = _astronomyParameters2[1];
    var h = _astronomyParameters2[2];
    var ps = _astronomyParameters2[3];
    var s = _astronomyParameters2[4];
    var p = _astronomyParameters2[5];
    var N = _astronomyParameters2[6];

    var _where = _slicedToArray(where, 2);

    var phi = _where[0];
    var L = _where[1];

    var tau = time % 86400000 * 15 / 3600000 + h - s + L;
    var phase = somethingExciting([[phase_correct, 1], [a, tau], [b, s], [c, h], [d, p], [e, -N], [f, ps]], reduceAngle);

    return function (t) {
        return magic * func(phi) * cos(phase + w * t);
    };
}

function square(x) {
    return x * x;
}

function doodsonMethod(time, where) {
    var _where2 = _slicedToArray(where, 2);

    var phi = _where2[0];
    var L = _where2[1];

    var C = 82.49;
    var d1 = function d1(phi) {
        return C * square(cos(phi));
    },
        d2 = function d2(phi) {
        return C * sin(phi * 2);
    };

    var factory = function factory(a, b, c, d) {
        return generateDoodson(a, b, c, d, time, where);
    };
    var M2 = factory(0.90812, d1, [2, 5, 5, 5, 5, 5], 180),
        S2 = factory(0.42358, d1, [2, 7, 3, 5, 5, 5], 180),
        N2 = factory(0.17387, d1, [2, 4, 5, 6, 5, 5], 180),
        K1 = factory(0.53050, d2, [1, 6, 5, 5, 5, 5], -90),
        O1 = factory(0.37689, d2, [1, 4, 5, 5, 5, 5], 90);

    return function (t) {
        return M2(t) + S2(t) + N2(t) + K1(t) + O1(t);
    };
}

function astronomyMethod(orig_time, where) {
    var _where3 = _slicedToArray(where, 2);

    var phi = _where3[0];
    var l = _where3[1];

    return function func(delta_hour) {
        var d = new Date(orig_time.getTime() + delta_hour * 3600000);

        var _astronomyParameters3 = astronomyParameters(d);

        var _astronomyParameters32 = _slicedToArray(_astronomyParameters3, 7);

        var _ = _astronomyParameters32[0];
        var t = _astronomyParameters32[1];
        var h = _astronomyParameters32[2];
        var ps = _astronomyParameters32[3];
        var s = _astronomyParameters32[4];
        var p = _astronomyParameters32[5];
        var n = _astronomyParameters32[6];

        var cm_rm = somethingExciting([[1, 1], [0.054501, cos(s - p)], [0.010025, cos(s - 2 * h + p)], [0.008249, cos(2 * (s - h))], [0.002970, cos(2 * (s - p))]]);
        var lmd_m = somethingExciting([[1, s], [degrees(0.109760), sin(s - p)], [degrees(0.022236), sin(s - 2 * h + p)], [degrees(0.011490), sin(2 * (s - h))], [degrees(0.003728), sin(2 * (s - p))]], reduceAngle);
        var beta_m = somethingExciting([[degrees(0.089504), sin(s - n)], [degrees(0.004897), sin(2 * s - p - n)], [-degrees(0.004847), sin(p - n)], [degrees(0.003024), sin(s - 2 * h + n)]], reduceAngle);

        var cs_rs = somethingExciting([[1, 1], [0.016750, cos(h - ps)], [0.000280, cos(2 * (h - ps))], [0.000005, cos(3 * (h - ps))]]);
        var lmd_s = somethingExciting([[1, h], [degrees(0.016750), cos(h - ps)], [degrees(0.000280), cos(2 * (h - ps))], [degrees(0.000005), cos(3 * (h - ps))]], reduceAngle);

        var x = d % 86400000 * 15 / 3600000 + h + l - 180;
        var e = somethingExciting([[23.452294, 1], [-0.0130125, t], [-0.0000016, t * t], [0.0000005, t * t * t]], reduceAngle);

        var cos_zm = sin(phi) * (sin(e) * sin(lmd_m) * cos(beta_m) + cos(e) * sin(beta_m)) + cos(phi) * (cos(lmd_m) * cos(beta_m) * cos(x) + sin(x) * (cos(e) * sin(lmd_m) * cos(beta_m) + -sin(e) * sin(beta_m)));
        var d_gm = 54.993 * Math.pow(cm_rm, 3) * (1 - 3 * square(cos_zm)) + 1.369 * Math.pow(cm_rm, 4) * (3 * cos_zm - 5 * Math.pow(cos_zm, 3));

        var cos_zs = sin(phi) * sin(lmd_s) * sin(e) + cos(phi) * (cos(lmd_s) * cos(x) + sin(lmd_s) * sin(x) * cos(e));
        var d_gs = 25.358 * Math.pow(cs_rs, 3) * (1 - 3 * Math.pow(cos_zs, 2));

        return d_gm + d_gs;
    };
}

function main() {
    var time = new Date("2015-10-15T00:00:00+0800");
    var duration = 6 * 24;
    var where = [34.75, 113.63];

    var ra = range(duration);

    var f1 = doodsonMethod(time, where),
        f2 = astronomyMethod(time, where);

    var result1 = ra.map(f1),
        result2 = ra.map(f2);

    var trace1 = {
        x: range(result1.length),
        y: result1,
        name: 'Doodson',
        type: 'scatter'
    };
    var trace2 = {
        x: range(result2.length),
        y: result2,
        name: 'astro',
        type: 'scatter'
    };

    var tester = document.getElementById("tester");
    tester.innerHTML = '';
    Plotly.newPlot(tester, [trace1, trace2], { title: "Gravity tide!" });
}

document.addEventListener("DOMContentLoaded", function (event) {
    return main();
});
window.onresize = function () {
    return main();
};
