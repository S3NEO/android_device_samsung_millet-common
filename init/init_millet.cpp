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

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"

#include "init_msm8226.h"

using android::base::GetProperty;
using android::init::property_set;

void vendor_load_properties()
{
    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("T330XX") == 0) {
        /* milletwifixx */
        property_override("ro.build.description", "milletwifixx-user 5.1.1 LMY47X T330XXS1BSB1 release-keys");
        set_ro_product_prop("device", "milletwifi");
        set_ro_build_prop("fingerprint", "samsung/milletwifixx/milletwifi:5.1.1/LMY47X/T330XXS1BSB1:user/release-keys");
        set_ro_product_prop("model", "SM-T330");
        set_ro_product_prop("name", "milletwifi");
        wifi_properties("wifi-only", "1");
    } else if (bootloader.find("T330NU") == 0) {
        /* milletwifiue */
        property_override("ro.build.description", "milletwifiue-user 5.1.1 LMY47X T330NUUES1BPL1 release-keys");
        set_ro_product_prop("device", "milletwifiue");
        set_ro_build_prop("fingerprint", "samsung/milletwifiue/milletwifiue:5.1.1/LMY47X/T330NUUES1BPL1:user/release-keys");
        set_ro_product_prop("model", "SM-T330NU");
        set_ro_product_prop("name", "milletwifiue");
        wifi_properties("wifi-only", "1");
    } else if (bootloader.find("T331XX") == 0) {
        /* millet3g */
        property_override("ro.build.description", "millet3gxx-user 5.1.1 LMY47X T331XXS1BSA2 release-keys");
        set_ro_product_prop("device", "millet3g");
        set_ro_build_prop("fingerprint", "samsung/millet3gxx/millet3g:5.1.1/LMY47X/T331XXS1BSA2:user/release-keys");
        set_ro_product_prop("model", "SM-T331");
        set_ro_product_prop("name", "millet3g");
        gsm_properties("3", "0");
    } else if (bootloader.find("T335XX") == 0) {
        /* milletltexx */
        property_override("ro.build.description", "milletltexx-user 5.1.1 LMY47X T335XXS1BRL3 release-keys");
        set_ro_product_prop("device", "milletlte");
        set_ro_build_prop("fingerprint", "samsung/milletltexx/milletlte:5.1.1/LMY47X/T335XXS1BRL3:user/release-keys");
        set_ro_product_prop("model", "SM-T335");
        set_ro_product_prop("name", "milletlte");
        gsm_properties("9", "1");
    } else if (bootloader.find("T337T") == 0) {
        /* milletltetmo */
        property_override("ro.build.description", "milletltetmo-user 5.1.1 LMY47X T337TUVS1CPL1 release-keys");
        set_ro_product_prop("name", "milletltetmo");
        set_ro_build_prop("fingerprint", "samsung/milletltetmo/milletltetmo:5.1.1/LMY47X/T337TUVS1CPL1:user/release-keys");
        set_ro_product_prop("model", "SM-T337T");
        set_ro_product_prop("name", "milletltetmo");
        gsm_properties("9", "1");
    } else {
        wifi_properties("wifi-only", "1");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
