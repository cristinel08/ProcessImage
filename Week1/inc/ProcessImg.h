#include <stdint.h>
#include <stdio.h>
#include "Image.h"
#include "Matrix.h"
class ProcessImg
{
private:
    /* data */
public:
    ProcessImg() = delete;
    ~ProcessImg() = delete;

    static void ModifyIntensityLvl(
        Image&          destImg,
        Image* const    sourceImg,
        uint16_t const& desiredIntensity
    );

    static void FilterImg(
        Image&                 destImg,
        Image* const           sourceImg,
        Matrix<uint8_t>* const filterImg
    );
};
