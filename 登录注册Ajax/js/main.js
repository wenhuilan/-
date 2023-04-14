const message = new Message();
let Ajax = {
  // datat应为'a=a1&b=b1'这种字符串格式，在jq里如果data为对象会自动将对象转成这种字符串格式
  post: function (url, data, fn) {
    // XMLHttpRequest对象用于在后台与服务器交换数据
    // 1、创建了XMLHttpRequest对象之后，必须为XMLHttpRequest对象创建HTTP请求，用于说明XMLHttpRequest对象要从哪里获取数据。通常可以是网站中的数据,也可以是本地中其他文件中的数据。
    let xhr = new XMLHttpRequest();
    //2、 创建HTTP请求
    xhr.open("POST", url, true);
    // 添加http头，发送信息至服务器时内容编码类型
    xhr.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    // 3、设置当xhr对象状态改变时调用的函数，
    xhr.onreadystatechange = function () {
      // 对象的readyState属性值为4，表示异步调用请求完成 
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 304)) {
        //4、 从服务器获得数据
        fn.call(this, xhr.responseText);
      }
    };
    // 5、发送HTTP请求
    xhr.send(data);
  }
}


let loginForm = document.getElementById("loginForm");
loginForm.addEventListener("submit", function (e) {
  // 通知 Web 浏览器不要执行与事件关联的默认动作
  // type 属性是 “submit”，在事件传播的任意阶段可以调用任意的事件句柄，通过调用该方法，可以阻止提交表单
  e.preventDefault();
  let formData = {
    // 获取用户输入的用户名和密码
    username: document.getElementById("username").value,
    password: document.getElementById("password").value
  };
  // 发送Ajax到登录接口
  Ajax.post('http://119.91.210.79:3000/login', JSON.stringify(formData), function (data) {
    // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
    // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
    let result = JSON.parse(data);
    if (result.status == 1) {
      message.show({ type: 'success', text: '登录成功' })
    } else {
      message.show({ type: 'error', text: '账号或者密码错误' })
    }
  });
});



