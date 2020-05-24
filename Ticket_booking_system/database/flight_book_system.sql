/*
Navicat MySQL Data Transfer

Source Server         : guanggao_db
Source Server Version : 50556
Source Host           : localhost:3306
Source Database       : flight_book_system

Target Server Type    : MYSQL
Target Server Version : 50556
File Encoding         : 65001

Date: 2020-05-24 18:03:02
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
  `e_name` varchar(255) DEFAULT NULL,
  `e_flight_num` varchar(255) DEFAULT NULL,
  `e_flight_seat` varchar(255) DEFAULT NULL,
  `e_flight_price` double(255,0) DEFAULT NULL,
  `e_oil_price` double(255,0) DEFAULT NULL,
  `e_other_price` double(255,0) DEFAULT NULL,
  `e_count_price` double(255,0) DEFAULT NULL,
  PRIMARY KEY (`e_ticket_num`),
  KEY `电子客票_交易订单_航班号` (`e_flight_num`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of ele_ticket
-- ----------------------------

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
INSERT INTO `flight_info` VALUES ('GZ-SZ123', '120', '2020-05-26', '2020-05-26', '09:11:58', '320', '波音747', null, '广州', '深圳');
INSERT INTO `flight_info` VALUES ('SH-GZ123', '720', '2020-05-26', '2020-05-27', '16:02:01', '1352', '波音777', null, '上海', '广州');
INSERT INTO `flight_info` VALUES ('SZ-GZ123', '132', '2020-05-28', '2020-05-29', '20:12:04', '325', '波音777', null, '深圳', '广州');

-- ----------------------------
-- Table structure for order_info
-- ----------------------------
DROP TABLE IF EXISTS `order_info`;
CREATE TABLE `order_info` (
  `order_num` varchar(255) NOT NULL,
  `order_flight_num` varchar(255) DEFAULT NULL,
  `order_u_tel` varchar(11) NOT NULL,
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
INSERT INTO `order_info` VALUES ('12320200524170101', 'SH-GZ123', '123', 'tuto', '未支付', '2020-05-26', '16:02:01', '上海', '广州', '1352', '17:01:01', null);
INSERT INTO `order_info` VALUES ('12320200524172710', 'SH-GZ123', '123', 'tuto', '未支付', '2020-05-26', '16:02:01', '上海', '广州', '1352', '17:27:10', null);
INSERT INTO `order_info` VALUES ('12320200524173138', 'GZ-SZ123', '123', 'tuto', '未支付', '2020-05-26', '09:11:58', '广州', '深圳', '320', '17:31:38', null);
INSERT INTO `order_info` VALUES ('12320200524180159', 'GZ-SZ123', '123', 'tuto', '未支付', '2020-05-26', '09:11:58', '广州', '深圳', '320', '18:01:59', null);
INSERT INTO `order_info` VALUES ('12320200524180212', 'GZ-SZ123', '123', 'tuto', '未支付', '2020-05-26', '09:11:58', '广州', '深圳', '320', '18:02:12', null);

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
  `u_tel` varchar(11) NOT NULL,
  `u_pwd` varchar(255) NOT NULL,
  PRIMARY KEY (`u_tel`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of user_info
-- ----------------------------
INSERT INTO `user_info` VALUES ('李富', '789', '1', '1');
INSERT INTO `user_info` VALUES ('??', '8845456561', '110', '110');
INSERT INTO `user_info` VALUES ('111', '111', '111', '111');
INSERT INTO `user_info` VALUES ('tuto', '441524188832456518', '123', '123');
INSERT INTO `user_info` VALUES ('tuto123', '441545987899889', '1314', '1314');
INSERT INTO `user_info` VALUES ('123', '123', '134', '123');
