DROP TABLE IF EXISTS `books`;
CREATE TABLE `books` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `isbn` varchar(100) DEFAULT '' COMMENT '书籍isbn',
	`name` varchar(250) DEFAULT '' COMMENT '书籍名称',
  `author` varchar(100) DEFAULT '' COMMENT '书籍作者',
	`description` varchar(250) DEFAULT '' COMMENT '书籍介绍',
	`file` varchar(250) DEFAULT '' COMMENT '书籍文件',
  `image` varchar(250) DEFAULT '' COMMENT '书籍照片',
 `type` tinyint NOT NULL DEFAULT '0' COMMENT '书籍类型[1青春2小说3文学4艺术]',
	`feedback` varchar(250) DEFAULT '' COMMENT '书籍管理员反馈审核意见',
	`status` tinyint(4) NOT NULL COMMENT '书籍状态[1未提交2待审核3已通过4被退回]',
	`createrName` varchar(100) DEFAULT '' COMMENT '创建人姓名',
	`createrPhone` varchar(100) DEFAULT '' COMMENT '创建人电话',
	`createrAddress` varchar(100) DEFAULT '' COMMENT '创建人地址',
	`createrUserId` int(11) NOT NULL COMMENT '创建人用户id',
	`createrFeedback` varchar(250) DEFAULT '' COMMENT '创建人反馈意见',
  `created_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '数据修改时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_isbn` (`isbn`) USING BTREE,
  KEY `index_author` (`author`) USING BTREE,
	KEY `index_name` (`name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='书籍';
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `pwd` varchar(100) DEFAULT '' COMMENT '用户密码',
  `name` varchar(100) DEFAULT '' COMMENT '用户名称',
  `email` varchar(250) DEFAULT '' COMMENT '用户邮箱',
   `image` varchar(255) DEFAULT '' COMMENT '头像地址',
    `address` varchar(255) DEFAULT '' COMMENT '住址',
    `phone` varchar(255) DEFAULT '' COMMENT '手机号',
  `status` tinyint NOT NULL DEFAULT '1' COMMENT '0为挂失,1为正常',
  `admin` tinyint NOT NULL DEFAULT '0' COMMENT '0为普通用户,1为管理员',
  `created_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '数据修改时间',
  PRIMARY KEY (`id`) USING BTREE,
	UNIQUE KEY `index_name` (`name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户';
