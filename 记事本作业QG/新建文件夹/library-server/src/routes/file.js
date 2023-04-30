//保存前端上传的文件这样 然后返回url地址
var File = require('../controllers/fileControllers');

const handlerFile = (req) => {
  if (req.url == '/files/fileUpload' && req.method.toLowerCase() == 'post') {
    return File.fileUpload(req);
  }
};
module.exports = {
  handlerFile,
};

// toLowerCase() 方法用于把字符串转换为小写。