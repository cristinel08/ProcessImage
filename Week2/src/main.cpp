#include "ProcessImg.h"

int main()
{
    Image sourceImg{100, 100};
    Image destinationImg{};
    ProcessImg process{};
    sourceImg.ReadImg("carnavalWheel.jfif");
    sourceImg.Display(100, "Input");
    process.CreateJPEG(destinationImg, &sourceImg, 127);
    destinationImg.Display(100, "FilterOut");
    return 0;
}