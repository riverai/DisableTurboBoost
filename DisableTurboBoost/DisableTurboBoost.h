//
//  DisableTurboBoost.h
//  DisableTurboBoost
//
//  Created by Ge on 14-1-9.
//  Copyright (c) 2014年 Ge. All rights reserved.
//

#ifndef KextTest_KextTest_h
#define KextTest_KextTest_h

#include <IOKit/IOService.h>

class DisableTurboBoost : public IOService
{
	OSDeclareDefaultStructors(DisableTurboBoost)
	
public:
    virtual bool		start(IOService *provider);

    virtual IOReturn    setPowerState(
                                      unsigned long powerStateOrdinal,
                                      IOService *   whatDevice );
    virtual void        stop(IOService* provider);
    virtual void        free();
};

#endif
