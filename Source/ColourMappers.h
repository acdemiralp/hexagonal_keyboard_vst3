#pragma once

#include <array>
#include <cstdint>

#include <JuceHeader.h>

namespace ColourMappers
{
enum class Mapping
{
  pitch_octave_constant,
  pitch_constant_octave,
  octave_pitch_constant,
  octave_constant_pitch,
  constant_pitch_octave,
  constant_octave_pitch
};

std::array <std::uint8_t, 2> extract_pitch_octave(std::uint8_t midi_note);

Colour map_piano_keys(std::uint8_t midi_note, bool highlight_c = false);
Colour map_hsv       (std::uint8_t midi_note, Mapping mapping, float        constant = 0.75f);
Colour map_rgb       (std::uint8_t midi_note, Mapping mapping, std::uint8_t constant = 127  );
};
