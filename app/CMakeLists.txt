# SPDX-License-Identifier: Apache-2.0

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(DTC_OVERLAY_FILE "${PARENT_DIR}/boards/stm32f4_disco.overlay")
set(BOARD_ROOT "${PARENT_DIR}")
set(DTS_ROOT "${PARENT_DIR}")
# set(KCONFIG_ROOT ${PARENT_DIR})

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(button_capture)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_sources(app PRIVATE src/main.c)
