var timer = null;
var aNow = null;

var g_aImg = []; //用来获取数字部分的图片+星期号
var g_oImgweek = [];
var g_aWeekName = [
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven"
];

window.onload = function() {
    // alert("13");

    // var oDiv = document.getElementById("clock");
    // var aImg = oDiv.getElementsByTagName("img");

    var oDiv = $("#clock");
    var aImg = $("img");

    // alert(aImg.length);

    for (var i = 0; i < aImg.length; i++) {
        if (!isNaN(parseInt(aImg[i].alt))) {
            g_aImg.push(aImg[i]);
        }

    }

    // alert(g_aImg.length);

    g_aImg.push(aImg[aImg.length - 2]); //星期号加进去

    setInterval(updateTime, 1000);
    updateTime();
}


function updateTime() {
    aNow = getTimeArray();

    for (var i = 0; i < g_aImg.length - 1; i++) {
        g_aImg[i].src = "images/" + aNow[i] + ".png";
    }

    g_aImg[g_aImg.length - 1].src = "images/" + g_aWeekName[aNow[i]] + ".png";
}

var g_iImgHeigth = 0;
var g_iTarget = 0;
var g_iMax = 0;


function checkSwitch() {
    var i = 0;

    aNow = getTimeArray();

    g_imgHeigth = g_aImg[0].offsetHeight;
    g_iTarget = -g_imgHeigth;
    g_iMax = g_imgHeigth;

    timer = setInterval(doSwitch, 30);
}


function toDouble(num) {
    if (num < 10) {
        return '0' + num;
    } else {
        return '' + num;
    }
}


function getTimeArray() {
    var oDate = new Date();
    var aNumber = [];

    var iYear = oDate.getFullYear();
    var iMonth = oDate.getMonth();
    var iDay = oDate.getDate();
    var iHour = oDate.getHours();
    var iMin = oDate.getMinutes();
    var iSec = oDate.getSeconds();
    var iWeek = (oDate.getDay() + 6) % 7;

    if (iYear < 1900) {
        iYear += 1900;
    }

    // ''是帮助后面数字变成字符串的
    var str = '' + (iYear) + toDouble(iMonth + 1) + toDouble(iDay) + toDouble(iHour) + toDouble(iMin) + toDouble(iSec) + iWeek;

    var aChar = str.split('');

    for (var i = 0; i < aChar.length; i++) {
        aNumber.push(aChar[i]);
    }

    return aNumber;

}