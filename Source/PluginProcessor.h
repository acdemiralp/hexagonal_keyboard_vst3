#pragma once

#include <JuceHeader.h>

class HexagonalKeyboardPluginAudioProcessor : public AudioProcessor
{
public:
  HexagonalKeyboardPluginAudioProcessor();
 ~HexagonalKeyboardPluginAudioProcessor();
 
  const String          getName               () const override;
  bool                  acceptsMidi           () const override;
  bool                  producesMidi          () const override;
  bool                  isMidiEffect          () const override;
  double                getTailLengthSeconds  () const override;
  
  bool                  hasEditor             () const override;
  AudioProcessorEditor* createEditor          () override;
  
  void                  getStateInformation   (MemoryBlock& data) override;
  void                  setStateInformation   (const void*  data, std::int32_t size) override;

  std::int32_t          getNumPrograms        () override;
  std::int32_t          getCurrentProgram     () override;
  void                  setCurrentProgram     (std::int32_t index) override;
  const String          getProgramName        (std::int32_t index) override;
  void                  changeProgramName     (std::int32_t index, const String& name) override;
  
  void                  prepareToPlay         (double sample_rate, std::int32_t samples_per_block) override;
  void                  releaseResources      () override;

  void                  processBlock          (AudioBuffer<float>&, MidiBuffer&) override;
  
#ifndef JucePlugin_PreferredChannelConfigurations
  bool                  isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

  void                  addCommand            (std::uint8_t note, bool down);

private:
  std::vector<std::pair<std::uint8_t, bool>> command_queue_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HexagonalKeyboardPluginAudioProcessor)
};
