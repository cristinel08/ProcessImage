#include "Image.h"

int main()
{
    Image img(100, 100);
    img.ReadImg("carnavalWheel.jfif");
    img.Display(0, "Window");
    img.GetProcessImg()->ModifyIntensityLvl(2);
    img.Display(0, "Window with 2 intensity lvl");
    return 0;
}