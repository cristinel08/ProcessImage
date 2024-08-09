#include "ProcessImg.h"

ProcessImg::ProcessImg(
    uint16_t const& width,
    uint16_t const& height,
    uint8_t const&  channels,
    uint8_t*        imgData
) : intensityLvl_ { 256 }
{
    SetProcessData(width, height, channels, imgData);
}

void ProcessImg::SetProcessData(
    uint16_t const& width,
    uint16_t const& height,
    uint8_t const&  channels,
    uint8_t*        imgData
)
{
    width_ = width;
    height_ = height;
    channels_ = channels;
    imgPixels_ = imgData;
}

void ProcessImg::ModifyIntensityLvl(
    uint16_t const& intensityLvl
)
{
    if(intensityLvl_ != intensityLvl)
    {
        if(intensityLvl & (intensityLvl - 1) != 0 && intensityLvl > intensityLvl_)
        {
            printf("Please enter a number that is the power of 2 and less then the img intesity: %d", intensityLvl_);
            return;
        }
        int level = intensityLvl_ / intensityLvl;
        intensityLvl_ = intensityLvl;
        uint8_t* data = imgPixels_;
        for(uint32_t pixel = 0; pixel < width_ * height_ * channels_; pixel++)
        {
            *data = (*data / level) * level;
            data++;
        }
    }
}