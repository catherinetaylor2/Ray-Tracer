#include "BITMAP.hpp"
#include <iostream>
#include <fstream>

void fill_bitmap_headers(BITMAP_File_Header *file_header, BITMAP_Info_Header *info_header, int width, int height){
    file_header->bfType = 0x4d42;
    file_header->bfSize =  54 + width*height*24;
    file_header->bfReserved1 = 0;
    file_header->bfReserved2 = 0;
    file_header->bfOffBits =54;

    info_header->biSize = 40;
    info_header->biWidth = width;
    info_header->biHeight =height ;
    info_header->biPlanes = 1;
    info_header->biBitCount = 24;
    info_header->biCompression = 0;
    info_header->biSizeImage = width*height*24;
    info_header->biXPelsPerMeter= 2835;
    info_header->biYPelsPerMeter= 2835;
    info_header->biClrUsed = 0;
    info_header->biClrImportant = 0;
}

void write_bitmap (BITMAP_File_Header* file_header, BITMAP_Info_Header* info_header, std::ofstream *image){
    image->write((const char*)(&file_header->bfType), sizeof(file_header->bfType) );
    image->write((const char*)(&file_header->bfSize), sizeof(file_header->bfSize) );
    image->write((const char*)(&file_header->bfReserved1), sizeof(file_header->bfReserved1) );
    image->write((const char*)(&file_header->bfReserved2), sizeof(file_header->bfReserved2) );
    image->write((const char*)(&file_header->bfOffBits), sizeof(file_header->bfOffBits) );
    image->write((const char *)(info_header), sizeof(BITMAP_Info_Header));
}