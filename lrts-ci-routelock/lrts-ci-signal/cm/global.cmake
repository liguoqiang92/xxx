# This file is the most important basic file for framework
# You can set -DLINT=True to support add_pc_lint functions

# to include path
FUNCTION (INC_PATH root post)
	include_directories(${root}/${post})
ENDFUNCTION()

# get build infomation from vars
FUNCTION(get_buildinfo)
	set(fver ${CMAKE_C_COMPILER_VERSION}".1.0")
	string(REGEX MATCHALL "[0-9]+"
		verinfo ${fver})
	list(GET verinfo 0 MAJOR)
	list(GET verinfo 1 MINOR)
	set(_UNIFW_COMPILER ${CMAKE_C_COMPILER_ID}${MAJOR}.${MINOR} CACHE INTERNAL "AUTO compiler info")
	set(_UNIFW_AUTOBUILDINFO 
		${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_C_COMPILER_ID}${MAJOR}.${MINOR}
		CACHE INTERNAL "AUTO build info")
ENDFUNCTION()

# set compiler flags
if (NOT _UNIFW_INIT)
	# run once
	if (MSVC)
		# 4013 to prevent error
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /we4013" CACHE INTERNAL "extra CFLAGS")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /we4013" CACHE INTERNAL "extra CXXFLAGS")
	elseif (${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
		message(STATUS "**Find gcc compiler")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" CACHE INTERNAL "CXX flags")
	elseif(UNIX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" CACHE INTERNAL "CXX flags")
	endif()
	get_buildinfo()
	set(_UNIFW_INIT true  CACHE INTERNAL "set initial flag")
endif()

if (NOT _GLOBAL_H)
	add_custom_target(update_buildinfo
		echo "==Detecting build env..."
		COMMAND echo "==" ${_UNIFW_AUTOBUILDINFO}
		COMMAND echo ${_UNIFW_AUTOBUILDINFO} > ${PROJECT_SOURCE_DIR}/smvn-build-info
		)
	set(_GLOBAL_H true)
endif()

if (WIN32)
	set(OSLIB "ws2_32" "winmm"
		CACHE INTERNAL "os support libs")
elseif(UNIX)
	set(OSLIB "pthread" "m"
		CACHE INTERNAL "os support libs")
endif()
set(UNITLIB "unitframe" "cppunit" CACHE INTERNAL "unit test libs")

# check buildinfo: 
#	- if buildinfo change by extern, unset _UNIFW_GPATH flag to reset vars
#   - if buildinfo unchange, do nothing
#	- if buildinfo not set, init it
FUNCTION(check_buildinfo)
	if(EXISTS ${CMAKE_SOURCE_DIR}/smvn-build-info)
		file(READ ${CMAKE_SOURCE_DIR}/smvn-build-info line)
		string(STRIP ${line} info)
		if(_UNIFW_BUILDINFO STREQUAL info)
			# if equal, do nothing
		else()
			message(STATUS "setting buildinfo " ${info})
			set(_UNIFW_GPATH false CACHE INTERNAL "smvn build info change to reset")
			set(_UNIFW_BUILDINFO ${info} CACHE INTERNAL "formal build info from file")
		endif()
	else()
		get_buildinfo()
		file(WRITE ${CMAKE_SOURCE_DIR}/smvn-build-info ${_UNIFW_AUTOBUILDINFO})
		set(_UNIFW_BUILDINFO ${_UNIFW_AUTOBUILDINFO} CACHE INTERNAL "formal build info from auto")
	endif()
ENDFUNCTION(check_buildinfo)

# determine exact ARCH name:
# PRIORITY: cross-win, win, linux
FUNCTION(update_arch)
	if (NOT _UNIFW_COMPILER)
		get_buildinfo()
	endif()

	# If _UNIFW_CROSS set, use it as include/arch/dir name
	# else use win32 or linux
	if (_UNIFW_CROSS)
		set(T_UNIFW_ARCH_NAME ${_UNIFW_CROSS})
	elseif(WIN32)
		set(T_UNIFW_ARCH_NAME "win32")
	elseif (UNIX)
		set(T_UNIFW_ARCH_NAME "linux")
	endif()
	set(_UNIFW_ARCH_NAME ${T_UNIFW_ARCH_NAME} CACHE INTERNAL "archname")
ENDFUNCTION(update_arch)

# Set global path, and add pub definition
FUNCTION(GET_GPATH root)
	check_buildinfo()
	if (NOT _UNIFW_GPATH)
		update_arch()
		set(USER_LIB_OUTPUT ${root}/lib/${_UNIFW_BUILDINFO} CACHE INTERNAL libpath)
		set(LIBRARY_OUTPUT_PATH ${USER_LIB_OUTPUT} CACHE INTERNAL userlib)
		set(EXECUTABLE_OUTPUT_PATH ${root}/bin/${CMAKE_SYSTEM_PROCESSOR}-${_UNIFW_COMPILER} CACHE INTERNAL "binpath first")
		set(_UNIFW_GPATH true CACHE INTERNAL "set Global path")
	endif()

	if (MSVC)
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	endif(MSVC)

	INC_PATH(${root} "include/arch/${_UNIFW_ARCH_NAME}")
	INC_PATH(${root} "include")

	# when using _UNIFW_S12X the format of link_libraries are different, do not add any link path using -L
	if (NOT _UNIFW_S12X)
		link_directories(${USER_LIB_OUTPUT})
	endif()

	message(STATUS "Project : " ${CMAKE_PROJECT_NAME} " @ARCH: " ${_UNIFW_AUTOBUILDINFO})
	message(STATUS "RootPath: " ${root} " bin: " ${EXECUTABLE_OUTPUT_PATH})
	message(STATUS "Buildinfo: "  ${_UNIFW_BUILDINFO})
	message(STATUS "Arch path: " "include/arch/${_UNIFW_ARCH_NAME}")
	message(STATUS "Lib path: " ${USER_LIB_OUTPUT})
	message(STATUS "C FLAGS : " ${CMAKE_C_FLAGS})
ENDFUNCTION(GET_GPATH)

FUNCTION(GET_LIB_PATH LIBPATH LIBNAME)
	find_library(${LIBPATH} ${LIBNAME} PATHS ${LIBRARY_OUTPUT_PATH} ${LIBRARY_OUTPUT_PATH}/Debug NO_DEFAULT_PATH)
ENDFUNCTION(GET_LIB_PATH)

# set use folder in Visual Studio IDEs
FUNCTION(SET_USE_FOLDER)
	if (WIN32 AND MSVC)
		# Provide a way for Visual Studio Express users to turn OFF the new FOLDER
		# organization feature. Default to ON for non-Express users. Express users must
		# explicitly turn off this option to build CMake in the Express IDE...
		OPTION(CMAKE_USE_FOLDERS "Enable folder grouping of projects in IDEs." ON)
		MARK_AS_ADVANCED(CMAKE_USE_FOLDERS)
	endif()
ENDFUNCTION()

# a macro that only sets the FOLDER target property if it's
# "appropriate"
MACRO(CMAKE_SET_TARGET_FOLDER tgt folder)
	IF(CMAKE_USE_FOLDERS)
		SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

		# Really, I just want this to be an "if(TARGET ${tgt})" ...
		# but I'm not sure that our min req'd., CMake 2.4.5 can handle
		# that... so I'm just activating this for now, with a version
		# compare, and only for MSVC builds.
		IF(MSVC)
			IF(NOT ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 2.8)
				SET_PROPERTY(TARGET "${tgt}" PROPERTY FOLDER "${folder}")
			ENDIF()
		ENDIF()
	ELSE()
		SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS OFF)
	ENDIF()
ENDMACRO(CMAKE_SET_TARGET_FOLDER)

# Generate VC dir structure
# class by src, line, unittest
MACRO(SET_PMOD)
	string(REPLACE ${ROOTPATH} "" rest ${CMAKE_CURRENT_SOURCE_DIR} )
	string(REGEX MATCH "[^/]+" ret ${rest})
	set(PMOD ${ret})

	#message(STATUS ${PMOD}, ${ROOTPATH}, ${CMAKE_CURRENT_SOURCE_DIR})
	if (TARGET ${mname})
		CMAKE_SET_TARGET_FOLDER(${mname} src/${PMOD})
	elseif (TARGET ${mname}_LINT)
		CMAKE_SET_TARGET_FOLDER(${mname}_LINT lint/${PMOD})
	elseif (TARGET ${mtest})
		CMAKE_SET_TARGET_FOLDER(${mtest} unittest/${PMOD})
	elseif (TARGET ${mtarget})
		CMAKE_SET_TARGET_FOLDER(${mtarget} ftest/${PMOD})
	elseif (TARGET ${mtarget2})
		CMAKE_SET_TARGET_FOLDER(${mtarget2} ftest/${PMOD})
	endif()
ENDMACRO(SET_PMOD)
