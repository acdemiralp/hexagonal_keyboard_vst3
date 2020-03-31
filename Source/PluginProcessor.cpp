#include "PluginProcessor.h"
#include "PluginEditor.h"

HexagonalKeyboardPluginAudioProcessor::HexagonalKeyboardPluginAudioProcessor ()
#ifndef JucePlugin_PreferredChannelConfigurations
  : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
    .withInput ("Input" , AudioChannelSet::stereo(), true)
#endif
    .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
  )
#endif
{

}
HexagonalKeyboardPluginAudioProcessor::~HexagonalKeyboardPluginAudioProcessor()
{

}

const String          HexagonalKeyboardPluginAudioProcessor::getName               () const
{
  return JucePlugin_Name;
}
bool                  HexagonalKeyboardPluginAudioProcessor::acceptsMidi           () const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}
bool                  HexagonalKeyboardPluginAudioProcessor::producesMidi          () const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}
bool                  HexagonalKeyboardPluginAudioProcessor::isMidiEffect          () const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}
double                HexagonalKeyboardPluginAudioProcessor::getTailLengthSeconds  () const
{
  return 0.0;
}
                                                                                 
bool                  HexagonalKeyboardPluginAudioProcessor::hasEditor             () const
{
  return true;
}
AudioProcessorEditor* HexagonalKeyboardPluginAudioProcessor::createEditor          ()
{
  return new HexagonalKeyboardPluginAudioProcessorEditor(*this);
}
                                                                                 
void                  HexagonalKeyboardPluginAudioProcessor::getStateInformation   (MemoryBlock& data)
{

}
void                  HexagonalKeyboardPluginAudioProcessor::setStateInformation   (const void*  data, std::int32_t size)
{

}
                                                                                 
std::int32_t          HexagonalKeyboardPluginAudioProcessor::getNumPrograms        ()
{
  return 1;
}
std::int32_t          HexagonalKeyboardPluginAudioProcessor::getCurrentProgram     ()
{
  return 0;
}
void                  HexagonalKeyboardPluginAudioProcessor::setCurrentProgram     (std::int32_t index)
{

}
const String          HexagonalKeyboardPluginAudioProcessor::getProgramName        (std::int32_t index)
{
  return {};
}
void                  HexagonalKeyboardPluginAudioProcessor::changeProgramName     (std::int32_t index, const String& name)
{

}

void                  HexagonalKeyboardPluginAudioProcessor::prepareToPlay         (double sample_rate, std::int32_t samples_per_block)
{

}
void                  HexagonalKeyboardPluginAudioProcessor::releaseResources      ()
{

}

void                  HexagonalKeyboardPluginAudioProcessor::processBlock          (AudioBuffer<float>& buffer, MidiBuffer& midi)
{
  MidiBuffer midi_buffer;
  auto sample_number = 0;
  for (auto& command : command_queue_)
    if (command.second)
      midi_buffer.addEvent(MidiMessage::noteOn (1, command.first, float(1.0)), sample_number++); // TODO: Enable velocity.
    else
      midi_buffer.addEvent(MidiMessage::noteOff(1, command.first), sample_number++);
  buffer.clear();
  midi  .swapWith(midi_buffer);
  command_queue_.clear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool                  HexagonalKeyboardPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;
#else
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

#if ! JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void                  HexagonalKeyboardPluginAudioProcessor::addCommand            (std::uint8_t note, bool down)
{
  command_queue_.push_back({note, down});
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new HexagonalKeyboardPluginAudioProcessor();
}
