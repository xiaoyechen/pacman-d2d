#pragma once

#include "resource.h"
#include "PacmanGame.h"

#define CELL_DIM 15

const float DEFAULT_DPI = 96.f;

class AstarPac 
{
public:
  AstarPac();
  ~AstarPac();

  HRESULT Initialize();
  void RunMsgLoop(HACCEL& hAccelTable);
private:
  HRESULT CreateDeviceIndependentResources();
  HRESULT CreateDeviceResources();
  HRESULT CreateD2DBitmapFromFile(int idx);
  void DiscardDeviceResources();
  HRESULT OnRender();
  void OnResize(UINT width, UINT height);
  ATOM RegClass();
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  PacmanGame* m_pgame;

  HWND m_hwnd;
  ID2D1Factory* m_pDirect2dFactory;
  IWICImagingFactory* m_pIWICFactory;
  ID2D1HwndRenderTarget* m_pRenderTarget;
  ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
  ID2D1SolidColorBrush* m_pOrangeRedBrush;
  ID2D1Bitmap *m_pD2DBitmap;
  //ID2D1ImageSourceFromWic *m_pD2DImageSource;

  IWICFormatConverter *m_pConvertedSourceBitmap;
};