// #include "opencv2/"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <memory>
#include "Matrix.h"
#pragma once
class Image
{
public:
    Image();
    ~Image();
    Image(
        uint16_t const& width,
        uint16_t const& height
    );
    void SetIntensityLvl(
        uint16_t const& intesityLvl
    );
    uint8_t* GetImageData(
        void
    );
    uint32_t GetFullImageSize(
        void
    );
    void ReadImg(
        std::string const& imgPath
    );
    void Display(
        uint8_t const& delay,
        std::string const& windowName
    );
    uint16_t GetIntensityLvl(
        void
    );
    uint16_t GetWidth(
        void
    );
    uint16_t GetHeight(
        void
    );
    cv::Mat GetMat(
        void
    );

private:
    /* data */
    cv::Mat img_;
    uint16_t width_;
    uint16_t height_;
    uint8_t channels_;
    uint16_t intensityLvl_;
};
