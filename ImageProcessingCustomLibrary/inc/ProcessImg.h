#include <stdint.h>
#include <stdio.h>
#include "Image.h"
#include "Matrix.h"
#pragma once
class ProcessImg
{
private:
    /* data */
public:
    ProcessImg() = default;
    ~ProcessImg() = default;

    void ModifyIntensityLvl(
        Image&          destImg,
        Image* const    sourceImg,
        uint16_t const& desiredIntensity
    );

    void FilterImg(
        Image&                 destImg,
        Image* const           sourceImg,
        Matrix<uint8_t>* const filterImg
    );

    void RotateImg(
        Image&                  destImg,
        Image* const            sourceImg,
        Matrix<float>* const    rotMatrix
    );
};
