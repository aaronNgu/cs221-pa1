#include "block.h" 

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

void Block::build(PNG & im, int column, int width) {
    // Note the boundaries are set to indicate that we want to stop at the width position
    // Not many pixels we want to go to 
    for (int x = column; x < column + width; x++) { 
        vector<HSLAPixel> verticalStrip; 
        for (unsigned int y = 0; y < im.height(); x++) {
            HSLAPixel * gottenPixel = im.getPixel(x,y);
            verticalStrip.push_back(*gottenPixel);
        }
        data.push_back(verticalStrip);
        }
    }

void Block::render(PNG & im, int column ) const {
    // Replaces each strip of image with the columns in the data one by one.
    // Start at the column index of the image
    // Replace the coloumn of the original image with the new 
    for (unsigned int y = 0; y < im.height(); y++) {
        for (unsigned int x = column; x < column + width(); x++) {
            *(im.getPixel(x,y)) = data[x-column][y] ;
        }

    }

}

void Block::greyscale() {
    for (unsigned y = 0; y < height( ); y++) {
        for (unsigned x = 0; x < width(); x++) {
            HSLAPixel gottenPixel = data[x][y];
            gottenPixel.s=0;
        }
    }
}





