#ifndef C_WND_MAIN_H
#define C_WND_MAIN_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "csgl.h"
#include <memory>

class CWnd_Main
{
 protected:
  //-Переменные класса-------------------------------------------------------
  CSGL cSGL;
  float angle;
  std::unique_ptr<uint8_t[]> Texture_Ptr;
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* window_surface;
  //SDL_Surface* screen_surface;
  //SDL_Texture* screen_texture;
  //uint8_t* screen_pixels;
  SDL_Event evt;
  bool quit;
  double delta_time;
  int fps;
  unsigned int cur_time = 0, prevTime = 0;
  int accumulated_fps = 0, num_frames = 0;
  double framerate_count = 0;     

  //-Функции класса----------------------------------------------------------
  //-Прочее------------------------------------------------------------------
 public:
  //-Конструктор класса------------------------------------------------------
  CWnd_Main(void);
  //-Деструктор класса-------------------------------------------------------
  ~CWnd_Main();
  //-Переменные класса-------------------------------------------------------
  //-Функции класса----------------------------------------------------------
  void VectorProduct(float *xv1,float *yv1,float *zv1,float xv2,float yv2,float zv2);
  void Octahedron(float height);
  void Paint();
  void Update();
  void UpdateTimer();
  double GetDeltaTime();
  int GetFps();
  bool IsQuit();
  //-Прочее------------------------------------------------------------------
};
#endif
