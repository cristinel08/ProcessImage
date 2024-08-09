// #include "opencv2/"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "ProcessImg.h"
#include <memory>
class Image
{
private:
    /* data */
    cv::Mat img_;
    std::unique_ptr<ProcessImg> processImg_;

public:
    Image() = default;
    ~Image() = default;
    Image(
        uint16_t const& width,
        uint16_t const& height
    );
    void ReadImg(
        std::string const& imgPath
    );
    void Display(
        uint8_t const& delay,
        std::string const& windowName
    );
    ProcessImg* GetProcessImg(
        void
    );
};
