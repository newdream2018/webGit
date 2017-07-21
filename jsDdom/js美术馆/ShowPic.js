function showPic(whichPic) {
    var oImgPalceHolder = document.getElementById("placeholder");
    var imgSrc = whichPic.getAttribute("href");
    var imgDescription = document.getElementById("description");
    var text = whichPic.getAttribute("title");

    oImgPalceHolder.setAttribute("src", imgSrc);

    imgDescription.firstChild.nodeValue = text;
}

//查找parentNode节点作为父节点的子节点数量(元素节点),chooseNodeType(1=元素节点，2=属性节点，3=文本节点)
function countParentNodeChildren(parentNode, chooseNodeType) {
    var element = document.getElementsByTagName(parentNode)[0];
    var Children = element.childNodes;
    var elementChild = [];

    for (var i = 0; i < Children.length; i++) {
        if (Children[i].nodeType == chooseNodeType)
            elementChild.push(Children[i]);
    }

    //alert(elementChild.length);
    return elementChild;
}