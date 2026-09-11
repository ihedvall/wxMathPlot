/*
 * Copyright 2026 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <array>
#include <string_view>

#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/brush.h>
#include <wx/pen.h>

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
  namespace MathPlot {
#endif // MP_ENABLE_NAMESPACE

enum class mp_Colour_Scheme : int {
 SystemMode = 0,
 LightMode,
 DarkMode,
 NoirMode,
 CaviarMode,
 CustomMode
};

class mpColourScheme {
public:

 static mpColourScheme& Instance();


 void SetName(std::string name) { m_name = std::move(name); }
 [[nodiscard]] const std::string& GetName() const {
  return m_name;
 };

 static void SetColourScheme(mp_Colour_Scheme scheme);
 [[nodiscard]] mp_Colour_Scheme GetColourScheme() const {
  return m_colour_scheme;
 }

 [[nodiscard]] wxColor GetDefaultFgColour() const {
  return m_default_fg_colour;
 }

 [[nodiscard]] wxColor GetDefaultBgColour() const {
  return m_default_bg_colour;
 }

 [[nodiscard]] wxColour GetInfoBgColour() const {  return m_info_bg_colour; }

 [[nodiscard]] wxColour GetAxisColour() const { return m_axis_colour; }
 [[nodiscard]] wxColour GetGridColour() const { return m_grid_colour; }
 [[nodiscard]] wxColour GetBarBgColour() const {
  return m_bar_bg_colour;
 }

 [[nodiscard]] wxColour GetIndexColour(size_t index) const;
 [[nodiscard]] std::string_view GetIndexColourName(size_t index) const;

 [[nodiscard]] wxPen GetLinePen(size_t line_index) const;

protected:
 std::string m_name = "Light Mode";
 mp_Colour_Scheme m_colour_scheme = mp_Colour_Scheme::LightMode;

 wxColour m_default_fg_colour = *wxBLACK;
 wxColour m_default_bg_colour = *wxWHITE;
 wxColour m_info_bg_colour = *wxLIGHT_GREY;
 wxColour m_axis_colour = *wxStockGDI::GetColour(wxStockGDI::COLOUR_GREY);
 wxColour m_grid_colour = *wxLIGHT_GREY;
 wxColour m_bar_bg_colour = *wxLIGHT_GREY;

 std::array<wxColour, 6> m_line_colours = {
  *wxGREEN, *wxRED, *wxBLUE, *wxBLACK, *wxYELLOW, *wxCYAN
 };
 std::array<std::string_view, 6> m_colour_names = {
  "Green", "Red", "Blue", "Black", "Yellow", "Cyan"
};

private:

 static void SetLightMode();
 static void SetDarkMode();
 static void SetSystemMode();
 static void SetNoirMode();
 static void SetCaviarMode();
};

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
  }// namespace MathPlot
#endif // MP_ENABLE_NAMESPACE
