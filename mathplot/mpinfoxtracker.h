/*
* Copyright 2026 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "mathplot.h"

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
namespace MathPlot {
#endif // MP_ENABLE_NAMESPACE

using XEventFunction = std::function<void(double x_value)>;

std::function<void(double x_value)> XEvent(double x_value);
class mpInfoXTracker : public mpInfoLegend {
 public:
  mpInfoXTracker() = default;
  ~mpInfoXTracker() override = default;

  int GetLegendHitRegion(wxPoint mousePos) override;
  void DrawContent(wxDC &dc, mpWindow &w) override;
  void SetXValue(double x_value) const;
  void AddXEventFunction(const XEventFunction &function);
protected:
  void DoPlot(wxDC &dc, mpWindow &w) override;
  static void DrawXPosition(double x_value, wxDC &dc, mpWindow &w);
private:
  std::deque<XEventFunction> m_event_list;
  void FireXEvent(double x_value) const;
};

#if defined(MP_ENABLE_NAMESPACE) || defined(ENABLE_MP_NAMESPACE)
} // namespace MathPlot
#endif // MP_ENABLE_NAMESPACE
