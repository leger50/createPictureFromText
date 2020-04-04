#ifndef PICTURE_FROM_TEXT_H_
#define PICTURE_FROM_TEXT_H_

#include "stb_image_write.h" //Each function returns 0 on failure and non-0 on success.
#include "stb_truetype.h"   //Each function returns 0 on failure and non-0 on success.

#define COMPO_CHANNEL_MONO  1
#define COMPO_CHANNEL_YA    2
#define COMPO_CHANNEL_RGB   3
#define COMPO_CHANNEL_RGBA  4

#define OFFSET_FONT 0

void createPictureFromText(char *text, char *filename, int width, int height, const char* pathToFont, int fontSize);

unsigned char* readFontFile(const char* pathToFontFile);
void addTextToBitmap(stbtt_fontinfo *fontInfo, unsigned char* bitmap, float scale, int width, const char *text);
void changeTextLine(int *x, int *line, int hSizeCharacter);

#endif /* PICTURE_FROM_TEXT_H_ */
