/*
  ==============================================================================

    DelayLine.h
    Created: 17 Oct 2018 1:56:13pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

//
//  DelayLine.hpp
//  VirtualTubeDelay
//
//  Created by Riccardo Simionato on 03/10/18.
//
//

#pragma once

#include <math.h>
#include <tgmath.h>
#include <vector>

class DelayLine {
public:
    
    DelayLine()
    {initialize();};
    
    ~DelayLine(){
        
        for(int i = 0; i < 2; ++i)
        {
            delete delayBuffer[i];
            delete delayBuffer_1[i];
            delete delayBuffer_2[i];
            delete delayBuffer_3[i];
        }
    
    };
    
    void initialize(){
        
        delayBufferLength_ = 8*mSampleRate;//3835;//(int)(30/0.345)*44.1 + 1;
        
        for(int i = 0; i < 2; ++i)
        {
            
            delayBuffer[i] = new double[delayBufferLength_];
            
            rptr[i] = delayBuffer[i]; // read ptr
            wptr[i] = delayBuffer[i]; // write ptr
            
            delayBuffer_1[i] = new double[delayBufferLength_];
        
            rptr_1[i] = delayBuffer_1[i]; // read ptr
            wptr_1[i] = delayBuffer_1[i]; // write ptr
            
            delayBuffer_2[i] = new double[delayBufferLength_];
            
            rptr_2[i] = delayBuffer_2[i]; // read ptr
            wptr_2[i] = delayBuffer_2[i]; // write ptr
            
            delayBuffer_3[i] = new double[delayBufferLength_];

            rptr_3[i] = delayBuffer_3[i]; // read ptr
            wptr_3[i] = delayBuffer_3[i]; // write ptr
            
        }
    }
    
    void setDelays(int channel);
    
    double delayLines(double input_1, double input_2, double input_3, float feedback, int channel);
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    double hermiteInterpolation(double* pointer, double* buffer, int bufferLenght, double frac);
    
    inline void computeTimeSpacedComponents(float first, float second, float third) {
        
        //int tot = first + second + third;
        TimeSpacedComponent_1 = first * (mSampleRate/1000);
        TimeSpacedComponent_2 = second * (mSampleRate/1000);
        TimeSpacedComponent_3 = third * (mSampleRate/1000);
    };
    
    inline void setSamplesSpacedComponents(float first, float second, float third) {
        
        TimeSpacedComponent_1 = first;
        TimeSpacedComponent_2 = second;
        TimeSpacedComponent_3 = third;
    };
    
    
    // flush buffers
    inline void suspend(){
        for(int i = 0; i < 2; ++i)
        {
            memset(delayBuffer[i], 0, delayBufferLength_*sizeof(double));
            memset(delayBuffer_1[i], 0, delayBufferLength_*sizeof(double));
            memset(delayBuffer_2[i], 0, delayBufferLength_*sizeof(double));
            memset(delayBuffer_3[i], 0, delayBufferLength_*sizeof(double));
        }
    }
    
    
    float TimeSpacedComponent_1{1014.3f};
    float TimeSpacedComponent_2{2205.0f};
    float TimeSpacedComponent_3{3042.9f};
    
private:
    
    float fracDelaySamples_1[2]{0.3f,0.3f};
    float fracDelaySamples_2[2]{0.0f,0.0f};
    float fracDelaySamples_3[2]{0.9f,0.9f};
    
    double mSampleRate;
    
    int delayBufferLength_;
    
    double *delayBuffer[2];
    double *delayBuffer_1[2];
    double *delayBuffer_2[2];
    double *delayBuffer_3[2];
    
    double *rptr[2]; // read ptr
    double *wptr[2]; // write ptr
    
    double *rptr_1[2]; // read ptr
    double *wptr_1[2]; // write ptr
    
    double *rptr_2[2]; // read ptr
    double *wptr_2[2]; // write ptr
    
    double *rptr_3[2]; // read ptr
    double *wptr_3[2]; // write ptr

};