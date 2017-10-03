//
//  Animation.h
//
//  Created by Mikael Deurell on 20/06/2012.
//
//

#pragma once
#include "Quaternion.h"

struct Animation {
    Quaternion Start;
    Quaternion End;
    Quaternion Current;
    float Elapsed;
    float Duration;
};
