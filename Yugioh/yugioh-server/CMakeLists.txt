cmake_minimum_required(VERSION 3.16)

project(Yugioh-Server VERSION 1.0 LANGUAGES CXX)

# Set INCLUDE_CURRENT_DIR to ON so it can find the files easier:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Automatically solve qt's vtable and moc errors:
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Network Widgets)

# Sources
set(SourcesPath "${CMAKE_CURRENT_SOURCE_DIR}/sources")
set(Sources
  "${SourcesPath}/main.cpp"
  "${SourcesPath}/MyTcpServer.cpp"
)

# Headers
set(HeadersPath "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(Headers
  "${HeadersPath}/MyTcpServer.h"
)

add_executable(Yugioh-Server ${Sources} ${Headers})

target_link_libraries(Yugioh-Server
  Qt::Core
  Qt::Gui
  Qt::Network
  Qt::Widgets
)
