/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeReverbAudioProcessor::VirtualTubeReverbAudioProcessor() :
AudioProcessor (BusesProperties().withInput  ("Input",     AudioChannelSet::stereo(), true)
                  .withOutput ("Output",    AudioChannelSet::stereo(), true)), parameters (*this, nullptr)
{
  
    parameters.createAndAddParameter("pan_", "pan", "pan", NormalisableRange<float>(0.0f,1.0f), 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0f, 1.0f), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    parameters.createAndAddParameter("decay_", "decay", "decay", NormalisableRange<float>(0.1f,0.9f), 0.75f, nullptr, nullptr);
    parameters.createAndAddParameter("decayVel_", "decayVel", "decayVel", NormalisableRange<float>(1.0f,4.0f), 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("amp_", "amp", "amp", NormalisableRange<float>(0.0f,4.0f), 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("ampRef_", "ampRef", "ampRef", NormalisableRange<float>(0.0f,4.0f), 0.0f, nullptr, nullptr);
    
    parameters.createAndAddParameter("mode_", "mode", "mode", NormalisableRange<float>(0.0f,1.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("firstRef_", "firstRef", "firstRef", NormalisableRange<float>(1.0f,28.0f), 23.0f, nullptr, nullptr);
    parameters.createAndAddParameter("secondRef_", "secondRef", "secondRef", NormalisableRange<float>(1.0f,28.0f), 27.0f, nullptr, nullptr);
    parameters.createAndAddParameter("thirdRef_", "thirdRef", "thirdRef", NormalisableRange<float>(1.0f,28.0f), 19.0f, nullptr, nullptr);
    
    parameters.state = ValueTree("SavedParams");
    
    pan_ = parameters.getRawParameterValue ("pan_");
    dryWetMix_ = parameters.getRawParameterValue ("dryWetMix_");
    tubeSize_ = parameters.getRawParameterValue ("tubeSize_");
    decay_ = parameters.getRawParameterValue ("decay_");
    decayVel_ = parameters.getRawParameterValue ("decayVel_");
    amp_ = parameters.getRawParameterValue ("amp_");
    ampRef_ = parameters.getRawParameterValue ("ampRef_");
    mode_ = parameters.getRawParameterValue ("mode_");
    firstRef_ = parameters.getRawParameterValue ("firstRef_");
    secondRef_ = parameters.getRawParameterValue ("secondRef_");
    thirdRef_ = parameters.getRawParameterValue ("thirdRef_");
    
}

VirtualTubeReverbAudioProcessor::~VirtualTubeReverbAudioProcessor()
{
}

//==============================================================================
const String VirtualTubeReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualTubeReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VirtualTubeReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualTubeReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualTubeReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualTubeReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String VirtualTubeReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void VirtualTubeReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VirtualTubeReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Set default values:
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
        
        mDelayLine[channel].setSampleRate(getSampleRate());
        mFilter_1[channel].setSampleRate(getSampleRate());
        mFilter_2[channel].setSampleRate(getSampleRate());
        mFilter_3[channel].setSampleRate(getSampleRate());
        
        mFilter_1[channel].setValues(7.935f, 0);
        mFilter_2[channel].setValues(17.25f, 0);
        mFilter_3[channel].setValues(23.805f, 0);
        
        mFilter_ref_1[channel].setSampleRate(getSampleRate());
        mFilter_ref_2[channel].setSampleRate(getSampleRate());
        mFilter_ref_3[channel].setSampleRate(getSampleRate());
        
        mFilter_ref_1[channel].setValues(7.935f, 0);
        mFilter_ref_2[channel].setValues(17.25f, 0);
        mFilter_ref_3[channel].setValues(23.805f, 0);
        
        mDelayLine[channel].initialize();
        
        //computing delays samples (sample rate dependents)
        mDelayLine[channel].computeTimeSpacedComponents(23, 27, 19);
        
        //setting delaylines
        mDelayLine[channel].setDelays(channel);
    }
    
}

void VirtualTubeReverbAudioProcessor::releaseResources()
{
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualTubeReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VirtualTubeReverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    int numSamples = buffer.getNumSamples();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    //storing parameters values
    float wetValue_ = *dryWetMix_;
    
    float currentDecayVel = *decayVel_;
    float currentDecay = powf(*decay_, currentDecayVel);
    float pan[2];
    
    int mode = *mode_;
    
    float firstRef = 23.0f;
    float secondRef = 50.0f;
    float thirdRef = 69.0f;
    
    float currentAmp = *amp_;
    float currentAmpRef = *ampRef_;
    
    if(mode == 1)
    {
        firstRef = static_cast<int>(*firstRef_);
        secondRef = static_cast<int>(*firstRef_ + *secondRef_);
        thirdRef = static_cast<int>(*firstRef_ + *secondRef_ + *thirdRef_);
    }
  
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        
        firstDistance[channel] = 0.345*firstRef;
        secondDistance[channel] = 0.345*secondRef;
        thirdDistance[channel] = 0.345*thirdRef;
        
        //computing delays samples (sample rate dependents)
        mDelayLine[channel].computeTimeSpacedComponents(firstRef, secondRef, thirdRef);
    }
    
    pan[1] = *pan_;
    pan[0] = 1 - pan[1];
    
    rad = floor(*tubeSize_*10 - 12);
    
    for (int channel = 0; channel < 2; ++channel)
    {
        applyFilterDelay(numSamples, channel);
        
        auto* channelData = buffer.getWritePointer(channel);
    
        for (int i = 0; i < numSamples; ++i)
        {
            //setting delaylines
            mDelayLine[channel].setSamplesSpacedComponents(interpolatedFirstDelaySamples[channel], interpolatedSecondDelaySamples[channel], interpolatedThirdDelaySamples[channel]);
            
            mDelayLine[channel].setDelays(channel);
            
            process(channel);
        
            //computing filter coefficients
            mFilter_1[channel].setValues(interpolatedFirstDistance[channel], rad);
            mFilter_1[channel].getCalculatedCoefficients();
            
            mFilter_2[channel].setValues(interpolatedSecondDistance[channel], rad);
            mFilter_2[channel].getCalculatedCoefficients();
            
            mFilter_3[channel].setValues(interpolatedThirdDistance[channel], rad);
            mFilter_3[channel].getCalculatedCoefficients();
        
            //computing filter coefficients (reflection)
            mFilter_ref_1[channel].setValues(interpolatedFirstDistance[channel], rad);
            mFilter_ref_1[channel].getCalculatedCoefficients();
            
            mFilter_ref_2[channel].setValues(interpolatedSecondDistance[channel], rad);
            mFilter_ref_2[channel].getCalculatedCoefficients();
            
            mFilter_ref_3[channel].setValues(interpolatedThirdDistance[channel], rad);
            mFilter_ref_3[channel].getCalculatedCoefficients();
            
            const double in = channelData[i];
            
            double out = 0.0;
        
            double x_1 = computeOutFilter(mFilter_1[channel], bufOut_1[channel], bufIn_1[channel], in, channel);
            double x_2 = computeOutFilter(mFilter_2[channel], bufOut_2[channel], bufIn_2[channel], in, channel);
            double x_3 = computeOutFilter(mFilter_3[channel], bufOut_3[channel], bufIn_3[channel], in, channel);
                
            double delayOut = pan[channel] * currentAmp * mDelayLine[channel].delayLines(x_1, x_2, x_3, currentDecay, channel);
        
            double x_ref_1 = computeOutReflectionFilter(mFilter_ref_1[channel], bufOut_Ref_1[channel], bufIn_Ref_1[channel], bufOut_Fin_1[channel], bufIn_Fin_1[channel], x_1, channel);
            double x_ref_2 = computeOutReflectionFilter(mFilter_ref_2[channel], bufOut_Ref_2[channel], bufIn_Ref_2[channel], bufOut_Fin_2[channel], bufIn_Fin_2[channel], x_2, channel);
            double x_ref_3 = computeOutReflectionFilter(mFilter_ref_3[channel], bufOut_Ref_3[channel], bufIn_Ref_3[channel], bufOut_Fin_3[channel], bufIn_Fin_3[channel], x_3, channel);
            
            double delayRefOut = pan[channel] * currentAmpRef * mDelayLine[channel].delayLines(x_ref_1, x_ref_2, x_ref_3, currentDecay, channel);
            
            out = (1.0 - wetValue_) * in + wetValue_ * (delayOut + delayRefOut);
            
            channelData[i] = out;
            
            interpolatedFirstDistance[channel] += incrementFirstDistance[channel];
            interpolatedSecondDistance[channel] += incrementSecondDistance[channel];
            interpolatedThirdDistance[channel] += incrementThirdDistance[channel];
            
            interpolatedFirstDelaySamples[channel] += incrementFirstDelaySamples[channel];
            interpolatedSecondDelaySamples[channel] += incrementSecondDelaySamples[channel];
            interpolatedThirdDelaySamples[channel] += incrementThirdDelaySamples[channel];
            
        }
    }
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}


void VirtualTubeReverbAudioProcessor::process(int channel) {
    
    i_0 = ptr[channel]%7;       //->6
    i_1 = (ptr[channel] + 1)%7; //->0
    i_2 = (ptr[channel] + 2)%7; //->1
    i_3 = (ptr[channel] + 3)%7; //->2
    i_4 = (ptr[channel] + 4)%7; //->3
    i_5 = (ptr[channel] + 5)%7; //->4
    i_6 = (ptr[channel] + 6)%7; //->5
    
    if (--ptr[channel] < 0) { ptr[channel] += 7; }
    
    j_0 = ptr2[channel]%4;       //->3
    j_1 = (ptr2[channel] + 1)%4; //->0
    j_2 = (ptr2[channel] + 2)%4; //->1
    j_3 = (ptr2[channel] + 3)%4; //->2
    
    if (--ptr2[channel] < 0) { ptr2[channel] += 4; }
}

double VirtualTubeReverbAudioProcessor::computeOutFilter(Filter &filter, double bufOut[], double bufIn[], double input, int channel){
    
    double in = input;
    double out;
    
    bufIn[i_0] = in;
    
    bufOut[i_0] = bufIn[i_0] * filter.b0f + bufIn[i_1] * filter.b1f + bufIn[i_2] * filter.b2f + bufIn[i_3] * filter.b3f + bufIn[i_4] * filter.b4f + bufIn[i_5] * filter.b5f + bufIn[i_6] * filter.b6f - bufOut[i_1] * filter.a1f - bufOut[i_2] * filter.a2f - bufOut[i_3] * filter.a3f - bufOut[i_4] * filter.a4f - bufOut[i_5] * filter.a5f - bufOut[i_6] * filter.a6f;
    
    out = bufOut[i_0];
    
    return out;
    
}

double VirtualTubeReverbAudioProcessor::computeOutReflectionFilter(Filter mFilter_ref, double bufOut_Ref[], double bufIn_Ref[], double bufOut_Fin[], double bufIn_Fin[], double input, int channel){
    
    double in = input;
    double out;
    
    bufIn_Ref[i_0] = in;
    
    bufOut_Ref[i_0] = bufIn_Ref[i_0] * mFilter_ref.b0f + bufIn_Ref[i_1] * mFilter_ref.b1f + bufIn_Ref[i_2] * mFilter_ref.b2f + bufIn_Ref[i_3] * mFilter_ref.b3f + bufIn_Ref[i_4] * mFilter_ref.b4f + bufIn_Ref[i_5] * mFilter_ref.b5f + bufIn_Ref[i_6] * mFilter_ref.b6f - bufOut_Ref[i_1] * mFilter_ref.a1f - bufOut_Ref[i_2] * mFilter_ref.a2f - bufOut_Ref[i_3] * mFilter_ref.a3f - bufOut_Ref[i_4] * mFilter_ref.a4f - bufOut_Ref[i_5] * mFilter_ref.a5f - bufOut_Ref[i_6] * mFilter_ref.a6f;
    
    bufIn_Fin[j_0] = bufOut_Ref[i_0];
    
    bufOut_Fin[j_0] = bufIn_Fin[j_0] * b_Ref[rad][0] + bufIn_Fin[j_1] * b_Ref[rad][1] + bufIn_Fin[j_2] * b_Ref[rad][2] + bufIn_Fin[j_3] * b_Ref[rad][3] - bufOut_Fin[j_1] * a_Ref[rad][0] - bufOut_Fin[j_2] * a_Ref[rad][1] - bufOut_Fin[j_3] * a_Ref[rad][2];
    
    out = bufOut_Fin[j_0];
    
    return out;
    
}

void VirtualTubeReverbAudioProcessor::applyFilterDelay(int numSamples, int channel){
    
    //interpolating lengths (filter coefficients)
    incrementFirstDistance[channel] = (firstDistance[channel] - previousFirstDistance[channel]) / (float) numSamples;
    interpolatedFirstDistance[channel] = previousFirstDistance[channel];
    previousFirstDistance[channel] = firstDistance[channel];
    
    incrementSecondDistance[channel] = (secondDistance[channel] - previousSecondDistance[channel]) / (float) numSamples;
    interpolatedSecondDistance[channel] = previousSecondDistance[channel];
    previousSecondDistance[channel] = secondDistance[channel];
    
    incrementThirdDistance[channel] = (thirdDistance[channel] - previousThirdDistance[channel]) / (float) numSamples;
    interpolatedThirdDistance[channel] = previousThirdDistance[channel];
    previousThirdDistance[channel] = thirdDistance[channel];
    
    
    //interpolating delays
    incrementFirstDelaySamples[channel] = (long)(mDelayLine[channel].TimeSpacedComponent_1 - previousFirstDelaySamples[channel]) / (float) numSamples;
    interpolatedFirstDelaySamples[channel] = previousFirstDelaySamples[channel];
    previousFirstDelaySamples[channel] = mDelayLine[channel].TimeSpacedComponent_1;

    incrementSecondDelaySamples[channel] = (long)(mDelayLine[channel].TimeSpacedComponent_2 - previousSecondDelaySamples[channel]) / (float) numSamples;
    interpolatedSecondDelaySamples[channel] = previousSecondDelaySamples[channel];
    previousSecondDelaySamples[channel] = mDelayLine[channel].TimeSpacedComponent_2;
    
    incrementThirdDelaySamples[channel] = (long)(mDelayLine[channel].TimeSpacedComponent_3 - previousThirdDelaySamples[channel]) / (float) numSamples;
    interpolatedThirdDelaySamples[channel] = previousThirdDelaySamples[channel];
    previousThirdDelaySamples[channel] = mDelayLine[channel].TimeSpacedComponent_3;
    
}

//==============================================================================
bool VirtualTubeReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VirtualTubeReverbAudioProcessor::createEditor()
{
    return new VirtualTubeReverbAudioProcessorEditor (*this);
}

//==============================================================================
void VirtualTubeReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualTubeReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr){
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.state = ValueTree::fromXml(*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualTubeReverbAudioProcessor();
}
