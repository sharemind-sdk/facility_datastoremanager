/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#include <cassert>
#include <cstring>
#include <new>
#include <sharemind/DataStoreManager.h>
#include <sharemind/compiler-support/GccPR54526.h>
#include <sharemind/libfmodapi/api_0x1.h>

extern "C" {

SHAREMIND_FACILITY_MODULE_API_MODULE_INFO("DataStoreManager", 1u, 1u);

SHAREMIND_FACILITY_MODULE_API_0x1_INITIALIZER(c,errorStr);
SHAREMIND_FACILITY_MODULE_API_0x1_INITIALIZER(c,errorStr) {
    (void) errorStr;
    assert(c);
    try {
        ::sharemind::DataStoreManager * const manager =
            new ::sharemind::DataStoreManager{};

        ::SharemindModuleApi0x1Facility * const facility =
            new SharemindModuleApi0x1Facility{&manager->wrapper(), nullptr};
        c->moduleHandle = facility;
        return ::SHAREMIND_FACILITY_MODULE_API_0x1_OK;
    } catch (::std::bad_alloc const &) {
        return ::SHAREMIND_FACILITY_MODULE_API_0x1_OUT_OF_MEMORY;
    } catch (...) {
        return ::SHAREMIND_FACILITY_MODULE_API_0x1_MODULE_ERROR;
    }
}

SHAREMIND_FACILITY_MODULE_API_0x1_DEINITIALIZER(c);
SHAREMIND_FACILITY_MODULE_API_0x1_DEINITIALIZER(c) {
    assert(c);
    assert(c->moduleHandle);
    ::SharemindModuleApi0x1Facility * const facility =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::SharemindModuleApi0x1Facility *>(
                c->moduleHandle);
    assert(facility->facility);
    ::SharemindDataStoreManager * const managerWrapper =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::SharemindDataStoreManager *>(
            facility->facility);
    assert(managerWrapper->internal);
    ::sharemind::DataStoreManager * const manager =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::sharemind::DataStoreManager *>(
                managerWrapper->internal);
    delete manager;
    delete facility;
}

SHAREMIND_FACILITY_MODULE_API_0x1_PI_STARTUP(c, errorStr);
SHAREMIND_FACILITY_MODULE_API_0x1_PI_STARTUP(c, errorStr) {
    (void) errorStr;
    assert (c);
    assert (c->moduleHandle);

    try {
        ::SharemindModuleApi0x1Facility * const facility =
            static_cast<
                SHAREMIND_GCCPR54526_WORKAROUND::SharemindModuleApi0x1Facility *>(
                    c->moduleHandle);
        ::SharemindDataStoreManager * const managerWrapper =
            static_cast<
                SHAREMIND_GCCPR54526_WORKAROUND::SharemindDataStoreManager *>(
                facility->facility);
        assert(managerWrapper->internal);
        ::sharemind::DataStoreManager * const manager =
            static_cast<
                SHAREMIND_GCCPR54526_WORKAROUND::sharemind::DataStoreManager *>(
                    managerWrapper->internal);
        ::sharemind::DataStoreFactory * const factory =
            new ::sharemind::DataStoreFactory{};

        manager->registerFactory(c->processId, *factory);

        c->processHandle = factory;

        return SHAREMIND_FACILITY_MODULE_API_0x1_OK;
    } catch (const std::bad_alloc &) {
        return SHAREMIND_FACILITY_MODULE_API_0x1_OUT_OF_MEMORY;
    } catch (...) {
        return SHAREMIND_FACILITY_MODULE_API_0x1_MODULE_ERROR;
    }
}

SHAREMIND_FACILITY_MODULE_API_0x1_PI_SHUTDOWN(c);
SHAREMIND_FACILITY_MODULE_API_0x1_PI_SHUTDOWN(c) {
    assert(c);
    assert(c->moduleHandle);
    ::SharemindModuleApi0x1Facility * const facility =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::SharemindModuleApi0x1Facility *>(
                c->moduleHandle);
    assert(facility->facility);
    ::SharemindDataStoreManager * const managerWrapper =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::SharemindDataStoreManager *>(
            facility->facility);
    assert(managerWrapper->internal);
    ::sharemind::DataStoreManager * const manager =
        static_cast<
            SHAREMIND_GCCPR54526_WORKAROUND::sharemind::DataStoreManager *>(
                managerWrapper->internal);
    ::sharemind::DataStoreFactory * const factory =
        static_cast<SHAREMIND_GCCPR54526_WORKAROUND::sharemind::DataStoreFactory *>(
                c->processHandle);
    manager->unregisterFactory(c->processId);
    delete factory;
}

#define FIND_FACILITY(NAME) \
    SHAREMIND_FACILITY_MODULE_API_0x1_FIND_ ## NAME ## _FACILITY(c, signature);\
    SHAREMIND_FACILITY_MODULE_API_0x1_FIND_ ## NAME ## _FACILITY(c, signature) \
    { \
        assert(c); \
        assert(c->moduleHandle); \
        using WORKAROUND_GCCPR54526 = ::SharemindModuleApi0x1Facility; \
        return std::strcmp(signature, "DataStoreManager") != 0 \
               ? nullptr \
               : static_cast<WORKAROUND_GCCPR54526 *>(c->moduleHandle); \
    }
FIND_FACILITY(MODULE)
FIND_FACILITY(PD)
FIND_FACILITY(PDPI)

} // extern "C" {
