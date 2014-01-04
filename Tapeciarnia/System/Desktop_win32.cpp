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

    ConvertImageToBMP(wallpaperPathJPG, wallpaperPathBMP);

    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0,
                          (void*)wallpaperPathBMP.toStdWString().c_str(),
                          SPIF_SENDCHANGE);
}

void Desktop::ConvertImageToBMP(const QString &src, const QString &dest)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    Bitmap *bmp = Bitmap::FromFile(src.toStdWString().c_str());
    Bitmap *newBitmap = Desktop::RescaleBitmapToFillScreen(bmp);
    delete bmp; bmp = 0;

    CLSID bmpClsid;
    GetEncoderClsid(L"image/bmp", &bmpClsid);
    newBitmap->Save(dest.toStdWString().c_str(), &bmpClsid, NULL);
    delete newBitmap; newBitmap = 0;

    GdiplusShutdown(gdiplusToken);
}

Bitmap *Desktop::RescaleBitmapToFillScreen(Bitmap *bmp)
{
    int bitmapWidth = bmp->GetWidth();
    int bitmapHeight = bmp->GetHeight();

    QRect desktopSize = GetSize();
    int desktopWidth = desktopSize.width();
    int desktopHeight = desktopSize.height();

    int srcWidth;
    int srcHeight;
    if (bitmapWidth*1.0 / bitmapHeight > desktopWidth*1.0 / desktopHeight)
    {
        srcWidth = bitmapHeight * (desktopWidth*1.0 / desktopHeight);
        srcHeight = bitmapHeight;
    }
    else
    {
        srcWidth = bitmapWidth;
        srcHeight = bitmapWidth * (desktopHeight*1.0 / desktopWidth);
    }

    Bitmap *newBitmap = new Bitmap(desktopWidth, desktopHeight);
    Graphics *g = Graphics::FromImage(newBitmap);
    g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
    Rect destRect(0, 0, desktopWidth, desktopHeight);
    g->DrawImage(bmp, destRect,
                 (int)((bitmapWidth - srcWidth) / 2),
                 (int)((bitmapHeight - srcHeight) / 2),
                 srcWidth, srcHeight, UnitPixel);
    delete g; g = 0;

    return newBitmap;
}

#endif // _WIN32
