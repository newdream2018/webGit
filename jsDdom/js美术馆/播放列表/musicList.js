  function showHideUL() {
      var oDiv = document.getElementById("drop");
      var oUl = oDiv.getElementsByTagName("ul")[0];
      var oH2 = oDiv.getElementsByTagName("h2")[0];

      if (oUl.style.display === "none") {
          oUl.style.display = "block";
          oH2.className = "up";
      } else {
          oUl.style.display = "none";
          oH2.className = "down";
      }
  }

  window.onload = function() {
      var oDiv = document.getElementById("drop");
      var oUl = oDiv.getElementsByTagName("ul")[0];
      var oH2 = oDiv.getElementsByTagName("h2")[0];

      oH2.onclick = showHideUL;
  }