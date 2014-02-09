//
//  TurboBoost.cpp
//  DisableTurboBoost
//
//  Created by Ge on 14-1-9.
//  Copyright (c) 2014年 Ge. All rights reserved.
//

#include "TurboBoost.h"
#include <i386/proc_reg.h>

const uint64_t expectedFeatures  = 0x850089LL;
const uint64_t disableTurboBoost = 0x4000000000LL;

bool disable_tb() {
    uint64_t prev = rdmsr64(MSR_IA32_MISC_ENABLE);
    if(!(prev & disableTurboBoost))
    {
        wrmsr64(MSR_IA32_MISC_ENABLE, rdmsr64(MSR_IA32_MISC_ENABLE) | disableTurboBoost);
        uint64_t current = rdmsr64(MSR_IA32_MISC_ENABLE);
        if(prev == current)
            return false;
    }
    return true;
}

bool enable_tb() {
    uint64_t prev = rdmsr64(MSR_IA32_MISC_ENABLE);
    if((prev & disableTurboBoost))
    {
        wrmsr64(MSR_IA32_MISC_ENABLE, rdmsr64(MSR_IA32_MISC_ENABLE) & ~disableTurboBoost);
        uint64_t current = rdmsr64(MSR_IA32_MISC_ENABLE);
        if(prev == current)
            return false;
    }
    return true;
}

