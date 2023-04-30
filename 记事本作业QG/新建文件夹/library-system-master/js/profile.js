document.getElementById("img-upload").onclick = function () {
  document.getElementById("img-file").click();
}
document.getElementById("img-file").onchange = function () {
  document.getElementById("gallery").innerHTML = "";
  var img = document.getElementById("img-file").files;
  for (var i = 0; i < img.length; i++) {
    var file = img[i];
    var url = URL.createObjectURL(file);
    var box = document.createElement("img");
    box.setAttribute("src", url);
    box.className = 'img';

    var imgBox = document.createElement("div");
    imgBox.style.display = 'inline-block';
    imgBox.className = 'img-item';

    var deleteIcon = document.createElement("span");
    deleteIcon.className = 'delete';
    deleteIcon.innerText = 'x';
    deleteIcon.dataset.filename = img[i].name;
    imgBox.appendChild(deleteIcon);

    imgBox.appendChild(box);
    var body = document.getElementsByClassName("gallery")[0];
    body.appendChild(imgBox);

    //ajax调用后台上传
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "http://127.0.0.1:3000/files/fileUpload", true);
    // 添加http头，发送信息至服务器时内容编码类型
    xhr.setRequestHeader("filename", encodeURIComponent(img[i].name));
    xhr.onreadystatechange = function () {
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 304)) {
        let result = JSON.parse(xhr.responseText);
        if (result.code == 200) {
          document.getElementById("book-file").value = result.data;
        }
      }
    };
    xhr.send(file);

    deleteIcon.onclick = function () {
      this.parentElement.remove();
      document.getElementById("img-file").value = "";
    }
  }
}


showProfile();

function showProfile() {
  Ajax.get('http://127.0.0.1:3000/users/getUserInfo', function (data) {
    let result = JSON.parse(data);
    if (result.code == 200) {
      if (result.data != null) {
        let userObj = result.data;
        document.getElementById("userId").value = userObj.id;
        document.getElementById("createrName").value = userObj.name;
        document.getElementById("createrPhone").value = userObj.phone;
        document.getElementById("createrAddress").value = userObj.address;
        document.getElementById("createrEmail").value = userObj.email;
        if (userObj.image) {
          document.getElementById("book-file").value = userObj.image;
          var box = document.createElement("img");
          box.setAttribute("src", userObj.image);
          box.className = 'img';
          var imgBox = document.createElement("div");
          imgBox.style.display = 'inline-block';
          imgBox.className = 'img-item';
          var deleteIcon = document.createElement("span");
          deleteIcon.className = 'delete';
          deleteIcon.innerText = 'x';
          imgBox.appendChild(deleteIcon);
          imgBox.appendChild(box);
          var body = document.getElementsByClassName("gallery")[0];
          body.appendChild(imgBox);
          deleteIcon.onclick = function () {
            this.parentElement.remove();
            document.getElementById("img-file").value = "";
          }
        }
      }
    }


  });

}

//提交编辑资料
let editProfile = document.getElementById("editProfile");
editProfile.addEventListener("submit", function (e) {
  e.preventDefault();
  let formData = {
    id:document.getElementById("userId").value,
    name: document.getElementById("createrName").value,
    phone: document.getElementById("createrPhone").value,
    address: document.getElementById("createrAddress").value,
    email: document.getElementById("createrEmail").value,
    image: document.getElementById("book-file").value
  };
  if (formData.image == null || formData.image == undefined || formData.image == "") {
    message.show({type: 'warning', text: '请选择头像封面'})
    return;
  }
  Ajax.post('http://127.0.0.1:3000/users/editUserinfo', JSON.stringify(formData), function (data) {
    let result = JSON.parse(data);
    if (result.code == 200) {
      message.show({type: 'success', text: result.msg})
    } else {
      message.show({type: 'error', text: result.msg})
    }
  });
});
