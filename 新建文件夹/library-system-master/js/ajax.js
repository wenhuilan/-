const message = new Message();
let Ajax = {
  get: function (url, fn) {
    let xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    if(sessionStorage.getItem("token")){
      xhr.setRequestHeader("token", sessionStorage.getItem("token"));
    }
    xhr.onreadystatechange = function () {
      // readyState == 4说明请求已完成
      if (xhr.readyState == 4 && xhr.status == 200 || xhr.status == 304) {
        if (xhr.responseText){
          // let result = JSON.parse(xhr.responseText);
          let result = xhr.responseText;
          //token验证失败提示信息  需要重新返回登录  
          if(result.code==502){
            message.show({ type: 'error', text: result.msg });
            // 登陆成功跳转
            let t=2;
            // 间隔性定时器
            setInterval(function(){
              if (t == 1) {
                window.location.href = 'landing.html';
              }
              t--;
            },1000);
            return;
          }
        }
        // 从服务器获得数据
        fn.call(this, xhr.responseText);
      }
    };
    xhr.send();
  },
  post: function (url, data, fn) {
    // 1、创建XMLHttpRequest对象
    let xhr = new XMLHttpRequest();
    // 2、创建HTTP 请求
    xhr.open("POST", url, true);
    // 添加http头，发送信息至服务器时内容编码类型
    xhr.setRequestHeader("Content-Type", "application/json; charset=utf-8");
    if(sessionStorage.getItem("token")){
      xhr.setRequestHeader("token", sessionStorage.getItem("token"));
    }
    // 3、设置 xhr 对象状态发生改变时调用的函数
    xhr.onreadystatechange = function () {
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 304)) {
        // 以文本形式返回响应
        if(xhr.responseText){
          let result = xhr.responseText;
          //token验证失败  需要重新返回登录

           // 4、设置获取服务器返回数据的语句
          if(result.code==502){
            message.show({ type: 'error', text: result.msg });
            // 登陆成功跳转
            let t=2;
            // 间隔性定时器
            setInterval(function(){
              if (t == 1) {
                window.location.href = 'landing.html';
              }
              t--;
            },1000);
            return;
          }
        }
        fn.call(this, xhr.responseText);
      }
    };
    // 5、发送HTTP请求
    xhr.send(data);
  }
}

