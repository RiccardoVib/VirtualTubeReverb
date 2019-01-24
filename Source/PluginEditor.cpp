/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualTubeReverbAudioProcessorEditor::VirtualTubeReverbAudioProcessorEditor (VirtualTubeReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
        panLabel_("", "Stereo Pan:"), tubeSizeLabel_("", "Tube Size (cm):"), dryWetMixLabel_("", "Dry/Wet:"),
        decayLabel_("", "Decay:"), decayVelLabel_("", "Decay Velocity:"), ampLabel_("", "Main:"), ampRefLabel_("", "Reflections:"),
        firstRefLabel_("", "First Reflection:"),
        secondRefLabel_("", "Second Reflection:"), thirdRefLabel_("", "Third Reflection:")
{
    
    setSize (800, 350);
    
    panAttachment = new SliderAttachment(processor.parameters, "pan_", panSlider_);
    tubeSizeAttachment = new SliderAttachment(processor.parameters, "tubeSize_", tubeSizeSlider_);
    dryWetMixAttachment = new SliderAttachment(processor.parameters, "dryWetMix_", dryWetMixSlider_);
    decayAttachment = new SliderAttachment(processor.parameters, "decay_", decaySlider_);
    decayVelAttachment = new SliderAttachment(processor.parameters, "decayVel_", decayVelSlider_);
    ampAttachment = new SliderAttachment(processor.parameters, "amp_", ampSlider_);
    ampRefAttachment = new SliderAttachment(processor.parameters, "ampRef_", ampRefSlider_);
    modeAttachment = new SliderAttachment(processor.parameters, "mode_", modeSlider_);
    firstRefAttachment = new SliderAttachment(processor.parameters, "firstRef_", firstRefSlider_);
    secondRefAttachment = new SliderAttachment(processor.parameters, "secondRef_", secondRefSlider_);
    thirdRefAttachment = new SliderAttachment(processor.parameters, "thirdRef_", thirdRefSlider_);
    
    leftText_.setReadOnly(true);
    leftText_.setText("L");
    addAndMakeVisible (&leftText_);
    
    rightText_.setReadOnly(true);
    rightText_.setText("R");
    addAndMakeVisible (&rightText_);
    
    modeText_.setReadOnly(true);
    if(*processor.mode_ == 0)
    {
       modeText_.setText("Mode: Olsen");
    }
    else
    {
        modeText_.setText("Mode: Customized");
    }
    addAndMakeVisible (&modeText_);
    
    ampText_.setReadOnly(true);
    ampText_.setText("Amplification");
    addAndMakeVisible (&ampText_);
    
    panSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    panSlider_.setRange (0.0f, 1.0f, 0.01f);
    panSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    panSlider_.setPopupDisplayEnabled (true, false, this);
    panSlider_.setDoubleClickReturnValue(true, 0.5f);
    addAndMakeVisible (&panSlider_);
    panSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    tubeSizeSlider_.setDoubleClickReturnValue(true, 1.2);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider_.setRange (0.0f, 1.0f, 0.01f);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0f);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    decaySlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decaySlider_.setRange (0.1f, 0.9f, 0.01f);
    decaySlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    decaySlider_.setPopupDisplayEnabled (true, false, this);
    decaySlider_.setTextValueSuffix(" ");
    decaySlider_.setDoubleClickReturnValue(true, 0.75f);
    addAndMakeVisible (&decaySlider_);
    decaySlider_.addListener(this);
    
    decayVelSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decayVelSlider_.setRange (1.0f, 4.0f, 0.01f);
    decayVelSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    decayVelSlider_.setPopupDisplayEnabled (true, false, this);
    decayVelSlider_.setTextValueSuffix(" ");
    decayVelSlider_.setDoubleClickReturnValue(true, 1.0f);
    addAndMakeVisible (&decayVelSlider_);
    decayVelSlider_.addListener(this);
    
    ampSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ampSlider_.setRange (0.0f, 4.0f, 0.01f);
    ampSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ampSlider_.setPopupDisplayEnabled (true, false, this);
    ampSlider_.setTextValueSuffix(" ");
    ampSlider_.setDoubleClickReturnValue(true, 1.0f);
    addAndMakeVisible (&ampSlider_);
    ampSlider_.addListener(this);
    
    
    ampRefSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ampRefSlider_.setRange (0.0f, 4.0f, 0.01f);
    ampRefSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ampRefSlider_.setPopupDisplayEnabled (true, false, this);
    ampRefSlider_.setTextValueSuffix(" ");
    ampRefSlider_.setDoubleClickReturnValue(true, 0.0f);
    addAndMakeVisible (&ampRefSlider_);
    ampRefSlider_.addListener(this);
    
    modeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    modeSlider_.setRange (0.0f, 1.0f, 1.0f);
    modeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modeSlider_.setPopupDisplayEnabled (false, false, this);
    addAndMakeVisible (&modeSlider_);
    modeSlider_.addListener(this);
    
    firstRefSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    firstRefSlider_.setRange (1.0f, 28.0f, 0.01f);
    firstRefSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    firstRefSlider_.setPopupDisplayEnabled (true, false, this);
    firstRefSlider_.setTextValueSuffix(" ms");
    addAndMakeVisible (&firstRefSlider_);
    firstRefSlider_.addListener(this);
    
    secondRefSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    secondRefSlider_.setRange (1.0f, 28.0f, 0.01f);
    secondRefSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    secondRefSlider_.setPopupDisplayEnabled (true, false, this);
    secondRefSlider_.setTextValueSuffix(" ms");
    addAndMakeVisible (&secondRefSlider_);
    secondRefSlider_.addListener(this);
    
    thirdRefSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    thirdRefSlider_.setRange (1.0f, 28.0f, 0.01f);
    thirdRefSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    thirdRefSlider_.setPopupDisplayEnabled (true, false, this);
    thirdRefSlider_.setTextValueSuffix(" ms");
    addAndMakeVisible (&thirdRefSlider_);
    thirdRefSlider_.addListener(this);
    
    panLabel_.attachToComponent(&panSlider_, false);
    panLabel_.setFont(Font (14.0f));
    
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (14.0f));
    
    dryWetMixLabel_.attachToComponent(&dryWetMixSlider_, false);
    dryWetMixLabel_.setFont(Font (14.0f));
    
    decayLabel_.attachToComponent(&decaySlider_, false);
    decayLabel_.setFont(Font (14.0f));
    
    decayVelLabel_.attachToComponent(&decayVelSlider_, false);
    decayVelLabel_.setFont(Font (14.0f));
    
    ampLabel_.attachToComponent(&ampSlider_, false);
    ampLabel_.setFont(Font (14.0f));
    
    ampRefLabel_.attachToComponent(&ampRefSlider_, false);
    ampRefLabel_.setFont(Font (14.0f));
    
    firstRefLabel_.attachToComponent(&firstRefSlider_, false);
    firstRefLabel_.setFont(Font (14.0f));

    secondRefLabel_.attachToComponent(&secondRefSlider_, false);
    secondRefLabel_.setFont(Font (14.0f));
    
    thirdRefLabel_.attachToComponent(&thirdRefSlider_, false);
    thirdRefLabel_.setFont(Font (14.0f));
}

VirtualTubeReverbAudioProcessorEditor::~VirtualTubeReverbAudioProcessorEditor()
{
}

void VirtualTubeReverbAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &panSlider_)
    {
        *processor.pan_ = panSlider_.getValue();
    }
    else if (slider == &dryWetMixSlider_)
    {
        *processor.dryWetMix_ = dryWetMixSlider_.getValue();
    }
    else if (slider == &tubeSizeSlider_)
    {
        *processor.tubeSize_ = tubeSizeSlider_.getValue();
        
        processor.rad = floor(*processor.tubeSize_*10 - 12);
    }
    else if (slider == &decaySlider_)
    {
        *processor.decay_ = decaySlider_.getValue();
    }
    else if (slider == &decayVelSlider_)
    {
        *processor.decayVel_ = decayVelSlider_.getValue();
    }
    else if (slider == &ampSlider_)
    {
        *processor.amp_ = ampSlider_.getValue();
    }
    else if (slider == &ampRefSlider_)
    {
        *processor.ampRef_ = ampRefSlider_.getValue();
    }
    else if (slider == &modeSlider_)
    {
        *processor.mode_ = modeSlider_.getValue();
        
        if(*processor.mode_ == 0)
        {
            modeText_.setText("Mode: Olsen");
            firstRefSlider_.setValue(23);
            secondRefSlider_.setValue(27);
            thirdRefSlider_.setValue(19);
        }
        else if(*processor.mode_ == 1)
        {
            modeText_.setText("Mode: Customized");
        }
    }
    else if (slider == &firstRefSlider_)
    {
        *processor.firstRef_ = firstRefSlider_.getValue();
    }
    else if (slider == &secondRefSlider_)
    {
        *processor.secondRef_ = secondRefSlider_.getValue();
    }
    else if (slider == &firstRefSlider_)
    {
        *processor.secondRef_ = secondRefSlider_.getValue();
    }
}

//==============================================================================
void VirtualTubeReverbAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    g.setColour (Colours::white);
    g.setFont(15.0f);
}

void VirtualTubeReverbAudioProcessorEditor::resized()
{
    //Texts
    
    leftText_.setBounds (690, 90, 18, 18);
    
    rightText_.setBounds(770, 90, 18, 18);
    
    modeText_.setBounds(40, 170, 120, 20);
    
    //feedbackText_.setBounds(550, 140, 70, 20);
    
    ampText_.setBounds(550, 5, 90, 20);
    
    //Sliders
    
    modeSlider_.setBounds (30, 190, 80, 100);
    
    firstRefSlider_.setBounds (30, 50, 80, 100);
    
    secondRefSlider_.setBounds (130, 50, 80, 100);
    
    thirdRefSlider_.setBounds (230, 50, 80, 100);
    
    panSlider_.setBounds (700, 50, 80, 100);
    
    dryWetMixSlider_.setBounds (700, 190, 80, 100);
    
    tubeSizeSlider_.setBounds (300, 190, 80, 100);
 
    decaySlider_.setBounds (600, 190, 80, 100);
    
    decayVelSlider_.setBounds (500, 190, 80, 100);
    
    ampSlider_.setBounds (600, 50, 80, 100);
    
    ampRefSlider_.setBounds (500, 50, 80, 100);
}