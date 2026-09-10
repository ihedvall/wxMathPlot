/***************************************************************
 * Name:      MathPlotDemoApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lionel ()
 * Created:   2020-11-26
 * Copyright: Lionel ()
 * License:
 **************************************************************/

#include "MathPlotDemoApp.h"
#include <locale>

#include "MathPlotDemoMain.h"
#include <wx/image.h>

IMPLEMENT_APP(MathPlotDemoApp); // NOLINT(*-pro-type-static-cast-downcast)

bool MathPlotDemoApp::OnInit()
{
  std::locale::global(std::locale(""));

#if wxCHECK_VERSION(3,3,0)
  SetAppearance(Appearance::System);
  mpColourScheme::Instance().SetColourScheme(mp_Colour_Scheme::SystemMode);
#endif
  bool wxsOK = true;
  wxInitAllImageHandlers();
  if ( wxsOK )
  {
    auto* Frame = new MathPlotDemoFrame(nullptr);
    Frame->Show();
    SetTopWindow(Frame);
  }

  return wxsOK;

}
