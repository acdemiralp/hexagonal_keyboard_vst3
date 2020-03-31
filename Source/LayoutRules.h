#pragma once

#include <array>
#include <cstdint>

#include <JuceHeader.h>

namespace LayoutRules
{
enum class Ruleset
{
  harmonic_table,
  wicki_hayden  ,
  janko         ,
  chromatic_b   ,
  chromatic_c
};

std::int32_t get_note(std::array<std::size_t, 2> position, Ruleset ruleset);
};
