#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include "pictureFromText.h"

/*---------------------------------------------------------------------------*/
/**
 * \brief      Create PNG picture from text
 * \details    
 *             
 * \param[in]   char *text              : text to put on picture
 * \param[in]   char *filename          : picture filename
 * \param[in]   int width               : width of picture
 * \param[in]   int height              : height of picture
 * \param[in]   const char* pathToFont  : complete path to font file
 * \param[in]   int fontSize            : size font in pixel
 * \param[in]   int marginLeft          : margin-left in pixel
 * \param[in]   int marginTop           : margin-top in pixel
 *
 * \param[out] NA
 * \return     NA
 *
 * \warning    Params[in] must be not null
 * \note       NA
 */
/*---------------------------------------------------------------------------*/
void createPictureFromText(char *text, char *filename, int width, int height, const char* pathToFont, int fontSize, int marginLeft, int marginTop){
    stbtt_fontinfo fontInfo;
    int compoChannel = COMPO_CHANNEL_MONO;
    
    /*Init font*/
    unsigned char* fontBuffer = readFontFile(pathToFont);
    if (!stbtt_InitFont(&fontInfo, fontBuffer, OFFSET_FONT)){
        fprintf(stderr, "Failed to initialize font\n");
        exit(EXIT_FAILURE);
    }
    
    float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontSize);

    /*Create bitmap picture*/
    unsigned char* bitmap = (unsigned char*)calloc(width * height * compoChannel, sizeof(unsigned char));
    if(!bitmap){
        fprintf(stderr, "Allocation of bitmap failed, out of memory ?\n");
        exit(EXIT_FAILURE);
    }
    addTextToBitmap(&fontInfo, bitmap, scale, width, text, marginLeft, marginTop);

    /*Save picture*/
    printf("--- Picture info ---\nText : %s\nSize : %d x %d\nMargin (left|top) : %d|%d\nFilename : %s\nFont : %s (%d px)\n------\n", 
        text, width, height, marginLeft, marginTop, filename, pathToFont, fontSize);

    int result = stbi_write_png(filename, width, height, compoChannel, bitmap, width);
    if(result != 0){
        fprintf(stdout, "Creation of picture %s done\n", filename);
    }else{
        fprintf(stderr, "Failed to create picture %s\n", filename);
    }

    /*Free before close app*/
    free(fontBuffer);
    free(bitmap);
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Reading font file
 * \details    
 *             
 * \param[in]   const char* pathToFontFile  : path to font file
 *
 * \param[out] NA
 * \return     unsigned char*   : buffer of font file
 *
 * \warning    Exit program if error occured
 * \note       You must be free() fontBuffer
 */
/*---------------------------------------------------------------------------*/
unsigned char* readFontFile(const char* pathToFontFile)
{
    FILE* fontFile = fopen(pathToFontFile, "rb");

    if (!fontFile){
        fprintf(stderr, "Cannot find font: %s\n", pathToFontFile);
        exit(EXIT_FAILURE);
    }

    /* get length of file */
    fseek(fontFile, 0, SEEK_END); // seek to end of file
    size_t fileSize = ftell(fontFile); // get current file pointer
    fseek(fontFile, 0, SEEK_SET); // seek back to beginning of file
    
    /* allocate buffer*/
    unsigned char* fontBuffer = malloc(fileSize);

    if (!fontBuffer){
        fprintf(stderr, "Allocation of fontBuffer failed, out of memory ?\n");
        exit(EXIT_FAILURE);
    }
   
    /* read into buffer */ 
    fread(fontBuffer, fileSize, 1, fontFile);
    
    fclose(fontFile);
    return fontBuffer;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Add text to bitmap
 * \details    
 *             
 * \param[in]   stbtt_fontinfo *fontInfo    : font
 * \param[in]   float scale                 : scale of pixel height
 * \param[in]   int width                   : width of picture
 * \param[in]   const char *text            : text of picture
 *
 * \param[out] unsigned char* bitmap : picture bitmap
 * \return     NA
 *
 * \warning    Params[in] must be not null
 * \warning    Params[out] bitmap must be allocated before calling this function
 * \note       NA
 */
/*---------------------------------------------------------------------------*/
void addTextToBitmap(stbtt_fontinfo *fontInfo, unsigned char* bitmap, float scale, int width, const char *text, int marginLeft, int marginTop){
    int x = marginLeft;
    int yLine = marginTop;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(fontInfo, &ascent, &descent, &lineGap);

    ascent *= scale;
    descent *= scale;

    int textLenght = strlen(text);
    int i = 0;
    while (i < textLenght)
    {
        /*If '\n' then we change line*/
        if(text[i] == '\\' && text[i+1] == 'n'){
            changeTextLine(&x, &yLine, ascent, marginLeft);

            i++; //to skip next character
        
        }else{
            /* get bounding box for character (may be offset to account for chars that dip above or below the line */
            int c_x1, c_y1, c_x2, c_y2;
            stbtt_GetCodepointBitmapBox(fontInfo, text[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

            /* how wide is this character */
            int ax;
            stbtt_GetCodepointHMetrics(fontInfo, text[i], &ax, 0);
            int hSizeCodepoint = ax * scale;

            /*Check if we can put character on picture (horizontally), else, we change line*/
            if( (x+hSizeCodepoint) >= width){
                changeTextLine(&x, &yLine, ascent, marginLeft);
            }

            /* compute y (different characters have different heights) */
            int y = yLine + ascent + c_y1;

            /* render character (stride and offset is important here) */
            int byteOffset = x + (y  * width);
            stbtt_MakeCodepointBitmap(fontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, width, scale, scale, text[i]);

            /* Increase x value with h size codepoint */
            x += hSizeCodepoint;

            /* add kerning */
            int kern = stbtt_GetCodepointKernAdvance(fontInfo, text[i], text[i + 1]);
            x += kern * scale;
        }

        i++;
    }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Change (x,y) coordinates to next line
 * \details    
 *             
 * \param[in]  int hSizeCharacter   : size H of font, equivalent to :
 *                      stbtt_GetFontVMetrics(fontInfo, &ascent, &descent, &lineGap);
 *                      ascent *= scale;
 *                      hSizeCharacter = ascent; 
 *
 * \param[out] int *x               : x coordinate
 * \param[out] int *line            : line coordinate
 * 
 * \return     NA
 *
 * \warning    Params[in] must be not null
 * \note       NA
 */
/*---------------------------------------------------------------------------*/
void changeTextLine(int *x, int *line, int hSizeCharacter, int marginLeft){
    *x = marginLeft;
    *line += hSizeCharacter;
}
