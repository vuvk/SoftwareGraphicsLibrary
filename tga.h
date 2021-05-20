#ifndef TGA_H
#define TGA_H

//====================================================================================================
//подключаемые библиотеки
//====================================================================================================

#include <stdio.h>
#include <stdint.h>

//====================================================================================================
//структуры
//====================================================================================================

//заголовок TGA-файла
#pragma pack(1)
struct STGAHeader
{
 uint8_t identsize;//размер поля заголовка
 uint8_t colorMapType;//если ли палитра:0-нет,1-есть
 uint8_t imageType;//тип картинки:0-нет,1-индексные цвета,2-RGB,3-оттенки серого, (3-й бит - RLE- кодирование)
 uint16_t colorMapStart;//начало карты цветов
 uint16_t colorMapLength;//количество цветов в карте
 uint8_t colorMapBits;//размерность палитры
 uint16_t xstart;//начальные координаты изображения
 uint16_t ystart;
 uint16_t width;//размер изображения по X
 uint16_t height;//размер изображения по Y
 uint8_t bits;//количесто бит на пиксель (8,16,24,32)
 uint8_t descriptor;//дескриптор изрображения
};
#pragma pack()

//====================================================================================================
//прототипы функций
//====================================================================================================

uint8_t *LoadTGAFromFile(const char *file_name,int32_t &width,int32_t &height);//загрузить tga-файл
uint8_t *LoadTGAFromResource(const char* file_name,int32_t id,int32_t &width,int32_t &height);//загрузить tga-файл из ресурсов
bool SaveTGA(const char *file_name,int32_t width,int32_t height,uint8_t *image);//сохранить картинку в tga-файл

#endif
