#include "ProcessImg.h"
// #include "Math.h"
#include <iostream>
int main()
{
    Image sourceImg{100, 100};
    Image destinationImg{};
    ProcessImg process{};
    sourceImg.ReadImg("carnavalWheel.jfif");
    process.ModifyIntensityLvl(destinationImg, &sourceImg, 2);
    sourceImg.Display(100, "Input");
    destinationImg.Display(100, "IntensityLvlOut");
    Matrix<uint8_t>matrix(3, 3);
    process.FilterImg(destinationImg, &sourceImg, &matrix);
    destinationImg.Display(100, "FilterOut");
    Matrix<float> a{3, 3};
    a.CreateRotMatrix(180.0);
    process.RotateImg(destinationImg, &sourceImg, &a);
    destinationImg.Display(0, "Rotated Output");

    return 0;
}