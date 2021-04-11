#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

using uiuc::PNG;
using uiuc::HSLAPixel;

PNG grayscale(PNG image) {
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.s = 0;
    }
  }

  return image;
}


PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned i = 0; i < image.width(); i++)
  {
    for (unsigned j = 0; j < image.height(); j++)
    {
      HSLAPixel & pixel = image.getPixel(i, j);
      
      int hor = centerX - i;

      int ver = centerY - j;

      if(hor < 0)
      {
        hor = -hor;
      }
      if(ver < 0)
      {
        ver = -ver;
      }
      double away = sqrt((hor*hor) + (ver*ver));
      double dec = min(away*0.5,80.0);

      pixel.l = pixel.l - (dec/100) * pixel.l ;
    }
    
  }
  
  return image;
  
}
 
PNG illinify(PNG image) {

  for (unsigned i = 0; i < image.width(); i++)
  {
    for (unsigned j = 0; j < image.height(); j++)
    {
      HSLAPixel & pixel = image.getPixel(i, j);

      if(pixel.h >= 113.5 && pixel.h <= 293.5)
      {
        pixel.h = 216;
      }else
      {
        pixel.h = 11;
      }
      
    }
    
  }

  return image;
}

PNG watermark(PNG firstImage, PNG secondImage) {

  for (unsigned i = 0; i < secondImage.width(); i++)
  {
    for (unsigned j = 0; j < secondImage.height(); j++)
    {
      HSLAPixel& secondPixel = secondImage.getPixel(i,j);
      HSLAPixel& fisrPixel = firstImage.getPixel(i,j);

      if (secondPixel.l == 1)
      {
        fisrPixel.l += 0.2;
      }
      
    }
    
  }
  
  return firstImage;
}
