// 登录
let loginForm = document.getElementById("loginForm");
loginForm.addEventListener("submit", function (e) {
    // 通知 Web 浏览器不要执行与事件关联的默认动作
    // type 属性是 “submit”，在事件传播的任意阶段可以调用任意的事件句柄，通过调用该方法，可以阻止提交表单
    e.preventDefault();
    let formData = {
        // 获取用户输入的用户名和密码
         name: document.getElementById("username").value,
         pwd: document.getElementById("password").value

    };
    // 发送Ajax到登录接口
    // http://127.0.0.1:3000/users/login
    Ajax.post('http://127.0.0.1:3000/users/login', JSON.stringify(formData), function (data) {
        // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
        // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
        let result = JSON.parse(data);
                                                                                  // if (result.code == 200) {
        if (result.code==200) {
            sessionStorage.setItem("token",result.data);
            message.show({ type: 'success', text: result.msg });
            // 登陆成功页面跳转
            let t=2;
            // 间隔性定时器
            setInterval(function(){
                if (t == 1) {
                    window.location.href = 'lunbo.html';
                }
                t--;
            },1000);
        } else {
            message.show({ type: 'error', text: result.msg })
        }
    });
});



// 注册
let signupForm=document.getElementById("signupForm");
let flip=document.getElementById("flip");

signupForm.addEventListener("submit",function(e){

    // 通知浏览器不要执行与事件关联的默认动作
    // type属性是“submit”，在事件传播的任意阶段可以调用任意的事件句柄，通过调用改方法，可以阻止提交表单
    e.preventDefault();
    let formData= {
        // 获取用户输入的用户名和密码
        name:document.getElementById("signname").value,
        email:document.getElementById("signemail").value,
        pwd:document.getElementById("signpwd").value,
        admin: 1
    };

    // 发送Ajax到登录接口
    Ajax.post('http://127.0.0.1:3000/users/register',JSON.stringify(formData),function(data){
         // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
        // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
        let result=JSON.parse(data);
        if(result.code==200) {
            // 注册成功
            message.show({ type: 'success', text: result.msg})
            // 注册成功后清空填写的信息
            document.getElementById("signname").value="";
            document.getElementById("signemail").value="";
            document.getElementById("signpwd").value="";
            // 勾选框
            flip.checked=false;
        } else {
            message.show({type: 'error', text: result.msg})
        }
    });
});

