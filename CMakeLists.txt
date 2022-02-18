#
# Copyright (C) 2015 Cybernetica
#
# Research/Commercial License Usage
# Licensees holding a valid Research License or Commercial License
# for the Software may use this file according to the written
# agreement between you and Cybernetica.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl-3.0.html.
#
# For further information, please contact us at sharemind@cyber.ee.
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(SharemindFacilityDataStoreManager VERSION 0.3.0 LANGUAGES CXX)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.6 REQUIRED)


FIND_PACKAGE(SharemindFacilityModuleApis 2.1.0 REQUIRED)
FIND_PACKAGE(SharemindLibDataStoreManager 0.3.0 REQUIRED)


# The facility:
FILE(GLOB_RECURSE SharemindFacilityDataStoreManager_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE SharemindFacilityDataStoreManager_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
SharemindAddSharedLibrary(FacilityDataStoreManager
    MODULE
    OUTPUT_NAME "sharemind_facility_datastoremanager"
    SOURCES
        ${SharemindFacilityDataStoreManager_SOURCES}
        ${SharemindFacilityDataStoreManager_HEADERS}
)
TARGET_COMPILE_DEFINITIONS(FacilityDataStoreManager
    PRIVATE
        "_XOPEN_SOURCE=700"
        "SHAREMIND_INTERNAL_"
    )
TARGET_LINK_LIBRARIES(FacilityDataStoreManager
    PRIVATE
        Sharemind::FacilityModuleApis
        Sharemind::LibDataStoreManager
    )


# Configuration files:
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/packaging/configs/sharemind/"
        DESTINATION "/etc/sharemind/"
        COMPONENT "lib"
        EXCLUDE_FROM_ALL)

# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("lib"
    NAME "libsharemind-facility-datastoremanager"
    DESCRIPTION "Sharemind Data Store Manager facility"
    DEB_SECTION "libs"
    DEB_DEPENDS
        "libsharemind-datastoremanager (>= 0.2.0)"
        "libstdc++6 (>= 4.8.0)"
        "libc6 (>= 2.19)"
    DEB_EXTRA_CONTROL_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/packaging/debian/conffiles"
)
SharemindAddComponentPackage("debug"
    NAME "libsharemind-facility-datastoremanager-dbg"
    DESCRIPTION "Sharemind Data Store Manager facility debug symbols"
    DEB_SECTION "debug"
    DEB_DEPENDS
        "libsharemind-facility-datastoremanager (= ${SharemindFacilityDataStoreManager_DEB_lib_PACKAGE_VERSION})"
)
SharemindPackagingFinalize()
