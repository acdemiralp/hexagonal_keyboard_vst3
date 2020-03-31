#pragma once

#include <memory>
#include <vector>

#include <JuceHeader.h>

#include "PluginProcessor.h"

class HexagonalKeyboardPluginAudioProcessorEditor : public AudioProcessorEditor
{
public:
  struct Key
  {
    std::unique_ptr<ShapeButton> button;
    std::unique_ptr<Label>       label ;
  };

  explicit HexagonalKeyboardPluginAudioProcessorEditor(HexagonalKeyboardPluginAudioProcessor& processor);
          ~HexagonalKeyboardPluginAudioProcessorEditor();

  void paint  (Graphics& graphics) override;
  void resized()                   override;

  void update ();

private:
  HexagonalKeyboardPluginAudioProcessor& processor_;
  std::vector<Key>                       keys_     ;
  ComboBox                               mode_     ;
  ComboBox                               transpose_;
  ComboBox                               colour_   ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HexagonalKeyboardPluginAudioProcessorEditor)
};
