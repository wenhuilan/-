var dbConfig = require('../utils/dbConfig')
const url = require("url");

// 获取总条数
let getBookCount = async () => {
  let sql = `select count(*) as nums from books`;
  let result = await dbConfig.SySqlConnect(sql, []);
  return result[0].nums;
}


// 获取有条件的总条数
let getBookWhereCount = async (table, where) => {
  let sql = `select count(*) as nums from ${table} where ${where}`;
  let result = await dbConfig.SySqlConnect(sql, []);
  return result[0].nums;
}


//根据名称查找书籍
findBookAll = async (req) => {
  let {
    bookname, //名称
    bookauthor,//书名作者
    bookisbn,//图书isbn
    booktype,//图书类型
    bookstatus,//图书审核状态
    pagenum, //当前页数
    pagesize //获取条数
  } = req.body;

  let start = (pagenum - 1) * pagesize;

  let param = ` 1=1 `;
  if (bookname) {
    param += ` and name like '%${bookname}%' `;
  }
  if (bookauthor != null && bookauthor != undefined && bookauthor != "") {
    param += ` and author like '%${bookauthor}%' `;
  }
  if (bookisbn != null && bookisbn != undefined && bookisbn != "") {
    param += ` and isbn = '${bookisbn}' `;
  }
  if (booktype != null && booktype != undefined && booktype != "") {
    param += ` and type = '${booktype}' `;
  }
  if (bookstatus != null && bookstatus != undefined && bookstatus != "") {
    param += ` and status = '${bookstatus}' `;
  }
  let sql = `select * from books where ` + param + ` limit ${start},${pagesize}`;
  let result = await dbConfig.SySqlConnect(sql, []);

  //获取总条数
  let total = await getBookWhereCount('books', param);

  if (result.length) {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': {
        'result': result,
        'total': total,
        'pagenum': pagenum,
        'pagesize': pagesize
      }
    }
  } else {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': {
        'result': result,
        'total': total,
        'pagenum': pagenum,
        'pagesize': pagesize
      }
    }
  }
}

//根据图书id查找
findBookId = async (req) => {
  let {
    id
  } = req.body;

  let sql = `select * from books where id = ?`;
  let result = await dbConfig.SySqlConnect(sql, [id]);
  if (result.length) {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': result[0]
    }
  } else {
    return {
      'code': 400,
      'msg': '不存在'
    }
  }
}


//删除书籍
deleteBookId = async (req) => {
  let {
    id
  } = req.body;

  let sql = `delete from books where id=?`;
  let result = await dbConfig.SySqlConnect(sql, [id])
  if (result.affectedRows == 1) {
    return {
      'code': 200,
      'msg': '删除书籍成功'
    }
  } else {
    return {
      'code': 400,
      'msg': '删除书籍失败'
    }
  }
}

feedbackBook = async (req) => {
  let {
    id,
    createrFeedback,
    feedback,
    status
  } = req.body;
  //需要更新书籍操作
  let sql = 'update books set createrFeedback=?,feedback=?,status=? where id=?';
  let sqlAll = [
    createrFeedback,
    feedback,
    status,
    id
  ];
  let result = await dbConfig.SySqlConnect(sql, sqlAll);
  if (result.affectedRows == 1) {
    return ({
      'code': 200,
      'msg': '发送审核成功'
    })
  } else {
    return ({
      'code': 400,
      'msg': '发送审核失败'
    })
  }

}

commentBook = async (req) => {
  let {
    id,
    comment
  } = req.body;
  console.log(id, comment);
  //需要更新书籍操作
  let sql = 'update books set commentBook=? where id=?';
  let sqlAll = [
    comment,
    id
  ];
  let result = await dbConfig.SySqlConnect(sql, sqlAll);
  if (result.affectedRows == 1) {
    return ({
      'code': 200,
      'msg': '发送评论成功'
    })
  } else {
    return ({
      'code': 400,
      'msg': '发送评论失败'
    })
  }

}

addBook = async (req) => {
  let {
    id,
    name,
    author,
    description,
    file,
    image,
    type,
    status,
    createrName,
    createrPhone,
    createrAddress
  } = req.body;
  let createrUserId = req.user.id;

  if (id != null && id != undefined && id != "") {
    //需要更新书籍操作
    let sql = 'update books set name=?,author=?,description=?,file=?,image=?,type=?,status=?,createrName=?,createrPhone=?,createrAddress=?,createrUserId=? where id=?';
    let sqlAll = [
      name,
      author,
      description,
      file,
      image,
      type,
      status,
      createrName,
      createrPhone,
      createrAddress,
      createrUserId,
      id
    ];
    let result = await dbConfig.SySqlConnect(sql, sqlAll);
    if (result.affectedRows == 1) {
      return ({
        'code': 200,
        'msg': '编辑书籍成功'
      })
    } else {
      return ({
        'code': 400,
        'msg': '编辑书籍失败'
      })
    }
  } else {
    //需要新增书籍操作
    let isbn = nanoid(8);
    let sql = 'insert into books(isbn,name,author,description,file,image,type,status,createrName,createrPhone,createrAddress,createrUserId) values(?,?,?,?,?,?,?,?,?,?,?,?)';
    let sqlAll = [
      isbn,
      name,
      author,
      description,
      file,
      image,
      type,
      status,
      createrName,
      createrPhone,
      createrAddress,
      createrUserId
    ];

    let result = await dbConfig.SySqlConnect(sql, sqlAll);
    if (result.affectedRows == 1) {
      return ({
        'code': 200,
        'msg': '添加书籍成功'
      })
    } else {
      return ({
        'code': 400,
        'msg': '添加书籍失败'
      })
    }
  }
}

//导出书籍查询
exportBookAll = async (req) => {
  let {
    createrUserId,//创建人id
    bookname, //名称
    bookauthor,//书名作者
    bookisbn,//图书isbn
    booktype,//图书类型
    bookstatus,//图书审核状态
    ids //书籍id选中集合
  } = url.parse(req.url, true).query;


  let param = ` 1=1 `;
  // 判断是否有勾选，有则选择所有勾选的书籍导出，否则按照将展示的书籍导出
  if (ids) {
    param += ` and id in (` + ids + `)`;
  } else {
    if (bookname) {
      param += ` and name like '%${bookname}%' `;
    }
    if (bookauthor != null && bookauthor != undefined && bookauthor != "") {
      param += ` and author like '%${bookauthor}%' `;
    }
    if (bookisbn != null && bookisbn != undefined && bookisbn != "") {
      param += ` and isbn = '${bookisbn}' `;
    }
    if (booktype != null && booktype != undefined && booktype != "") {
      param += ` and type = '${booktype}' `;
    }
    if (bookstatus != null && bookstatus != undefined && bookstatus != "") {
      param += ` and status = '${bookstatus}' `;
    }
    if (createrUserId != null && createrUserId != undefined && createrUserId != "") {
      param += ` and createrUserId = '${createrUserId}' `;
    }
  }

  let sql = `select * from books where ` + param + `order by created_time desc `;
  console.log('查询sql导出', sql)
  let result = await dbConfig.SySqlConnect(sql, []);
  return result;
}

// 随机生成
let urlAlphabet =
  'useandom26T198340PX75pxJACKVERYMINDBUSHWOLFGQZbfghjklqvwyzrict'

let nanoid = (size = 21) => {
  let id = ''
  let i = size
  while (i--) {
    id += urlAlphabet[(Math.random() * 62) | 0]
  }
  return id
}


module.exports = {
  findBookAll,
  deleteBookId,
  addBook,
  findBookId,
  feedbackBook,
  commentBook,
  exportBookAll
}
