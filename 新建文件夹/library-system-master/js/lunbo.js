
//轮播图类
class Slide {
    constructor(images) {
        this.slideBoxDOM = document.querySelector('.slide-box');
        this.slideLeftBtnDOM = this.slideBoxDOM.querySelector(".slide-left-btn");
        this.slideRightBtnDOM = this.slideBoxDOM.querySelector(".slide-right-btn");
        this.bannerBoxDOM = this.slideBoxDOM.querySelector(".banner-box");
        this.paginationBoxDOM = this.slideBoxDOM.querySelector(".pagination-box");

        // 计数器
        this._currentIndex = 0;
        this._bannerItemDOMs = null;
        this._bannerItemDOMsLen = 0;


        // 图片对象数据
        this.banners = images;
        this.imageUrl = '';

        //定时器
        this.timer = null;
    };

    get currentIndex() {
        return this._currentIndex;
    }

    //用来监听计数器变化,根据变换来改变当前的横幅
    set currentIndex(num) {
        // 将所有横幅归初始
        Object.values(this.bannerItemDOMs).forEach((item, i) => {
            item.classList.remove('left', 'middle', 'right');
            item.onclick = null;
            this.paginationBoxDOM.children[i].classList.remove('chose');
        });

        if (num < 0) {
            this._currentIndex = this.bannerItemDOMsLen - 1;
        } else if (num >= this.bannerItemDOMsLen) {
            this._currentIndex = 0;
        } else {
            this._currentIndex = num;
        }
        this.paginationBoxDOM.children[this._currentIndex].classList.add('chose');

        if (this._currentIndex === 0) {
            this.showCurrentBanner(this.bannerItemDOMsLen - 1, this._currentIndex, this._currentIndex + 1);
        } else if (this._currentIndex === this.bannerItemDOMsLen - 1) {
            this.showCurrentBanner(this._currentIndex - 1, this._currentIndex, 0)
        } else {
            this.showCurrentBanner(this._currentIndex - 1, this._currentIndex, this._currentIndex + 1);
        }
    }

    showCurrentBanner(leftIndex, mindleIndex, rightIndex) {

        this.bannerItemDOMs[leftIndex].classList.add('left');
        this.bannerItemDOMs[mindleIndex].classList.add('middle');
        this.bannerItemDOMs[rightIndex].classList.add("right");
        this.bannerItemDOMs[leftIndex].onclick = () => {
            this._currentIndex--;
        }
        this.bannerItemDOMs[rightIndex].onclick = () => {
            this._currentIndex++;
        }
    }

    getBannerItemDOMs() {
        return this.slideBoxDOM.querySelectorAll('.banner-item');
    }

    // 获取 banner-itemDOM 字符串，用来渲染 DOM
    // getBannerHTML(imageName){
    getBannerItemHTML(imageName) {
        return `<div class="banner-item"><img src="${this.imageUrl + imageName}"></div>`
    }

    //渲染DOM
    drawDOM(banners) {
        this.bannerBoxDOM.innerHTML = banners.reduce((html, item) => {
            return html + this.getBannerItemHTML(item.imageName);
        }, '');
        this.banners.forEach((item, i) => {
            const span = document.createElement('span');
            span.addEventListener('mouseover', () => {
                this._currentIndex = 1;
            });
            this.paginationBoxDOM.append(span);
        });
    }
    //启动定时器
    openTimer() {
        this.timer = setInterval(() => {
            this.currentIndex++;
        }, 3000);
    }
    stopTimer() {
        clearInterval(this.timer);
    }
    init() {
        //初始化
        this.drawDOM(this.banners);
        this.bannerItemDOMs = this.getBannerItemDOMs();
        this.bannerItemDOMsLen = this.bannerItemDOMs.length;
        this.currentIndex = 0;


        //监听事件
        this.slideLeftBtnDOM.addEventListener('click', () => {
            this.currentIndex--;
        })
        this.slideRightBtnDOM.addEventListener('click', () => {
            this.currentIndex++;
        })

        //自动轮播
        this.openTimer();
        this.slideBoxDOM.addEventListener('mouseover', () => {
            this.stopTimer();
        });
        this.slideBoxDOM.addEventListener('mouseout', () => {
            this.openTimer();
        })
    }
}

showbooks();
// 展示函数
function showbooks() {

    let searchData = {
        pagesize: 6,
        pagenum: 1
    };

    Ajax.post('http://127.0.0.1:3000/books/findBookAll', JSON.stringify(searchData), function (data) {
        // 后台返回的数据就是 字符串类型。要转成json，必须自己手动转换。
        // JSON.parse() 方法解析一个JSON字符串，构造由字符串描述的JavaScript值或对象
        let result = JSON.parse(data);
        if (result.code == 200) {
            let bookObj = [];
            if (result.data != null) {
                bookObj = result.data.result;
                let image = [];
                //for循环遍历本地存储的json数组内容,变成表单元素
                for (let index = 0; index < bookObj.length; index++) {
                    let item = bookObj[index];
                    image.push({
                        imageName: item.image,
                    });
                }
                new Slide(image).init();
            }
        }
    });

}
