// function changeDivStyle() {
//     var oDiv = document.getElementsByTagName("div")[0];

//     oDiv.onmouseover = function() {
//         oDiv.className = "active";
//         alert(event.type);
//     };

//     oDiv.onmouseout = function(ev) {
//         /////////////////
//         var oEvent = ev || event;
//         oDiv.className = "test";
//         alert(oEvent.type);
//     };
// }

// 在需要通过一个函数处理多个事件时，可以使用 type 属性
function changeDivStyle(event) {
    switch (event.type) {
        case "click":
            alert("clicked");
            break;
        case "mouseover":
            event.target.className = "active";
            break;
        case "mouseout":
            event.target.className = "test";
            break;
    }
}