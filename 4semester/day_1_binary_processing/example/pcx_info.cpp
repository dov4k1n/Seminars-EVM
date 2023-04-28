// Считываем традиционные характеристики изображения и служебную информацию из pcx файла.
// Версия 0.1
// http://машинноезрение.рф

#include <stdio.h>
#include <stdint.h>

struct __pcx_info__
{
	unsigned int ver; // Версия заголовка, в данном случае, pcx файла.
	unsigned int enc; // Используется ли rle сжатие.
	unsigned int bpp; // bits per pixel.

	// Окно куда предполагается отобразить изображение.
	unsigned int xmin, ymin;
	unsigned int xmax, ymax;

	unsigned int hDPI, vDPI;// Информация обычно используемая при печати.

	unsigned int rsrv;

	unsigned int planes; // Количество цветовых плоскостей, по сути: 1 (монохромное), 3(rgb) или 4 (rgb+прозрачность).
	unsigned int bpl; // bytes per line.
	unsigned int mode; // Палитра цветная или монохромная.

	unsigned int hRes, vRes;
};

typedef struct __pcx_info__ pcx_info;// Вводим сокращенное название для нашего типа.

// Мнемоники для возврата статуса выполнения, в частности, ошибок из наших функций.
#define PCX_SUCCESS	0  // Все  хорошо.
#define READ_ERROR	-1 // Ошибка чтения файла.

// Связанные со считыванием pcx данных.
#define NOT_PCX		-10 // Исходя из магии файл не является pcxым.
#define PCX_UNSUPPORTED	-11 // Данный файл (версия pcx файла) не поддерживается.

int read_pcx_info( pcx_info *pcx, FILE *f)
{
	fseek(f, 0, SEEK_SET);// На всякий случай явно переходим в начало файла.
	int res;// Для хранения возвращаемого статуса (в частности, ошибок) из вызываемых функций.

	// Магия соответствующая файловому формату pcx.
	uint8_t mag;// Для формата pcx это один байт (8-битный).
	// Считываем одну единицу данных (1) соответствующую переменной mag (т.е. размера sizeof(mag)).
	res = fread( &mag, sizeof(mag), 1, f);// Напомню, &mag является указателем на то место, где хранится переменная mag.
	if( res != 1 ) // Проверяем, что считали именно одну единицу данных (в частности, нет ошибок).
		return READ_ERROR;// Скорее всего файл закончился, т.е. в данном случае он пустой.
	// Проверяем магию которая должна быть в начале любого корректного pcx файла.
  	if( mag != 0x0A ) // Один байт магии заданный в шестнадцатеричном формате (на это указывает 0x).
		return NOT_PCX;

	// Версия заголовка pcx формата.
	uint8_t ver;
	res = fread( &ver, sizeof(ver), 1, f);
	if( res != 1)
		return READ_ERROR; 
	pcx->ver = ver; // Сохраняем в структуре для последующего применения (например, для вывода информации).

	// Факт использования сжатия (rle)
	uint8_t enc;
	res = fread( &enc, sizeof(enc), 1, f);
	if( res != 1)
		return READ_ERROR;
	pcx->enc = enc; // Потребуется и для доступа к пиксельным данным.

	// Сколько битов на пиксель.
	uint8_t bpp;// bits per pixel
	res = fread( &bpp, sizeof(bpp), 1, f);
	if( res != 1)
		return READ_ERROR;
	pcx->bpp = bpp;

	// Считываются то куда нужно картинку отобразить.
	// Вот такая вот интересная специфика для pcx формата.
	uint16_t xmin;
	res = fread( &xmin, sizeof(xmin), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->xmin = xmin;

	// Да, при считывании можно было бы использовать и одну и туже переменную.
	uint16_t ymin; // Но лучше, думаю, так, вводя свою отдельную переменную.
	res = fread( &ymin, sizeof(ymin), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->ymin = ymin;

	uint16_t xmax;
	res = fread( &xmax, sizeof(xmax), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->xmax = xmax;

	uint16_t ymax;
	res = fread( &ymax, sizeof(ymax), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->ymax = ymax;

	// DPI -- dots per inchю
	// Важно для печати.
	uint16_t hDPI;
	res = fread( &hDPI, sizeof(hDPI), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->hDPI = hDPI;

	uint16_t vDPI;
	res = fread( &vDPI, sizeof(vDPI), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->vDPI = vDPI;

	// Пропустим палитру EGA.
	// Была важна для отображения в системах с графической карточкой,
	// которая имеет как наилучший режим только EGA.
	fseek( f, 48, SEEK_CUR);

	// Некий резервный байт, который был оставлен для будущего. Так принято делать.
	// Теперь уже ясно, что вряд ли когда-либо этот байт будет использован.
	uint8_t rsrv;
	res = fread( &rsrv, sizeof(rsrv), 1, f);
	if( res != 1)
		return READ_ERROR;
	pcx->rsrv = rsrv;

	// Количество цветовых плоскостей.
	uint8_t planes;
	res = fread( &planes, sizeof(planes), 1, f);
	if( res != 1)
		return READ_ERROR;
	pcx->planes = planes;

	// Сколько байт в одной строке для несжатой картинки.
	uint16_t bpl;// bytes per line
	res = fread( &bpl, sizeof(bpl), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->bpl = bpl;

	// Режим хранения цветов в палитре.
	uint16_t mode;
	res = fread( &mode, sizeof(mode), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->mode = mode;

	// Разрешение предполагаемого устройства отображения картинки.
	uint16_t hRes;
	res = fread( &hRes, sizeof(hRes), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->hRes = hRes;

	uint16_t vRes;
	res = fread( &vRes, sizeof(vRes), 1, f);
	if( res != 1 )
		return READ_ERROR;
	pcx->vRes = vRes;

	// Пропустим 54 резервных байт.
	fseek( f, 54, SEEK_CUR);
	// Далее начнутся данные картинки.
	return PCX_SUCCESS;
}

int print_pcx_info( pcx_info *pcx )
{
	printf("version %d: ", pcx->ver);
	if( pcx->ver != 5 )
	{
		printf("unsupported\n");
		//return PCX_UNSUPPORTED;
		// Возврат убран ввиду того, что разные версии pcx формата совместимы.
		// В противном случае, нужно было бы завершить работу оной функции сообщением об отсутствии поддержки используемой версии данного формата.
	}
	else
		printf("PC Paintbrush version 3.0\n");

	// У разных версий совместимы далее идущие поля.
	// Поэтому ранее и не был сделан возврат из фнкции.
	printf("Encoding %d: %s\n", pcx->enc, pcx->enc == 1 ? "RLE" : "None" );
	printf("Bits per pixel %d\n", pcx->bpp);
	printf("Image position (%d, %d) x (%d, %d)\n", pcx->xmin, pcx->ymin, pcx->xmax, pcx->ymax);
	printf("DPI %dx%d\n", pcx->hDPI, pcx->vDPI);
	printf("Color planes %d\n", pcx->planes);
	printf("Bytes per line %d\n", pcx->bpl);
	printf("Palete mode %d\n", pcx->mode);
	printf("Screen resolution %dx%d\n", pcx->hRes, pcx->vRes);

	return PCX_SUCCESS;
}

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Need an image!\n");
		printf("%s <image name>\n", argv[0]);// В argv[0] хранится название исполняемого файла.
		return -1;
	}

	FILE *f = fopen( argv[1], "rb");// А в argv[1] -- первый аргумент.
	if( f == NULL )
	{
		printf("Error openning file\n");
		return -1;
	}

	pcx_info pcx;// То куда будет сохранена информация об изображении.

	int ret;
	// Вызываем функцию считывания информации об pcx изображении из файла.
	if( (ret = read_pcx_info( &pcx, f)) < 0 )
	{
		printf("error reading pcx file: %d\n", ret);
		return -1;
	}
	// Печатаем информацию об изображении по данным ранее сохраненным в структуре.
	print_pcx_info( &pcx );

	fclose( f );
	return 0;
}
