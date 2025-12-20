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
        src/networking/discovery/infrastructure/DiscoveryBroadcaster.cpp
        src/networking/discovery/infrastructure/DiscoveryBroadcaster.h
        src/app/ServerController.cpp
        src/app/ServerController.h
        src/networking/discovery/infrastructure/DiscoveryPacket.h
        src/networking/discovery/ports/IDiscoveryListener.h
        src/networking/discovery/infrastructure/UdpDiscoveryListener.cpp
        src/networking/discovery/infrastructure/UdpDiscoveryListener.h
        src/networking/discovery/domain/DiscoveredServer.h
        src/networking/discovery/domain/DiscoveredServerRegistry.cpp
        src/networking/discovery/domain/DiscoveredServerRegistry.h
        src/networking/session/messaging/domain/StateSnapshot.h
        src/networking/session/messaging/domain/ProtocolMessage.h
        src/networking/session/messaging/infrastructure/JsonSerializer.h
        src/networking/session/transport/TcpSession.cpp
        src/networking/session/transport/TcpSession.h
        src/networking/session/transport/TcpServer.cpp
        src/networking/session/transport/TcpServer.h
        src/networking/session/messaging/domain/ProtocolMessageType.h
        src/networking/session/domain/SessionState.h
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
