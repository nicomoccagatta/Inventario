# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nicomoccagatta/Inventario

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicomoccagatta/Inventario/build

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o: ../Servidor/server_BaseDeDatos.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o -c /home/nicomoccagatta/Inventario/Servidor/server_BaseDeDatos.cpp

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Servidor/server_BaseDeDatos.cpp > CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.i

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Servidor/server_BaseDeDatos.cpp -o CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.s

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.requires

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.provides: CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.provides

CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.provides.build: CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o: ../Servidor/server_Operador.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o -c /home/nicomoccagatta/Inventario/Servidor/server_Operador.cpp

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Servidor/server_Operador.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Servidor/server_Operador.cpp > CMakeFiles/Server.dir/Servidor/server_Operador.cpp.i

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Servidor/server_Operador.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Servidor/server_Operador.cpp -o CMakeFiles/Server.dir/Servidor/server_Operador.cpp.s

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.requires

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.provides: CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.provides

CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.provides.build: CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o: ../Servidor/server_Servidor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o -c /home/nicomoccagatta/Inventario/Servidor/server_Servidor.cpp

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Servidor/server_Servidor.cpp > CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.i

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Servidor/server_Servidor.cpp -o CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.s

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.requires

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.provides: CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.provides

CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.provides.build: CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o: ../Servidor/server_SocketServidor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o -c /home/nicomoccagatta/Inventario/Servidor/server_SocketServidor.cpp

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Servidor/server_SocketServidor.cpp > CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.i

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Servidor/server_SocketServidor.cpp -o CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.s

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.requires

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.provides: CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.provides

CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.provides.build: CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o

CMakeFiles/Server.dir/Servidor/Servidor.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Servidor/Servidor.cpp.o: ../Servidor/Servidor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Servidor/Servidor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Servidor/Servidor.cpp.o -c /home/nicomoccagatta/Inventario/Servidor/Servidor.cpp

CMakeFiles/Server.dir/Servidor/Servidor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Servidor/Servidor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Servidor/Servidor.cpp > CMakeFiles/Server.dir/Servidor/Servidor.cpp.i

CMakeFiles/Server.dir/Servidor/Servidor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Servidor/Servidor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Servidor/Servidor.cpp -o CMakeFiles/Server.dir/Servidor/Servidor.cpp.s

CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.requires

CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.provides: CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.provides

CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.provides.build: CMakeFiles/Server.dir/Servidor/Servidor.cpp.o

CMakeFiles/Server.dir/Common/client_Cliente.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/client_Cliente.cpp.o: ../Common/client_Cliente.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/client_Cliente.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/client_Cliente.cpp.o -c /home/nicomoccagatta/Inventario/Common/client_Cliente.cpp

CMakeFiles/Server.dir/Common/client_Cliente.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/client_Cliente.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/client_Cliente.cpp > CMakeFiles/Server.dir/Common/client_Cliente.cpp.i

CMakeFiles/Server.dir/Common/client_Cliente.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/client_Cliente.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/client_Cliente.cpp -o CMakeFiles/Server.dir/Common/client_Cliente.cpp.s

CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.requires

CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.provides: CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.provides

CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.provides.build: CMakeFiles/Server.dir/Common/client_Cliente.cpp.o

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o: ../Common/client_SocketCliente.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o -c /home/nicomoccagatta/Inventario/Common/client_SocketCliente.cpp

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/client_SocketCliente.cpp > CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.i

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/client_SocketCliente.cpp -o CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.s

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.requires

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.provides: CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.provides

CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.provides.build: CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o: ../Common/common_AreaDeVision.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_AreaDeVision.cpp

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_AreaDeVision.cpp > CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.i

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_AreaDeVision.cpp -o CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.s

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.requires

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.provides: CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.provides

CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o

CMakeFiles/Server.dir/Common/common_Mutex.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Mutex.cpp.o: ../Common/common_Mutex.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Mutex.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Mutex.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Mutex.cpp

CMakeFiles/Server.dir/Common/common_Mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Mutex.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Mutex.cpp > CMakeFiles/Server.dir/Common/common_Mutex.cpp.i

CMakeFiles/Server.dir/Common/common_Mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Mutex.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Mutex.cpp -o CMakeFiles/Server.dir/Common/common_Mutex.cpp.s

CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Mutex.cpp.o

CMakeFiles/Server.dir/Common/common_Producto.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Producto.cpp.o: ../Common/common_Producto.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Producto.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Producto.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Producto.cpp

CMakeFiles/Server.dir/Common/common_Producto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Producto.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Producto.cpp > CMakeFiles/Server.dir/Common/common_Producto.cpp.i

CMakeFiles/Server.dir/Common/common_Producto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Producto.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Producto.cpp -o CMakeFiles/Server.dir/Common/common_Producto.cpp.s

CMakeFiles/Server.dir/Common/common_Producto.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Producto.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Producto.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Producto.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Producto.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Producto.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Producto.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Producto.cpp.o

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o: ../Common/common_Protocolo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Protocolo.cpp

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Protocolo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Protocolo.cpp > CMakeFiles/Server.dir/Common/common_Protocolo.cpp.i

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Protocolo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Protocolo.cpp -o CMakeFiles/Server.dir/Common/common_Protocolo.cpp.s

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o

CMakeFiles/Server.dir/Common/common_Socket.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Socket.cpp.o: ../Common/common_Socket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Socket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Socket.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Socket.cpp

CMakeFiles/Server.dir/Common/common_Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Socket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Socket.cpp > CMakeFiles/Server.dir/Common/common_Socket.cpp.i

CMakeFiles/Server.dir/Common/common_Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Socket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Socket.cpp -o CMakeFiles/Server.dir/Common/common_Socket.cpp.s

CMakeFiles/Server.dir/Common/common_Socket.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Socket.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Socket.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Socket.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Socket.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Socket.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Socket.cpp.o

CMakeFiles/Server.dir/Common/common_Stock.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Stock.cpp.o: ../Common/common_Stock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Stock.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Stock.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Stock.cpp

CMakeFiles/Server.dir/Common/common_Stock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Stock.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Stock.cpp > CMakeFiles/Server.dir/Common/common_Stock.cpp.i

CMakeFiles/Server.dir/Common/common_Stock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Stock.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Stock.cpp -o CMakeFiles/Server.dir/Common/common_Stock.cpp.s

CMakeFiles/Server.dir/Common/common_Stock.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Stock.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Stock.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Stock.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Stock.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Stock.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Stock.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Stock.cpp.o

CMakeFiles/Server.dir/Common/common_Thread.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Common/common_Thread.cpp.o: ../Common/common_Thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nicomoccagatta/Inventario/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Server.dir/Common/common_Thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Common/common_Thread.cpp.o -c /home/nicomoccagatta/Inventario/Common/common_Thread.cpp

CMakeFiles/Server.dir/Common/common_Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Common/common_Thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nicomoccagatta/Inventario/Common/common_Thread.cpp > CMakeFiles/Server.dir/Common/common_Thread.cpp.i

CMakeFiles/Server.dir/Common/common_Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Common/common_Thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nicomoccagatta/Inventario/Common/common_Thread.cpp -o CMakeFiles/Server.dir/Common/common_Thread.cpp.s

CMakeFiles/Server.dir/Common/common_Thread.cpp.o.requires:
.PHONY : CMakeFiles/Server.dir/Common/common_Thread.cpp.o.requires

CMakeFiles/Server.dir/Common/common_Thread.cpp.o.provides: CMakeFiles/Server.dir/Common/common_Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/Common/common_Thread.cpp.o.provides.build
.PHONY : CMakeFiles/Server.dir/Common/common_Thread.cpp.o.provides

CMakeFiles/Server.dir/Common/common_Thread.cpp.o.provides.build: CMakeFiles/Server.dir/Common/common_Thread.cpp.o

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o" \
"CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o" \
"CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o" \
"CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o" \
"CMakeFiles/Server.dir/Servidor/Servidor.cpp.o" \
"CMakeFiles/Server.dir/Common/client_Cliente.cpp.o" \
"CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o" \
"CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Mutex.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Producto.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Socket.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Stock.cpp.o" \
"CMakeFiles/Server.dir/Common/common_Thread.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o
Server: CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o
Server: CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o
Server: CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o
Server: CMakeFiles/Server.dir/Servidor/Servidor.cpp.o
Server: CMakeFiles/Server.dir/Common/client_Cliente.cpp.o
Server: CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o
Server: CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Mutex.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Producto.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Socket.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Stock.cpp.o
Server: CMakeFiles/Server.dir/Common/common_Thread.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server
.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Servidor/server_BaseDeDatos.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Servidor/server_Operador.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Servidor/server_Servidor.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Servidor/server_SocketServidor.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Servidor/Servidor.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/client_Cliente.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/client_SocketCliente.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_AreaDeVision.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Mutex.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Producto.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Protocolo.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Socket.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Stock.cpp.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/Common/common_Thread.cpp.o.requires
.PHONY : CMakeFiles/Server.dir/requires

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/nicomoccagatta/Inventario/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nicomoccagatta/Inventario /home/nicomoccagatta/Inventario /home/nicomoccagatta/Inventario/build /home/nicomoccagatta/Inventario/build /home/nicomoccagatta/Inventario/build/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend

