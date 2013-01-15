# Install script for directory: J:/Projet Infographie/Moteur3D/AgmdEngine/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/AGMDENGINE")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/AgmdMaths/cmake_install.cmake")
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/AgmdNetwork/cmake_install.cmake")
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/AgmdUtilities/cmake_install.cmake")
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/Agmd3D/cmake_install.cmake")
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/Renderer/OpenGL/cmake_install.cmake")
  INCLUDE("J:/Projet Infographie/Moteur3D/AgmdEngine/test/src/Demo/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

