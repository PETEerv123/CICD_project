cmake_minimum_required(VERSION 3.20.1)

project(Demo) #Tên Dự án
#message("Cmake Curr  Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
#message("Cmake Curr Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")

#set(Demo_Library_Path ${CMAKE_CURRENT_SOURCE_DIR})
include(GNUInstallDirs) #cung cap cac bien Cmake la cac duong dan (directory) được tổ chức theo GNU file system
add_library(DemoLibrary ${CMAKE_CURRENT_SOURCE_DIR}/lib/DemoLibrary.c) # lenh add Library se them cac file thu vien de build
add_executable(Demo_App main.c) #Tao ra doi tuong cmake Demo_App , Demo_App nay se lay main.c la noi bat dau chuong trinh

# Doi tuong DemoLibrary se tim kieu cac file dependency trong duong dan hien tai source code cua CMAKE_CURRENT_SOURCE_DIR , neu chuong trinh duoc build

target_include_directories(DemoLibrary
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(Demo_App DemoLibrary) #link đối tượng cmake Library vao đối tượng Demo_App
install(
      FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/DemoLibrary.h
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
#lay ten Target Demo Library de export doi tuong DemoLibraryExport
install(TARGETS DemoLibrary
    EXPORT DemoLibraryExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} #Thư viện thuộc các đuôi .so hoặc .dll thuộc lib được cài đăt bằng đường dẫn {Cmake_Install_libDir}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} #Thư viện đã được biên dịch có đuôi .a hoặc .lib sẽ thuộc loại ARCHIVE được cài đặt tại đường dẫn${CMAKE_INSTALL_LIBDIR} → lib/
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} #File thực thi sẽ thuộc loại RUNTIME được cài đặt tại {Cmake_Insstall BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} #File header thuoc InclUde se cai dat tai Folder include
)
install( TARGETS Demo_App
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT DemoLibraryExport
    FILE DemoLibraryExport.cmake
    NAMESPACE DemoLibrary::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DemoLibrary
)
# To use configure_package_config_file function
include(CMakePackageConfigHelpers)

# Using file Config.cmake.in to create DemoLibraryConfig.cmake
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
     "${CMAKE_CURRENT_BINARY_DIR}/DemoLibraryConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DemoLibrary
)

# Create DemoLibraryConfigVersion.cmake that can compatible with newer version
write_basic_package_version_file(
  DemoLibraryConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY AnyNewerVersion
)

# Install these file at ${CMAKE_INSTALL_LIBDIR}/cmake/DemoLibrary
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/DemoLibraryConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DemoLibraryConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DemoLibrary
)
# Output_packagejk
