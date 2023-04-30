const fs = require('fs');
fileUpload = async (req) => {

  let temp = new Promise(function (resolve, reject) {
 // 请求头里文件大小，如果没有这个请求头，说明文件内容是空的
    let contentLength = parseInt(req.headers['content-length'])
    if (isNaN(contentLength) || contentLength <= 0) {
      resolve({
        'code': 400,
        'msg': '上传失败!'
      })
    }
    let filename = decodeURIComponent(req.headers['filename']);
    const filestream = fs.createWriteStream(`static/${filename}`)
    let result = null;
     //读取文件发生错误事件
    filestream.on("error", (error) => {
      console.error(error)
      resolve({
        'code': 400,
        'msg': '上传失败!'
      })
    })
      // 将请求里的文件内容往filestream里写
    req.pipe(filestream);
    req.on('end', () => {
        // 关闭通道
      filestream.close(() => {
        resolve({
          'code': 200,
          'msg': '上传成功!',
          'data': `http://127.0.0.1:3000/static/${filename}`
        })
      })
    })
  })
  return temp;
}
module.exports = {
  fileUpload
}


// isNaN只对数值有效，如果传入其他值，会被先转成数值。

// isNaN为true的值，有可能不是NaN，而是一个字符串。
// decodeURIComponent() 能够解码使用 encodeURIComponent() 编码的所有字符串。
