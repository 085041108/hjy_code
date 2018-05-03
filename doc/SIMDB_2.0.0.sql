/*
MySQL - 2.0.0-log : Database - SIMDB
v2.0.0 初始版本 2016-10-16 zengyuan.xue
去掉用户表中的机构id
*********************************************************************
*/

CREATE DATABASE `SIMDB`;
USE `SIMDB`;


DROP TABLE IF EXISTS `school_info`;

CREATE TABLE `school_info` (
  `sch_id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(64) COLLATE utf8_unicode_ci  NOT NULL,
  `address` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `create_time` datetime  NULL,
  `president` varchar(64)  COLLATE utf8_unicode_ci DEFAULT NULL,
  `telephone` varchar(15) COLLATE utf8_unicode_ci DEFAULT NULL,
  `email` varchar(49) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`sch_id`),
  UNIQUE KEY `school_info_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `user_info`;

CREATE TABLE `user_info` (
  `user_id` bigint unsigned NOT NULL,
  `pwd` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL,
  `role_id` int unsigned  NULL,
  `create_time` datetime  NULL,
  `name` varchar(64) COLLATE utf8_unicode_ci  NULL,
  `nation` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL,
  `identity` varchar(32)  COLLATE utf8_unicode_ci DEFAULT NULL,
  `bir_time` datetime  NULL,
  `sex` int unsigned  NULL,
  `telephone` varchar(15) COLLATE utf8_unicode_ci DEFAULT NULL,
  `email` varchar(49) COLLATE utf8_unicode_ci DEFAULT NULL,
  `address` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_int3` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_str2` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_info_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE INDEX user_info_id ON user_info(user_id);


DROP TABLE IF EXISTS `course`;

CREATE TABLE `course` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `sch_id` bigint unsigned NOT NULL,
  `cour_id` int unsigned  NULL,
  `sub_cour_id` int unsigned  NULL,
  `cour_type` int unsigned  NULL,
  `start_time` datetime  NULL,
  `end_time` datetime  NULL,
  `cour_count` int unsigned  NULL,
  `create_time` datetime  NULL,
  `teacher_id` bigint unsigned NOT NULL,
  `name` varchar(256) COLLATE utf8_unicode_ci  NULL,
  `cour_leve` int unsigned  NULL,
  `remark` varchar(256) COLLATE utf8_unicode_ci  NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `course_uniqueid` (`cour_id`,`sub_cour_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE INDEX course_sch_tea_id ON course(sch_id,teacher_id);


DROP TABLE IF EXISTS `select_course`;

CREATE TABLE `select_course` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint unsigned NOT NULL,
  `sch_id` bigint unsigned NOT NULL,
  `teacher_id` bigint unsigned NOT NULL,
  `cour_id` bigint unsigned NOT NULL,
  `sub_cour_id` bigint unsigned NOT NULL,
  `create_time` datetime  NULL,
  `name` varchar(64) COLLATE utf8_unicode_ci DEFAULT NULL,
  `address` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `start_time` datetime  NULL,
  `end_time` datetime  NULL,
  `remark` varchar(256) COLLATE utf8_unicode_ci  NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_int3` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_str2` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `select_course_uniqueid` (`cour_id`,`sub_cour_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE INDEX select_course_sch_id ON select_course(sch_id);
CREATE INDEX select_course_teacher_id ON select_course(teacher_id);


DROP TABLE IF EXISTS `attend_course`;

CREATE TABLE `attend_course` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `sch_id` bigint unsigned NOT NULL,
  `user_id` bigint unsigned NOT NULL, 
  `cour_id` int unsigned NOT NULL,
  `sub_cour_id` int unsigned NOT NULL,
  `create_time` datetime  NULL,
  `get_score` float DEFAULT '0',
  `put_score` float DEFAULT '0',
  `if_attend` int unsigned  NULL,
  `feedback` varchar(512) COLLATE utf8_unicode_ci  NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_int3` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_str2` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `attend_course_uniqueid` (`user_id`,`cour_id`,`sub_cour_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE INDEX attend_course_user_id ON attend_course(user_id);

DROP TABLE IF EXISTS `teacher_sch`;

CREATE TABLE `teacher_sch` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `sch_id` bigint unsigned NOT NULL,
  `user_id` bigint unsigned NOT NULL, 
  `create_time` datetime  NULL,
  `ext_int1` int unsigned  NULL,
  `ext_int2` int unsigned  NULL,
  `ext_int3` int unsigned  NULL,
  `ext_str1` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ext_str2` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `teacher_sch_uniqueid` (`user_id`,`sch_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE INDEX teacher_sch_id ON teacher_sch(sch_id);
CREATE INDEX teacher_user_id ON teacher_sch(user_id);