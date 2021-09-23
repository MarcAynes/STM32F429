#ifndef PANTALLA_LCD_H_
#define PANTALLA_LCD_H_

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

typedef enum {
   NO_OK = 0 ,
   OK = !NO_OK
} RetSt;

RetSt EsborraPantalla(uint8_t alfa, uint8_t rVal, uint8_t gVal, uint8_t bVal);
RetSt DibuixaLiniaHoritzontal (uint16_t col_inici, uint16_t col_fi, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval);
RetSt DibuixaLiniaVertical (uint16_t col, uint16_t fila_inici, uint16_t fila_fi, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval);
RetSt SetPixel(uint16_t col, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval);
RetSt DibuixaCircumferencia (uint16_t ccol, uint16_t cfila, uint16_t radi, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval);
void set_buffer(uint32_t framebuffer);
void pintaFons(void);
RetSt DibuixaBitmap (uint16_t col, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval);

#endif /* PANTALLA_LCD_H_ */
