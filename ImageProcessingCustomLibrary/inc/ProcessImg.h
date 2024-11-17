#include <stdint.h>
#include <stdio.h>
#include "Image.h"
#include "Matrix.h"
#pragma once
class ProcessImg
{
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
    void CreateJPEG(
        Image&      destImg,
        Image* const sourceImg,
        uint8_t const& quantScale
    );
private:
    void ComputeDCT(
        Image& destImg,
        Image* const sourceImg
    );
    void ComputeInverseDCT(
        Image& destImg,
        Image* const sourceImg
    );
    void ApplyQuantisation(
        Image& destImg,
        uint8_t const& quantScale
    );
};
