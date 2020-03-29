#ifndef PICTURE_FROM_TEXT_H_
#define PICTURE_FROM_TEXT_H_

#define COMPO_CHANNEL_MONO  1
#define COMPO_CHANNEL_YA    2
#define COMPO_CHANNEL_RGB   3
#define COMPO_CHANNEL_RGBA  4

#define OFFSET_FONT 0

#include <stdbool.h>

void createPictureFromText(char *text, char *filename, int width, int height);

unsigned char* readFontFile(const char* pathToFontFile);

#endif /* PICTURE_FROM_TEXT_H_ */
