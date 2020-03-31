#include "LayoutRules.h"

std::int32_t LayoutRules::get_note(std::array<std::size_t, 2> position, Ruleset ruleset)
{
  auto note = 0;

  if (ruleset == Ruleset::harmonic_table)
  {
    for (auto i = 0; i < position[1]; ++i)
      note += i % 2 == 0 ? 4 : -3;
    note += 7 * position[0];
  }
  else if (ruleset == Ruleset::wicki_hayden)
  {
    for (auto i = 0; i < position[1]; ++i)
      note += i % 2 == 0 ? 7 : 5;
    note += 2 * position[0];
  }
  else if (ruleset == Ruleset::janko)
  {
    for (auto i = 0; i < position[1]; ++i)
      note += i % 2 == 0 ? 1 : -1;
    note += 2 * position[0];
  }
  else if (ruleset == Ruleset::chromatic_b)
  {
    for (auto i = 0; i < position[1]; ++i)
      note += i % 2 == 0 ? 2 : -1;
    note += 3 * position[0];
  }
  else if (ruleset == Ruleset::chromatic_c)
  {
    for (auto i = 0; i < position[1]; ++i)
      note += i % 2 == 0 ? 1 : -2;
    note += 3 * position[0];
  }

  return note;
}
