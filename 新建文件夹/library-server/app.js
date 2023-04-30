// 项目入口文件
const url = require("url");
const http = require("http");
const fs = require('fs');

const user_module = require("./src/routes/user");
const file_module = require("./src/routes/file");
const book_module = require("./src/routes/book");

const tokenUtil = require("./src/utils/token");
// 响应类型对象配置项
const mime = {
  ".jpg": "image/jpeg",
  ".jpeg": "image/jpeg",
  ".gif": "image/gif",
  ".png": "image/png",
  ".html": "text/html;charset=UTF-8",
  ".css": "text/css",
  ".js": "application/x-javascript",
  ".mp3": "audio/mpeg",
  ".mp4": "video/mpeg",
  ".txt": "text/plain"
};
// 创建 http 服务
const app = http.createServer((req, res) => {
  // 设置返回格式：JSON
  res.setHeader("content-type", "application/json");

  // 设置允许跨域请求
  res.setHeader("Access-Control-Allow-Origin", "*"); // 允许所有路径跨域
  res.setHeader("Access-Control-Allow-Headers", "*");
  res.setHeader("Access-Control-Allow-Methods", "PUT,POST,GET,DELETE,OPTIONS");

  /*     startsWith() 方法用于检测字符串是否以指定的子字符串开始。
 如果是以指定的子字符串开头返回 true，否则 false。
   startsWith() 方法对大小写敏感。*/
  // req.url就是端口号后面的路径
  
  //不是这些路径都得验证token
  if(req.url != "/users/login" && req.url != "/users/register" && !req.url.startsWith("/files") && !req.url.startsWith("/static")){
    //token验证
    let resulttoken=tokenUtil.verToken(req.headers["token"]);
    if(resulttoken.code==200){
      req.user=resulttoken.data;
    }else {
      res.end(JSON.stringify(resulttoken));
      return;
    }
  }

  getPostData(req).then((data) => {
    req.body = data; // 至此，已经能够完全获取到以post 方式提交的数据了
    let msgResult = null;
    if (req.url.startsWith("/users")) {
      msgResult = user_module.handlerUser(req, res);
      if (msgResult) {
        msgResult.then((data) => {
          res.end(JSON.stringify(data));
          // return return 不能放在这里
        });
        return; // 中断当前函数
      }
    } else if (req.url.startsWith("/books")) {
      msgResult = book_module.handlerBook(req);
      if (msgResult) {
        msgResult.then((data) => {
          res.end(JSON.stringify(data));
          // return return 不能放在这里
        });
        return; // 中断当前函数
      }
    } else if (req.url.startsWith("/files")) {
      //文件上传
      msgResult = file_module.handlerFile(req);
      if (msgResult) {
        msgResult.then((data) => {
          res.end(JSON.stringify(data));
        });
        return; // 中断当前函数
      }
    } else if (req.url.startsWith("/static")) {
      //静态文件请求
      fs.readFile(__dirname + decodeURIComponent(req.url), (err, data) => {
        if (err) {
          console.log(err)
          res.statusCode = 404;
          res.end('404 not Found');
        } else {
          const suffix = '.' + req.url.split('.').pop();
          console.log(suffix);
          if (mime[suffix]) {
            res.setHeader('Content-Type', mime[suffix]);
            res.end(data);
          } else {
            res.statusCode = 416;
            res.setHeader('Content-Type', 'text/plain;charset=UTF-8');
            res.end('该类型文件不支持访问！');
          }
        }
      });
      return;
    } else {
      msgResult = {
        'code': 400,
        'msg': '请求接口不存在!'
      };
    }
    res.end(JSON.stringify(msgResult));
  });
});
// 处理所有网络请求
// app.on('reques',(req, res) => {});
// 启动服务
app.listen(3000, () => {
  console.log("Server is running at http://127.0.0.1:3000");
});

// 封装一个函数处理以 post 方式提交的数据
const getPostData = (req) => {
  return new Promise((resolve, reject) => {
    if (req.method !== 'POST') {
      resolve({});
      return;
    }
    if (!req.headers['content-type'].includes('application/json')) {
      resolve({});
      return;
    }
    let postData = "";
    req.on("data", (chunk) => {
      postData += chunk.toString();
    });
    req.on("end", () => {
      if (!postData) {
        resolve({});
        return;
      }
      resolve(JSON.parse(postData));
    });
  });
};

