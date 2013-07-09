cmake_minimum_required ( VERSION 2.8.9)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-fPIC")
set (project_name "timelapse")
project (${project_name})
set (${project_name}_VERSION_MAJOR 1)
set (${project_name}_VERSION_MINOR 0)
#Clear cmake cache
#unset (* CACHE)

#Set c++11 flag for unix build
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Setting C++11 flag for linux")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")
        ADD_DEFINITIONS(
            -std=gnu++11
        )
endif()

#Dependencies
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
#SET(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_THREAD_USE_LIB=1")

SET(OpenCV_USE_STATIC_LIBS ON)
#PKG-CONFIG
find_package(PkgConfig REQUIRED)

#OpenCV
FIND_PACKAGE( OpenCV REQUIRED )

IF(OpenCV_FOUND)
    MESSAGE("OPENCV libraries found ")
  #  MESSAGE(${OpenCV_VERSION_MAJOR}.${OpenCV_VERSION_MINOR}.${OpenCV_VERSION_PATCH}.${OpenCV_VERSION_TWEAK})
   # MESSAGE(${OpenCV_INCLUDE_DIRS})
    #MESSAGE(${OpenCV_LIBS})
    include_directories(${OpenCV_INCLUDE_DIRS})
#SET (EXTRA_LIBS ${EXTRA_LIBS} ${OpenCV_LIBS} )
ELSE(OpenCV_FOUND)
	MESSAGE(FATAL ERROR " OPENCV libraries not found ")
ENDIF(OpenCV_FOUND)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})



include_directories(.)
SET(${project_name}_SRCS ${${project_name}_SRCS}src/main.cpp
)
#SET(${project_name}_HDRS ${${project_name}_HDRS} src/qvideo.h src/qglcanvas.h src/glInfo.h src/videorecorder.h src/videotrack.h src/track.cpp
 #                                               src/trackname.h src/sourceselector.h
#)

# add the binary tree to the search path for include files
# so that we will find ${project_name}Config.h
include_directories (${PROJECT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_BINARY_DIR})

# add the Subdirectories

SET (FFMPEG_LIBRARIES
	avcodec
	avformat
	avutil
	swresample
	swscale
)

# add the executable
add_executable (${project_name} ${${project_name}_SRCS} ${${project_name}_HDRS})
SET (EXTRA_LIBS ${EXTRA_LIBS} ${OpenCV_LIBS} )



#MESSAGE ("${EXTRA_LIBS}")
target_link_libraries (${project_name} ${EXTRA_LIBS})



# add the install targets
install (TARGETS ${project_name} DESTINATION /usr/bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE       "${CMAKE_CURRENT_SOURCE_DIR}/Eula.rtf")
set (CPACK_PACKAGE_VERSION_MAJOR "${${project_name}_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${${project_name}_VERSION_MINOR}")
include (CPack) 


