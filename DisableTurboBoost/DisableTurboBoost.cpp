//
//  DisableTurboBoost.cpp
//  DisableTurboBoost
//
//  Created by Ge on 14-1-9.
//  Copyright (c) 2014年 Ge. All rights reserved.
//

#include "DisableTurboBoost.h"
#include <IOKit/IOLib.h>
#include "TurboBoost.h"

static const char *className = NULL;

static void Log(const char *log);
static void disabletb();
static void enabletb();

#define super IOService
OSDefineMetaClassAndStructors (DisableTurboBoost, IOService)

#pragma mark -
#pragma mark Overridden methods
bool DisableTurboBoost::start(IOService *provider)
{
	if (!super::start(provider))
        return false;
    
    className = this->getName();
    
    // two power states - off and on
	static const IOPMPowerState powerStates[2] = {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, IOPMDeviceUsable, IOPMPowerOn, IOPMPowerOn, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    
    // register interest in power state changes
	PMinit();
	provider->joinPMtree(this);
	registerPowerDriver(this, (IOPMPowerState *)powerStates, 2);
    
    // Register service
    registerService();
    
    return true;
}

IOReturn DisableTurboBoost::setPowerState(unsigned long powerState, IOService *device)
{
	switch (powerState) {
        case 1: // Power On
            disabletb();
            break;
        default:
            break;
    }
	return(IOPMAckImplied);
}


void DisableTurboBoost::stop(IOService *provider)
{
    enabletb();
    Log("stoped");
    super::stop(provider);
}

void DisableTurboBoost::free()
{
    super::free();
}

#pragma mark cpp function
static void enabletb()
{
    if(enable_tb())
        Log("turbo boost enabled");
    else
        Log("reset failed");
}

static void disabletb()
{
    if(disable_tb())
        Log("turbo boost disabled");
    else
        Log("failed");
}

static void Log(const char *log)
{
    IOLog("%s:%s.\n", className, log);
}


