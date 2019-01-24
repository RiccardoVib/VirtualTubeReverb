//
//  DelayLine.cpp
//  VirtualTubeDelay
//
//  Created by Riccardo Simionato on 03/10/18.
//
//

#include "DelayLine.h"
#include <iostream>
#include <math.h>

double DelayLine::hermiteInterpolation(double* pointer, double* buffer, int bufferLenght, double frac){
    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    double y;
    double *y_1 = (pointer - 1);
    double *y_2 = (pointer - 2);
    double *y_3 = (pointer - 3);
    
    if (y_1 < buffer) { y_1 += bufferLenght; }
    if (y_2 < buffer) { y_2 += bufferLenght; }
    if (y_3 < buffer) { y_3 += bufferLenght; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *pointer);
    c2 = (*pointer - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3- *pointer) + (3.0/2.0)*(*y_1 - *y_2);
    
    return y = ((c3*frac+c2)*frac+c1)*frac+c0;
    
}

void DelayLine::setDelays(int channel)
{
    rptr[channel] = wptr[channel] - (long)TimeSpacedComponent_3;
    rptr_1[channel] = wptr[channel] - (long)TimeSpacedComponent_1;
    rptr_2[channel] = wptr[channel] - (long)TimeSpacedComponent_2;
    rptr_3[channel] = wptr[channel] - (long)TimeSpacedComponent_3;

    while (rptr[channel] < delayBuffer[channel]) { rptr[channel] += delayBufferLength_; }
    while (rptr_1[channel] < delayBuffer_1[channel]) { rptr_1[channel] += delayBufferLength_; }
    while (rptr_2[channel] < delayBuffer_2[channel]) { rptr_2[channel] += delayBufferLength_; }
    while (rptr_3[channel] < delayBuffer_3[channel]) { rptr_3[channel] += delayBufferLength_; }
    
    fracDelaySamples_1[channel] = TimeSpacedComponent_1 - (long)TimeSpacedComponent_1;
    fracDelaySamples_2[channel] = TimeSpacedComponent_2 - (long)TimeSpacedComponent_2;
    fracDelaySamples_3[channel] = TimeSpacedComponent_3 - (long)TimeSpacedComponent_3;
    
}

double DelayLine::delayLines(double x_1, double x_2, double x_3, float feedback, int channel)
{
    
    double h0 = hermiteInterpolation(rptr[channel], delayBuffer[channel], delayBufferLength_, fracDelaySamples_3[channel]);
    
    double h1 = hermiteInterpolation(rptr_1[channel], delayBuffer_1[channel], delayBufferLength_, fracDelaySamples_1[channel]);
    
    double h2 = hermiteInterpolation(rptr_2[channel], delayBuffer_2[channel], delayBufferLength_, fracDelaySamples_2[channel]);
    
    double h3 = hermiteInterpolation(rptr_3[channel], delayBuffer_3[channel], delayBufferLength_, fracDelaySamples_3[channel]);
    
    double y = h0 + h1 + h2 + h3;;
    
    rptr[channel] += 1;
    *wptr[channel]++ = feedback * y;
    
    rptr_1[channel] += 1;
    *wptr_1[channel]++ = x_1;
    
    rptr_2[channel] += 1;
    *wptr_2[channel]++ = x_2;
    
    rptr_3[channel] += 1;
    *wptr_3[channel]++ = x_3;
    
    if (rptr[channel] - delayBuffer[channel] >= delayBufferLength_) { rptr[channel] -= delayBufferLength_; }
    if (wptr[channel] - delayBuffer[channel] >= delayBufferLength_) { wptr[channel] -= delayBufferLength_; }
    
    if (rptr_1[channel] - delayBuffer_1[channel] >= delayBufferLength_) { rptr_1[channel] -= delayBufferLength_; }
    if (wptr_1[channel] - delayBuffer_1[channel] >= delayBufferLength_) { wptr_1[channel] -= delayBufferLength_; }
    
    if (rptr_2[channel] - delayBuffer_2[channel] >= delayBufferLength_) { rptr_2[channel] -= delayBufferLength_; }
    if (wptr_2[channel] - delayBuffer_2[channel] >= delayBufferLength_) { wptr_2[channel] -= delayBufferLength_; }
    
    if (rptr_3[channel] - delayBuffer_3[channel] >= delayBufferLength_) { rptr_3[channel] -= delayBufferLength_; }
    if (wptr_3[channel] - delayBuffer_3[channel] >= delayBufferLength_) { wptr_3[channel] -= delayBufferLength_; }
    
    //H(z) = 1/(1 - az^-D)
    //y(n) = ay(n - D) + x(n)
    
    return y;
}
