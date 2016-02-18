#/***********************************************************************
# Copyright (c) 2013-2016 Flakor.org All Rights Reserved.
# Author: Steve Hsu (steve@kunkua.com,saint@aliyun.com)
# last edited: 2016-02-18
#************************************************************************

cmake_minimum_required(VERSION 2.8)

project(Flakor)
set(FLAKOR_VERSION 0.1.0alpha)

message(${BUILDING_STRING})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})




