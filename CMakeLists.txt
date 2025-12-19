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
        Network
        Widgets
        Test
        REQUIRED)

add_executable(sundown_server
        src/main.cpp

        src/shutdown/domain/ShutdownScheduler.cpp
        src/shutdown/domain/ShutdownScheduler.h

        src/shutdown/infrastructure/WindowsShutdownExecutor.cpp
        src/shutdown/infrastructure/WindowsShutdownExecutor.h

        src/shutdown/ports/IShutdownExecutor.h

        src/app/Controller.cpp
        src/app/Controller.h
        src/shutdown/domain/ShutdownState.h
        src/shutdown/ports/IShutdownStateRepository.h
        src/shutdown/infrastructure/InMemoryShutdownStateRepository.h
        src/shutdown/infrastructure/FileShutdownStateRepository.cpp
        src/shutdown/infrastructure/FileShutdownStateRepository.h
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/discovery/infrastructure/DiscoveryBroadcaster.cpp
        src/discovery/infrastructure/DiscoveryBroadcaster.h
        src/app/ServerController.cpp
        src/app/ServerController.h
        src/discovery/infrastructure/DiscoveryPacket.h
        src/discovery/ports/IDiscoveryListener.h
        src/discovery/infrastructure/UdpDiscoveryListener.cpp
        src/discovery/infrastructure/UdpDiscoveryListener.h
        src/discovery/domain/DiscoveredServer.h
        src/discovery/domain/DiscoveredServerRegistry.cpp
        src/discovery/domain/DiscoveredServerRegistry.h
)

target_link_libraries(sundown_server
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::Widgets
)

add_executable(ControllerTests
        src/tests/controller/ControllerTest.cpp

        src/shutdown/tests/TestShutdownExecutor.cpp
        src/shutdown/tests/TestShutdownExecutor.h

        src/app/Controller.cpp
        src/shutdown/domain/ShutdownScheduler.cpp
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
