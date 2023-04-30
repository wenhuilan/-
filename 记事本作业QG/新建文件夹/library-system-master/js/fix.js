let safe = document.getElementById("safe");
safe.addEventListener("submit", function (e) {
  e.preventDefault();
  let new1=document.getElementById("new1").value;
  let new2=document.getElementById("new2").value;
  let formData = {
    pwd: document.getElementById("old").value,
    newpwd: document.getElementById("new2").value,
  };
  console.log(formData);
  if (new1.toString()!= new2.toString()) {
    message.show({type: 'error', text: '两次输入密码不一致!'});
    return;
  }
  Ajax.post('http://127.0.0.1:3000/users/editUserpass', JSON.stringify(formData), function (data) {
    let result = JSON.parse(data);
    if (result.code == 200) {
      message.show({type: 'success', text: result.msg})
    } else {
      message.show({type: 'error', text: result.msg})
    }
  });
});
