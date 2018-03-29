cmake_minimum_required(VERSION 3.8)
project(PTZcmd)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


include_directories(include)

link_directories(lib)
link_directories(lib/HCNetSDKCom)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(PTZcmd   main.cpp  Player.cpp Player.h Setting.cpp Setting.h Control.cpp Control.h)

# Use the Widgets module from Qt 5.
target_link_libraries(PTZcmd Qt5::Widgets
        AudioRender
        HCCore
        hcnetsdk
        hpr
        PlayCtrl
        SuperRender

        analyzedata
        HCAlarm
        HCCoreDevCfg
        HCDisplay
        HCGeneralCfgMgr
        HCIndustry
        HCPlayBack
        HCPreview
        HCVoiceTalk
        iconv2
        StreamTransClient
        SystemTransform
        )