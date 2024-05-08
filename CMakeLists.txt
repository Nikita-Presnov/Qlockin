cmake_minimum_required(VERSION 3.0)
project(Qlockin)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find libraryies
include(FindQwt.cmake)
find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(Qwt REQUIRED)



set(qlockin_SRC
  main.cpp
  lockin.cpp
  mainwindow.cpp
)

# Tell CMake to create the helloworld executable
add_executable(qlockin ${qlockin_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(qlockin Qt5::Widgets Qwt::Qwt)

# Install the executable
install(TARGETS qlockin DESTINATION bin)
