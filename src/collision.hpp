#pragma once
#include <QuickGame.hpp>
#include <cmath>
using namespace QuickGame::Graphics;
int getRed(int x, int y, QGTexture tex)
		{
		    QGTexture* testImage = &tex;

            float box_width = testImage->width/(testImage->width*4/16);
            float box_height = testImage->height/(testImage->height/8);
            float box_num = testImage->width/box_width;

		    /// box width = 4
		    /// box height = 8
		    /// strip = 64
		    /// strip number = 4096
		    /// box number  = 64

		    float box_x = x / box_width;
		    floor(box_x);
		    box_x = (int)box_x;
		    float box_y = y / box_height;
		    floor(box_y);
		    box_y = (int)box_y;

		    int box_number = box_x + (box_y * box_num);
		    int box_first_index = box_number * box_width*box_height*2;

		    int x_in_box = x - (box_x * box_width);
		    int y_in_box = y - (box_y * box_height);

		    int end_index = box_first_index + ((x_in_box*2) + (y_in_box*box_width*2));
            u32 returnval = ((uint32_t*)testImage->data)[end_index];
            return returnval;
            //testImage->ImageData[end_index+1] >> 8;
		}