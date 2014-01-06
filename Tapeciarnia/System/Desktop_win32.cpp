#ifdef _WIN32

#include "Desktop.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>

#include <windows.h>
#include <stdio.h>
#include <gdiplus.h>

using namespace Gdiplus;

static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

static Bitmap *RescaleBitmap(Bitmap *bmp, int destWidth, int destHeight)
{
    int bitmapWidth = bmp->GetWidth();
    int bitmapHeight = bmp->GetHeight();

    int srcWidth;
    int srcHeight;
    if (bitmapWidth*1.0 / bitmapHeight > destWidth*1.0 / destHeight)
    {
        srcWidth = bitmapHeight * (destWidth*1.0 / destHeight);
        srcHeight = bitmapHeight;
    }
    else
    {
        srcWidth = bitmapWidth;
        srcHeight = bitmapWidth * (destHeight*1.0 / destWidth);
    }

    Bitmap *newBitmap = new Bitmap(destWidth, destHeight);
    Graphics *g = Graphics::FromImage(newBitmap);
    g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    Rect destRect(0, 0, destWidth, destHeight);
    g->DrawImage(bmp, destRect,
                 (int)((bitmapWidth - srcWidth) / 2),
                 (int)((bitmapHeight - srcHeight) / 2),
                 srcWidth, srcHeight, UnitPixel);
    delete g; g = 0;

    return newBitmap;
}

static void ConvertImageToBMP(const QString &src, const QString &dest,
                              int width, int height)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    Bitmap *bmp = Bitmap::FromFile(src.toStdWString().c_str());
    Bitmap *newBitmap = RescaleBitmap(bmp, width, height);
    delete bmp; bmp = 0;

    CLSID bmpClsid;
    GetEncoderClsid(L"image/bmp", &bmpClsid);
    newBitmap->Save(dest.toStdWString().c_str(), &bmpClsid, NULL);
    delete newBitmap; newBitmap = 0;

    GdiplusShutdown(gdiplusToken);
}

QRect Desktop::GetSize()
{
    return QApplication::desktop()->screenGeometry();
}

void Desktop::SetWallpaper(const QByteArray &image)
{
    QString wallpaperPathJPG = QApplication::applicationDirPath() + "/wallpaper.jpg";
    QString wallpaperPathBMP = QApplication::applicationDirPath() + "/wallpaper.bmp";

    // save array
    QFile file(wallpaperPathJPG);
    file.open(QIODevice::WriteOnly);
    file.write(image);
    file.close();

    QRect desktopSize = GetSize();
    int desktopWidth = desktopSize.width();
    int desktopHeight = desktopSize.height();

    ConvertImageToBMP(wallpaperPathJPG, wallpaperPathBMP,
                      desktopWidth, desktopHeight);

    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0,
                          (void*)wallpaperPathBMP.toStdWString().c_str(),
                          SPIF_SENDCHANGE);
}

#endif // _WIN32
