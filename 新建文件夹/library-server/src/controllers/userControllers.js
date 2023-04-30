// controllers是从数据库里拿到数据内容后，进行增加删除查询等操作

var dbConfig = require('../utils/dbConfig');
var tokenUtil = require('../utils/token');

// async表示函数里有异步操作，await表示紧跟在后面的表达式需要等待结果。

// 根据用户名称判断用户存不存在
let isExist = async (name) => {
  let sql = `select * from user where name=?`;
  let sqlArr = [name];
  let result = await dbConfig.SySqlConnect(sql, sqlArr);
  if (result.length) {
    return result[0];
  } else {
    return false;
  }
}

 
let isExistId = async (id) => {
  let sql = `select * from user where id=?`;
  let sqlArr = [id];
  let result = await dbConfig.SySqlConnect(sql, sqlArr);
  if (result.length) {
    return result[0];
  } else {
    return false;
  }
}


//用户名和密码登录
login = async (req) => {
// 从req.body请求参数的body里把请求内容，赋值给name pwd email admin--用户输入的账号密码
  let {
    name,
    pwd
  } = req.body;
  console.log(name, pwd)
  let result = await isExist(name);
  // 用户存在
  if (result) {
    //比较数据库里保存的用户密码和是用户表单里输入的密码
    if (result.pwd == pwd) {
      let token = tokenUtil.setToken({name: result.name, admin: result.admin, id: result.id});
      return {
        'code': 200,
        'msg': '登录成功',
        'data': token
      }
    } else {
      return {
        'code': 400,
        'msg': '密码错误'
      }
    }
  } else {
    return {
      'code': 400,
      'msg': '该用户不存在'
    }
  }
}

//注册
register = async (req) => {
  let {
    name,
    pwd,
    email,
    admin
  } = req.body;

  let result = await isExist(name);
  console.log(name,
      pwd,
      email,
      admin)
  if (result) {
    return {
      'code': 400,
      'msg': '注册失败，用户已经存在'
    }
  } else {
    if (name && pwd && email) {
      let sql = `insert into user(pwd,name,email,admin) values(?,?,?,?)`;
      let sqlArr = [pwd, name, email, admin];
      let result = await dbConfig.SySqlConnect(sql, sqlArr);
      console.log(result.affectedRows)
      if (result.affectedRows == 1) {
        return {
          'code': 200,
          'msg': '注册成功'
        }
      } else {
        return {
          'code': 400,
          'msg': '注册失败!'
        }
      }
    } else {
      return {
        'code': 400,
        'msg': '没有输入有效的信息！'
      }
    }
  }
}


//修改密码
editUserpass = async (req) => {
  let {
    pwd,
    newpwd
  } = req.body;
  let id=req.user.id;
  let result = await isExistId(id);
  if (result) {
    if (result.pwd == pwd) {
      let sql = `update user set pwd=? where id=?`;
      let sqlArr = [newpwd, id];
      let data = await dbConfig.SySqlConnect(sql, sqlArr);
      if (data.affectedRows == 1) {
        return {
          'code': 200,
          'msg': '修改成功'
        }
      } else {
        return {
          'code': 400,
          'msg': '修改失败'
        }
      }
    } else {
      return {
        'code': 400,
        'msg': '密码错误'
      }
    }
  } else {
    return {
      'code': 400,
      'msg': '该用户名不存在'
    }
  }

}


// 修改用户信息  名称/状态/身份
editUserinfo = async (req) => {
  let {
    name,
    email,
    image,
    phone,
    address,
  } = req.body;
  let id=req.user.id;

  let sql = `update user set name=?,email=?,image=?,phone=?,address=? where id=?`;
  let sqlArr = [name, email, image, phone,address,id];
  let data = await dbConfig.SySqlConnect(sql, sqlArr);
  console.log(data, data.affectedRows)
  if (data.affectedRows == 1) {
    return {
      'code': 200,
      'msg': '修改成功'
    }
  } else {
    return {
      'code': 400,
      'msg': '修改失败'
    }
  }

}


//获取当前用户信息
getUserInfo = async (req) => {
  let {
    id
  } = req.user;
  let result = await isExistId(id);
  console.log(result, id)
  if (result) {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': result
    }
  } else {
    return {
      'code': 400,
      'msg': '获取失败',
    }
  }
}


//获取所有用户信息
getUserAll = async (req) => {
  let sql = `select * from user`;
  let sqlArr = [];
  let result = await dbConfig.SySqlConnect(sql, sqlArr);
  return {
    'code': 200,
    'msg': '获取成功',
    'data': result
  }
}

//修改用户的激活状态
editUserStatus = async (req) => {
  let {
    id,
    status
  } = req.body;


  let sql = `update user set status=? where id=?`;
  let sqlArr = [status, id];
  let data = await dbConfig.SySqlConnect(sql, sqlArr);
  if (data.affectedRows == 1) {
    return {
      'code': 200,
      'msg': '修改成功'
    }
  } else {
    return {
      'code': 400,
      'msg': '修改失败'
    }
  }
}

//查找用户
findUsername = async (req) => {
  let {
    name
  } = req.body;
  let sql = `select * from user where name like '${name}%'`;
  let result = await dbConfig.SySqlConnect(sql, []);
  if (result.length) {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': result
    }
  } else {
    return {
      'code': 400,
      'msg': '用户不存在',
    }
  }

}

//删除用户
deleteUser = async (req) => {
  let {
    id
  } = req.body;
  let sql = `delete from user where id=?`;
  let sqlArr = [id];
  let data = await dbConfig.SySqlConnect(sql, sqlArr);
  console.log(id, data)
  if (data.affectedRows == 1) {
    return {
      'code': 200,
      'msg': '删除成功'
    }
  } else {
    return {
      'code': 400,
      'msg': '删除失败'
    }
  }

}

//统计用户
userDataCount = async (req) => {
  let sql = 'SELECT COUNT(*) AS count FROM `user` WHERE admin=0 and admin=1';
  let result = await dbConfig.SySqlConnect(sql, []);
  if (result.length) {
    return {
      'code': 200,
      'msg': '获取成功',
      'data': result
    }
  } else {
    return {
      'code': 400,
      'msg': '获取失败'
    }
  }
}


module.exports = {
  login,
  register,
  editUserpass,
  editUserinfo,
  editUserStatus,
  getUserInfo,
  getUserAll,
  findUsername,
  deleteUser,
  userDataCount
}
