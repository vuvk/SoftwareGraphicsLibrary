#include <math.h>
#include "cwnd_main.h"
#include "tga.h"

//-Конструктор класса--------------------------------------------------------
CWnd_Main::CWnd_Main(void)
{
 if (SDL_Init (SDL_INIT_VIDEO) < 0)
 {
  fprintf (stderr, "ERROR: cannot initialize SDL video.\n");
  return;
 }

 window = SDL_CreateWindow ("SGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

 //screen_surface = SDL_GetWindowSurface(window);
 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
/*
 screen_surface = SDL_CreateRGBSurface(0, 640, 480, 24, 0, 0, 0, 0);
 if (!screen_surface)
 {
  fprintf(stderr, "SDL_SetVideoMode() failed: %s\n", SDL_GetError());
  return;
 }
*/
 screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 640, 480);
 //screen_pixels = new uint8_t [640 * 480 * 3];

 quit = false;

 cSGL.Init(640,480);
 cSGL.Perspective(60,(float)(640.0/480.0),1,1000);
 cSGL.SetViewport(0,0,640,480);
 //int32_t width;
 //int32_t height;
 //Texture_Ptr.reset(LoadTGAFromFile("texture.tga",width,height));
 //cSGL.BindTexture(width,height,reinterpret_cast<SGLRGBAByteColor*>(Texture_Ptr.get()));
 const uint16_t TEXTURE_SIZE_X=8;
 const uint16_t TEXTURE_SIZE_Y=8;
 const uint16_t COLOR_SIZE=4;

 static uint8_t texture[TEXTURE_SIZE_X*TEXTURE_SIZE_Y*COLOR_SIZE];
 int16_t index;
 for(uint32_t x=0;x<TEXTURE_SIZE_X;x++)
 {
  for(uint32_t y=0;y<TEXTURE_SIZE_Y;y++)
  {
     uint8_t r=63;
     uint8_t g=64;
     uint8_t b=127;
     if ((x+y)%2)
     {
        if (index%3==0)
        {
     r=255;
     g=127;
     b=255;
        }
        if (index%3==1)
        {
     r=255;
     g=127;
     b=127;
        }
        if (index%3==2)
        {
     r=127;
     g=255;
     b=127;
        }
    index++;
     }
     uint32_t offset=(x+y*TEXTURE_SIZE_X)*COLOR_SIZE;
     texture[offset+0]=r;
     texture[offset+1]=g;
     texture[offset+2]=b;
     texture[offset+3]=255;
  }
 }
 cSGL.BindTexture(8,8,reinterpret_cast<SGLRGBAByteColor*>(texture));
}
//-Деструктор класса---------------------------------------------------------
CWnd_Main::~CWnd_Main()
{
 //SDL_FreeSurface(screen_surface);
 SDL_DestroyTexture (screen_texture);
 //delete screen_pixels;
 SDL_DestroyWindow(window);
 SDL_Quit();
}
//-Функции класса------------------------------------------------------------
void CWnd_Main::VectorProduct(float *xv1,float *yv1,float *zv1,float xv2,float yv2,float zv2)
{
 float x1=*xv1;
 float y1=*yv1;
 float z1=*zv1;
 float x2=xv2;
 float y2=yv2;
 float z2=zv2;
 float xn=y1*z2-z1*y2;
 float yn=-(x1*z2-z1*x2);
 float zn=x1*y2-y1*x2;
 float len=sqrtf(xn*xn+yn*yn+zn*zn);
 float inv_len = (len != 0.0f) ? 1.0f / len : 0.0f;

 xn *= inv_len;
 yn *= inv_len;
 zn *= inv_len;

 *xv1=xn;
 *yv1=yn;
 *zv1=zn;
}
void CWnd_Main::Octahedron(float height)
{
 float a=height/2;
 float x1=0;
 float z1=0;
 float y1=0;
 float x2=0;
 float z2=0;
 float y2=height;
 float x3=a;
 float z3=0;
 float y3=a;
 float x4=-a;
 float z4=0;
 float y4=a;
 float x5=0;
 float z5=a;
 float y5=a;
 float x6=0;
 float z6=-a;
 float y6=a;
 float nx,ny,nz;
  nx=x3-x1;
  ny=y3-y1;
  nz=z3-z1;
  VectorProduct(&nx,&ny,&nz,x5-x1,y5-y1,z5-z1);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(1,1,1);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x3,y3,z3);
   cSGL.Color3f(1,0,1);
   cSGL.TexCoordf(1,0);
   cSGL.Vertex3f(x5,y5,z5);
   cSGL.Color3f(0,1,0);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x1,y1,z1);
  cSGL.End();
  //========================================
  nx=x5-x1;
  ny=y5-y1;
  nz=z5-z1;
  VectorProduct(&nx,&ny,&nz,x4-x1,y4-y1,z4-z1);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(1,1,0);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x5,y5,z5);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x4,y4,z4);
   cSGL.TexCoordf(1,0);
   cSGL.Vertex3f(x1,y1,z1);
  cSGL.End();
  //========================================
  nx=x4-x1;
  ny=y4-y1;
  nz=z4-z1;
  VectorProduct(&nx,&ny,&nz,x6-x1,y6-y1,z6-z1);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(1,0,1);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x4,y4,z4);
   cSGL.TexCoordf(1,1);
   cSGL.Vertex3f(x6,y6,z6);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x1,y1,z1);
  cSGL.End();
  //========================================
  nx=x6-x1;
  ny=y6-y1;
  nz=z6-z1;
  VectorProduct(&nx,&ny,&nz,x3-x1,y3-y1,z3-z1);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(0,1,1);
  /*cSGL.Begin();
   cSGL.Vertex3f(x6,y6,z6);
   cSGL.Vertex3f(x3,y3,z3);
   cSGL.Vertex3f(x1,y1,z1);
  cSGL.End();*/
  //========================================
  nx=x4-x2;
  ny=y4-y2;
  nz=z4-z2;
  VectorProduct(&nx,&ny,&nz,x5-x2,y5-y2,z5-z2);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(1,0,0);
  cSGL.Begin();
   cSGL.TexCoordf(1,1);
   cSGL.Vertex3f(x4,y4,z4);
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x5,y5,z5);
   cSGL.TexCoordf(1,0);
   cSGL.Vertex3f(x2,y2,z2);
  cSGL.End();
  //========================================
  nx=x6-x2;
  ny=y6-y2;
  nz=z6-z2;
  VectorProduct(&nx,&ny,&nz,x4-x2,y4-y2,z4-z2);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(0,1,0);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x6,y6,z6);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x4,y4,z4);
   cSGL.TexCoordf(1,0);
   cSGL.Vertex3f(x2,y2,z2);
  cSGL.End();
  //========================================
  nx=x3-x2;
  ny=y3-y2;
  nz=z3-z2;
  VectorProduct(&nx,&ny,&nz,x6-x2,y6-y2,z6-z2);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(0,0,1);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x3,y3,z3);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x6,y6,z6);
   cSGL.TexCoordf(1,1);
   cSGL.Vertex3f(x2,y2,z2);
  cSGL.End();
  //========================================
  nx=x5-x2;
  ny=y5-y2;
  nz=z5-z2;
  VectorProduct(&nx,&ny,&nz,x3-x2,y3-y2,z3-z2);
  cSGL.Normal3f(nx,ny,nz);
  cSGL.Color3f(0.5,0.5,1);
  cSGL.Begin();
   cSGL.TexCoordf(0,0);
   cSGL.Vertex3f(x5,y5,z5);
   cSGL.TexCoordf(0,1);
   cSGL.Vertex3f(x3,y3,z3);
   cSGL.TexCoordf(1,0);
   cSGL.Vertex3f(x2,y2,z2);
  cSGL.End();
  //========================================
}
//-Функции обработки сообщений класса----------------------------------------
void CWnd_Main::Paint()
{
 cSGL.Clear(CSGL::SGL_COLOR_BUFFER_BIT|CSGL::SGL_DEPTH_BUFFER_BIT);
 cSGL.MatrixMode(CSGL::SGL_MATRIX_MODELVIEW);
 cSGL.LoadIdentity();

 float l0_position[]={0,0,0};
 float l0_ambient[]={0.5,0.5,0.5};
 float l0_diffuse[]={0.5,1,0.5};
 float l0_specular[]={0.9,0.9,0.9};
 float l0_shininess[]={1};
 cSGL.Lightfv(CSGL::SGL_LIGHT0,CSGL::SGL_POSITION,l0_position);
 cSGL.Lightfv(CSGL::SGL_LIGHT0,CSGL::SGL_AMBIENT,l0_ambient);
 cSGL.Lightfv(CSGL::SGL_LIGHT0,CSGL::SGL_DIFFUSE,l0_diffuse);
 cSGL.Lightfv(CSGL::SGL_LIGHT0,CSGL::SGL_SPECULAR,l0_specular);
 cSGL.Lightfv(CSGL::SGL_LIGHT0,CSGL::SGL_SHININESS,l0_shininess);

 cSGL.Enable(CSGL::SGL_LIGHTING);
 cSGL.Enable(CSGL::SGL_LIGHT0);

 cSGL.Translatef(0,0,-25);
 cSGL.Rotatef(angle,1,1,0);
 cSGL.Translatef(0,-5,0);

 cSGL.MatrixMode(CSGL::SGL_MATRIX_TEXTURE);
 cSGL.LoadIdentity();
 cSGL.Rotatef(angle,0,0,1);
 cSGL.Translatef(-0.5,-0.5,0);

 float m0_ambient[]={0.1,0.1,0.1};
 float m0_diffuse[]={1,1,1};
 float m0_specular[]={0.5,0.5,0.5};
 float m0_emission[]={0.1,0.1,0.1};
 cSGL.Materialfv(CSGL::SGL_AMBIENT,m0_ambient);
 cSGL.Materialfv(CSGL::SGL_DIFFUSE,m0_diffuse);
 cSGL.Materialfv(CSGL::SGL_SPECULAR,m0_specular);
 cSGL.Materialfv(CSGL::SGL_EMISSION,m0_emission);

 //нарисуем фигуру
 Octahedron(10);

 cSGL.Begin();
  cSGL.Color3f(1,1,1);
  cSGL.TexCoordf(0,0);
  cSGL.Vertex3f(-10,10,0);
  cSGL.Color3f(1,0,1);
  cSGL.TexCoordf(0,1);
  cSGL.Vertex3f(-10,-10,0);
  cSGL.Color3f(1,1,0);
  cSGL.TexCoordf(1,1);
  cSGL.Vertex3f(10,-10,0);
  cSGL.Color3f(0,1,1);
  cSGL.TexCoordf(1,0);
  cSGL.Vertex3f(10,10,0);
 cSGL.End();

 // выведем картинку на экран
 //SDL_RenderClear (renderer);
 /*if (!SDL_LockSurface (screen_surface))
 {
  memcpy (screen_surface->pixels, cSGL.ImageMap, 640 * 480 * 3);
  SDL_UnlockSurface (screen_surface);

  SDL_Texture* screen_texture = SDL_CreateTextureFromSurface (renderer, screen_surface);
  SDL_RenderCopy (renderer, screen_texture, NULL, NULL);
  SDL_DestroyTexture (screen_texture);
 }*/

 int pitch;
 void* screen_pixels;
 if (!SDL_LockTexture (screen_texture, NULL, &screen_pixels, &pitch))
 {
  memcpy (screen_pixels, cSGL.ImageMap, 640 * 480 * 3);
  SDL_UnlockTexture (screen_texture);
  SDL_RenderCopy (renderer, screen_texture, NULL, NULL);
 }
 SDL_RenderPresent (renderer);
}

void CWnd_Main::Update()
{
 while (SDL_PollEvent(&evt))
 {
  switch(evt.type)
  {
   case SDL_KEYDOWN:
   {
    switch (evt.key.keysym.sym)
    {
     case SDLK_ESCAPE: quit = true; break;
     default: break;
    }
    break;
   }

   case SDL_QUIT: quit = true; break;

   default: break;
  }
 }

 angle += 25 * delta_time;
}

void CWnd_Main::UpdateTimer()
{
 prevTime = cur_time;
 cur_time = SDL_GetTicks();
 //delta_time = (cur_time - prevTime) / 1000.0;
 delta_time = (cur_time - prevTime) * 0.001;
 int int_fps = (int)(1.0 / delta_time);
 framerate_count += delta_time;
 accumulated_fps += int_fps;
 ++num_frames;

 //if (num_frames > 60)
 if (framerate_count >= 0.5)
 {
  if (num_frames != 0.0)
  {
   fps = accumulated_fps / num_frames;
  }
  else
  {
   fps = accumulated_fps;
  }
/*
  if (fps >= 1000 || fps < 0)
  {
   fps  = 1000;
  }
*/
  num_frames = 0;
  accumulated_fps = 0;

  framerate_count -= 0.5;

  char title[255] = {0};
  sprintf (title, "SGL - FPS: %d", fps);
  SDL_SetWindowTitle (window, title);
 }
}

double CWnd_Main::GetDeltaTime()
{
 return delta_time;
}

int CWnd_Main::GetFps()
{
 return fps;
}

bool CWnd_Main::IsQuit()
{
 return quit;
}
//-Прочее--------------------------------------------------------------------

