#include "ProcessImg.h"

void ProcessImg::ModifyIntensityLvl(
        Image&          destImg,
        Image* const    sourceImg,
        uint16_t const& desiredIntensity
)
{
    assert(destImg.GetFullImageSize());
    destImg = Image(sourceImg->GetWidth(), sourceImg->GetHeight());
    uint16_t intLvl = destImg.GetIntensityLvl();
    uint32_t fullImgSize = sourceImg->GetFullImageSize();
    assert(fullImgSize > 0);
    memcpy(destImg.GetImageData(), sourceImg->GetImageData(), fullImgSize * sizeof(uint8_t));
    if(intLvl != desiredIntensity)
    {
        if(desiredIntensity & (desiredIntensity - 1) != 0 && desiredIntensity > intLvl)
        {
            printf("Please enter a number that is the power of 2 and less then the img intesity: %d", intLvl);
            return;
        }
        int level = intLvl / desiredIntensity;
        destImg.SetIntensityLvl(desiredIntensity);
        uint8_t* data = destImg.GetImageData();
        for(uint32_t pixel = 0; pixel < fullImgSize; pixel++)
        {
            *data = (*data / level) * level;
            data++;
        }
    }
}

void ProcessImg::FilterImg(
    Image&                  destImg,
    Image* const            sourceImg,
    Matrix<uint8_t>* const  filterImg
)
{
    uint16_t width = sourceImg->GetWidth();
    uint16_t height = sourceImg->GetHeight();
    uint32_t imgSize = destImg.GetFullImageSize();
    uint16_t sumPix{0};
    uint16_t matrixSize = filterImg->GetMatrixSize();
    uint8_t cols = filterImg->GetCols();
    uint8_t* data = destImg.GetImageData();
    uint16_t idx{};

    if(destImg.GetWidth() * destImg.GetHeight() != 
        sourceImg->GetWidth() * sourceImg->GetHeight())
    {
        destImg = Image(sourceImg->GetWidth(), sourceImg->GetHeight());
    }
    assert(imgSize > 0 && width == imgSize / height);

    memcpy(destImg.GetImageData(), sourceImg->GetImageData(), sourceImg->GetFullImageSize());

    for(uint32_t pix = 0; pix < imgSize; pix++)
    {
        if(pix % width + cols < width && 
           pix / width + matrixSize / cols < height)
        {
            for(uint16_t neighbor{0}; neighbor < matrixSize; neighbor++)
            {
                idx = pix + neighbor % cols + neighbor / cols * width;
                sumPix += data[idx]; 
            }
            data[pix] = sumPix / 9;
            sumPix = 0;
        }
        else
        {
            data[pix] = 0;
        }
    }
}

void ProcessImg::RotateImg(
    Image&                  destImg,
    Image* const            sourceImg,
    Matrix<float>* const    rotMatrix
)
{
    uint16_t width = sourceImg->GetWidth();
    uint16_t height = sourceImg->GetHeight();
    uint32_t imgSize = destImg.GetFullImageSize();
    uint8_t* rotatedData = destImg.GetImageData();
    uint8_t* data = sourceImg->GetImageData();
    float* rotMat = rotMatrix->GetMatrix();
    uint16_t idxA{};
    if(destImg.GetWidth() * destImg.GetHeight() != 
        sourceImg->GetWidth() * sourceImg->GetHeight())
    {
        destImg = { sourceImg->GetWidth(), sourceImg->GetHeight() };
    }
    assert(imgSize > 0 && width == imgSize / height);
    memcpy(destImg.GetImageData(), sourceImg->GetImageData(), sourceImg->GetFullImageSize());

    // Calculate the center of the image
    int centerX = width / 2;
    int centerY = height / 2;
    int srcX {0};
    int srcY {0};

    for(int pix = 0; pix < height * width; pix++)
    {
        srcX = static_cast<int>
        (
            std::round
            (
                rotMat[4] * 
                (pix % width - centerX) + rotMat[7] * 
                (pix / width - centerY) + centerX
            )
        );
        srcY = static_cast<int>
        (
            std::round
            (
                rotMat[5] * 
                (pix % width - centerX) + rotMat[8] * 
                (pix / width - centerY) + centerY
            )
        ); 
        if (srcX >= 0 && srcX < width && srcY >= 0 && srcY < height) 
        {
            idxA = srcY * width + srcX;
            rotatedData[pix] = data[idxA];
            
        } 
        else
        {
            rotatedData[pix] = 0;  // Background color
        }
    }
}

void ProcessImg::CreateJPEG(
    Image& destImg,
    Image* const sourceImg,
    uint8_t const& quantScale
)
{
    assert(sourceImg->GetFullImageSize() > 0);
    if(sourceImg->GetFullImageSize() != destImg.GetFullImageSize())
    {
        destImg = {sourceImg->GetWidth(), sourceImg->GetHeight()};
    }
    uint8_t pixelBlock8x8[64]{};
    uint8_t* pixelDataIn = sourceImg->GetImageData();
    uint16_t width = sourceImg->GetWidth();
    uint16_t height = sourceImg->GetHeight();
    uint16_t currentLine = 0;
    for(uint16_t block = 0; block < sourceImg->GetFullImageSize();)
    {
        for(uint8_t u = 0; u < 8; u++)
        {
            for(uint8_t v = 0; v < 8; v++)
            {
                pixelBlock8x8[u * 8 + v] = pixelDataIn[block % width + v + (block / width + u) * width];
            }
        }
        if((block + 8) / width > currentLine)
        {
            block = (block / width + 8) * width;
            currentLine = block / sourceImg->GetWidth() + 8;
        }
        else
        {
            block += 8;
        }
    }
    ComputeDCT(destImg, sourceImg);
    ApplyQuantisation(destImg, quantScale);
    ComputeInverseDCT(destImg, &destImg);
}

void ProcessImg::ComputeDCT(
    Image& destImg,
    Image* const sourceImg
)
{
    int i, j, u, v;
    uint8_t N{8}, M{8};
    uint8_t* pixelDest = destImg.GetImageData();
    uint8_t* pixelSource = sourceImg->GetImageData();
    uint16_t imageSize = sourceImg->GetFullImageSize();
    for (u = 0; u < N; ++u) 
    {
        for (v = 0; v < M; ++v) 
        {
            for (i = 0; i < N; i++) 
            {
                for (j = 0; j < M; j++)
                {
                    pixelDest[u * v] += pixelSource[i * j] * 
                                        cos(M_PI/((float)N) * 
                                        (i + 1.0 / 2.0) * u) * 
                                        cos(M_PI/((float)M) * 
                                        (j + 1.0 / 2.0) * v);
                }               
            }
        }
    }  
    
}

void ProcessImg::ComputeInverseDCT(
    Image &destImg,
    Image *const sourceImg)
{
    uint8_t N{8}, M{8}, u, v, i, j;
    uint8_t* pixelDest = destImg.GetImageData();
    uint8_t* pixelSource = sourceImg->GetImageData();
    uint16_t imageSize = sourceImg->GetFullImageSize();
    uint16_t widthImg = sourceImg->GetWidth();
    for(uint16_t block = 0; block < imageSize; )
    {
        for (u = 0; u < N; ++u) 
        {
            for (v = 0; v < M; ++v)
            {
                // Matrix[u][v] = 1.0 / 4.0 * DCTMatrix[0][0];
                pixelDest[u * v + block] = 1.0 / 4.0 * pixelSource[0];
                for(i = 1; i < N; i++)
                {
                    // Matrix[u][v] += 1.0 / 2.0 * DCTMatrix[i][0];
                    pixelDest[u * v] += 1.0 / 2.0 * pixelSource[i * N];
                }
                for(j = 1; j < M; j++)
                {
                    // Matrix[u][v] += 1.0 / 2.0 * DCTMatrix[0][j];
                    pixelDest[u * v] += 1.0 / 2.0 * pixelSource[j];
                }

                for (i = 1; i < N; i++)
                {
                    for (j = 1; j < M; j++) 
                    {
                        // Matrix[u][v] += DCTMatrix[i][j] * 
                        //                 cos(M_PI/((float)N) *
                        //                 (u + 1.0/2.0) * i)*
                        //                 cos(M_PI / ((float)M) *
                        //                 (v + 1.0/2.0) * j);
                        pixelDest[u * v] += pixelSource[i * j] *
                                            cos(M_PI/((float)N) *
                                            (u + 1.0/2.0) * i)*
                                            cos(M_PI / ((float)M) *
                                            (v + 1.0/2.0) * j);
                    }               
                }
                // Matrix[u][v] *= 2.0 / ((float)N) * 2.0 / ((float)M);
                pixelDest[u * v] *= 2.0 / ((float)N) * 2.0 / ((float)M);
            }
        }
        if (block % widthImg == 0)
        {

        }  
    }

}

void ProcessImg::ApplyQuantisation(
    Image& destImg,
    uint8_t const& quantScale
)
{
    uint8_t* pixelData = destImg.GetImageData();
    for(uint16_t i = 0; destImg.GetFullImageSize(); i++)
    {
        pixelData[i] = pixelData[i] / quantScale;
    }
}