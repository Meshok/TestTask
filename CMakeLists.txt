cmake_minimum_required(VERSION 3.12.0)

project(DailyPlanner)

set(CMAKE_CXX_STANDARD 17)

set(PATH_SRC src)

add_executable(DailyPlanner
    ${PATH_SRC}/main.cc
    ${PATH_SRC}/daily_planner.cc
    ${PATH_SRC}/date.cc
    ${PATH_SRC}/date_time.cc
    ${PATH_SRC}/full_name.cc
    ${PATH_SRC}/event.cc
    ${PATH_SRC}/birthday.cc
    ${PATH_SRC}/hash.cc
    ${PATH_SRC}/daily_planner.h
    ${PATH_SRC}/date.h
    ${PATH_SRC}/date_time.h
    ${PATH_SRC}/full_name.h
    ${PATH_SRC}/event.h
    ${PATH_SRC}/birthday.h
    ${PATH_SRC}/hash.h
    ${PATH_SRC}/bad_input.h
    ${PATH_SRC}/serialize.h
    ${PATH_SRC}/deserialize.h
)
