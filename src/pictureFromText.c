#include "pictureFromText.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" //Each function returns 0 on failure and non-0 on success.

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"   //Each function returns 0 on failure and non-0 on success.

/*---------------------------------------------------------------------------*/
/**
 * \brief      Create PNG picture from text
 * \details    
 *             
 * \param[in]   char *text      : text to put on picture
 * \param[in]   char *filename  : picture filename
 * \param[in]   int width       : width of picture
 * \param[in]   int height      : height of picture
 *
 * \param[out] NA
 * \return     NA
 *
 * \warning    Params[in] must be not null
 * \note       NA
 */
/*---------------------------------------------------------------------------*/
void createPictureFromText(char *text, char *filename, int width, int height){
    stbtt_fontinfo fontInfo;
    
    /*Init font*/
    unsigned char* fontBuffer = readFontFile("fonts/cmunrm.ttf");
    if (!stbtt_InitFont(&fontInfo, fontBuffer, OFFSET_FONT)){
        fprintf(stderr, "Failed to initialize font\n");
        exit(EXIT_FAILURE);
    }
    
    int fontSize = 16;
    float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontSize);

    /*Create bitmap picture*/
    unsigned char* bitmap = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    if(!bitmap){
        fprintf(stderr, "Allocation of bitmap failed, out of memory ?\n");
        exit(EXIT_FAILURE);
    }

    /*Save picture*/
    printf("Picture %s|%d|%d|%s\n", text, width, height, filename);

    /*FILE *fileOut = fopen(filename, "wb");
    if(!fileOut){
        printf(stderr, "Cannot create file : %s\n", filename);
        exit(EXIT_FAILURE);
    }*/

    //stbi_write_png(filename, width, height, COMPO_CHANNEL_MONO, );

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

void addTextToBitmap(){

}
