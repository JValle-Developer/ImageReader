#include <winbgim.h>
 #include <string.h>
 #include<windows.h>
 #include<stdio.h>
 #include <stdlib.h>

 const char *Filename;

 BITMAPFILEHEADER FileHeader;
 BITMAPINFOHEADER InfoHeader;
 int k;
 typedef struct{
 BYTE colorr;
 BYTE colorg;
 BYTE colorb;
 }cine;

 cine color;

 HANDLE hArch, hProy;
 LPSTR base,puntero;
 DWORD tam;
 int main()
 {
 int gdriver=9;
 int gmode=2;
 // initgraph(&gdriver,&gmode, "");
 cleardevice();

 UnmapViewOfFile(base);
 CloseHandle(hProy);
 CloseHandle(hArch);
 char *p;
 char *base;
 DWORD buf;
 Filename="D:\\music\\IMSLP00795-BWV0971\\01.bmp";
 int gd = DETECT, gm;
 int x = 320, y = 240, radius;
 k=0;

 int i;
 int j;




 FILE *File=NULL;
 if(!Filename)
 {
 MessageBox(NULL,"Konnte Filename nicht  finden!","Error",MB_OK|MB_ICONERROR);
 }
 else
 {
 File=fopen("D:\\music\\IMSLP00795-BWV0971\\01.bmp","rb");
 }

 fread(&FileHeader,sizeof(BITMAPFILEHEADER),1,File);
 if(FileHeader.bfType != 0x4D42)
 {
 MessageBox(NULL,"Ungültiges Bildformat!","Error",MB_OK|MB_ICONERROR);
 exit(1); 
 }
 printf("tamaño total del archivo %d\n",FileHeader.bfSize);
 printf("comienzo del mapa de bits (imagen en pixels) en bits         %d\n",FileHeader.bfOffBits);

 buf=FileHeader.bfOffBits/8; //offset from the begining of BMP file (pixel array)
 printf("comienzo del mapa de bits en bytes desde el origen del archivo      %d\n",buf);
 fread(&InfoHeader,sizeof(BITMAPINFOHEADER),1,File);

 printf("horizontal resolution in pixels por metro %li\n",InfoHeader.biWidth);
 printf("vertical resolution in pixels por metro %li\n",InfoHeader.biHeight);
 printf("numero de bits por pixel %d", InfoHeader.biBitCount);
 initwindow(InfoHeader.biWidth,InfoHeader.biHeight);


 hArch = CreateFile("D:\\music\\IMSLP00795-BWV0971\\01.bmp", /* file  name */
 GENERIC_ALL , /* read/write access */
 0, /* no sharing of the file */
 NULL, /* default security */
 OPEN_ALWAYS, /* open new or existing file */
 FILE_ATTRIBUTE_NORMAL, /* routine file attributes */
 NULL); /* no file template */
 if (hArch==INVALID_HANDLE_VALUE){

 fprintf(stderr,"no puede abrirse el archivo");

 }

 hProy = CreateFileMapping(hArch, /* file handle */
 NULL, /* default security */
 PAGE_READWRITE, /* read/write access to mapped pages */
 0, /* map entire file */
 0,
 TEXT("SharedObject")); /* named shared memory object */

 /* write to shared memory */
 base=(LPSTR)MapViewOfFile(hProy,FILE_MAP_ALL_ACCESS,0,0,0);
 tam=GetFileSize(hArch,NULL);
 int cont=0;
 puntero=base;
 p=base+FileHeader.bfOffBits;
 k=0;int t=0,v,l;
 fseek(File,FileHeader.bfOffBits,SEEK_SET );
 int read=0,read2=0;
 k=0;
 for( i=0; i<InfoHeader.biWidth; i++ ) {
       fread(&color,sizeof(cine),1,File);
        read += sizeof(cine);
        printf( "Pixel %d: %3d %3d %3d\n", i+1, int(color.colorb),         int(color.colorg), int(color.colorr) );
    }
    if( read % 4 != 0 ) {
        read2 = 4 - (read%4);
        printf( "Padding: %d bytes\n", read2 );
        //fread( &color, read2, 1, File );

    }
    fseek(File,FileHeader.bfOffBits,SEEK_SET );
    for (i=0;i<InfoHeader.biHeight;i++)
 for(j=0;j<InfoHeader.biWidth ;j++)

{
 fread(&color,sizeof(cine),1,File);

 putpixel(j,InfoHeader.biHeight-  i,COLOR(int(color.colorb),int(color.colorg),int(color.colorr)));
 if(j==InfoHeader.biWidth-1&&read2!=0)fseek(File,read2,SEEK_CUR);
} 
 fclose(File);

 UnmapViewOfFile(base);
 CloseHandle(hProy);
 CloseHandle(hArch);
 getch();
}