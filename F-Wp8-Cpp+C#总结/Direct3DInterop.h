/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once

#include <wrl/client.h>
#include <mutex>
#include <queue>
#include <memory>
#include "Cocos2dRenderer.h"
#include "InputEvent.h"

namespace PhoneDirect3DXamlAppComponent
{

[Windows::Foundation::Metadata::WebHostHidden]
public ref class Direct3DInterop sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
{
public:
    Direct3DInterop();

    Windows::Phone::Graphics::Interop::IDrawingSurfaceContentProvider^ CreateContentProvider();

    // IDrawingSurfaceManipulationHandler
    virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

    void UpdateForWindowSizeChange(float width, float height);
    Windows::Foundation::IAsyncAction^ OnSuspending();
    bool OnBackKeyPress();

    void OnCocos2dKeyEvent(Cocos2dKeyEvent key);
    void OnCocos2dKeyEvent(Cocos2dKeyEvent key, Platform::String^ text);
	void onCocos2dPostInputData(Cocos2dKeyEvent key, Platform::String^ text);
	void onCocos2dPurchaseDone(Cocos2dKeyEvent key, Platform::String^ text);

    property Windows::Graphics::Display::DisplayOrientations WindowOrientation;

    property Windows::Foundation::Size NativeResolution;
    property Windows::Foundation::Size RenderResolution;
    property Windows::Foundation::Size WindowBounds;

    void SetCocos2dEventDelegate(Cocos2dEventDelegate^ delegate);

protected:
    // Event Handlers
    void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

internal:
    void Connect();
    void Disconnect();
    void PrepareResources(LARGE_INTEGER presentTargetTime);
    void Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView);
    bool SendCocos2dEvent(Cocos2dEvent event);

private:
    void ProcessEvents();
    void AddPointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);
    Cocos2dRenderer^ m_renderer;
    Windows::Graphics::Display::DisplayOrientations mCurrentOrientation;

    std::queue<std::shared_ptr<InputEvent>> mInputEvents;
    std::mutex mMutex;


    Windows::Foundation::Size m_renderResolution;
    Cocos2dEventDelegate^ m_delegate;
};

}
