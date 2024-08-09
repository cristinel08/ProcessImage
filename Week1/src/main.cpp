#include "ProcessImg.h"
int main()
{
    Image sourceImg{100, 100};
    Image destinationImg{};
    sourceImg.ReadImg("carnavalWheel.jfif");
    ProcessImg::ModifyIntensityLvl(destinationImg, &sourceImg, 2);
    sourceImg.Display(0, "Window");
    destinationImg.Display(0, "DestWnd");
    Matrix<uint8_t>matrix(3, 3);
    ProcessImg::FilterImg(destinationImg, &sourceImg, &matrix);
    destinationImg.Display(0, "FilterWnd");
    return 0;
}