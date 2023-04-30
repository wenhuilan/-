// 路由文件：接受用户的请求，并进行返回数据
var User = require('../controllers/userControllers');

const handlerUser = (req) => {
  if (req.url == "/users/login" &&  req.method.toLowerCase() == 'post') {
    return User.login(req);
  } else if (req.url == "/users/register" && req.method.toLowerCase() == 'post') {
    return User.register(req);
  }else if (req.url == "/users/getUserInfo" && req.method.toLowerCase() == 'get') {
    return User.getUserInfo(req);
  }else if (req.url == "/users/editUserinfo" && req.method.toLowerCase() == 'post') {
    return User.editUserinfo(req);
  }else if (req.url == "/users/editUserpass" && req.method.toLowerCase() == 'post') {
    return User.editUserpass(req);
  }
};
module.exports = {
  handlerUser,
};
