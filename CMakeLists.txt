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
PROJECT(SharemindFacilityDataStoreManager VERSION 0.1.0 LANGUAGES CXX)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers REQUIRED)

SharemindSetProjectVersion()


FIND_PACKAGE(SharemindCxxHeaders REQUIRED)
FIND_PACKAGE(SharemindFacilityModuleApis REQUIRED)
FIND_PACKAGE(SharemindLibDataStoreManager REQUIRED)


# The facility:
SharemindSetCxx11CompileOptions()
FILE(GLOB_RECURSE SharemindFacilityDataStoreManager_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE SharemindFacilityDataStoreManager_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
SharemindAddSharedLibrary("sharemind_facility_datastoremanager"
    MODULE
    OUTPUT_NAME "sharemind_facility_datastoremanager"
    SOURCES
        ${SharemindFacilityDataStoreManager_SOURCES}
        ${SharemindFacilityDataStoreManager_HEADERS}
    INCLUDE_DIRECTORIES
        ${SharemindCxxHeaders_INCLUDE_DIRS}
        ${SharemindLibDataStoreManager_INCLUDE_DIRS}
        ${SharemindFacilityModuleApis_INCLUDE_DIRS}
    COMPILE_DEFINITIONS
        "_XOPEN_SOURCE=700"
        "SHAREMIND_INTERNAL_"
    LEGACY_DEFINITIONS
        ${SharemindCxxHeaders_DEFINITIONS}
        ${SharemindLibDataStoreManager_DEFINITIONS}
    LINK_LIBRARIES
        ${SharemindLibDataStoreManager_LIBRARIES}
)


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("lib"
    NAME "libsharemind-facility-datastoremanager"
    DESCRIPTION "Sharemind Data Store Manager facility"
    DEB_SECTION "libs"
    DEB_DEPENDS
        "libsharemind-datastoremanager (>= 0.1.0)"
        "libstdc++6 (>= 4.8.0)"
        "libc6 (>= 2.19)"
)
SharemindAddComponentPackage("debug"
    NAME "libsharemind-facility-datastoremanager-dbg"
    DESCRIPTION "Sharemind Data Store Manager facility debug symbols"
    DEB_SECTION "debug"
    DEB_DEPENDS
        "libsharemind-facility-datastoremanager (= ${SharemindFacilityDataStoreManager_VERSION})"
)
SharemindPackagingFinalize()

