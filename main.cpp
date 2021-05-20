#include <math.h>

//------------------------------------------------------------------------------
#include "cwnd_main.h"

int main (int argc, char** args)
{
 CWnd_Main* wnd_main = new CWnd_Main();

 while (!wnd_main->IsQuit())
 {
  wnd_main->Paint();
  wnd_main->Update();
  wnd_main->UpdateTimer();
 }

 delete wnd_main;

 return 0;
}

