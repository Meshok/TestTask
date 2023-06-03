cmake_minimum_required(VERSION 3.12.0)

project(DailyPlanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(DailyPlanner
    main.cc
    daily_planner.cc
    date.cc
    date_time.cc
    full_name.cc
    event.cc
    birthday.cc
    daily_planner.h
    date.h
    date_time.h
    full_name.h
    event.h
    birthday.h
    bad_input.h
)
