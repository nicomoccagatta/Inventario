cmake_minimum_required (VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=gnu++98 -Wall -Werror -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -ggdb -DDEBUG -fno-inline")
SET(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic -pedantic-errors") 

project("Control de Inventario")
#-------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Common")
include_directories("${PROJECT_SOURCE_DIR}/Common")
#-------------------------------------------------------------------------------
#ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Administrador")
#include_directories("${PROJECT_SOURCE_DIR}/Administrador")
#add_executable(Admin
#			Administrador/
#			Common/
#		)
#TARGET_LINK_LIBRARIES(Admin m)
#TARGET_LINK_LIBRARIES(Admin pthread)
#INSTALL(FILES Admin DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------
#ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Cliente")
#include_directories("${PROJECT_SOURCE_DIR}/Cliente")
#add_executable(Client
#			Cliente/main.c
#			Common/
#		)
#TARGET_LINK_LIBRARIES(Client m)
#TARGET_LINK_LIBRARIES(Client pthread)
#INSTALL(FILES Client DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Servidor")
include_directories("${PROJECT_SOURCE_DIR}/Servidor")
add_executable(Server
			Servidor/server_BaseDeDatos.cpp
			Servidor/server_Operador.cpp
			Servidor/server_Servidor.cpp
			Servidor/server_SocketServidor.cpp
			Servidor/Servidor.cpp
			Common/client_Cliente.cpp
			Common/client_SocketCliente.cpp
			Common/common_AreaDeVision.cpp
			Common/common_Mutex.cpp
			Common/common_Producto.cpp
			Common/common_Protocolo.cpp
			Common/common_Socket.cpp
			Common/common_Stock.cpp
			Common/common_Thread.cpp
			)
TARGET_LINK_LIBRARIES(Server tinyxml)
TARGET_LINK_LIBRARIES(Server pthread)
INSTALL(FILES Server DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------

