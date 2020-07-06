/*
Navicat MySQL Data Transfer

Source Server         : guanggao_db
Source Server Version : 50556
Source Host           : localhost:3306
Source Database       : flight_book_system

Target Server Type    : MYSQL
Target Server Version : 50556
File Encoding         : 65001

Date: 2020-06-11 10:06:55
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for aim_info
-- ----------------------------
DROP TABLE IF EXISTS `aim_info`;
CREATE TABLE `aim_info` (
  `aim_id` int(11) NOT NULL,
  `aim_pwd` varchar(255) NOT NULL,
  PRIMARY KEY (`aim_id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of aim_info
-- ----------------------------
INSERT INTO `aim_info` VALUES ('111', '111');
INSERT INTO `aim_info` VALUES ('123', '123');

-- ----------------------------
-- Table structure for ele_ticket
-- ----------------------------
DROP TABLE IF EXISTS `ele_ticket`;
CREATE TABLE `ele_ticket` (
  `e_ticket_num` varchar(255) NOT NULL,
  `e_order_num` varchar(255) DEFAULT NULL,
  `e_ticket_u_name` varchar(255) DEFAULT NULL,
  `e_flight_num` varchar(255) DEFAULT NULL,
  `e_filght_to_city` varchar(255) DEFAULT NULL,
  `e_flight_ar_city` varchar(255) DEFAULT NULL,
  `e_flight_date` varchar(255) DEFAULT NULL,
  `e_flight_to_time` varchar(255) DEFAULT NULL,
  `e_flight_price` varchar(255) DEFAULT '',
  PRIMARY KEY (`e_ticket_num`),
  KEY `电子客票_交易订单_航班号` (`e_flight_num`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of ele_ticket
-- ----------------------------
INSERT INTO `ele_ticket` VALUES ('GZ-BJ12320200527201049', '12320200527200519', 'tuto', 'GZ-BJ123', '广州', '北京', '2020-05-29', '16:11:52', '1300');
INSERT INTO `ele_ticket` VALUES ('GZ-BJ12320200527201717', '12320200527200909', 'tuto', 'GZ-BJ123', '广州', '北京', '2020-05-29', '16:11:52', '1300');
INSERT INTO `ele_ticket` VALUES ('GZ-BJ12320200527211706', '12320200527211700', 'tuto1', 'GZ-BJ123', '广州', '北京', '2020-05-29', '16:11:52', '1300');
INSERT INTO `ele_ticket` VALUES ('GZ-SZ12320200527171911', '13302420200527171900', '李军', 'GZ-SZ123', '广州', '深圳', '2020-05-26', '09:11:58', '320');

-- ----------------------------
-- Table structure for flight_com_info
-- ----------------------------
DROP TABLE IF EXISTS `flight_com_info`;
CREATE TABLE `flight_com_info` (
  `f_com_num` varchar(255) NOT NULL,
  `f_com_name` varchar(255) NOT NULL,
  `f_com_addr` varchar(255) DEFAULT NULL,
  `f_com_tel` int(11) DEFAULT NULL,
  PRIMARY KEY (`f_com_num`,`f_com_name`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of flight_com_info
-- ----------------------------

-- ----------------------------
-- Table structure for flight_info
-- ----------------------------
DROP TABLE IF EXISTS `flight_info`;
CREATE TABLE `flight_info` (
  `f_num` varchar(255) NOT NULL,
  `f_price` varchar(255) NOT NULL,
  `f_to_date` date NOT NULL,
  `f_ar_date` date NOT NULL,
  `f_to_time` time NOT NULL,
  `f_dis` double(255,0) NOT NULL,
  `f_type` varchar(255) NOT NULL,
  `f_cro_city` varchar(255) DEFAULT NULL,
  `f_take_city` varchar(255) NOT NULL,
  `f_ar_city` varchar(255) NOT NULL,
  PRIMARY KEY (`f_num`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of flight_info
-- ----------------------------
INSERT INTO `flight_info` VALUES ('BJ-GZ123', '352', '2020-05-23', '2020-05-24', '09:11:49', '1331', '波音777', '福建', '北京', '广州');
INSERT INTO `flight_info` VALUES ('GZ-BJ123', '253', '2020-05-29', '2020-05-30', '16:11:52', '1300', '波音747', '济南', '广州', '北京');
INSERT INTO `flight_info` VALUES ('GZ-SH123', '654', '2020-05-29', '2020-05-29', '11:59:09', '1300', '波音747', '黄山', '广州', '上海');
INSERT INTO `flight_info` VALUES ('GZ-SZ123', '120', '2020-05-26', '2020-05-26', '09:11:58', '320', '波音747', '', '广州', '深圳');
INSERT INTO `flight_info` VALUES ('SZ-GZ123', '132', '2020-05-28', '2020-05-29', '20:12:04', '325', '波音777', null, '深圳', '广州');

-- ----------------------------
-- Table structure for order_info
-- ----------------------------
DROP TABLE IF EXISTS `order_info`;
CREATE TABLE `order_info` (
  `order_num` varchar(255) NOT NULL,
  `order_flight_num` varchar(255) DEFAULT NULL,
  `order_u_tel` varchar(255) NOT NULL,
  `order_u_name` varchar(255) DEFAULT NULL,
  `order_pay_state` varchar(255) NOT NULL,
  `order_flight_date` varchar(255) DEFAULT NULL,
  `order_flight_time` varchar(255) DEFAULT NULL,
  `order_flight_to_city` varchar(255) DEFAULT NULL,
  `order_flight_ar_city` varchar(255) DEFAULT NULL,
  `order_flight_price` varchar(255) DEFAULT NULL,
  `order_time` varchar(255) DEFAULT NULL,
  `order_pay_time` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`order_num`),
  KEY `航班号` (`order_flight_num`),
  KEY `交易订单_旅客信息_手机号码` (`order_u_tel`),
  KEY `交易订单_旅客信息_姓名` (`order_u_name`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of order_info
-- ----------------------------
INSERT INTO `order_info` VALUES ('12320200527200519', 'GZ-BJ123', '123', 'tuto', '已支付', '2020-05-29', '16:11:52', '广州', '北京', '1200', '20:05:19', '20:10:49');
INSERT INTO `order_info` VALUES ('12320200527200909', 'GZ-BJ123', '123', 'tuto', '已支付', '2020-05-29', '16:11:52', '广州', '北京', '1300', '20:09:09', '20:17:17');
INSERT INTO `order_info` VALUES ('12320200527211700', 'GZ-BJ123', '123', 'tuto1', '已支付', '2020-05-29', '16:11:52', '广州', '北京', '1300', '21:17:00', '21:17:06');
INSERT INTO `order_info` VALUES ('12320200528100404', 'GZ-BJ123', '123', 'tuto1', '未支付', '2020-05-29', '16:11:52', '广州', '北京', '1300', '10:04:04', null);

-- ----------------------------
-- Table structure for ticket_info
-- ----------------------------
DROP TABLE IF EXISTS `ticket_info`;
CREATE TABLE `ticket_info` (
  `flight_num` varchar(255) NOT NULL,
  `flight_to_city` varchar(255) NOT NULL,
  `flight_ar_city` varchar(255) NOT NULL,
  `flight_dis` varchar(255) NOT NULL,
  `flight_to_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `flight_ar_time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `flight_type` varchar(255) NOT NULL,
  `flight_seat` varchar(255) NOT NULL,
  `flight_decount` float(255,0) DEFAULT NULL,
  PRIMARY KEY (`flight_num`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of ticket_info
-- ----------------------------

-- ----------------------------
-- Table structure for user_info
-- ----------------------------
DROP TABLE IF EXISTS `user_info`;
CREATE TABLE `user_info` (
  `u_name` varchar(255) CHARACTER SET utf8 NOT NULL,
  `u_IDCard` varchar(255) NOT NULL,
  `u_tel` varchar(255) NOT NULL,
  `u_pwd` varchar(255) NOT NULL,
  PRIMARY KEY (`u_tel`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of user_info
-- ----------------------------
INSERT INTO `user_info` VALUES ('??', '8845456561', '110', '110');
INSERT INTO `user_info` VALUES ('111', '111', '111', '111');
INSERT INTO `user_info` VALUES ('tuto1', '441524188832456518', '123', '123');
INSERT INTO `user_info` VALUES ('tuto123', '441545987899889', '1314', '1314');
INSERT INTO `user_info` VALUES ('李军', '12345465487', '133024', '123');
INSERT INTO `user_info` VALUES ('123', '123', '134', '123');
