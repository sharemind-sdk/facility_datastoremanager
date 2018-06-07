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

#include <memory>
#include <sharemind/DataStoreFactory.h>
#include <sharemind/facility-module-apis/api.h>
#include <sharemind/facility-module-apis/api_0x2.h>
#include <utility>


namespace {

namespace V2 = sharemind::FacilityModuleApis::v2;

struct DataStoreFactoryProcessFacilityFactory final
        : V2::ProcessFacilityFactory
{

    V2::FacilitySharedPtr createFacility(
            V2::ProcessFacilityFactoryContext const &) final override
    {
        auto factory(std::make_shared<::sharemind::DataStoreFactory>());
        return std::shared_ptr<::SharemindDataStoreFactory>(
                    std::move(factory),
                    &factory->wrapper());
    }

};

void initializeModule(V2::ModuleInitContext & context) {
    context.registerProcessFacilityFactory(
                "DataStoreFactory",
                std::make_shared<DataStoreFactoryProcessFacilityFactory>());
}

} // anonymous namespace

extern "C" {

SHAREMIND_FACILITY_MODULE_API_MODULE_INFO("DataStoreManager", 2u, 2u);
extern V2::FacilityModuleInfo sharemindFacilityModuleInfo_v2;
V2::FacilityModuleInfo sharemindFacilityModuleInfo_v2{initializeModule};

} // extern "C" {
