cmake_minimum_required (VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=gnu++98 -Wall -Werror -pedantic -pedantic-errors -g -O3 -DNDEBUG -ggdb -DDEBUG -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -ggdb -DDEBUG -fno-inline")
SET(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic -pedantic-errors") 

project("Control de Inventario")
#-------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Common")
include_directories("${PROJECT_SOURCE_DIR}/Common")
#-------------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Administrador")
include_directories("${PROJECT_SOURCE_DIR}/Administrador")
INCLUDE(FindPkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})  
include_directories(${GTKMM_INCLUDE_DIRS} ${GSTMM_INCLUDE_DIRS})
#add_executable(Admin
#			Administrador/Administrador.cpp
#		)
#TARGET_LINK_LIBRARIES(Admin pthread)
#link_directories(${GTKMM_LIBRARY_DIRS})  
#target_link_libraries(Admin ${GTKMM_LIBRARIES}) 
#INSTALL(FILES Admin DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Cliente")
include_directories("${PROJECT_SOURCE_DIR}/Cliente")
pkg_check_modules(OpenCV REQUIRED opencv)
include_directories(${OpenCV_INCLUDE_DIRS}) 
add_executable(Client
			Cliente/client_main.cpp
			Cliente/Modelo/client_ClienteDemo.cpp
			Cliente/Modelo/client_Data.cpp
			Cliente/Modelo/client_ModeloObservable.cpp
			Cliente/Vista/client_VistaEnviar.cpp
			Cliente/Vista/client_AreasDeVisionComboBoxModel.h
			Cliente/Control/client_ControladorVistaEnviar.cpp
			#Common/common_Cliente.cpp
			Common/common_SocketCliente.cpp
			Common/common_AreaDeVision.cpp
			Common/common_Mutex.cpp
			Common/common_Producto.cpp
			Common/common_Stock.cpp
			Common/common_Protocolo.cpp
			Common/common_Socket.cpp
			Common/common_Thread.cpp
			Common/common_CommandParser.cpp
			Common/common_Imagen.cpp
		)

FIND_PACKAGE(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(Client ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(Client pthread)
link_directories(${GTKMM_LIBRARY_DIRS})  
target_link_libraries(Client ${GTKMM_LIBRARIES})
target_link_libraries(Client ${OpenCV_LIBS})
INSTALL(FILES Client DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Servidor")
include_directories("${PROJECT_SOURCE_DIR}/Servidor")
add_executable(Server
			Servidor/server_BaseDeDatos.cpp
			Servidor/server_DetectorDeObjetos.cpp
			Servidor/server_Operador.cpp
			Servidor/server_Servidor.cpp
			Servidor/server_SocketServidor.cpp
			Servidor/Servidor.cpp
			Common/client_Cliente.cpp
			Common/common_SocketCliente.cpp
			Common/common_AreaDeVision.cpp
			Common/common_Mutex.cpp
			Common/common_Producto.cpp
			Common/common_Protocolo.cpp
			Common/common_Socket.cpp
			Common/common_Stock.cpp
			Common/common_Thread.cpp
			Common/common_Imagen.cpp
			)
TARGET_LINK_LIBRARIES(Server tinyxml)
TARGET_LINK_LIBRARIES(Server pthread)
target_link_libraries(Server ${OpenCV_LIBS})
INSTALL(FILES Server DESTINATION ${PROJECT_SOURCE_DIR})
#-------------------------------------------------------------------------------

