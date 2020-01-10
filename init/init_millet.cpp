/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::init::property_set;

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void hspa_properties()
{
    property_set("ro.telephony.default_network", "3");
    property_set("telephony.lteOnGsmDevice", "0");
}

void lte_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

void wifi_only_properties()
{
    property_set("ro.carrier", "wifi-only");
    property_set("ro.radio.noril", "1");
}

void vendor_load_properties()
{

    std::string bootloader = GetProperty("ro.bootloader", "");

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    if (bootloader.find("T330NU") == 0) {
        /* s3ve3gxx */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/milletwifixx/milletwifi:5.0.2/LRX22G/T330NUU1BOJ4:user/release-keys");
            set_ro_product_prop(source, "model", "SM-T330");
            set_ro_product_prop(source, "device", "milletwifi");
        }
        property_override("ro.build.description", "milletwifixx-user 5.0.2 LRX22G T330NUU1BOJ4 release-keys");
        wifi_only_properties();
    } else if (bootloader.find("T330XX") == 0) {
        /* s3ve3gxx */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/milletwifixx/milletwifi:5.0.2/LRX22G/T330XXU1BOJ4:user/release-keys");
            set_ro_product_prop(source, "model", "SM-T330");
            set_ro_product_prop(source, "device", "milletwifi");
        }
        property_override("ro.build.description", "milletwifixx-user 5.0.2 LRX22G T330XXU1BOJ4 release-keys");
        wifi_only_properties();
    } else if (bootloader.find("T331") == 0) {
        /* s3ve3gjv */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/millet3gxx/millet3g:5.0.2/LRX22G/T331XXU1BOD8:user/release-keys");
            set_ro_product_prop(source, "model", "SM-T331");
            set_ro_product_prop(source, "device", "millet3g");
        }
        property_override("ro.build.description", "millet3gxx-user 5.0.2 LRX22G T331XXU1BOD8 release-keys");
        hspa_properties();
    } else if (bootloader.find("T335") == 0) {
        /* s3ve3gdsds */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/milletltexx/milletlte:5.0.2/LRX22G/T335XXU1BOD8:user/release-keys");
            set_ro_product_prop(source, "model", "SM-T335");
            set_ro_product_prop(source, "device", "milletlte");
    }
        property_override("ro.build.description", "milletltexx-user 5.0.2 LRX22G T335XXU1BOD8 release-keys");
        lte_properties();
    } else if (bootloader.find("T337T") == 0) {
        /* s3ve3gdsds */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/milletltetmo/milletltetmo:5.1.1/LMY47X/T337TUVS1CPL1:user/release-keys");
            set_ro_product_prop(source, "model", "SM-T337T");
            set_ro_product_prop(source, "device", "milletltetmo");
    }
        property_override("ro.build.description", "milletltetmo-user 5.1.1 LMY47X T337TUVS1CPL1 release-keys");
        lte_properties();
    }else {
        wifi_only_properties();
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
