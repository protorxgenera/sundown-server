cmake_minimum_required(VERSION 4.0)
project(sundown_server)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED)

add_executable(sundown_server
        src/main.cpp

        src/domain/ShutdownScheduler.cpp
        src/domain/ShutdownScheduler.h

        src/infrastructure/WindowsShutdownExecutor.cpp
        src/infrastructure/WindowsShutdownExecutor.h

        src/domain/IShutdownExecutor.h

        src/app/Controller.cpp
        src/app/Controller.h
        src/domain/ShutdownState.cpp
        src/domain/ShutdownState.h
        src/domain/IShutdownStateRepository.h
)

target_link_libraries(sundown_server
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_executable(ControllerTests
        src/tests/controller/ControllerTest.cpp

        src/infrastructure/TestShutdownExecutor.cpp
        src/infrastructure/TestShutdownExecutor.h

        src/app/Controller.cpp
        src/domain/ShutdownScheduler.cpp
)

target_link_libraries(ControllerTests
        Qt::Core
        Qt::Test
)

if(MINGW)
    target_link_options(ControllerTests PRIVATE -Wl,--subsystem,console)
endif()

add_test(
        NAME ControllerTests
        COMMAND ControllerTests
)

if (WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt
            HINTS "${CMAKE_PREFIX_PATH}/bin")

    add_custom_command(TARGET sundown_server POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE:sundown_server>"
    )

    add_custom_command(TARGET ControllerTests POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE:ControllerTests>"
    )
endif ()
