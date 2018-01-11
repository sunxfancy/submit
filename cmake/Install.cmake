set(InstallLocation /opt/submit)

SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})


SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
SET(CPACK_PACKAGE_NAME "submit")
SET(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
SET(CPACK_PACKAGE_CONTACT "sunxfancy@gmail.com")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "short description")

IF(WIN32 AND NOT UNIX)
    SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\doc\\\\icon.ico")
    set(CPACK_GENERATOR NSIS)
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_CURRENT_SOURCE_DIR}\\\\bin\\\\submit")
    set (CPACK_NSIS_MODIFY_PATH "ON")
ELSEIF(LINUX)
   SET(CPACK_GENERATOR "STGZ;TGZ;DEB")
ENDIF()

install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/bin
        ${CMAKE_CURRENT_SOURCE_DIR}/conf
        DESTINATION .
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        COMPONENT core
        PATTERN ".git" EXCLUDE)

install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/tools
        DESTINATION .
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        COMPONENT toolchain
        PATTERN ".git" EXCLUDE)


install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/packages
        DESTINATION .
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        COMPONENT plugins
        PATTERN ".git" EXCLUDE)

install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        DESTINATION .
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        COMPONENT lib
        PATTERN ".git" EXCLUDE)



install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime
        DESTINATION .
        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        DIRECTORY_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_READ
        COMPONENT runtime
        PATTERN ".git" EXCLUDE)


set(CPACK_COMPONENT_CORE_DISPLAY_NAME "submit Core")
set(CPACK_COMPONENT_CORE_DESCRIPTION "submit core system")
set(CPACK_COMPONENT_CORE_GROUP "Application")

set(CPACK_COMPONENT_TOOLCHAIN_DISPLAY_NAME "Toolchain")
set(CPACK_COMPONENT_TOOLCHAIN_DESCRIPTION "The toolchain of submit")
set(CPACK_COMPONENT_TOOLCHAIN_GROUP "Application")

set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "The runtime libraries for built program")
set(CPACK_COMPONENT_RUNTIME_GROUP "Application")

set(CPACK_COMPONENT_HEADER_DISPLAY_NAME "C++ Headers")
set(CPACK_COMPONENT_HEADER_DESCRIPTION "The header files of Cpp")
set(CPACK_COMPONENT_HEADER_GROUP "Development")

set(CPACK_COMPONENT_LIB_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIB_DESCRIPTION "submit libraries")
set(CPACK_COMPONENT_LIB_GROUP "Development")

set(CPACK_COMPONENT_DOC_DISPLAY_NAME "User Manual")
set(CPACK_COMPONENT_DOC_DESCRIPTION "The Documentation of submit")
set(CPACK_COMPONENT_DOC_GROUP "Documentation")

set(CPACK_COMPONENT_GROUP_APPLICATION_DESCRIPTION
    "The major part of the submit system")
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
    "All of the libraries you'll ever need to develop with submit")
set(CPACK_COMPONENT_GROUP_DOCUMENTATION_DESCRIPTION
    "The documentation of submit")

set(CPACK_COMPONENTS_ALL core doc header runtime toolchain lib)

INCLUDE(CPack)