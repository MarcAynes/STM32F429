#include "pantalla_lcd.h"
#include "stm32f429i_discovery_lcd.h"

#define FRAME_BUFFER_SIZE BUFFER_OFFSET

static uint32_t currentBuffer = LCD_FRAME_BUFFER;

RetSt EsborraPantalla(uint8_t alfa, uint8_t rVal, uint8_t gVal, uint8_t bVal) {
	uint16_t data = (((uint16_t)(0x0F&alfa)) << 12) | (((uint16_t)(0x0F&rVal)) << 8) | (((uint16_t)(0x0F&gVal)) << 4) | (((uint16_t)(0x0F&bVal)) << 0);
	int i;
	int j;
	for (i = 0; i < LCD_PIXEL_HEIGHT ; i++) {		//dividit entre 2
		for (j = 0; j < LCD_PIXEL_WIDTH ; j++) {		//dividit entre 2
			*(uint16_t *) (currentBuffer + (2 * (((LCD_PIXEL_WIDTH) * (i)) + (j)))) = data;	//D000000, D0000002, D000004,...
		}
	}

	return OK;
}

RetSt DibuixaLiniaHoritzontal (uint16_t col_inici, uint16_t col_fi, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval){
	if (col_inici >= LCD_PIXEL_HEIGHT || col_fi >= LCD_PIXEL_HEIGHT || fila >= LCD_PIXEL_WIDTH)
			return NO_OK;
	col_inici = LCD_PIXEL_HEIGHT - col_inici;
	col_fi = LCD_PIXEL_HEIGHT - col_fi;
	uint16_t data = (((uint16_t)(0x0F&alfa)) << 12) | (((uint16_t)(0x0F&Rval)) << 8) | (((uint16_t)(0x0F&Gval)) << 4) | (((uint16_t)(0x0F&Bval)) << 0);
	int i;
	int cmp = col_fi > col_inici ? ((col_fi) - (col_inici)) + 1 : ((col_inici) - (col_fi)) + 1 ;
	uint16_t col_inicial = col_fi > col_inici ? (col_inici) : col_fi;
	for (i = 0; i < cmp; i++) {
		*((uint16_t *) (currentBuffer + 2 * ((LCD_PIXEL_WIDTH) * (col_inicial + (i)) + (fila)))) = data;
	}

	return OK;
}

RetSt DibuixaLiniaVertical (uint16_t col, uint16_t fila_inici, uint16_t fila_fi, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval){
	if (col >= LCD_PIXEL_HEIGHT || fila_inici >= LCD_PIXEL_WIDTH || fila_fi >= LCD_PIXEL_WIDTH)
			return NO_OK;

	col = LCD_PIXEL_HEIGHT - col;
	uint16_t *Xaddress = fila_fi > fila_inici ? (uint16_t *) (currentBuffer + 2 * ((LCD_PIXEL_WIDTH) * (col) + (fila_inici))) : (uint16_t *) (currentBuffer + 2 * ((LCD_PIXEL_WIDTH) * (col) + (fila_fi)));
	uint16_t data = (((uint16_t)(0x0F&alfa)) << 12) | (((uint16_t)(0x0F&Rval)) << 8) | (((uint16_t)(0x0F&Gval)) << 4) | (((uint16_t)(0x0F&Bval)) << 0);
	int i;
	int cmp = fila_fi > fila_inici ? (fila_fi - fila_inici) + 1 : (fila_inici - fila_fi) + 1 ;
	for (i = 0; i < cmp; i++) {
		Xaddress[i] = data;
	}

	return OK;
}

RetSt SetPixel(uint16_t col, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval){
	if (col >= LCD_PIXEL_HEIGHT || fila >= LCD_PIXEL_WIDTH)
		return NO_OK;

	col = LCD_PIXEL_HEIGHT - col;
	uint16_t *Xaddress = ((uint16_t *) (currentBuffer + 2 * ((LCD_PIXEL_WIDTH) * (col) + (fila))));
	uint16_t data = (((uint16_t)(0x0F&alfa)) << 12) | (((uint16_t)(0x0F&Rval)) << 8) | (((uint16_t)(0x0F&Gval)) << 4) | (((uint16_t)(0x0F&Bval)) << 0);

	*Xaddress = data;
	return OK;
}

RetSt DibuixaCircumferencia (uint16_t ccol, uint16_t cfila, uint16_t radi, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval){
	if(ccol + radi >= LCD_PIXEL_HEIGHT || cfila + radi >= LCD_PIXEL_WIDTH || cfila - radi < 0 || ccol - radi < 0)
		return NO_OK;
	int x, y, d;
	x = 0;
	y = radi;
	d = 3 - (radi << 1);                     /* D0                  */
	while (x <= y) {
		SetPixel( x + ccol,  y + cfila, alfa, Rval, Gval, Bval);
		SetPixel((-1*x) + ccol,  y + cfila, alfa, Rval, Gval, Bval);
		SetPixel( x + ccol, -y + cfila, alfa, Rval, Gval, Bval);
		SetPixel(-x + ccol, -y + cfila, alfa, Rval, Gval, Bval);
		SetPixel( y + ccol,  x + cfila, alfa, Rval, Gval, Bval);
		SetPixel(-y + ccol,  x + cfila, alfa, Rval, Gval, Bval);
		SetPixel( y + ccol, -x + cfila, alfa, Rval, Gval, Bval);
		SetPixel(-y + ccol, -x + cfila, alfa, Rval, Gval, Bval);

		if( d < 0 )                          /* Selecciona el punt A */
			d += (x<<2) + 6;                  /* 4*x + 6              */
		else {                               /* Selecciona el punt B */
			d += ((x-y)<<2) + 10;             /* 4*(x‐y) + 10         */
			y--;                              /* y = y‐1              */
		}
		x++;
	}

	return OK;
}

RetSt DibuixaBitmap (uint16_t col, uint16_t fila, uint8_t alfa, uint8_t Rval, uint8_t Gval, uint8_t Bval){
	if(col + 1 >= LCD_PIXEL_HEIGHT || fila + 1 >= LCD_PIXEL_WIDTH || fila - 1 < 0 || col - 1 < 0)
			return NO_OK;

	SetPixel( 1 + col,  1 + fila, alfa, Rval, Gval, Bval);
	SetPixel( col,  1 + fila, alfa, Rval, Gval, Bval);
	SetPixel( 1 + col,  fila, alfa, Rval, Gval, Bval);
	SetPixel( col,  fila, alfa, Rval, Gval, Bval);
	SetPixel( 1 - col,  1 + fila, alfa, Rval, Gval, Bval);
	SetPixel( 1 + col,  1 - fila, alfa, Rval, Gval, Bval);
	SetPixel( 1 - col,  1 - fila, alfa, Rval, Gval, Bval);
	SetPixel( 1 - col,  fila, alfa, Rval, Gval, Bval);
	SetPixel( col,  1 - fila, alfa, Rval, Gval, Bval);

	return OK;
}

void pintaFons(void){
	EsborraPantalla(0xF, 0xF, 0xF, 0xF);
	DibuixaLiniaHoritzontal (4, 86, 35, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaHoritzontal (4, 86, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaHoritzontal (101, 302, 154, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaHoritzontal (101, 302, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaHoritzontal (101, 302, 197, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaHoritzontal (134, 266, 76, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (4, 35, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (86, 35, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (45, 35, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (101, 154, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (302, 154, 236, 0xF, 0x0, 0x0, 0x0);
	DibuixaLiniaVertical (200, 10, 142, 0xF, 0x0, 0x0, 0x0);
	DibuixaCircumferencia (200, 76, 15, 0xF, 0x0, 0x0, 0x0);
	DibuixaCircumferencia (200, 76, 30, 0xF, 0x0, 0x0, 0x0);
	DibuixaCircumferencia (200, 76, 45, 0xF, 0x0, 0x0, 0x0);
	DibuixaCircumferencia (200, 76, 60, 0xF, 0x0, 0x0, 0x0);


}

void set_buffer(uint32_t framebuffer) {
	currentBuffer = framebuffer;
}



