#include <stdint.h>
#include <stdio.h>
class ProcessImg
{
private:
    /* data */
    uint16_t width_;
    uint16_t height_;
    uint8_t channels_;
    uint16_t intensityLvl_;
    uint8_t* imgPixels_;
public:
    ProcessImg() = default;
    ~ProcessImg() = default;
    ProcessImg(
        uint16_t const& width,
        uint16_t const& height,
        uint8_t const&  channels,
        uint8_t*        imgData
    );
    void SetProcessData(
        uint16_t const& width,
        uint16_t const& height,
        uint8_t const&  channels,
        uint8_t*        imgData
    );
    void ModifyIntensityLvl(
        uint16_t const& intensityLvl
    );
};
