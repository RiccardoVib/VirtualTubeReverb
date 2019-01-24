/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VirtualTubeReverbAudioProcessorEditor  : public AudioProcessorEditor,
                                               private Slider::Listener
{
public:
    VirtualTubeReverbAudioProcessorEditor (VirtualTubeReverbAudioProcessor&);
    ~VirtualTubeReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override;
    
inline std::string createTextForDelays(float value){
        
        std::string valueText = std::to_string(value);
        valueText.erase(5);
        valueText.append(" ms");
        return valueText;
    }
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
private:
    
    VirtualTubeReverbAudioProcessor& processor;

    Label panLabel_, tubeSizeLabel_, dryWetMixLabel_;
    
    Label decayLabel_, decayVelLabel_, ampLabel_, ampRefLabel_;
    
    Label firstRefLabel_, secondRefLabel_, thirdRefLabel_;
    
    Slider panSlider_, tubeSizeSlider_, dryWetMixSlider_;
    
    Slider decaySlider_, decayVelSlider_, ampSlider_, ampRefSlider_;
    
    Slider modeSlider_, firstRefSlider_, secondRefSlider_, thirdRefSlider_;
    
    TextEditor leftText_, rightText_, modeText_, ampText_;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> panAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeSizeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryWetMixAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVelAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> ampAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> ampRefAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> modeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> firstRefAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> secondRefAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> thirdRefAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeReverbAudioProcessorEditor)
};
