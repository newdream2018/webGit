function leo(n) {
    var navUi = document.getElementById("m" + n);
    if (navUi.style.display != "block") {
        for (var i = 0; i <= 5; i++) {
            document.getElementById("m" + i).style.display = "none";
        }
        navUi.style.display = "block";
    } else {
        navUi.style.display = "none";
    }
}

window.onload = function() {
    var oNavUl = document.getElementById("nav");
    var oNavArch = oNavUl.getElementsByClassName("navLink");

    for (var i = 0; i < oNavArch.length; i++) {
        oNavArch[i].index = i;

        oNavArch[i].onclick = function() {
            leo(this.index);
        };
    }
}