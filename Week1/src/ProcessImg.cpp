#include "ProcessImg.h"

void ProcessImg::ModifyIntensityLvl(
        Image&          destImg,
        Image* const    sourceImg,
        uint16_t const& desiredIntensity
)
{
    destImg = Image(sourceImg->GetWidth(), sourceImg->GetHeight());
    uint16_t intLvl = destImg.GetIntensityLvl();
    uint32_t fullImgSize = sourceImg->FullImageSize();
    memcpy(destImg.GetImageData(), sourceImg->GetImageData(), fullImgSize * sizeof(uint8_t));
    if(intLvl != desiredIntensity)
    {
        if(desiredIntensity & (desiredIntensity - 1) != 0 && desiredIntensity > intLvl)
        {
            printf("Please enter a number that is the power of 2 and less then the img intesity: %d", intLvl);
            return;
        }
        int level = intLvl / desiredIntensity;
        destImg.SetIntensityLvl(desiredIntensity);
        uint8_t* data = destImg.GetImageData();
        for(uint32_t pixel = 0; pixel < fullImgSize; pixel++)
        {
            *data = (*data / level) * level;
            data++;
        }
    }
}

void ProcessImg::FilterImg(
    Image&                  destImg,
    Image* const            sourceImg,
    Matrix<uint8_t>* const  filterImg
)
{
    destImg = Image(sourceImg->GetWidth(), sourceImg->GetHeight());
    memcpy(destImg.GetImageData(), sourceImg->GetImageData(), sourceImg->FullImageSize());
    uint16_t width = sourceImg->GetWidth();
    uint16_t height = sourceImg->GetHeight();
    uint32_t imgSize = destImg.FullImageSize();
    uint16_t sumPix{0};
    uint16_t matrixSize = filterImg->GetMatrixSize();
    uint8_t cols = filterImg->GetCols();
    uint8_t* data = destImg.GetImageData();
    uint16_t idx{};
    for(uint32_t pix = 0; pix < imgSize; pix++)
    {
        if(pix % width + cols < width && 
           pix / width + matrixSize / cols < height)
        {
            for(uint16_t neighbor{0}; neighbor < matrixSize; neighbor++)
            {
                idx = pix + neighbor % cols + neighbor / cols * width;
                sumPix += data[idx]; 
            }
            data[pix] = sumPix / 9;
            sumPix = 0;
        }

    }
}