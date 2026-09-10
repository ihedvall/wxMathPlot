/*
 * Copyright 2026 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include "mpcolourscheme.h"
#include <wx/settings.h>

mpColourScheme mpColourScheme::m_instance;

void mpColourScheme::SetLightMode() {
  m_name = "Light Mode";
  m_colour_scheme = mp_Colour_Scheme::LightMode;
  m_default_fg_colour = *wxBLACK;
  m_default_bg_colour = *wxWHITE;
  m_info_bg_colour = *wxLIGHT_GREY;
  m_axis_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  m_grid_colour = *wxLIGHT_GREY;
  m_bar_bg_colour = *wxLIGHT_GREY;

  m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE, *wxBLACK, *wxYELLOW, *wxCYAN
   };
  m_colour_names = {
    "Green", "Red", "Blue", "Black", "Yellow", "Cyan"
  };
}

void mpColourScheme::SetDarkMode() {
  m_name = "Dark Mode";
  m_colour_scheme = mp_Colour_Scheme::DarkMode;
  m_default_fg_colour = *wxWHITE;
  m_default_bg_colour = *wxBLACK;
  m_info_bg_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  m_axis_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_LIGHTGREY);
  m_grid_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  m_bar_bg_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);

  m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE, *wxWHITE, *wxYELLOW, *wxCYAN
   };
  m_colour_names = {
    "Green", "Red", "Blue", "White", "Yellow", "Cyan"
  };
}

void mpColourScheme::SetSystemMode() {
  m_name = "System Mode";
  m_colour_scheme = mp_Colour_Scheme::SystemMode;
  m_default_fg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
  m_default_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
  m_info_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_DESKTOP);;
  m_axis_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT );;
  m_grid_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME);;
  m_bar_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME);;

  m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE,
    wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT ), *wxYELLOW, *wxCYAN
   };
  m_colour_names = {
    "Green", "Red", "Blue", "Gray", "Yellow", "Cyan"
  };
}
void mpColourScheme::SetColourScheme(mp_Colour_Scheme scheme) {
  switch (scheme) {
  case mp_Colour_Scheme::SystemMode:
    SetSystemMode();
    break;

  case mp_Colour_Scheme::LightMode:
    SetLightMode();
    break;

  case mp_Colour_Scheme::DarkMode:
    SetDarkMode();
    break;

  default:
    break;
  }
}

wxColour mpColourScheme::GetIndexColour(size_t index) const {
  return index < m_line_colours.size() ? m_line_colours[index]
                                       : m_line_colours[0];
}

std::string_view mpColourScheme::GetIndexColourName(size_t index) const {
   return index < m_colour_names.size() ? m_colour_names[index] : m_colour_names[0];
}

wxPen mpColourScheme::GetLinePen(size_t line_index) const {
  constexpr std::array<wxPenStyle, 4> line_styles = {
    wxPENSTYLE_SOLID, wxPENSTYLE_DOT,
    wxPENSTYLE_LONG_DASH, wxPENSTYLE_SHORT_DASH
  };
  const size_t max_colour = m_line_colours.size();
  const size_t max_style = line_styles.size();
  const size_t line_colour = line_index % max_colour;
  const size_t style_index = (line_index / max_colour) % max_style;
  const int line_width = static_cast<int>(line_index / max_colour / max_style);
  wxPen pen(m_line_colours[line_colour], line_width, line_styles[style_index]);
  return pen;
}