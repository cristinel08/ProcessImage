#include "Image.h"

Image::Image(
    uint16_t const& width,
    uint16_t const& height
)
{
    img_ = cv::Mat::zeros(cv::Size{width, height}, CV_8U);
    processImg_ = std::make_unique<ProcessImg>(
                    width, 
                    height, 
                    img_.channels(), 
                    img_.data
                );
}

void Image::ReadImg(
    std::string const& imgPath
)
{
    img_ = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);
    processImg_->SetProcessData(img_.cols, img_.rows, img_.channels(), img_.data);
}

void Image::Display(
    uint8_t const& delay,
    std::string const& windowName
)
{
    cv::imshow(windowName, img_);
    cv::waitKey(delay);
}

ProcessImg* Image::GetProcessImg(
    void
)
{
    return processImg_.get();
}
