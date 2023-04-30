// Nodejs使用MysQL的连接池
// 引入
const mysql = require('mysql');

module.exports = {
  config: {
    host: 'localhost',
    port: '3306',
    user: 'root',
    password: 'haohao',
    database: 'library_system'
  },
  sqlConnect: function (sql, sqlArr, callback) {
    // 创建连接池
    var pool = mysql.createPool(this.config);
     // 从创建的连接池中获取到一个我们需要的连接
    // 使用回调函数的参数conn来查询数据库
    pool.getConnection((err, conn) => {
      if (err) {
        console.log('---数据库连接失败---')
        return;
      }

      conn.query(sql, sqlArr, callback);
      //释放
      conn.release();
    })
  },
  SySqlConnect: function (sql, sqlArr) {
    return new Promise((resolve, reject) => {
      var pool = mysql.createPool(this.config);
      pool.getConnection((err, conn) => {
        if (err) {
          reject(err)
        } else {
          conn.query(sql, sqlArr, (err, data) => {
            if (err) {
              reject(err) //sql失败回调
            } else {
              console.log("数据库查询结果",data);
              resolve(data) //sql成功回调
            }
          });
          //释放
          conn.release();
        }
      })
    }).catch((err) => {
      console.log(err)
    })
  }
}

//Promise 的构造函数接收一个参数，是函数，而且传入两个参数：resolve，reject，分别表示异步操做执行成功后的回调函数和异步操做执行失败后的回调函数。
// Promise 的优点在于，能够在 then 方法中继续写 Promise 对象并返回，而后继续调用 then 来进行回调操做。