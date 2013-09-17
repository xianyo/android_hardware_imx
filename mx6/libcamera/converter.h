#ifndef CONVERTER_H
#define CONVERTER_H

void convertNV12toYUV420SP(uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height);
void convertYUYVtoYU12(uint8_t* inputBuffer, uint8_t* outputBuffer, int width, int height);
void convertYUYVtoNV12(uint8_t *inputBuffer, uint8_t *outputBuffer, int width, int height);
void yuv_to_rgb16(unsigned char y, unsigned char u, unsigned char v, unsigned char *rgb);
void convertYUYVtoRGB565(unsigned char *buf, unsigned char *rgb, int width, int height);

#endif
