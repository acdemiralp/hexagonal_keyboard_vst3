#include "PluginProcessor.h"
#include "PluginEditor.h"

#define _USE_MATH_DEFINES

#include <cstddef>
#include <cstdint>
#include <math.h>

#include "ColourMappers.h"
#include "LayoutRules.h"

HexagonalKeyboardPluginAudioProcessorEditor::HexagonalKeyboardPluginAudioProcessorEditor (HexagonalKeyboardPluginAudioProcessor& processor) 
: AudioProcessorEditor(&processor)
, processor_ (processor)
{
  mode_       .onChange = [&] () { update(); };
  mode_       .setCentrePosition(4  , 4 );
  mode_       .setSize          (180, 16);
  mode_       .addItem          ("harmonic_table", 1);
  mode_       .addItem          ("wicki_hayden"  , 2);
  mode_       .addItem          ("janko"         , 3);
  mode_       .addItem          ("chromatic_b"   , 4);
  mode_       .addItem          ("chromatic_c"   , 5);
  mode_       .setSelectedId    (1);
  mode_       .setAlwaysOnTop   (true);
  addAndMakeVisible             (mode_);                             
          
  transpose_   .onChange = [&] () { update(); };
  transpose_   .setCentrePosition(4  , 24);                           
  transpose_   .setSize          (180, 16);
  transpose_   .addItem          ("no_transpose", 1);
  transpose_   .addItem          ("transpose"   , 2);
  transpose_   .setSelectedId    (1);          
  transpose_   .setAlwaysOnTop   (true);
  addAndMakeVisible             (transpose_);                      
        
  colour_     .onChange = [&] () { update(); };
  colour_     .setCentrePosition(4  , 44);                           
  colour_     .setSize          (180, 16);
  colour_     .addItem          ("Piano colors"              , 1 );
  colour_     .addItem          ("Piano colors (highlight C)", 2 );
  colour_     .addItem          ("HSV: pitch_octave_constant", 3 );
  colour_     .addItem          ("HSV: pitch_constant_octave", 4 );
  colour_     .addItem          ("HSV: octave_pitch_constant", 5 );
  colour_     .addItem          ("HSV: octave_constant_pitch", 6 );
  colour_     .addItem          ("HSV: constant_pitch_octave", 7 );
  colour_     .addItem          ("HSV: constant_octave_pitch", 8 );
  colour_     .addItem          ("RGB: pitch_octave_constant", 9 );
  colour_     .addItem          ("RGB: pitch_constant_octave", 10);
  colour_     .addItem          ("RGB: octave_pitch_constant", 11);
  colour_     .addItem          ("RGB: octave_constant_pitch", 12);
  colour_     .addItem          ("RGB: constant_pitch_octave", 13);
  colour_     .addItem          ("RGB: constant_octave_pitch", 14);
  colour_     .setSelectedId    (1);
  colour_     .setAlwaysOnTop   (true);
  addAndMakeVisible             (colour_);

  update();

  //setResizable(true, true);
  setSize     (1400, 850);
}
HexagonalKeyboardPluginAudioProcessorEditor::~HexagonalKeyboardPluginAudioProcessorEditor()
{

}

void HexagonalKeyboardPluginAudioProcessorEditor::paint  (Graphics& graphics)
{
  graphics.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}
void HexagonalKeyboardPluginAudioProcessorEditor::resized()
{

}

void HexagonalKeyboardPluginAudioProcessorEditor::update ()
{
  keys_.clear();

  const auto lower_left_note = 30;                                 // TODO: Make adjustable.
  const auto dimensions      = std::array<std::size_t, 2> {14, 8}; // TODO: Make adjustable.
  const auto radius          = 48;                                 // TODO: Make adjustable.
  const auto rotation        = transpose_.getSelectedId() == 1 ? 0.0f : 30.0f * M_PI / 180.0f;

  for (std::size_t x = 0; x < dimensions[0]; ++x)
  {
    for (std::size_t y = 0; y < dimensions[1]; ++y)
    {
      auto id = rotation ? std::array<std::size_t, 2>{dimensions[1] - 1 - y, x} : std::array<std::size_t, 2>{x, dimensions[1] - 1 - y};

      std::int32_t midi_number;
      if (mode_.getSelectedId() == 1) midi_number = lower_left_note + LayoutRules::get_note(id, LayoutRules::Ruleset::harmonic_table);
      if (mode_.getSelectedId() == 2) midi_number = lower_left_note + LayoutRules::get_note(id, LayoutRules::Ruleset::wicki_hayden);
      if (mode_.getSelectedId() == 3) midi_number = lower_left_note + LayoutRules::get_note(id, LayoutRules::Ruleset::janko);
      if (mode_.getSelectedId() == 4) midi_number = lower_left_note + LayoutRules::get_note(id, LayoutRules::Ruleset::chromatic_b);
      if (mode_.getSelectedId() == 5) midi_number = lower_left_note + LayoutRules::get_note(id, LayoutRules::Ruleset::chromatic_c);

      if (MidiMessage::getMidiNoteName(midi_number, true, true, 4).contains("-") || midi_number > 127)
        continue;

      Colour colour;
      if (colour_.getSelectedId() == 1 ) colour = ColourMappers::map_piano_keys(midi_number, false);
      if (colour_.getSelectedId() == 2 ) colour = ColourMappers::map_piano_keys(midi_number, true );
      if (colour_.getSelectedId() == 3 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::pitch_octave_constant);
      if (colour_.getSelectedId() == 4 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::pitch_constant_octave);
      if (colour_.getSelectedId() == 5 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::octave_pitch_constant);
      if (colour_.getSelectedId() == 6 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::octave_constant_pitch);
      if (colour_.getSelectedId() == 7 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::constant_pitch_octave);
      if (colour_.getSelectedId() == 8 ) colour = ColourMappers::map_hsv       (midi_number, ColourMappers::Mapping::constant_octave_pitch);
      if (colour_.getSelectedId() == 9 ) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::pitch_octave_constant);
      if (colour_.getSelectedId() == 10) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::pitch_constant_octave);
      if (colour_.getSelectedId() == 11) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::octave_pitch_constant);
      if (colour_.getSelectedId() == 12) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::octave_constant_pitch);
      if (colour_.getSelectedId() == 13) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::constant_pitch_octave);
      if (colour_.getSelectedId() == 14) colour = ColourMappers::map_rgb       (midi_number, ColourMappers::Mapping::constant_octave_pitch);

      std::uint32_t x_position = (rotation ? 1.7 : 2.0) * radius * x;
      std::uint32_t y_position = (rotation ? 2.0 : 1.7) * radius * y;
      if ( rotation && x % 2 == 0) y_position += radius;
      if (!rotation && y % 2 == 0) x_position += radius;

      Path path;
      path.addPolygon(Point<float>(0, 0), 6, radius, rotation);

      auto  name = MidiMessage::getMidiNoteName(midi_number, true, true, 4) + " (" + std::to_string(midi_number) + ")";
      auto& key  = keys_.emplace_back(Key {
        std::make_unique<ShapeButton>(name, colour, colour.contrasting(0.1), colour.contrasting(0.2)),
        //std::make_unique<Label>      (name, std::to_string(x) + " " + std::to_string(dimensions[1] - 1 - y))});
        std::make_unique<Label>      (name, name)});
      
      const auto button = key.button.get();
      button->setCentrePosition       (x_position, y_position);
      button->setSize                 (radius, radius);
      button->setShape                (path, true, true, false);
      button->setTriggeredOnMouseDown (true);
      button->onStateChange = [=] () { processor_.addCommand(midi_number, button->getState() == Button::ButtonState::buttonDown); };
      addAndMakeVisible(button);

      const auto label = key.label.get();
      label ->setSize                 ((rotation ? 2.0 : 1.7) * radius, (rotation ? 1.7 : 2.0) * radius);
      label ->setColour               (Label::textColourId, colour.contrasting(1.0));
      label ->setJustificationType    (Justification::centred);
      label ->setInterceptsMouseClicks(false, false);
      button->addAndMakeVisible       (label);
    }
  }
}
