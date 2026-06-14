option (CPPLogger_SHARED "Build shared library" OFF)

if (CPPLogger_SHARED)
  add_library (CPPLogger SHARED)
else()
  add_library (CPPLogger STATIC)
endif()

target_sources(CPPLogger 
  PRIVATE
    src/StringHelp.cpp src/Logger.cpp src/LoggerScope.cpp)
target_include_directories(CPPLogger 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPPLogger PROPERTY CXX_STANDARD 20)
endif()
