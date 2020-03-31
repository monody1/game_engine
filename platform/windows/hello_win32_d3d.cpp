//
// Created by Chen.Zr on 2020/3/21.
//

#include <windowsx.h>
#include <windows.h>
#include <tchar.h>
#include <stdint.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace DirectX;
using namespace DirectX::PackedVector;

const uint32_t SCREEN_WIDTH = 960;
const uint32_t SCREEN_HEIGHT = 480;

IDXGISwapChain *g_pSwapChain = nullptr;
ID3D11Device *g_pDevice = nullptr;
ID3D11DeviceContext *g_pDeviceContext = nullptr;

ID3D11RenderTargetView *g_pRTView = nullptr;

ID3D11InputLayout *g_pLayout = nullptr;
ID3D11VertexShader *g_pVertexShader = nullptr;
ID3D11PixelShader *g_pPixelShader = nullptr;

ID3D11Buffer *g_pVBuffer = nullptr;

struct VERTEX{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

template <class T>
inline void SafeRelease(T **ppInterfaceRelease){
    if (*ppInterfaceRelease != nullptr){
        (*ppInterfaceRelease) -> Release();
        (*ppInterfaceRelease) = nullptr;
    }
}

void CreatRenderTarget(){
    ID3D11Texture2D *pBackBuffer;
    HRESULT hr;
    g_pSwapChain -> GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    hr = g_pDevice -> CreateRenderTargetView(pBackBuffer, NULL, &g_pRTView);
    std::cout << hr << std::endl;
    pBackBuffer -> Release();
    g_pDeviceContext -> OMSetRenderTargets(1, &g_pRTView, NULL);
}

void SetViewPort(){
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    g_pDeviceContext -> RSSetViewports(1, &viewport);
}

void InitPipeline(){
    ID3DBlob *VS, *PS;
    D3DReadFileToBlob(L"C:\\Users\\TUF\\CLionProjects\\game_engine\\game_engine\\platform\\windows\\copy.vso", &VS);
    D3DReadFileToBlob(L"C:\\Users\\TUF\\CLionProjects\\game_engine\\game_engine\\platform\\windows\\copy.pso", &PS);

    g_pDevice -> CreateVertexShader(VS->GetBufferPointer(),VS->GetBufferSize(),NULL, &g_pVertexShader);
    g_pDevice -> CreatePixelShader(PS->GetBufferPointer(),PS->GetBufferSize(),NULL,&g_pPixelShader);

    g_pDeviceContext -> VSSetShader(g_pVertexShader, 0, 0);
    g_pDeviceContext -> PSSetShader(g_pPixelShader, 0, 0);

    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    g_pDevice -> CreateInputLayout(inputElementDesc, 2, VS ->GetBufferPointer(), VS ->GetBufferSize(), &g_pLayout);
    g_pDeviceContext -> IASetInputLayout(g_pLayout);

    VS -> Release();
    PS -> Release();
}

void InitGraphics(){
    VERTEX Vertices[] = {
            {XMFLOAT3(0.0, 0.5, 0.0), XMFLOAT4(1.0, 0.0, 0.0, 1.0)},
            {XMFLOAT3(0.45, -0.5, 0.0), XMFLOAT4(0.0, 1.0, 0.0, 1.0)},
            {XMFLOAT3(-0.45, -0.5, 0.0), XMFLOAT4(0.0, 0.0, 1.0, 1.0)},
    };
    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));

    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = sizeof(VERTEX) * 3;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    g_pDevice -> CreateBuffer(&bufferDesc, NULL, &g_pVBuffer);
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    g_pDeviceContext -> Map(g_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
    memcpy(mappedSubresource.pData, Vertices, sizeof(VERTEX) * 3);
    g_pDeviceContext -> Unmap(g_pVBuffer, NULL);
}

HRESULT CreateGraphicsResources(HWND hwnd){
    HRESULT hr = S_OK;
    if (g_pSwapChain == nullptr){
        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
        swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hwnd;
        swapChainDesc.SampleDesc.Count = 4;
        swapChainDesc.Windowed = TRUE;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        const D3D_FEATURE_LEVEL FeatureLevels[] = {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
                D3D_FEATURE_LEVEL_9_3,
                D3D_FEATURE_LEVEL_9_2,
                D3D_FEATURE_LEVEL_9_1,
        };

        D3D_FEATURE_LEVEL featureLevelSupported;

        hr = D3D11CreateDeviceAndSwapChain(
                NULL,
                D3D_DRIVER_TYPE_HARDWARE,
                NULL,
                0,
                FeatureLevels,
                _countof(FeatureLevels),
                D3D11_SDK_VERSION,
                &swapChainDesc,
                &g_pSwapChain,
                &g_pDevice,
                &featureLevelSupported,
                &g_pDeviceContext
        );
        if (hr == E_INVALIDARG){
            hr = D3D11CreateDeviceAndSwapChain(
                    NULL,
                    D3D_DRIVER_TYPE_HARDWARE,
                    NULL,
                    0,
                    &featureLevelSupported,
                    1,
                    D3D11_SDK_VERSION,
                    &swapChainDesc,
                    &g_pSwapChain,
                    &g_pDevice,
                    NULL,
                    &g_pDeviceContext
                    );
        }
        if (hr == S_OK) {
            CreatRenderTarget();
            SetViewPort();
            InitPipeline();
            InitGraphics();
        }
    }
    return hr;
}

void DiscardGraphicsResource(){
    SafeRelease(&g_pLayout);
    SafeRelease(&g_pVertexShader);
    SafeRelease(&g_pPixelShader);
    SafeRelease(&g_pVBuffer);
    SafeRelease(&g_pSwapChain);
    SafeRelease(&g_pRTView);
    SafeRelease(&g_pDevice);
    SafeRelease(&g_pDeviceContext);
}

void RenderFrame(){
    const FLOAT clearColor[] = {0.0,0.2,0.4,1.0};
    g_pDeviceContext -> ClearRenderTargetView(g_pRTView, clearColor);
    {
        UINT stride = sizeof(VERTEX);
        UINT offset = 0;
        g_pDeviceContext -> IASetVertexBuffers(0, 1, &g_pVBuffer, &stride, &offset);
        g_pDeviceContext ->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        g_pDeviceContext -> Draw(3, 0);
    }
    g_pSwapChain -> Present(0, 0);
}

LRESULT CALLBACK WindowProc(
        HWND hWnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
) {
    LRESULT result = 0;
    bool wasHandled = false;

    switch (msg) {
        case WM_CREATE:
            wasHandled = true;
            break;
        case WM_PAINT:
            result = CreateGraphicsResources(hWnd);
            RenderFrame();
            wasHandled = true;
            break;

        case WM_SIZE:
            if (g_pSwapChain != nullptr){
                DiscardGraphicsResource();
//                g_pSwapChain -> ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
            }
            wasHandled = true;
            break;

        case WM_DESTROY:
            DiscardGraphicsResource();
            PostQuitMessage(0);
            wasHandled = true;
            break;
        case WM_DISPLAYCHANGE:
            InvalidateRect(hWnd, nullptr, false);
            wasHandled = true;
            break;
    }
    if (!wasHandled){
        result = DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return result;
}

int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow
) {
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(
            0,
            _T("WindowClass1"),
            _T("hello, Engine![Direct 3D]"),
            WS_OVERLAPPEDWINDOW,
            100,
            100,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            NULL,
            NULL,
            hInstance,
            NULL
    );
    ShowWindow(hWnd, nCmdShow);
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    return msg.wParam;
}
