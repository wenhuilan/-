// 路由文件：接受用户的请求，并进行返回数据

var Book = require('../controllers/bookControllers');

const handlerBook = (req) => {
  if (req.url == "/books/add" &&  req.method.toLowerCase() == 'post') {
    return Book.addBook(req);
  } else if (req.url == "/books/findBookAll" &&  req.method.toLowerCase() == 'post') {
    return Book.findBookAll(req);
  }else if (req.url == "/books/findBookId" &&  req.method.toLowerCase() == 'post') {
    return Book.findBookId(req);
  }else if (req.url == "/books/deleteBookId" &&  req.method.toLowerCase() == 'post') {
    return Book.deleteBookId(req);
  }else if (req.url == "/books/feedbackBook" &&  req.method.toLowerCase() == 'post') {
    return Book.feedbackBook(req);
  }
};

module.exports = {
  handlerBook
};
