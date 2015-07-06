//-----------------------------
// File:		wk3_homework_attempt_v2.cpp
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

//Function Prototypes
void MainMenu();
Sint32 InstructionsA();
Sint32 InstructionsB();
void SaveBMP();//Blank white bmp
void SaveBMP(const Uint8);//Random greyscale
void SaveBMP(const Uint8, const Uint8, const Uint8);//Random BGR
void SaveBMP(const Uint8, const Uint8, const Uint8, const Uint8);//User option greyscale
void SaveBMP(const Uint8, const Uint8, const Uint8, const Uint8, const Uint8, const Uint8);//User option colour
void CreateSmartBMP(const Uint8);//greyscale with user settings
void CreateSmartBMP(const Uint8, const Uint8, const Uint8);//colour with user settings
void QueryImageSize(Sint32&, Sint32&);
bool UserAgrees();
Sint32 EnsurePositive(Sint32);
Sint32 AnswerWithinBoundaries(Sint32, const Sint32, const Sint32);


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	MainMenu();
}


void MainMenu()
{
	switch(InstructionsA())
	{
		case 1:
			printf("Coming soon!\n");//NOT DONE YET!!!
			break;
		case 2:
			switch(InstructionsB())
			{
				case 1://random greyscale
					SaveBMP(rand() % 256);
					break;
				case 2://random colour
					SaveBMP(rand() % 256, rand() % 256, rand() % 256);
					break;
				case 3://greyscale with user settings
					{
						printf("How high would you like sea level to be? (minimum: 0, maximum: 255)\n");
						Sint32 greyValue = -1;
						scanf("%d", &greyValue);
						greyValue = AnswerWithinBoundaries(greyValue, 0, 255);
						CreateSmartBMP((Uint8)greyValue);
					}
					break;
				case 4://colour with user settings
					{
						printf("Coming soon!\n");//NOT DONE YET!!!
						/*
						printf("What colour would you like sea level to be represented by? (calculated through BGR)\n");
						printf("Blue value: (minimum: 0, maximum: 255)\n");
						Sint32 blueValue = -1;
						scanf("%d", &blueValue);
						printf("Green value: (minimum: 0, maximum: 255)\n");
						Sint32 greenValue = -1;
						scanf("%d", &greenValue);
						printf("Red value: (minimum: 0, maximum: 255)\n");
						Sint32 redValue = -1;
						scanf("%d", &redValue);
						blueValue = AnswerWithinBoundaries(blueValue, 0, 255);
						greenValue = AnswerWithinBoundaries(greenValue, 0, 255);
						redValue = AnswerWithinBoundaries(redValue, 0, 255);
						CreateSmartBMP((Uint8)blueValue,(Uint8)greenValue, (Uint8)redValue);
						*/
					}
					break;
				default:
					printf("ERROR: Invalid input from InstructionsB().\n");
					break;
			}
			break;
		case 0:
			break;
		default:
			printf("ERROR: Invalid input from InstructionsA().\n");
			break;
	}
}

Sint32 InstructionsA()
{
	Sint32 choice = -1;

	printf("How would you like to create a new heightmap bmp?\n");
	printf("1: Convert txt file.\n");
	printf("2: Create a new heightmap with user options.\n");
	printf("0: Quit.\n");
	scanf("%d", &choice);

	return AnswerWithinBoundaries(choice, 0, 2);
}

Sint32 InstructionsB()
{
	int choice = -1;

	printf("How would you like to create the heightmap?\n");
	printf("1: As a randomly generated greyscale bmp.\n");
	printf("2: As a randomly generated colour bmp.\n");
	printf("3: As a greyscale bmp generated with user options.\n");
	printf("4: As a colour bmp generated with user options.\n");
	scanf("%d", &choice);

	return AnswerWithinBoundaries(choice, 1, 4);
}

void CreateSmartBMP(const Uint8 greyValue)
{
	Sint32 step = -1;
	Sint32 min = -1;
	Sint32 max = -1;

	printf("Please enter your options. (1 for yes, 0 for no)\n");
	printf("Would you like the height differencial between any two tiles have a limit?\n");
	if(UserAgrees())
	{
		printf("What would you like the height differencial limit to be? (minimum: 0, maximum: 255)\n");
		scanf("%d", &step);
		step = AnswerWithinBoundaries(step, 0, 255);
	}
	else
	{
		step = 255;
	}
	printf("Would you like there to be a maximum height?\n");
	if(UserAgrees())
	{
		printf("What would you like the maximum height to be? (minimum: sea level (%d), maximum: 255)\n", greyValue);
		scanf("%d", &max);
		max = AnswerWithinBoundaries(max, greyValue, 255);
	}
	else
	{
		max = 255;
	}
	printf("Would you like there to be a minimum height?\n");
	if(UserAgrees())
	{
		printf("What would you like the minimum height to be? (minimum: 0, maximum: sea level (%d))\n", greyValue);
		scanf("%d", &min);
		min = AnswerWithinBoundaries(min, 0, greyValue);
	}
	else
	{
		min = 0;
	}

	SaveBMP((Uint8)greyValue, (Uint8)step, (Uint8)min, (Uint8)max);

}

void CreateSmartBMP(const Uint8 blueValue, const Uint8 greenValue, const Uint8 redValue)
{
	Sint32 blueHeightDiff = -1;
	Sint32 greenHeightDiff = -1;
	Sint32 redHeightDiff = -1;

	printf("Please enter your options. (1 for yes, 0 for no)\n");
	printf("Would you like the height differncial between any two areas have a limit?\n");
	if(UserAgrees())
	{
		printf("What would you like the height differencial limit to be?\n");
		printf("Blue: ");
		scanf("%d", &blueHeightDiff);
		blueHeightDiff = AnswerWithinBoundaries(blueHeightDiff, 0, 255 - blueValue);
		printf("\n");
		printf("Green: ");
		scanf("%d", &blueHeightDiff);
		greenHeightDiff = AnswerWithinBoundaries(greenHeightDiff, 0, 255 - greenValue);
		printf("\n");
		printf("Red: ");
		scanf("%d", &blueHeightDiff);
		redHeightDiff = AnswerWithinBoundaries(redHeightDiff, 0, 255 - redValue);
		printf("\n");
		//CONTINUE WORKING HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
}

void SaveBMP()
{
	FILE * f_out;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	char fileName[260] = "test.bmp";

	//default image size unless user specifies otherwise
	Sint32 width = 640;
	Sint32 height = 480;

	QueryImageSize(width, height);

	cPixel* img = new cPixel[width * height];

	//Open file
	f_out = fopen(fileName, "wb");
	printf("Opening file \"%s\" to write in binary mode...\n", fileName);
	if(f_out)
	{
		printf("File \"%s\" opened succesfully.\n", fileName);
		bfh.bfType = (0x4D42);//Specifies the file type. The file is a bmp if this is equal to 0x4D42
		bfh.bfSize = width * height;//Bitmap file size in bytes
		bfh.bfReserved1 = 0;//Must be 0
		bfh.bfReserved2 = 0;//Must be 0
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//Offset in bytes from the bitmapfileheader to the bitmap bits

		//Write bmp file header
		printf("Writing bmp file header...\n");
		if(fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER))
		{
			printf("Done writing bmp file header.\n");

			bih.biSize = sizeof(BITMAPINFOHEADER);//Number of bytes required by the struct
			bih.biWidth = width;
			bih.biHeight = height;
			bih.biPlanes = 1;//Number of colour planes, must be 1
			bih.biBitCount = 8;//Number of bit per pixel
			bih.biCompression = BI_RGB;//Compression type
			bih.biSizeImage = width * height/*or 0*/;//Image size in bytes
			bih.biXPelsPerMeter = 96;//Pixels per meter in x axis
			bih.biYPelsPerMeter = 96;//Pixels per meter in y axis
			bih.biClrUsed = 0;//Number of colours used by the bitmap
			bih.biClrImportant = 0;//Number of colours that are important

			//Write bmp info header
			printf("Writing bmp info header...\n");
			if(fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{
				printf("Done writing bmp info header.\n");

				//Write BMP data
				printf("Writing bmp data...\n");
				
				//cTimer* timer = new cTimer;
				//timer->Start();

				for(int i = 0; i < (width * height); ++i)
				{
					fwrite(&img[i].b, 1, 1, f_out);
					fwrite(&img[i].g, 1, 1, f_out);
					fwrite(&img[i].r, 1, 1, f_out);
				}
				
				//timer->Stop();

				printf("Done writing bmp data.\n");
				
				//printf("Time taken to create bmp: %d\n", timer->GetElapsed());

				//Clean-Up
				//delete timer;
				//timer = NULL;
			}
			else
			{
				printf("ERROR: Could not write bitmap info header!\n");
			}
		}
		else
		{
			printf("ERROR: Could not write bitmap file header!\n");
		}
		fclose(f_out);
	}

	//Clean-up
	delete[] img;
	img = NULL;
}

void SaveBMP(const Uint8 greyscale)
{
	FILE * f_out;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	char fileName[260] = "test.bmp";

	//default image size unless user specifies otherwise
	Sint32 width = 640;
	Sint32 height = 480;

	QueryImageSize(width, height);

	cPixel* img = new cPixel[width * height];

	for(int i = 0; i < (width * height); ++i)
	{
		img[i].b = greyscale;
		img[i].g = greyscale;
		img[i].r = greyscale;
	}

	//Open file
	f_out = fopen(fileName, "wb");
	printf("Opening file \"%s\" to write in binary mode...\n", fileName);
	if(f_out)
	{
		printf("File \"%s\" opened succesfully.\n", fileName);
		bfh.bfType = (0x4D42);//Specifies the file type. The file is a bmp if this is equal to 0x4D42
		bfh.bfSize = width * height;//Bitmap file size in bytes
		bfh.bfReserved1 = 0;//Must be 0
		bfh.bfReserved2 = 0;//Must be 0
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//Offset in bytes from the bitmapfileheader to the bitmap bits

		//Write bmp file header
		printf("Writing bmp file header...\n");
		if(fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER))
		{
			printf("Done writing bmp file header.\n");

			bih.biSize = sizeof(BITMAPINFOHEADER);//Number of bytes required by the struct
			bih.biWidth = width;
			bih.biHeight = height;
			bih.biPlanes = 1;//Number of colour planes, must be 1
			bih.biBitCount = 8;//Number of bit per pixel
			bih.biCompression = BI_RGB;//Compression type
			bih.biSizeImage = width * height/*or 0*/;//Image size in bytes
			bih.biXPelsPerMeter = 96;//Pixels per meter in x axis
			bih.biYPelsPerMeter = 96;//Pixels per meter in y axis
			bih.biClrUsed = 0;//Number of colours used by the bitmap
			bih.biClrImportant = 0;//Number of colours that are important

			//Write bmp info header
			printf("Writing bmp info header...\n");
			if(fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{
				printf("Done writing bmp info header.\n");

				//Write BMP data
				printf("Writing bmp data...\n");
				for(int i = 0; i < (width * height); ++i)
				{
					fwrite(&img[i].b, 1, 1, f_out);
					fwrite(&img[i].g, 1, 1, f_out);
					fwrite(&img[i].r, 1, 1, f_out);
				}
				//for(j*=3; j%4!=0; j++)
				//{
				//	fwrite(&zero,1,1,f_out);//Padding row to 4-byte multiple!
				//}
				printf("Done writing bmp data.\n");
			}
			else
			{
				printf("ERROR: Could not write bitmap info header!\n");
			}
		}
		else
		{
			printf("ERROR: Could not write bitmap file header!\n");
		}
		fclose(f_out);
	}

	//Clean-up
	delete[] img;
	img = NULL;
}

void SaveBMP(const Uint8 blue, const Uint8 green, const Uint8 red)
{
	FILE * f_out;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	char fileName[260] = "test.bmp";

	//default image size unless user specifies otherwise
	Sint32 width = 640;
	Sint32 height = 480;

	cPixel* img = new cPixel[width * height];

	for(int i = 0; i < (width * height); ++i)
	{
		img[i].b = blue;
		img[i].g = green;
		img[i].r = red;
	}


	//Open file
	f_out = fopen(fileName, "wb");
	printf("Opening file \"%s\" to write in binary mode...\n", fileName);
	if(f_out)
	{
		printf("File \"%s\" opened succesfully.\n", fileName);
		bfh.bfType = (0x4D42);//Specifies the file type. The file is a bmp if this is equal to 0x4D42
		bfh.bfSize = width * height;//Bitmap file size in bytes
		bfh.bfReserved1 = 0;//Must be 0
		bfh.bfReserved2 = 0;//Must be 0
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//Offset in bytes from the bitmapfileheader to the bitmap bits

		//Write bmp file header
		printf("Writing bmp file header...\n");
		if(fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER))
		{
			printf("Done writing bmp file header.\n");

			bih.biSize = sizeof(BITMAPINFOHEADER);//Number of bytes required by the struct
			bih.biWidth = width;
			bih.biHeight = height;
			bih.biPlanes = 1;//Number of colour planes, must be 1
			bih.biBitCount = 8;//Number of bit per pixel
			bih.biCompression = BI_RGB;//Compression type
			bih.biSizeImage = width * height/*or 0*/;//Image size in bytes
			bih.biXPelsPerMeter = 96;//Pixels per meter in x axis
			bih.biYPelsPerMeter = 96;//Pixels per meter in y axis
			bih.biClrUsed = 0;//Number of colours used by the bitmap
			bih.biClrImportant = 0;//Number of colours that are important

			//Write bmp info header
			printf("Writing bmp info header...\n");
			if(fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{
				printf("Done writing bmp info header.\n");

				//Write BMP data
				printf("Writing bmp data...\n");
				for(int i = 0; i < (width * height); ++i)
				{
					fwrite(&img[i].b, 1, 1, f_out);
					fwrite(&img[i].g, 1, 1, f_out);
					fwrite(&img[i].r, 1, 1, f_out);
				}
				//for(j*=3; j%4!=0; j++)
				//{
				//	fwrite(&zero,1,1,f_out);//Padding row to 4-byte multiple!
				//}
				printf("Done writing bmp data.\n");
			}
			else
			{
				printf("ERROR: Could not write bitmap info header!\n");
			}
		}
		else
		{
			printf("ERROR: Could not write bitmap file header!\n");
		}
		fclose(f_out);
	}

	//Clean-up
	delete[] img;
	img = NULL;
}

void SaveBMP(const Uint8 greyValue, const Uint8 maximumStep, const Uint8 min, const Uint8 max)
{
	FILE * f_out;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	char fileName[260] = "test.bmp";

	//default image size unless user specifies otherwise
	Sint32 width = 640;
	Sint32 height = 480;

	QueryImageSize(width, height);

	cPixel* img = new cPixel[width * height];

	//int randomStep = (rand() % (maximumStep * 2) - maximumStep);
	int randomStep = (rand() % (maximumStep * 2) + (0 - maximumStep));
	if((greyValue + randomStep) > max)
	{
		randomStep = max - greyValue;
	}
	else if((greyValue + randomStep) < min)
	{
		randomStep = min - greyValue;
	}
	img[0].b = greyValue + randomStep;
	img[0].g = greyValue + randomStep;
	img[0].r = greyValue + randomStep;

	//refer to paper notes to understand these (and the math done with these)
	Uint8 y = -1;
	Uint8 x = -1;
	Uint8 zmin = -1;
	Uint8 zmax = -1;

	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			if(!(j < width))//not first row
			{
				y = img[(i * (width - 1)) + j].b;
				x = img[((i * width) + j) - 1].b;
				if(x < y)
				{
					zmin = y - maximumStep;
					zmax = x + maximumStep;
				}
				else
				{
					zmin = x - maximumStep;
					zmax = y + maximumStep;
				}
				randomStep = rand() % (zmax - zmin) + zmin;
				if((greyValue + randomStep) > max)
				{
					randomStep = max - greyValue;
				}
				else if((greyValue + randomStep) < min)
				{
					randomStep = min - greyValue;
				}
				img[(i * width) + j].b = randomStep;
				img[(i * width) + j].g = randomStep;
				img[(i * width) + j].r = randomStep;
			}
			else if((j < width) && (j != 0))//first row but not first tile
			{
				//randomStep = (rand() % (maximumStep * 2) + maximumStep);
				randomStep = (rand() % (maximumStep * 2) + (0 - maximumStep));
				if((greyValue + randomStep) > max)
				{
					randomStep = max - greyValue;
				}
				else if((greyValue + randomStep) < min)
				{
					randomStep = min - greyValue;
				}
				img[(i * width) + j].b = img[i - 1].b + randomStep;
				img[(i * width) + j].g = img[i - 1].g + randomStep;
				img[(i * width) + j].r = img[i - 1].r + randomStep;
			}
		}
	}

	//Open file
	f_out = fopen(fileName, "wb");
	printf("Opening file \"%s\" to write in binary mode...\n", fileName);
	if(f_out)
	{
		printf("File \"%s\" opened succesfully.\n", fileName);
		bfh.bfType = (0x4D42);//Specifies the file type. The file is a bmp if this is equal to 0x4D42
		bfh.bfSize = width * height;//Bitmap file size in bytes
		bfh.bfReserved1 = 0;//Must be 0
		bfh.bfReserved2 = 0;//Must be 0
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//Offset in bytes from the bitmapfileheader to the bitmap bits

		//Write bmp file header
		printf("Writing bmp file header...\n");
		if(fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER))
		{
			printf("Done writing bmp file header.\n");

			bih.biSize = sizeof(BITMAPINFOHEADER);//Number of bytes required by the struct
			bih.biWidth = width;
			bih.biHeight = height;
			bih.biPlanes = 1;//Number of colour planes, must be 1
			bih.biBitCount = 8;//Number of bit per pixel
			bih.biCompression = BI_RGB;//Compression type
			bih.biSizeImage = width * height/*or 0*/;//Image size in bytes
			bih.biXPelsPerMeter = 96;//Pixels per meter in x axis
			bih.biYPelsPerMeter = 96;//Pixels per meter in y axis
			bih.biClrUsed = 0;//Number of colours used by the bitmap
			bih.biClrImportant = 0;//Number of colours that are important

			//Write bmp info header
			printf("Writing bmp info header...\n");
			if(fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{
				printf("Done writing bmp info header.\n");

				//Write BMP data
				printf("Writing bmp data...\n");
				for(int i = 0; i < (width * height); ++i)
				{
					fwrite(&img[i].b, 1, 1, f_out);
					fwrite(&img[i].g, 1, 1, f_out);
					fwrite(&img[i].r, 1, 1, f_out);
				}
				//for(j*=3; j%4!=0; j++)
				//{
				//	fwrite(&zero,1,1,f_out);//Padding row to 4-byte multiple!
				//}
				printf("Done writing bmp data.\n");
			}
			else
			{
				printf("ERROR: Could not write bitmap info header!\n");
			}
		}
		else
		{
			printf("ERROR: Could not write bitmap file header!\n");
		}
		fclose(f_out);
	}

	//Clean-up
	delete[] img;
	img = NULL;
}

void SaveBMP(const Uint8 blueValue, const Uint8 greenValue, const Uint8 redValue, const Uint8 maximumStep, const Uint8 min, const Uint8 max)
{

}

void QueryImageSize(Sint32& width, Sint32& height)
{
	printf("Would you like to specify a custom image resolution or use the defaults %d x %d?\n", width, height);
	printf("Enter 1 for yes, 0 for no.\n");

	if(UserAgrees())
	{
		width = -1;
		height = -1;

		printf("Please enter your desired image resolution.\n");
		
		printf("Width: ");
		scanf("%d", &width);
		width = EnsurePositive(width);
		printf("\n");
		
		printf("Height: ");
		scanf("%d", &height);
		height = EnsurePositive(height);
		printf("\n");
	}
	else
	{
		printf("Using default image resolution of %d x %d.\n\n", width, height);
	}
}

bool UserAgrees()
{
	int choice = -1;
	while(choice < 0 || choice > 1)
	{
		scanf("%d", &choice);
		if(choice < 0 || choice > 1)
		{
			printf("Invalid option. Please choose again.\n");
		}
	}

	if(choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Sint32 EnsurePositive(Sint32 choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
	return choice;
}

Sint32 AnswerWithinBoundaries(Sint32 answer, const Sint32 lower, const Sint32 upper)
{
	while(answer < lower || answer > upper)
	{
		if(answer < lower)
		{
			printf("Invalid answer. You must enter a value greater than %d.\n", (lower - 1));
			scanf("%d", &answer);
		}
		else if(answer > upper)
		{
			printf("Invalid answer. You must enter a value less than %d.\n", (upper + 1));
			scanf("%d", &answer);
		}
	}
	return answer;
}