#include "block.h"
   
   
   void Block::build(PNG & im, int column, int width){
       // Note the boundaries are set to indicate that we want to stop at the width position
       // Not many pixels we want to go to 
    unsigned int height = im.height();

       for(int x = column; x < column + width; x++){
           vector<HSLAPixel> verticalStrip;
            for(unsigned int y = 0; y < height; y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            verticalStrip.push_back(*pixel);
            }
            data.push_back(verticalStrip);
       }   
    }
   
   void Block::render(PNG & im, int column) const{
       // Replaces each strip of image with the columns in the data one by one.
       // Start at the column index of the image
       // Replace the coloumn of the original image with the new 
        for (unsigned int y = 0; y < im.height(); y++) {
            for (int x = column; x < column + width(); x++) {
                *(im.getPixel(x,y)) = data[x-column][y] ;
             }
        } 
   }

   void Block::greyscale() {
        for(int y = 0; y < height() ; y++){
            for(int x = 0; x < width();x++){
                data[x][y].s = 0;
             }
        }
   }

   int Block::width() const {
           return data.size();
   } 

   int Block::height() const {
        if (data.size() != 0) {
        return data[0].size();
        // Safest choice to see if the image is one pixel.
    }
    else return 0;
   }
 