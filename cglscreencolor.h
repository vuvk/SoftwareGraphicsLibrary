#ifndef C_GL_SCREEN_COLOR_H
#define C_GL_SCREEN_COLOR_H

//****************************************************************************************************
//класс точки на экране
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <stdint.h>

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

//****************************************************************************************************
//класс точки на экране
//****************************************************************************************************

#pragma pack(1)
//точка экрана
struct CGLScreenColor
{
 private:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
  //-переменные-----------------------------------------------------------------------------------------
  uint8_t R;
  uint8_t G;
  uint8_t B;
 public:
  //-конструктор----------------------------------------------------------------------------------------
  //-деструктор-----------------------------------------------------------------------------------------
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void SetColor(uint8_t r,uint8_t g,uint8_t b)
  {
   R=r;
   G=g;
   B=b;
  }
  void GetColor(uint8_t &r,uint8_t &g,uint8_t &b)
  {
   r=R;
   g=G;
   b=B;
  }
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
};
#pragma pack()

#endif
