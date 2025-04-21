#include<iostream>
#include"image.h"
#include "io_tools.h"
#include<cmath>

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

std::vector<float> Image::ComputeHistogram(int bins) {
	std::vector<float> histogram(bins);
	for(auto item:data_){
		int idx = (int)floor(item/bins);
		++histogram[idx] ;
	}
	return histogram;
}

void Image::DownScale(int scale) {
	std::vector<int> scaled_image;
	for(int r_idx = 0;r_idx < rows_; r_idx += scale) {
		for(int c_idx = 0;c_idx < cols_; c_idx += scale) {
			scaled_image.push_back(data_[rows_ * r_idx + c_idx]);
		}
	}
	rows_ /=scale;
	cols_ /=scale;
	data_ = scaled_image;
}

void Image::UpScale(int scale) {
	int upscaled_rows = rows_*scale;
    int upscaled_cols = cols_*scale;
    std::vector<int> upscaled_image(upscaled_rows * upscaled_cols + 1, 0);

    // Iterate over the image
    for (int i = 0; i < rows_; i++) {
        int row_jump = i * scale;
        for (int j = 0; j < cols_; j++) {
            int col_jump = j*scale;
            // Fill values for upscaled image
            for (int u = 0; u < scale; u++) {
                for (int v = 0; v < scale; v++) {
                    upscaled_image[(row_jump+u)*upscaled_cols + col_jump + v] = data_[i * cols_ + j];
                }
            }
        }
    }

    rows_ = upscaled_rows;
    cols_ = upscaled_cols;
    data_ = upscaled_image;
}
}

