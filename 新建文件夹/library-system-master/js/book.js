// 点击图书封面上传按钮时，触发input的上传按钮
document.getElementById("img-upload").onclick = function () {
  document.getElementById("img-file").click();
}
// 当输入框里面的文本发生变化之后才会触发的
// 通过change事件手动触发上传事件
document.getElementById("img-file").onchange = function () {
  document.getElementById("gallery").innerHTML = "";
  var img = document.getElementById("img-file").files;
  for (var i = 0; i < img.length; i++) {
    var file = img[i];
    var url = URL.createObjectURL(file);
    var box = document.createElement("img");
    box.setAttribute("src", url);
    box.className = 'img';

    var imgBox = document.createElement("div");
    imgBox.style.display = 'inline-block';
    imgBox.className = 'img-item';

    var deleteIcon = document.createElement("span");
    deleteIcon.className = 'delete';
    deleteIcon.innerText = 'x';
    deleteIcon.dataset.filename = img[i].name;
    imgBox.appendChild(deleteIcon);

    imgBox.appendChild(box);
     // 获取文档中所有指定类名gallery的元素集合
    var body = document.getElementsByClassName("gallery")[0];
    body.appendChild(imgBox);

    //ajax调用后台上传
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "http://127.0.0.1:3000/files/fileUpload", true);
    // 添加http头，发送信息至服务器时内容编码类型
    xhr.setRequestHeader("filename", encodeURIComponent(img[i].name));
    xhr.onreadystatechange = function () {
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 304)) {
        let result = JSON.parse(xhr.responseText);
        if (result.code == 200) {
          document.getElementById("book-file").value = result.data;
        }
      }
    };
    xhr.send(file);

    deleteIcon.onclick = function () {
      this.parentElement.remove();
      document.getElementById("img-file").value = "";
    }
  }
}


document.getElementById("txt-upload").onclick = function () {
  document.getElementById("txt-file").click();
}

document.getElementById("txt-file").addEventListener("change", ()=>{
  let file = document.getElementById("txt-file").files[0]; // 获取用户选择的第一个文件
  let reader = new FileReader(); // 创建 FileReader 对象
  reader.onload = showFile; // 添加 onload 事件监听器
  reader.readAsText(file, "utf-8"); // 以 utf-8 编码格式读取文件内容
  //ajax调用后台上传
  let xhr = new XMLHttpRequest();
  xhr.open("POST", "http://127.0.0.1:3000/files/fileUpload", true);
  // 添加http头，发送信息至服务器时内容编码类型
  xhr.setRequestHeader("filename", encodeURIComponent(file.name));
  xhr.onreadystatechange = function () {
    if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 304)) {
      let result = JSON.parse(xhr.responseText);
      if (result.code == 200) {
        document.getElementById("book-txt-file").value = result.data;
      }
    }
  };
  xhr.send(file);
});

function showFile(e) {
  let content = e.target.result; // 获取 FileReader 对象的 result 属性
  let textArea = document.getElementById("txt-show"); // 获取文本区域的元素对象
  textArea.value = content; // 将字符串赋值给文本区域的 value 属性
}


//提交新增书籍
let addBook = document.getElementById("addBook");
addBook.addEventListener("submit", function (e) {
  e.preventDefault();
  let formData = {
    // 获取用户输入的用户名和密码
    id: document.getElementById("book-id").value,
    createrName: document.getElementById("createrName").value,
    createrPhone: document.getElementById("createrPhone").value,
    createrAddress: document.getElementById("createrAddress").value,
    name: document.getElementById("name").value,
    author: document.getElementById("author").value,
    description: document.getElementById("description").value,
    type: document.getElementById("type").options[document.getElementById("type").selectedIndex].value,
    image: document.getElementById("book-file").value,
    file: document.getElementById("book-txt-file").value,
    status: 1
  };
  //格式校验
  if (!mobile(formData.createrPhone)) {
    message.show({type: 'warning', text: '申请人电话填写错误'})
    return;
  }
  if (formData.image == null || formData.image == undefined || formData.image == "") {
    message.show({type: 'warning', text: '请选择书籍封面'})
    return;
  }
  if (formData.file == null || formData.file == undefined || formData.file == "") {
    message.show({type: 'warning', text: '请选择书籍内容文件'})
    return;
  }

  Ajax.post('http://127.0.0.1:3000/books/add', JSON.stringify(formData), function (data) {
    // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
    // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
    let result = JSON.parse(data);
    if (result.code == 200) {
      message.show({type: 'success', text: result.msg})
    } else {
      message.show({type: 'error', text: result.msg})
    }
  });
  hideModal();
});


//提交草稿箱书籍 不做校验
let bookstore = document.getElementById("bookstore");
bookstore.addEventListener("click", () => {
  let formData = {
    id: document.getElementById("book-id").value,
    createrName: document.getElementById("createrName").value,
    createrPhone: document.getElementById("createrPhone").value,
    createrAddress: document.getElementById("createrAddress").value,
    name: document.getElementById("name").value,
    author: document.getElementById("author").value,
    description: document.getElementById("description").value,
    type: document.getElementById("type").options[document.getElementById("type").selectedIndex].value,
    image: document.getElementById("book-file").value,
    file: document.getElementById("book-txt-file").value,
    status: 1
  };


  Ajax.post('http://127.0.0.1:3000/books/add', JSON.stringify(formData), function (data) {
    // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
    // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
    let result = JSON.parse(data);
    if (result.code == 200) {
      message.show({type: 'success', text: '保存书籍到草稿箱成功'})
    } else {
      message.show({type: 'error', text: result.msg})
    }
  });
  hideModal();
})

let booksearch = document.getElementById("booksearch");
booksearch.addEventListener("click", () => {
  console.log('点击了')
  showbooks();
})
showbooks();

// 展示函数
function showbooks(pagenum) {

  let searchData = {
    // 获取用户输入的用户名和密码
    bookname: document.getElementById("bookname").value,
    bookauthor: document.getElementById("bookauthor").value,
    bookisbn: document.getElementById("bookisbn").value,
    booktype: document.getElementById("booktype").options[document.getElementById("booktype").selectedIndex].value,
    bookstatus: document.getElementById("bookstatus").options[document.getElementById("bookstatus").selectedIndex].value,
    pagesize: document.getElementById("paginationLimit").options[document.getElementById("paginationLimit").selectedIndex].value,
    pagenum: (pagenum == null || pagenum == '') ? 1 : pagenum
  };

  Ajax.post('http://127.0.0.1:3000/books/findBookAll', JSON.stringify(searchData), function (data) {
    // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
    // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
    let result = JSON.parse(data);
    if (result.code == 200) {
      let bookObj = [];
      if (result.data != null) {
        bookObj = result.data.result;
        let html = '';
        let booklist = document.getElementById("booklist");
        //for循环遍历本地存储的json数组内容,变成表单元素
        for (let index = 0; index < bookObj.length; index++) {
          let item = bookObj[index];
          let typename = '';
          if (item.type) {
            if (item.type == 1) {
              typename = '青春';
            } else if (item.type == 2) {
              typename = '小说';
            } else if (item.type == 3) {
              typename = '文学';
            } else if (item.type == 4) {
              typename = '艺术';
            }
          }
          let statusname = '';
          if (item.status) {
            if (item.status == 1) {
              statusname = '未提交';
            } else if (item.status == 2) {
              statusname = '待审核';
            } else if (item.status == 3) {
              statusname = '已通过';
            } else if (item.status == 4) {
              statusname = '被退回';
            }
          }
                // 拼接
          html += `<tr>
                      <td>
                        <div class="form-check check-tables">
                          <input class="form-check-input" type="checkbox" value="${item.id}">
                        </div>
                      </td>
                      <td>${item.isbn}</td>
                      <td>${item.name}</td>
                      <td>${item.author}</td>
                      <td>
                        <h2 class="table-avatar">
                          <a href="#" class="avatar avatar-sm me-2"><img
                                  class="avatar-img rounded-circle" src="${item.image}"
                           ></a>
                        </h2>
                      </td>
                      <td>${typename}</td>
                      <td>${statusname}</td>
                      <td>${item.feedback}</td>
                      <td class="text-end">
                        <a href="#" class="btn btn-sm btn-white text-success me-2" onclick="openeditmodal(${item.id})"><i
                                class="far fa-edit me-1"></i> 编辑</a>
                        <a class="btn btn-sm btn-white text-danger me-2" href="#" onclick="openDeleteModal(${item.id})"><i
                                class="far fa-trash-alt me-1"></i>删除</a>
                        <a class="btn btn-sm btn-white text-success me-2" href="#" onclick="openSendModal(${item.id},'${item.createrFeedback}','${item.feedback}')"><i
                                class="far fa-paper-plane me-1"></i>提交审核</a>
                      </td>
                    </tr>`;
        }
        //插入到表单元素中
        booklist.innerHTML = html;
        let pagetotal = document.getElementById("page-total");
        pagetotal.innerHTML = `共 ${result.data.total} 条数据`;
        let pagenum = document.getElementById("page-num");
        let paginationLimit = document.getElementById("paginationLimit").options[document.getElementById("paginationLimit").selectedIndex].value;
        const pageCount = result.data.total % paginationLimit == 0 ? result.data.total / paginationLimit : Math.floor(result.data.total / paginationLimit) + 1;
        let currentPage = result.data.pagenum;
        let pagehtml = '';
        if (currentPage == 1) {
          pagehtml += `<li class="page-item disabled"><a href="#" class="page-link">上一页</a></li>`;
        } else {
          pagehtml += `<li class="page-item" "><a href="#" class="page-link" onclick="prePage(${currentPage})">上一页</a></li>`;
        }

        for (let index = 1; index <= pageCount; index++) {
          if (currentPage == index) {
            pagehtml += `<li class="page-item active"><a href="#" class="page-link" onclick="indexPage(${index})">${index}</a></li>`;
          } else {
            pagehtml += `<li class="page-item"><a href="#" class="page-link" onclick="indexPage(${index})">${index}</a></li>`;
          }
        }
        if (currentPage == pageCount) {
          pagehtml += `<li class="page-item disabled"><a href="#" class="page-link">下一页</a></li>`;
        } else {
          pagehtml += `<li class="page-item"><a href="#" class="page-link" onclick="nexPage(${currentPage})">下一页</a></li>`;
        }
        pagenum.innerHTML = pagehtml;
        message.show({type: 'info', text: "查询成功"})
      }
    } else {
      message.show({type: 'error', text: result.msg})
    }
  });
}

//改变下拉条数
document.getElementById("paginationLimit").onchange = function () {
  showbooks(1);
}

//点击上一页
function prePage(currentPage) {
  showbooks(currentPage - 1);
}

//点击下一页
function nexPage(currentPage) {
  showbooks(currentPage + 1);
}

//点击具体的页码跳转
function indexPage(indexPage) {
  showbooks(indexPage);
}


var deleteModal = document.getElementById("deleteModal");
var sendModal = document.getElementById("sendModal");
var cancelBtn = document.querySelector(".cancel-btn");
var btnClose = document.querySelectorAll(".btn-close");

function openDeleteModal(bookid) {
  deleteModal.style.display = "block";
  let idData = {
    id: bookid
  };
  document.getElementById("delete-btn").onclick = function () {
    Ajax.post('http://127.0.0.1:3000/books/deleteBookId', JSON.stringify(idData), function (data) {
      // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
      // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
      let result = JSON.parse(data);
      if (result.code == 200) {
        message.show({type: 'success', text: result.msg})
      } else {
        message.show({type: 'error', text: result.msg})
      }
    });
    hideModal();
  }
}

function openSendModal(bookid, createrFeedback, feedback) {
  sendModal.style.display = "block";
  document.getElementById("createrFeedback").value = createrFeedback ? createrFeedback : "";
  document.getElementById("feedback").value = feedback ? feedback : "";
  document.getElementById("feedbackstatus").selectedIndex[0]=true;
  //提交审核
  let feedbookback = document.getElementById("feedbookback");
  feedbookback.addEventListener("submit", function (e) {
    e.preventDefault();
    let feedData = {
      id: bookid,
      createrFeedback: document.getElementById("createrFeedback").value,
      feedback: document.getElementById("feedback").value,
      status: document.getElementById("feedbackstatus").options[document.getElementById("feedbackstatus").selectedIndex].value
    };
    Ajax.post('http://127.0.0.1:3000/books/feedbackBook', JSON.stringify(feedData), function (data) {
      // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
      // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
      let result = JSON.parse(data);
      if (result.code == 200) {
        message.show({type: 'success', text: result.msg})
      } else {
        message.show({type: 'error', text: result.msg})
      }
    });
    hideModal();
  });
}

// 删除弹窗的关闭
// forEach遍历增加点击事件--因为btnClose不止一个
btnClose.forEach(item => {
  item.addEventListener("click", () => {
    hideModal();
  });
})

cancelBtn.addEventListener("click", () => {
  hideModal();
});

// 每次点击添加按钮，置空弹窗里的内容并显示弹窗
var addModal = document.getElementById("addModal");
var openAddModalBtn = document.querySelector(".openAddModal");
openAddModalBtn.addEventListener("click", () => {
  resetModal();
  addModal.style.display = "block";
  document.getElementById("addCenterModal").style.display = "block";
  document.getElementById("editCenterModal").style.display = "none";
});
// 开始把三大弹窗都置空的函数
function hideModal() {
  if (deleteModal) {
    deleteModal.style.display = "none";
  }
  if (addModal) {
    addModal.style.display = "none";
  }
  if (sendModal) {
    sendModal.style.display = "none";
  }
}
// 浏览器中：event获取的是点击事件的所处的标签。
window.onclick = function (event) {
  if (event.target == deleteModal) {
    hideModal();
  }
};


function openeditmodal(id) {
  resetModal();
  addModal.style.display = "block";
  document.getElementById("addCenterModal").style.display = "none";
  document.getElementById("editCenterModal").style.display = "block";
  let idData = {
    id: id
  };
  Ajax.post('http://127.0.0.1:3000/books/findBookId', JSON.stringify(idData), function (data) {
    let result = JSON.parse(data);
    if (result.code == 200) {
      if (result.data != null) {
        let bookObj = result.data;
        document.getElementById("book-id").value = bookObj.id;
        document.getElementById("createrName").value = bookObj.createrName;
        document.getElementById("createrName").value = bookObj.createrName;
        document.getElementById("createrPhone").value = bookObj.createrPhone;
        document.getElementById("createrAddress").value = bookObj.createrAddress;
        document.getElementById("name").value = bookObj.name;
        document.getElementById("author").value = bookObj.author;
        document.getElementById("description").value = bookObj.description;
        document.getElementById("type").options[bookObj.type].selected = true;
        document.getElementById("book-file").value = bookObj.image;
        document.getElementById("book-txt-file").value = bookObj.file;
        if (bookObj.image) {
          var box = document.createElement("img");
          box.setAttribute("src", bookObj.image);
          box.className = 'img';
          var imgBox = document.createElement("div");
          imgBox.style.display = 'inline-block';
          imgBox.className = 'img-item';
          var deleteIcon = document.createElement("span");
          deleteIcon.className = 'delete';
          deleteIcon.innerText = 'x';
          imgBox.appendChild(deleteIcon);
          imgBox.appendChild(box);
          var body = document.getElementsByClassName("gallery")[0];
          body.appendChild(imgBox);
          deleteIcon.onclick = function () {
            this.parentElement.remove();
            document.getElementById("img-file").value = "";
          }

        }
        if (bookObj.file) {
          Ajax.get(bookObj.file, function (data) {
            let textArea = document.getElementById("txt-show"); // 获取文本区域的元素对象
            textArea.value = data; // 将字符串赋值给文本区域的 value 属性
          })
        }
      }
    }


  });
}
//置空添加图书弹窗的函数
function resetModal() {
  document.getElementById("book-id").value = "";
  document.getElementById("createrName").value = "";
  document.getElementById("createrPhone").value = "";
  document.getElementById("createrAddress").value = "";
  document.getElementById("name").value = "";
  document.getElementById("author").value = "";
  document.getElementById("description").value = "";
  document.getElementById("type").options[0].selected = true;
  document.getElementById("img-file").value = "";
  document.getElementById("book-file").value = "";
  document.getElementById("txt-file").value = "";
  document.getElementById("book-txt-file").value = "";
  document.getElementById("txt-show").value = "";
  let img = document.querySelector(".img-item");
  if (img) {
    img.remove();
  }
}

//手机号校验
function mobile(value) {
  const reg = /^[1][3,4,5,6,7,8,9][0-9]{9}$/;
  return reg.test(value);
}
