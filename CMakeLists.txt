cmake_minimum_required (VERSION 3.0)
project (EjerciciosGraficas)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

add_subdirectory(external)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
  external/AntTweakBar-1.16/include/
  external/glfw-3.1.2/include/
  external/glm-0.9.7.1/
  external/glew-1.13.0/include/
  external/assimp-3.0.1270/include/
  external/bullet-2.81-rev2613/src/
  common/
  .
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  glfw
  GLEW_1130
  ${GLUT_LIBRARIES}
)

add_definitions(
  -DTW_STATIC
  -DTW_NO_LIB_PRAGMA
  -DTW_NO_DIRECT3D
  -DGLEW_STATIC
  -D_CRT_SECURE_NO_WARNINGS
)

cmake_policy(SET CMP0072 OLD)

add_subdirectory(common)

###############################################################################
# EJERCICIO 1
add_executable(ejercicio01
  e01/ejercicio01.cpp
  common/shader.cpp
  common/shader.hpp
  )
target_link_libraries(ejercicio01
    ${ALL_LIBS}
)

target_include_directories(ejercicio01 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/common"
  )

add_custom_command(
   TARGET ejercicio01 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/ejercicio01${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/e01/"
)
###############################################################################
# EJERCICIO 2
add_executable(ejercicio02
  e02/ejercicio02.cpp
  common/shader.cpp
  common/shader.hpp
  )
target_link_libraries(ejercicio02
    ${ALL_LIBS}
)

target_include_directories(ejercicio02 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/common"
  )

add_custom_command(
   TARGET ejercicio02 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/ejercicio02${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/e02/"
)
###############################################################################
# EJERCICIO 3
add_executable(ejercicio03
  e03/ejercicio03.cpp
  common/shader.cpp
  common/shader.hpp
  )
target_link_libraries(ejercicio03
    ${ALL_LIBS}
)

target_include_directories(ejercicio03 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/common"
  )

add_custom_command(
   TARGET ejercicio03 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/ejercicio03${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/e03/"
)
###############################################################################
# EJERCICIO 4
add_executable(ejercicio04
  e04/ejercicio04.cpp
  common/shader.cpp
  common/shader.hpp
  )
target_link_libraries(ejercicio04
    ${ALL_LIBS}
)

target_include_directories(ejercicio04 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/common"
  )

add_custom_command(
   TARGET ejercicio04 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/ejercicio04${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/e04/"
)
###############################################################################
# EJERCICIO 5
add_executable(ejercicio05
  e05/ejercicio05.cpp
  common/shader.cpp
  common/shader.hpp
  )
target_link_libraries(ejercicio05
    ${ALL_LIBS}
)

target_include_directories(ejercicio05 PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/common"
  )

add_custom_command(
   TARGET ejercicio05 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/ejercicio05${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/e05/"
)
