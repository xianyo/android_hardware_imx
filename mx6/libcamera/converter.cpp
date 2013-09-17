#include <stdint.h>
#include <stdlib.h>
#include "converter.h"

void convertNV12toYUV420SP(uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height)
{
        /* Color space conversion from I420 to YUV420SP */
        int Ysize = 0, UVsize = 0;
        uint8_t *Yin, *Uin, *Vin, *Yout, *Uout, *Vout;

        Ysize = width * height;
        UVsize = width *  height >> 2;

        Yin = inputBuffer;
        Uin = Yin + Ysize;
        Vin = Uin + 1;

        Yout = outputBuffer;
        Vout = Yout + Ysize;
        Uout = Vout + 1;

        memcpy(Yout, Yin, Ysize);

        for(int k = 0; k < UVsize; k++) {
            *Uout = *Uin;
            *Vout = *Vin;
            Uout += 2;
            Vout += 2;
            Uin  += 2;
            Vin += 2;
        }
}

void convertYUYVtoYU12(uint8_t* inputBuffer, uint8_t* outputBuffer, int width, int height)
{

    uint8_t* pyuv420u=outputBuffer+width*height;
    uint8_t* pyuv420v=pyuv420u+(width*height)/4;
    int uv_count=0;
    int i,j;

    for(i=0;i<height;i+=2) {
        for(j=0;j<width;j+=2) {
            memcpy(outputBuffer+i*width+j,inputBuffer+i*width*2+j*2,1);
            memcpy(outputBuffer+(i+1)*width+j,inputBuffer+(i+1)*width*2+j*2,1);
            memcpy(outputBuffer+i*width+(j+1),inputBuffer+i*width*2+(j+1)*2,1);
            memcpy(outputBuffer+(i+1)*width+(j+1),inputBuffer+(i+1)*width*2+(j+1)*2,1);
            memcpy(pyuv420u+uv_count,inputBuffer+i*width*2+j*2+1,1);
            memcpy(pyuv420v+uv_count,inputBuffer+(i+1)*width*2+(j+1)*2+1,1);
            uv_count++;
         }
    }
}

void convertYUYVtoNV12(uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height)
{
	uint8_t* Y	= (uint8_t*)outputBuffer;
	uint8_t* UV = (uint8_t*)Y + width * height;

	int i;
	int j;

	for(i = 0; i < height; i += 2)
	{
		for (j = 0; j < width; j++)
		{
			*(uint8_t*)((uint8_t*)Y + i * width + j) = *(uint8_t*)((uint8_t*)inputBuffer + i * width * 2 + j * 2);
			*(uint8_t*)((uint8_t*)Y + (i + 1) * width + j) = *(uint8_t*)((uint8_t*)inputBuffer + (i + 1) * width * 2 + j * 2);
			*(uint8_t*)((uint8_t*)UV + ((i * width) >> 1) + j) = *(uint8_t*)((uint8_t*)inputBuffer + i * width * 2 + j * 2 + 1);
		}
	}
}

void yuv_to_rgb16(unsigned char y, unsigned char u, unsigned char v, unsigned char *rgb)
{
    	int r,g,b;
    	int z;
    	int rgb16;

    	z = 0;

    	r = 1.164 * (y - 16) + 1.596 * (v - 128);
    	g = 1.164 * (y - 16) - 0.813 * (v - 128) - 0.391 * (u -128);
    	b = 1.164 * (y - 16) + 2.018 * (u - 128);

    	if (r > 255) r = 255;
    	if (g > 255) g = 255;
    	if (b > 255) b = 255;

    	if (r < 0) r = 0;
    	if (g < 0) g = 0;
    	if (b < 0) b = 0;

    	rgb16 = (int)(((r >> 3)<<11) | ((g >> 2) << 5)| ((b >> 3) << 0));

    	*rgb = (unsigned char)(rgb16 & 0xFF);
    	rgb++;
    	*rgb = (unsigned char)((rgb16 & 0xFF00) >> 8);
}

void convertYUYVtoRGB565(unsigned char *buf, unsigned char *rgb, int width, int height)
{
        int x,y,z=0;
        int blocks;

        blocks = (width * height) * 2;

        for (y = 0; y < blocks; y+=4) {
            unsigned char Y1, Y2, U, V;

        	Y1 = buf[y + 0];
        	U = buf[y + 1];
        	Y2 = buf[y + 2];
        	V = buf[y + 3];

            yuv_to_rgb16(Y1, U, V, &rgb[y]);
            yuv_to_rgb16(Y2, U, V, &rgb[y + 2]);
    	}
}

