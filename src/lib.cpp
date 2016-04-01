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
#include <sharemind/DataStoreFactory.h>
#include <sharemind/libfmodapi/api_0x1.h>


extern "C" {

SHAREMIND_FACILITY_MODULE_API_MODULE_INFO("DataStoreManager", 1u, 1u);

SHAREMIND_FACILITY_MODULE_API_0x1_INITIALIZER(c,errorStr);
SHAREMIND_FACILITY_MODULE_API_0x1_INITIALIZER(,) {
    return ::SHAREMIND_FACILITY_MODULE_API_0x1_OK;
}

SHAREMIND_FACILITY_MODULE_API_0x1_DEINITIALIZER(c);
SHAREMIND_FACILITY_MODULE_API_0x1_DEINITIALIZER() {}

SHAREMIND_FACILITY_MODULE_API_0x1_PI_STARTUP(c, errorStr);
SHAREMIND_FACILITY_MODULE_API_0x1_PI_STARTUP(c,) {
    assert(c);

    static constexpr auto const setProcessFailure =
            SHAREMIND_FACILITY_MODULE_API_0x1_USER_SET_PROCESS_FACILITY_FAILURE;
    try {
        auto const factory = new ::sharemind::DataStoreFactory();
        c->processHandle = factory;
        if (!c->setProcessFacility(c, "DataStoreFactory", factory))
            return setProcessFailure;
        return SHAREMIND_FACILITY_MODULE_API_0x1_OK;
    } catch (const std::bad_alloc &) {
        return SHAREMIND_FACILITY_MODULE_API_0x1_OUT_OF_MEMORY;
    } catch (...) {
        return SHAREMIND_FACILITY_MODULE_API_0x1_MODULE_ERROR;
    }
}

SHAREMIND_FACILITY_MODULE_API_0x1_PI_SHUTDOWN(processHandle);
SHAREMIND_FACILITY_MODULE_API_0x1_PI_SHUTDOWN(processHandle) {
    assert(processHandle);
    using Factory = ::sharemind::DataStoreFactory;
    delete static_cast<Factory *>(processHandle);
}

} // extern "C" {
