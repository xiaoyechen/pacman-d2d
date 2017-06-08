// AstarPac.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AstarPac.h"

#define MAX_LOADSTRING 100

// Global Variables:
//HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"A* Pacman";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szFilename[2][MAX_PATH] = {L"pacman.png",L"Capt.JPG"};
// Forward declarations of functions included in this code module:
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//int APIENTRY WinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
 //                    _In_ int       nCmdShow)
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow)
{
    //UNREFERENCED_PARAMETER(hPrevInstance);
   // UNREFERENCED_PARAMETER(lpCmdLine);
  
    HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTARPAC, szWindowClass, MAX_LOADSTRING);

    // Perform application initialization:
    if (SUCCEEDED(CoInitialize(nullptr)))
    {
      {
        AstarPac app;

        if (SUCCEEDED(app.Initialize()))
        {
          HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTARPAC));

          app.RunMsgLoop(hAccelTable);
        }
      }
      CoUninitialize();
    }

    return 0;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM AstarPac::RegClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = AstarPac::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = sizeof(LONG_PTR);
    wcex.hInstance      = HINST_THISCOMPONENT;
    wcex.hIcon          = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_ASTARPAC));
    wcex.hCursor        = LoadCursor(nullptr, IDI_APPLICATION);
    wcex.hbrBackground  = nullptr;//(HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_ASTARPAC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
/*BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
*/
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK AstarPac::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  LRESULT lr = 0;

  if (msg == WM_CREATE)
  {
    LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
    AstarPac *pApp = (AstarPac*)pcs->lpCreateParams;

    ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pApp));

    lr = 1;
  }
  else
  {
    AstarPac *pApp = reinterpret_cast<AstarPac*>(static_cast<LONG_PTR>(
      ::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

    bool wasHandled = false;

    if (pApp)
    {
      switch (msg)
      {
      case WM_SIZE:
      {
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        pApp->OnResize(width, height);
      }
        lr = 0;
        wasHandled = true;
        break;
      case WM_DISPLAYCHANGE:
        InvalidateRect(hwnd, nullptr, false);
        lr = 0;
        wasHandled = true;
        break;
      case WM_COMMAND:
      {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
          DialogBox(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
          break;
        case IDM_EXIT:
          DestroyWindow(hwnd);
          break;
        default:
          return DefWindowProc(hwnd, msg, wParam, lParam);
        }
      }
      lr = 0;
      wasHandled = true;
      break;
      case WM_PAINT:
        pApp->OnRender();
        ValidateRect(hwnd, nullptr);
        lr = 0;
        wasHandled = true;
        break;
      case WM_DESTROY:
        PostQuitMessage(0);
        lr = 1;
        wasHandled = true;
        break;
      //default:
      //  return DefWindowProc(hwnd, msg, wParam, lParam);
      }
    }

    if (!wasHandled)
    {
      lr = DefWindowProc(hwnd, msg, wParam, lParam);
    }
  }
    
  return lr;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

AstarPac::AstarPac()
  :m_hwnd(nullptr),
  m_pDirect2dFactory(nullptr),
  m_pRenderTarget(nullptr),
  m_pLightSlateGrayBrush(nullptr),
  m_pOrangeRedBrush(nullptr)
{
  m_pgame = new PacmanGame("grid.txt");
}

AstarPac::~AstarPac()
{
  SafeRelease(m_pIWICFactory);
  SafeRelease(m_pDirect2dFactory);
  SafeRelease(m_pRenderTarget);
  SafeRelease(m_pLightSlateGrayBrush);
  SafeRelease(m_pOrangeRedBrush);
  SafeRelease(m_pgame);
}

HRESULT AstarPac::Initialize()
{
  HRESULT hr;

  hr = CreateDeviceIndependentResources();

  if (SUCCEEDED(hr))
  {
    RegClass();

    FLOAT dpiX, dpiY;

    m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

    m_hwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
      static_cast<UINT>(ceil((m_pgame->GetWidth()+1)*CELL_DIM*dpiX / 96.f)), 
      static_cast<UINT>(ceil((m_pgame->GetHeight()+2)*CELL_DIM*dpiX / 96.f)),
      nullptr, nullptr, HINST_THISCOMPONENT, this);

    hr = m_hwnd ? S_OK : E_FAIL;

    if (SUCCEEDED(hr))
    {
      if (SUCCEEDED(CreateD2DBitmapFromFile(0)))
      {
        InvalidateRect(m_hwnd, nullptr, TRUE);
      }
      else
      {
        MessageBox(m_hwnd, L"Failed to load image", L"Application Error", MB_ICONEXCLAMATION | MB_OK);
      }

      ShowWindow(m_hwnd, SW_SHOWNORMAL);
      UpdateWindow(m_hwnd);  
    }
  }
  return hr;
}

void AstarPac::RunMsgLoop(HACCEL& hAccelTable)
{
  MSG msg;

  while (GetMessage(&msg, nullptr, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

HRESULT AstarPac::CreateDeviceIndependentResources()
{
  HRESULT hr = S_OK;

  hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pIWICFactory));

  if (SUCCEEDED(hr))
  {
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
  }

  return hr;
}

HRESULT AstarPac::CreateDeviceResources()
{
  HRESULT hr = S_OK;

  if (!m_pRenderTarget)
  {
    RECT rc;
    hr = GetClientRect(m_hwnd, &rc) ? S_OK : E_FAIL;

    if (SUCCEEDED(hr))
    {
      D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties();
      renderTargetProperties.dpiX = DEFAULT_DPI;
      renderTargetProperties.dpiY = DEFAULT_DPI;

      D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

      hr = m_pDirect2dFactory->CreateHwndRenderTarget(renderTargetProperties, D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_pRenderTarget);
    }

    if (SUCCEEDED(hr))
    {
      //create a gray brush
      hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);
    }

    if (SUCCEEDED(hr))
    {
      //create blue brush
      hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::OrangeRed), &m_pOrangeRedBrush);
    }
  }
  return hr;
}

HRESULT AstarPac::CreateD2DBitmapFromFile(int idx)
{
  HRESULT hr = S_OK;

  IWICBitmapDecoder *pDecoder = nullptr;

  hr = m_pIWICFactory->CreateDecoderFromFilename(szFilename[idx], nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);

  IWICBitmapFrameDecode *pFrame = nullptr;

  if (SUCCEEDED(hr))
  {
    hr = pDecoder->GetFrame(0, &pFrame);
  }

  if (SUCCEEDED(hr))
  {
    SafeRelease(m_pConvertedSourceBitmap);
    hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
  }

  if (SUCCEEDED(hr))
  {
    hr = m_pConvertedSourceBitmap->Initialize(
      pFrame, // input bitmap 
      GUID_WICPixelFormat32bppPBGRA, //destination pixel format
      WICBitmapDitherTypeNone, //specified dither pattern
      nullptr, //specify a particular palette 
      0.f, //alpha threshold
      WICBitmapPaletteTypeCustom // palette translation type
    );
  }

  if (SUCCEEDED(hr))
  {
    hr = CreateDeviceResources();
  }

  if (SUCCEEDED(hr))
  {
    SafeRelease(m_pD2DBitmap);
    hr = m_pRenderTarget->CreateBitmapFromWicBitmap(m_pConvertedSourceBitmap, nullptr, &m_pD2DBitmap);
  }

  SafeRelease(pDecoder);
  SafeRelease(pFrame);

  return hr;
}

void AstarPac::DiscardDeviceResources()
{
  SafeRelease(m_pRenderTarget);
  SafeRelease(m_pLightSlateGrayBrush);
  SafeRelease(m_pOrangeRedBrush);
}

HRESULT AstarPac::OnRender()
{
  HRESULT hr = S_OK;
  PAINTSTRUCT ps;

  if (BeginPaint(m_hwnd, &ps))
  {
    hr = CreateDeviceResources();

    if (SUCCEEDED(hr))
    {
      m_pRenderTarget->BeginDraw();
      m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

      // clear background
      m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

      D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

      // draw a grid background
      int width = static_cast<int>(rtSize.width);
      int height = static_cast<int>(rtSize.height);


      // draw map
      for (int y = 0; y < m_pgame->GetHeight(); ++y)
      {
        for (int x = 0; x < m_pgame->GetWidth(); ++x)
        {
          switch ((*m_pgame)(y, x))
          {
          case SYMBOL_WALL:
          {
            D2D1_RECT_F rect1 = D2D1::RectF(x*CELL_DIM, y*CELL_DIM, (x + 1)*CELL_DIM, (y + 1)*CELL_DIM);
            m_pRenderTarget->FillRectangle(&rect1, m_pLightSlateGrayBrush);
          }
            break;
          case SYMBOL_FOOD:
          {  
            float radius = CELL_DIM / 2.0f;
            D2D1_POINT_2F centre = D2D1_POINT_2F{ x*CELL_DIM + radius, y*CELL_DIM + radius };
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(centre, radius, radius);
            m_pRenderTarget->FillEllipse(&ellipse, m_pOrangeRedBrush);
          }
            break;
          case SYMBOL_PACMAN:
          {
            // D2DBitmap may have been released due to device loss
            // if so, re-create it from the source bitmap
            if (m_pConvertedSourceBitmap && !m_pD2DBitmap)
            {
              m_pRenderTarget->CreateBitmapFromWicBitmap(m_pConvertedSourceBitmap, &m_pD2DBitmap);
            }

            if (m_pD2DBitmap)
            {
              D2D1_RECT_F rect1 = D2D1::RectF(x*CELL_DIM, y*CELL_DIM, (x + 1)*CELL_DIM, (y + 1)*CELL_DIM);
              m_pRenderTarget->DrawBitmap(m_pD2DBitmap, rect1);
            }
          }
            break;
          default: 
            break;
          }
        }
      }
      /*
      for (int x = 0; x < width; x += 10)
      {
        m_pRenderTarget->DrawLine(D2D1::Point2F(static_cast<FLOAT>(x), 0.0f), D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height), m_pLightSlateGrayBrush, 0.5f);
      }

      for (int y = 0; y < height; y += 10)
      {
        m_pRenderTarget->DrawLine(D2D1::Point2F(0.0f, static_cast<FLOAT>(y)), D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)), m_pLightSlateGrayBrush, 0.5f);
      }*/

      hr = m_pRenderTarget->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
      hr = S_OK;
      DiscardDeviceResources();
    }

    EndPaint(m_hwnd, &ps);
  }
  return hr;
}

void AstarPac::OnResize(UINT width, UINT height)
{
  if (m_pRenderTarget)
  {
    m_pRenderTarget->Resize(D2D1::SizeU(width, height));
  }
}
