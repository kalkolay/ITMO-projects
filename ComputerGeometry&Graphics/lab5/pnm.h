#include <string>
#include <vector>

struct Pixel { unsigned char A, B, C; };

enum ColorSpace
{
    YCbCr601,
    RGB
};

enum Conversion
{
    RGB_SET,
    YCBCR_SET,
    YCBCR_AUTO_SIMPLE,
    RGB_AUTO,
    YCBCR_AUTO
};

class PNM
{
public:
    PNM();
    ~PNM();

    void read(const std::string&);
    void write(const std::string&);
    void setColorSpace(ColorSpace) noexcept;

    void changeBrightness(double, double) noexcept;
    void setAutoBrightness(bool) noexcept;
private:
    int width;
    int height;
    Pixel* image;
    ColorSpace colorSpace;
    bool color;

    std::vector<int> getBrightestAndDarkest(bool) noexcept;
};