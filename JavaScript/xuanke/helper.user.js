// ==UserScript==
// @name USTCmeee
// @namespace http://mis.teach.ustc.edu.cn/
// @description USTCmeee
// @include http://mis.teach.ustc.edu.cn/*
// @require https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js
// ==/UserScript==

function getOptions (select) {
  var opts = [];
  $(select + ' option').each(
    function () {
      $(this).val().split(',').forEach(
        function (d){
          opts.indexOf(d) == -1 && opts.push(d);
        }
      );
    }
  );
  return opts;
}

function Intersection (arr1, arr2) {
  return arr1.filter(function(n) {
    return arr2.indexOf(n) != -1;
  });
}

function convert2GPA (s) {
  if (!isNaN(s)) { // s is a number
    var score = Number(s);
    if (score < 60) return 0.0;
    if (score < 61) return 1.0;
    if (score < 64) return 1.3;
    if (score < 68) return 1.7;
    if (score < 72) return 2.0;
    if (score < 75) return 2.3;
    if (score < 78) return 2.7;
    if (score < 82) return 3.0;
    if (score < 85) return 3.3;
    if (score < 90) return 3.7;
    if (score < 95) return 4.0;
    return 4.3;
  } else if (s.search(/^([A-D][+-]?|F)$/) != -1) {
    if (s == 'F') return 0.0;
    if (s == 'D+') return 1.5;
    var bgpa = {'A':4, 'B':3, 'C':2, 'D':1.3}[s[0]];
    return bgpa + {'+':0.3, '-':-0.3, undefined:0.0}[s[1]];
  }
}

function init_st_xk_dx_MAIN() {
  var all_times = getOptions('#yxsjpdmlist'); // 上课时间
  var all_ids = getOptions('#yxkcidlist'); //课程ID
  var all_examtimes = getOptions('#yxkssjdmlist'); // 考试时间

  function querykc_mod () {
    var really = confirm("真的要强行选课吗？");
    if (!really) {
      return;
    }

    really = confirm("后果自负哦～");
    if (really) {
      console.log("强行选课启动！");
      console.log(arguments);
      //querykc.apply(this, arguments);
    }
  }

  $("#dxkctable1 input").each(function(){
    if ($(this).is(":disabled")) {
      $(">*",$(this).parent().parent())
        .css("background-color", "#AAA");
      $(this).val("选不了哦");
      return;
    }

    var onclick_src = $(this).undefinedattr("onclick");
    var args = eval(
      '['+onclick_src.match(/^return querykc\((.*)\);$/)[1]+']');
    var kc_id = args[3],
        kc_time = args[7] == "null" ? [] : args[7].split(','),
        kc_examtime = args[8] == "null" ? [] : args[8].split(',');

    var bad = true;
    if (all_ids.indexOf(kc_id) != -1) {
      $(">*",$(this).parent().parent())
        .css("background-color", "Silver");
      $(this).val("已经修读");
    } else if (Intersection(kc_examtime, all_examtimes).length) {
      $(">*",$(this).parent().parent())
        .css("background-color", "Gainsboro");
      $(this).val("考试冲突").css("color", "Gray");
    } else if (Intersection(kc_time, all_times).length) {
      $(">*",$(this).parent().parent())
        .css("background-color", "Gainsboro");
      $(this).val("时间冲突");
    } else {
      $(">*",$(this).parent().parent())
        .css("background-color", "SpringGreen");
      $(this).val("我就喜欢");
      bad = false;
    }

    if (bad) {
      $(this).css("color", "Gray");
      args[7] = args[8] = "null";
      $(this).attr("onclick",
        "return confirm('真的要强行选课吗？') && \
                confirm('后果自负哦！') && \
                querykc('" + args.join("','") + "');");
    }
  });
}

function init_st_xk_gwc_MAIN () {
  $("#yxsjpdmlist option,\
  #yxkcidlist option,\
  #yxkssjdmlist option").remove();
  $("#xdkctable1 input[type=checkbox]").attr("onclick", "");
}

function initquerycjxx_MAIN () {
  var trs = $('#cjxxlist').contents().find("table:last tr.bg");
  var gpa_total=0, gpa_weight=0;
  var courses = [], terms = [];
  trs.each(function () {
    var infoarr = [];
    $(this).find("td").each(function () {
      infoarr.push($(this).text());
    });

    if (terms.indexOf(infoarr[0]) == '-1') {
      terms.push(infoarr[0]);
    }

    var info = {
      'term': infoarr[0],
      'id': infoarr[1],
      'name': infoarr[2],
      'type': infoarr[3],
      'gpa': convert2GPA(infoarr[4]),
      'weight': Number(infoarr[6])
    };
    console.log(info);
    courses.push(info);
  });

  terms.forEach(function (term) {
    var up = 0, down = 0;
    courses.filter(function (c) {
      return c['term'] == term;
    }).forEach(function (c) {
      if (c['gpa'] != undefined) {
        up += c['gpa'] * c['weight'];
        down += c['weight'];
      }
    })
    console.log("学期: " + term);
    console.log("GPA: " + up/down);
  });
}

if (document.URL.search("init_st_xk_gwc.do") != -1) {
  init_st_xk_gwc_MAIN();
} else if (document.URL.search("init_st_xk_dx.do") != -1) {
  init_st_xk_dx_MAIN();
} else if (document.URL.search("initquerycjxx.do") != -1) {
  initquerycjxx_MAIN();
}
