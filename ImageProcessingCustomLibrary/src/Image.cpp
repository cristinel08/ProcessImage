#include "Image.h"

Image::Image(
    void
)
{
    width_          = 0 ;
    height_         = 0 ;
    channels_       = 0 ;
    intensityLvl_   = 0 ;
    img_ = cv::Mat::zeros(100, 100, CV_8U);
}

Image::~Image(
    void
)
{
    img_.release();
}

Image::Image(
    uint16_t const& width,
    uint16_t const& height
) : width_  { width },
    height_ { height },
    channels_{ 1 },
    intensityLvl_{ 256 }
{
    img_ = cv::Mat::zeros(cv::Size{width, height}, CV_8U);
    // img_.release();
}

void Image::ReadImg(
    std::string const& imgPath
)
{
    img_ = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);
    width_ = img_.cols;
    height_ = img_.rows;
    channels_ = img_.channels();
}

void Image::SetIntensityLvl(
    uint16_t const& intensityLvl
)
{
    intensityLvl_ = intensityLvl;
}

uint8_t* Image::GetImageData(
    void
)
{
    return reinterpret_cast<uint8_t*>(img_.data);
}

uint32_t Image::FullImageSize(
    void
)
{
    return static_cast<uint32_t>(width_ * height_ * channels_);
}

uint16_t Image::GetIntensityLvl(
    void
)
{
    return intensityLvl_;
}

void Image::Display(
    uint8_t const& delay,
    std::string const& windowName
)
{
    cv::imshow(windowName, img_);
    cv::waitKey(delay);
}

uint16_t Image::GetWidth(
    void
)
{
    return width_;
}

uint16_t Image::GetHeight(
    void
)
{
    return height_;
}
