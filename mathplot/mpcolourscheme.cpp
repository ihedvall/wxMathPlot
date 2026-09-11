/*
 * Copyright 2026 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include "mpcolourscheme.h"

#include <wx/settings.h>

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
  namespace MathPlot {
#endif // MP_ENABLE_NAMESPACE

mpColourScheme& mpColourScheme::Instance() {
  static mpColourScheme instance;
  return instance; 
}

void mpColourScheme::SetLightMode() {
  auto& scheme = mpColourScheme::Instance();
  scheme.m_name = "Light Mode";
  scheme.m_colour_scheme = mp_Colour_Scheme::LightMode;
  scheme.m_default_fg_colour = *wxBLACK;
  scheme.m_default_bg_colour = *wxWHITE;
  scheme.m_info_bg_colour = *wxLIGHT_GREY;
  scheme.m_axis_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  scheme.m_grid_colour = *wxLIGHT_GREY;
  scheme.m_bar_bg_colour = *wxLIGHT_GREY;

  scheme.m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE, *wxBLACK, *wxYELLOW, *wxCYAN
   };
  scheme.m_colour_names = {
    "Green", "Red", "Blue", "Black", "Yellow", "Cyan"
  };
}

void mpColourScheme::SetDarkMode() {
  auto& scheme = mpColourScheme::Instance();
  scheme.m_name = "Dark Mode";
  scheme.m_colour_scheme = mp_Colour_Scheme::DarkMode;
  scheme.m_default_fg_colour = *wxWHITE;
  scheme.m_default_bg_colour = *wxBLACK;
  scheme.m_info_bg_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  scheme.m_axis_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_LIGHTGREY);
  scheme.m_grid_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  scheme.m_bar_bg_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);

  scheme.m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE, *wxWHITE, *wxYELLOW, *wxCYAN
   };
  scheme.m_colour_names = {
    "Green", "Red", "Blue", "White", "Yellow", "Cyan"
  };
}

void mpColourScheme::SetSystemMode() {
  auto& scheme = mpColourScheme::Instance();
  scheme.m_name = "System Mode";
  scheme.m_colour_scheme = mp_Colour_Scheme::SystemMode;
  scheme.m_default_fg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
  scheme.m_default_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
  scheme.m_info_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_DESKTOP);
  scheme.m_axis_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT );
  scheme.m_grid_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME);
  scheme.m_bar_bg_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME);

  scheme.m_line_colours = {
    *wxGREEN, *wxRED, *wxBLUE,
    wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT ), *wxYELLOW, *wxCYAN
   };
  scheme.m_colour_names = {
    "Green", "Red", "Blue", "Gray", "Yellow", "Cyan"
  };
}

void mpColourScheme::SetNoirMode() {
  auto& scheme = mpColourScheme::Instance();
  scheme.m_name = "Noir Mode";
  scheme.m_colour_scheme = mp_Colour_Scheme::NoirMode;
  scheme.m_default_fg_colour = *wxWHITE;;
  scheme.m_default_bg_colour = wxColour(77,77,77);
  scheme.m_info_bg_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
  scheme.m_axis_colour = wxColour(179,179,179);
  scheme.m_grid_colour = wxColour(179,179,179);
  scheme.m_bar_bg_colour = wxColour(179,179,179);

  scheme.m_line_colours = {
    *wxYELLOW, *wxRED, *wxGREEN,
    wxColour(255,128,0), wxColour(255,0,128),
    *wxWHITE
   };
  scheme.m_colour_names = {
    "Yellow", "Red", "Green", "Orange", "Pink", "White"
  };
}

void mpColourScheme::SetCaviarMode() {
  auto& scheme = mpColourScheme::Instance();
  scheme.m_name = "Caviar Mode";
  scheme.m_colour_scheme = mp_Colour_Scheme::NoirMode;
  scheme.m_default_fg_colour = wxColour(204,204,255);;
  scheme.m_default_bg_colour = wxColour(61,61,102);
  scheme.m_info_bg_colour = wxColour(70,70,99);
  scheme.m_axis_colour = wxColour(179,179,179);
  scheme.m_grid_colour = wxColour(179,179,179);
  scheme.m_bar_bg_colour = wxColour(179,179,179);

  scheme.m_line_colours = {
    *wxYELLOW, *wxRED, *wxGREEN,
    wxColour(255,128,0), wxColour(255,0,128),
    *wxWHITE
   };
  scheme.m_colour_names = {
    "Yellow", "Red", "Green", "Orange", "Pink", "White"
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

  case mp_Colour_Scheme::NoirMode:
    SetNoirMode();
    break;

  case mp_Colour_Scheme::CaviarMode:
    SetCaviarMode();
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

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
  }// namespace MathPlot
#endif // MP_ENABLE_NAMESPACE