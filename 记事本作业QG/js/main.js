// 动态展示表格内容
showtask();
// 获取元素
let addtaskinput = document.getElementById("addtaskinput");
let addtaskbtn = document.getElementById("addtaskbtn");


// 给添加笔记按钮注册点击事件
addtaskbtn.addEventListener("click", function () {
  addtaskinputval = addtaskinput.value;
  let Val = addtaskinputval.trim();
  // trim() 方法用于删除字符串的头尾空白符，空白符包括：空格、制表符 tab、换行符等其他空白符等。
  if (Val && Val != '' && Val.length > 0) {
    // localStorage.getItem(key): 获取指定key本地存储的值  
    // key是本地存储 存放的时候 这个key的名称是key               
    let webtask = localStorage.getItem("key");
    if (webtask == null) {
      // 定义一个空数组
      a = [];
    } else {
      // 类型转化, JSON.parse()方法将JSON格式字符串转换为js对象
      a = JSON.parse(webtask);
    }
    // 添加新的值 往数组里
    a.push({ 'task_name': addtaskinputval });
    // JSON.stringify()先将对象转换为字符串；
    localStorage.setItem("key", JSON.stringify(a));
    // 将新添加的笔记存储好后，输入框内容置空
    addtaskinput.value = '';
  }
  // 每添加完一次笔记，就显示出来
  showtask();
})


// 展示函数
function showtask() {
  let webtask = localStorage.getItem("key");
  if (webtask == null) {
    a = [];
  } else {
    a = JSON.parse(webtask);
  }
  // 定义一个空字符串变量  变量名叫html
  let html = '';
  let addedtasklist = document.getElementById("addedtasklist");
  //for循环遍历本地存储的json数组内容,变成表单元素
  for (let index = a.length - 1; index >= 0; index--) {
    let item = a[index];
    // js 动态添加 html 代码  拼接标签字符串，并用 innerHTML 来添加
    html += `<tr>
                    <th scope="row">${index + 1}</th>
                     <td>${item.task_name}</td>
                    <td><button type="button" onclick="edittask(${index})" ><img src="images/edit.png" alt="" class="button-img"></button></td>
                    <td><button type="button" onclick="deleteitem(${index})" ><img src="images/delete.png" alt="" class="button-img"></button></td>
                </tr>`;
  }
  //插入到表单元素中
  addedtasklist.innerHTML = html;
}


// 编辑函数-编辑选中的笔记  修改之前保存的笔记用
function edittask(index) {
  let saveindex = document.getElementById("saveindex");
  let addtaskbtn = document.getElementById("addtaskbtn");
  let savetaskbtn = document.getElementById("savetaskbtn");
  //设置当前记录值为索引
  saveindex.value = index;
  let webtask = localStorage.getItem("key");
  let a = JSON.parse(webtask);
  //设置输入框内容为取出的值
  // a[index]['task_name']就是说a数组第index个对象里面'task_name'的值
  addtaskinput.value = a[index]['task_name'];
  // 切换动作
  //设置添加按钮不展示
  addtaskbtn.style.display = "none";
  //设置保存笔记按钮展示
  savetaskbtn.style.display = "block";
}


// 保存函数
let savetaskbtn = document.getElementById("savetaskbtn");
// 添加事件监听
savetaskbtn.addEventListener("click", function () {
  let addtaskbtn = document.getElementById("addtaskbtn");
  let webtask = localStorage.getItem("key");
  let a = JSON.parse(webtask);
  let saveindex = document.getElementById("saveindex").value;

  //JS for in 循环是一种特殊类型的循环，也是普通 for 循环的变体，主要用来遍历对象，使用它可以将对象中的属性依次循环出来
  for (keys in a[saveindex]) {
    if (keys == 'task_name') {
      //如果key是task_name，则更新值为输入框的内容
      a[saveindex].task_name = addtaskinput.value;
    }
  }
  savetaskbtn.style.display = "none";
  addtaskbtn.style.display = "block";
  localStorage.setItem("key", JSON.stringify(a));
  addtaskinput.value = '';
  showtask();
})


// 删除函数
function deleteitem(index) {
  let webtask = localStorage.getItem("key");
  let a = JSON.parse(webtask);
  //splice删除index位置的元素
  a.splice(index, 1);
  savetaskbtn.style.display = "none";
  addtaskbtn.style.display = "block";
  localStorage.setItem("key", JSON.stringify(a));

  showtask();
}


// 删除所有函数
let deleteallbtn = document.getElementById("deleteallbtn");
deleteallbtn.addEventListener("click", function () {
  let savetaskbtn = document.getElementById("savetaskbtn");
  let addtaskbtn = document.getElementById("addtaskbtn");
  let a = [];
  savetaskbtn.style.display = "none";
  addtaskbtn.style.display = "block";
  localStorage.setItem("key", JSON.stringify(a));
  showtask();

})


// 查询函数
let searchtextbox = document.getElementById("searchtextbox");
searchtextbox.addEventListener("input", function () {
  //获取所有tr 行元素
  let trlist = document.querySelectorAll("tr");
  // Array.from将trlist转换数组然后foreach遍历  每个值是item
  Array.from(trlist).forEach(function (item) {
    //因为第一个td元素是笔记本内容 所以获取td[0]
    let tdGet = item.getElementsByTagName("td")[0];
    //获取查询内容
    let tdText = tdGet.innerText;
    let searchtextboxval = searchtextbox.value;
    //RegExp表示正则表达式匹配
    let re = new RegExp(searchtextboxval, 'gi');
    if (tdText.match(re)) {
      //若匹配到则将这一行显示出来
      item.style.display = "table-row";
      if (searchtextboxval && searchtextboxval != '' && searchtextboxval.length > 0) {
        //如果查询内容不为空，则将样式变成高亮completed
        tdGet.className = "completed";
      } else {
        tdGet.className = "";
      }
    } else {
      item.style.display = "none";
    }
  })
})












