#include "ColourMappers.h"

std::array<std::uint8_t, 2> ColourMappers::extract_pitch_octave         (std::uint8_t midi_note)
{
  std::array<std::uint8_t, 2> result;

  auto name = MidiMessage::getMidiNoteName(midi_note, true, true, 4);
  result[0] = midi_note % 12;
  result[1] = (name.contains("#") ? name[2] : name[1]) - '0';

  return result;
}

Colour ColourMappers::map_piano_keys(std::uint8_t midi_note, bool highlight_c)
{
  auto name = MidiMessage::getMidiNoteName(midi_note, true, false, 4);
  if (name == "C" && highlight_c) return Colours::red  ;
  if (name.contains("#"))         return Colours::black;
  return Colours::white;
}
Colour ColourMappers::map_hsv       (std::uint8_t midi_note, Mapping mapping, float        constant)
{
  const auto pitch_octave = extract_pitch_octave(midi_note);
  const auto pitch        = float(pitch_octave[0]) / 12.0f;
  const auto octave       = float(pitch_octave[1]) / 9.0f ;
  if (mapping == Mapping::pitch_octave_constant) return Colour(pitch   , 1.0 - octave, constant, 1.0f);
  if (mapping == Mapping::pitch_constant_octave) return Colour(pitch   , constant    , octave  , 1.0f);
  if (mapping == Mapping::octave_pitch_constant) return Colour(octave  , pitch       , constant, 1.0f);
  if (mapping == Mapping::octave_constant_pitch) return Colour(octave  , constant    , pitch   , 1.0f);
  if (mapping == Mapping::constant_pitch_octave) return Colour(constant, pitch       , octave  , 1.0f);
                                                 return Colour(constant, octave      , pitch   , 1.0f);
}
Colour ColourMappers::map_rgb       (std::uint8_t midi_note, Mapping mapping, std::uint8_t constant)
{
  const auto pitch_octave = extract_pitch_octave(midi_note);
  const auto pitch        = std::uint8_t(float(pitch_octave[0]) / 12.0f * 255.0f);
  const auto octave       = std::uint8_t(float(pitch_octave[1]) / 9.0f  * 255.0f);
  if (mapping == Mapping::pitch_octave_constant) return Colour(pitch   , octave  , constant);
  if (mapping == Mapping::pitch_constant_octave) return Colour(pitch   , constant, octave  );
  if (mapping == Mapping::octave_pitch_constant) return Colour(octave  , pitch   , constant);
  if (mapping == Mapping::octave_constant_pitch) return Colour(octave  , constant, pitch   );
  if (mapping == Mapping::constant_pitch_octave) return Colour(constant, pitch   , octave  );
                                                 return Colour(constant, octave  , pitch   );
}
