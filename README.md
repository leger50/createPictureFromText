# app_createPicture

App to convert text into a PNG picture

## Usage

```shell
Usage: appCreatePicture -t "complete sentence" -w WIDTH -h HEIGHT -s SIZE_FONT -f "fileout.png"
	--text|-t : text to put on picture
	--width|-w : width in pixels (default : 128)
	--height|-h : height in pixels (default : 128)
	--margin-left|-l : margin-left in pixels (default : 0)
	--margin-top|-m : margin-top in pixels (default : 0)
	--font|-p : path to font file (default : fonts/cmunrm.ttf)
	--size-font|-s : size of font (default : 16)
	--filename|-f : name of fileout (default : fileout.png)
	--usage|-u : Display usage
	--version|-v : Display version
```

- Support '\n' character
- Change line if we cannot put more character on the actual line

## Known issues
- Only characters on ASCII table (0-127) are supported

## Credits

Use public domain libraries C/C++ from [https://github.com/nothings/stb](https://github.com/nothings/stb) :
- [stb_truetype.h](https://github.com/nothings/stb/blob/master/stb_truetype.h)
- [stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h)

## License

This project is licensed under the terms of the MIT license.