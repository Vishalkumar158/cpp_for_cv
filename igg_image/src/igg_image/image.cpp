#include<iostream>
#include"image.h"
#include "io_tools.h"

namespace igg{
Image::Image(){};
Image::Image(int rows, int cols):rows_(rows),cols_(cols){};

int Image::rows(){
    return rows_;
}

int Image::cols(){
    return cols_;
}

int& Image::at(const int& row, const int& col){
    return data_[rows_ *row + col];
}

bool Image::FillFromPgm(const std::string& file_name){
    io_tools::ImageData image_data = io_tools::ReadFromPgm(file_name);
    if(image_data.data.size() == 0){
        return false;
    }else{
        data_ = image_data.data;
        rows_ = image_data.rows;
        cols_ = image_data.cols;

        return true;
    }
}

void Image::WriteToPgm(const std::string& file_name) {
	
	io_tools::ImageData image_data;
	image_data.data = data_;
	image_data.rows = rows_;
	image_data.cols = cols_;
	image_data.max_val = max_val_;
	io_tools::WriteToPgm(image_data, file_name);
}
}

