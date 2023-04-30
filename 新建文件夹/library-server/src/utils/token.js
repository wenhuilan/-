const jwt = require('jsonwebtoken');
//秘钥
const screat = 'haohao';

//生成token
function setToken(playload) {
    return jwt.sign(playload, screat,{
        expiresIn: "1h",
    });
}

//验证token
function verToken(token) {
    console.log("验证token",token);
    try {
        const decoded = jwt.verify(token, screat);
        return {code: 200, data:decoded};
    } catch (err) {
        return {code: 502, msg: 'token 验证失败'};
    }
}

module.exports = { setToken, verToken }
