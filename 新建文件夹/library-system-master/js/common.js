// 侧边导航栏
var allDropdown = document.querySelectorAll('#sidebar .side-dropdown');
var sidebar = document.getElementById('sidebar');

allDropdown.forEach(item => {
	const a = item.parentElement.querySelector('a:first-child');
	a.addEventListener('click', function (e) {
		e.preventDefault();

		if (!this.classList.contains('subdrop')) {
			allDropdown.forEach(i => {
				const aLink = i.parentElement.querySelector('a:first-child');

				aLink.classList.remove('subdrop');
				i.classList.remove('show');
			})
		}
		this.classList.toggle('subdrop');
		item.classList.toggle('show');
	})
})


// SIDEBAR COLLAPSE
var brand = document.querySelector('.header .brand');
var toggleSidebar = document.querySelector('.header .toggle-sidebar');
var allSideDivider = document.querySelectorAll('#sidebar .divider');


allDropdown.forEach(item => {
	const a = item.parentElement.querySelector('a:first-child');
	if (a.classList.contains('active')) {
		a.classList.toggle('subdrop');
		item.classList.toggle('show');
	} else {
		a.classList.remove('subdrop');
		item.classList.remove('show');
	}
})


toggleSidebar.addEventListener('click', function () {
	sidebar.classList.toggle('hide');
	brand.classList.toggle('hide');
	if (sidebar.classList.contains('hide')) {
		allSideDivider.forEach(item => {
			item.textContent = '-'
		})
		allDropdown.forEach(item => {
			const a = item.parentElement.querySelector('a:first-child');
			a.classList.remove('subdrop');
			item.classList.remove('show');
		})
	} else {
		allDropdown.forEach(item => {
			const a = item.parentElement.querySelector('a:first-child');
			if (a.classList.contains('active')) {
				a.classList.toggle('subdrop');
				item.classList.toggle('show');
			} else {
				a.classList.remove('subdrop');
				item.classList.remove('show');
			}
		})



		allSideDivider.forEach(item => {
			item.textContent = item.dataset.text;
		})
	}
})


sidebar.addEventListener('mouseleave', function () {
	if (this.classList.contains('hide')) {
		allDropdown.forEach(item => {
			const a = item.parentElement.querySelector('a:first-child');
			a.classList.remove('subdrop');
			item.classList.remove('show');
		})
		allSideDivider.forEach(item => {
			item.textContent = '-'
		})
	}
})


sidebar.addEventListener('mouseenter', function () {
	if (this.classList.contains('hide')) {
		allDropdown.forEach(item => {
			const a = item.parentElement.querySelector('a:first-child');
			if (a.classList.contains('active')) {
				a.classList.toggle('subdrop');
				item.classList.toggle('show');
			} else {
				a.classList.remove('subdrop');
				item.classList.remove('show');
			}
		})
		allSideDivider.forEach(item => {
			item.textContent = item.dataset.text;
		})
	}
})


// PROFILE DROPDOWN
const profile = document.querySelector('.header .profile');
const imgProfile = profile.querySelector('img');
const dropdownProfile = profile.querySelector('.profile-link');

imgProfile.addEventListener('click', function () {
	dropdownProfile.classList.toggle('show');
})


function logout() {
  sessionStorage.removeItem("token");
	message.show({ type: 'success', text: "退出成功!" });
	// 登陆成功跳转
	let t=2;
	// 间隔性定时器
	setInterval(function(){
		if (t == 1) {
			window.location.href = 'landing.html';
		}
		t--;
	},1000);
	return;
}
