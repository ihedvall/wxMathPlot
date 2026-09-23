/*
* Copyright 2026 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include "mpinfoxtracker.h"

#include <wx/dcclient.h>

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
  namespace MathPlot {
#endif // MP_ENABLE_NAMESPACE

int mpInfoXTracker::GetLegendHitRegion(wxPoint) {
  return -1;
}

void mpInfoXTracker::DrawContent(wxDC &dc, mpWindow &w) {
  const double mouseXValue = w.p2x(w.GetMousePosition().x);
  DrawXPosition(mouseXValue, dc, w);
  FireXEvent(mouseXValue);
}

void mpInfoXTracker::SetXValue(double x_value) const {
  if (m_win != nullptr) {
    wxClientDC dc(m_win);
    DrawXPosition(x_value, dc, *m_win);
  }
}

void mpInfoXTracker::AddXEventFunction(const XEventFunction &function) {
  m_event_list.emplace_back(function);
}

void mpInfoXTracker::DoPlot(wxDC &dc, mpWindow &w) {
  DrawContent(dc, w);
}

void mpInfoXTracker::DrawXPosition(double x_value, wxDC &dc, mpWindow &win) {
  const auto& scheme = mpColourScheme::Instance();
  const mpRect bound = win.GetPlotBoundaries(true);

  // Draw a circle on the series where the vertical line cross it
  size_t y_count = 0;
  for (unsigned int p = 0; p < win.CountAllLayers(); ++p)  {
    mpLayer* layer = win.GetLayer(static_cast<int>(p));
    if (layer == nullptr || layer->GetLayerType() != mpLAYER_PLOT) {
      continue;
    }
    auto* function = dynamic_cast<mpFunction*>(layer);
    if(function == nullptr) {
      continue;
    }
    if (const std::optional<double> value = function->GetSeriesValue(x_value);
       value.has_value()) {
      const double valueScaled = win.IsLogYaxis(function->GetYAxisID()) ?
        log10(value.value()) : value.value();
      const wxCoord yCoord = win.y2p(valueScaled, function->GetYAxisID());
      if (yCoord >= bound.top && yCoord <= bound.bottom) {
        dc.SetPen(wxPen(scheme.GetDefaultFgColour(), 1));
        dc.SetBrush(wxBrush(function->GetPen().GetColour()));
        dc.DrawCircle(win.GetMousePosition().x, win.y2p(valueScaled,
          function->GetYAxisID()), 4);
        ++y_count;
      }
    }
  }
  if (y_count > 0) {
    // Draw a vertical line to indicate location of the shown values (where the line cross a series)
    dc.SetPen(scheme.GetAxisColour());
    const wxCoord x_pos = win.x2p(x_value);
    dc.DrawLine(x_pos, bound.top, x_pos, bound.bottom);
  }
}

void mpInfoXTracker::FireXEvent(double x_value) const {
  for (auto& function : m_event_list) {
    function(x_value);
  }
}

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
}// namespace MathPlot
#endif // MP_ENABLE_NAMESPACE