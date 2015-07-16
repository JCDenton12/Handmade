#include <windows.h>
#include <wingdi.h>
#include <winuser.h>
#include <stdio.h>
#pragma comment(lib, "gdi32.lib")

static bool Running;

/* how to write structs and typedef's in C:
       struct foo 
       {
              int x;
       }
       typedef struct foo *foo;
       foo Foo;
       */


LRESULT CALLBACK 
MainWindowCallback( HWND   Window,
                     UINT   Message,
                     WPARAM WParam,
                     LPARAM LParam)
{
      LRESULT Result = 0;
     switch(Message)
     {
        case WM_SIZE:
        {
             OutputDebugStringA("WM_SIZE\n");
        } 
        break;
        
        case WM_DESTROY:
             {
                        Running = false;
                  OutputDebugStringA("WM_DESTROY\n");      
             } break;
        case WM_CLOSE:
             {
                      Running = false;
                  OutputDebugStringA("WM_CLOSE\n");
             } break;
             
        case WM_ACTIVATEAPP:
             {
                  OutputDebugStringA("WM_ACTIVATEAPP\n");
             } break;
             
        case WM_PAINT:
             {
                    PAINTSTRUCT Paint;
                    HDC DeviceContext = BeginPaint(Window, &Paint);
                    int X = Paint.rcPaint.left;
                    int Y = Paint.rcPaint.top;
                    LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
                    LONG Width = Paint.rcPaint.right - Paint.rcPaint.left;
                    static DWORD Operation = WHITENESS;
                    PatBlt(DeviceContext, X, Y, Width, Height, Operation);
                    if(Operation == WHITENESS)
                    {
                       Operation = BLACKNESS;
                    }
                    else
                    {
                        Operation = WHITENESS;
                    }
                  
                    EndPaint(Window, &Paint);
             } break;
        default:
        {
                OutputDebugStringA("default\n");
        } break;
     }
}

int CALLBACK 
WinMain(
   HINSTANCE Instance,
   HINSTANCE PrevInstance,
   LPSTR     CommandLine,
   int       ShowCode)
{
     WNDCLASS WindowClass = {0};
     
     // Check if HREDRAW/VREDRAW/OWNDC  still matter
     WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
     WindowClass.lpfnWndProc = MainWindowCallback;
     WindowClass.hInstance = Instance;
     // WindowClass.hIcon
     WindowClass.lpszClassName = "HandmadeHeroWindowClass";
     
     if(RegisterClass(&WindowClass))
     { 
         HWND WindowHandle =  
         CreateWindowEx(
  0,
  WindowClass.lpszClassName,
  "Handmade Hero",
  WS_OVERLAPPEDWINDOW|WS_VISIBLE,
  CW_USEDEFAULT,
  CW_USEDEFAULT,
  CW_USEDEFAULT,
  CW_USEDEFAULT,
  0,
  0,
  Instance,
  0);
  if(WindowHandle != NULL)
  {
    MSG Message; 
    while(Running)
    {        
    BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
    if(MessageResult > 0)
    {
       TranslateMessage(&Message);
       DispatchMessage(&Message);
    }
    else
    {
        break;
    }
  {
  }
  
  }
  
}
  else
  {
      // Todo: Logging
  }
}
     else
     {
         // Todo: Logging
     }       
     /* MessageBox(0, "This is Handmade Hero", "Handmade Hero", 
             MB_OK|MB_ICONINFORMATION);
             */
            
             return(0);
}

