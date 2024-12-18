cmake_minimum_required(VERSION 3.10)

project(cmEngine)

set(CMAKE_CXX_STANDARD 14)

include_directories(cmEngine)
include_directories(cmEngine/imgui)
include_directories(cmEngine/ini)
include_directories(cmEngine/Inter/Debug)
include_directories(cmEngine/Inter/Release)
include_directories(Libraries)
include_directories(Libraries/DirectXTex)
include_directories(Libraries/DirectXTK)
include_directories(Sample)
include_directories(Sample/x64)
include_directories(Sample/x64/Debug)
include_directories(TestClient)
include_directories(TestClient/Inter)

add_executable(cmEngine
    cmEngine/imgui/imconfig.h
    cmEngine/imgui/imgui.cpp
    cmEngine/imgui/imgui.h
    cmEngine/imgui/imgui_demo.cpp
    cmEngine/imgui/imgui_draw.cpp
    cmEngine/imgui/imgui_impl_dx11.cpp
    cmEngine/imgui/imgui_impl_dx11.h
    cmEngine/imgui/imgui_impl_win32.cpp
    cmEngine/imgui/imgui_impl_win32.h
    cmEngine/imgui/imgui_internal.h
    cmEngine/imgui/imgui_tables.cpp
    cmEngine/imgui/imgui_widgets.cpp
    cmEngine/imgui/imstb_rectpack.h
    cmEngine/imgui/imstb_textedit.h
    cmEngine/imgui/imstb_truetype.h
    cmEngine/imgui/stb_image.h
    cmEngine/ini/INIReader.cpp
    cmEngine/ini/INIReader.h
    cmEngine/Inter/Debug/cmEngine.pch
    cmEngine/Inter/Release/cmEngine.pch
    cmEngine/CameraScript.cpp
    cmEngine/CameraScript.h
    cmEngine/cmAlgorithm.cpp
    cmEngine/cmAlgorithm.h
    cmEngine/cmApplication.cpp
    cmEngine/cmApplication.h
    cmEngine/cmAssert.cpp
    cmEngine/cmAssert.h
    cmEngine/cmCamera.cpp
    cmEngine/cmCamera.h
    cmEngine/cmColors.cpp
    cmEngine/cmColors.h
    cmEngine/cmCommonCommand.cpp
    cmEngine/cmCommonCommand.h
    cmEngine/cmComponent.cpp
    cmEngine/cmComponent.h
    cmEngine/cmConsole.cpp
    cmEngine/cmConsole.h
    cmEngine/cmConsoleData.cpp
    cmEngine/cmConsoleData.h
    cmEngine/cmConsoleGUI.cpp
    cmEngine/cmConsoleGUI.h
    cmEngine/cmConstantBuffer.cpp
    cmEngine/cmConstantBuffer.h
    cmEngine/cmConstantBufferBase.cpp
    cmEngine/cmConstantBufferBase.h
    cmEngine/cmConstantBufferData.cpp
    cmEngine/cmConstantBufferData.h
    cmEngine/cmDebugger.cpp
    cmEngine/cmDebugger.h
    cmEngine/cmDebugGUI.cpp
    cmEngine/cmDebugGUI.h
    cmEngine/cmDepthStencil.cpp
    cmEngine/cmDepthStencil.h
    cmEngine/cmEditorComponent.cpp
    cmEngine/cmEditorComponent.h
    cmEngine/cmEditorManager.cpp
    cmEngine/cmEditorManager.h
    cmEngine/cmEngine.cpp
    cmEngine/cmEngine.h
    cmEngine/cmFlipbook.cpp
    cmEngine/cmFlipbook.h
    cmEngine/cmFlipbookData.cpp
    cmEngine/cmFlipbookData.h
    cmEngine/cmFlipbookRenderer.cpp
    cmEngine/cmFlipbookRenderer.h
    cmEngine/cmGameObject.cpp
    cmEngine/cmGameObject.h
    cmEngine/cmGeometryHelper.cpp
    cmEngine/cmGeometryHelper.h
    cmEngine/cmGraphicsDevice.cpp
    cmEngine/cmGraphicsDevice.h
    cmEngine/cmGraphicsHelper.cpp
    cmEngine/cmGraphicsHelper.h
    cmEngine/cmGraphicsResourceManager.cpp
    cmEngine/cmGraphicsResourceManager.h
    cmEngine/cmGUI.cpp
    cmEngine/cmGUI.h
    cmEngine/cmGUIRenderer.cpp
    cmEngine/cmGUIRenderer.h
    cmEngine/cmHelper.cpp
    cmEngine/cmHelper.h
    cmEngine/cmICommand.cpp
    cmEngine/cmICommand.h
    cmEngine/cmIFinalUpdateable.cpp
    cmEngine/cmIFinalUpdateable.h
    cmEngine/cmIKeyboard.cpp
    cmEngine/cmIKeyboard.h
    cmEngine/cmIndexBuffer.cpp
    cmEngine/cmIndexBuffer.h
    cmEngine/cmInputLayout.cpp
    cmEngine/cmInputLayout.h
    cmEngine/cmInputLayoutBase.cpp
    cmEngine/cmInputLayoutBase.h
    cmEngine/cmIPreRenderable.cpp
    cmEngine/cmIPreRenderable.h
    cmEngine/cmISetupable.cpp
    cmEngine/cmISetupable.h
    cmEngine/cmIUpdateable.cpp
    cmEngine/cmIUpdateable.h
    cmEngine/cmKeyboardEv.cpp
    cmEngine/cmKeyboardEv.h
    cmEngine/cmKeyboardPoll.cpp
    cmEngine/cmKeyboardPoll.h
    cmEngine/cmLogData.cpp
    cmEngine/cmLogData.h
    cmEngine/cmLogger.cpp
    cmEngine/cmLogger.h
    cmEngine/cmLoggerGUI.cpp
    cmEngine/cmLoggerGUI.h
    cmEngine/cmMath.cpp
    cmEngine/cmMath.h
    cmEngine/cmMenuGUI.cpp
    cmEngine/cmMenuGUI.h
    cmEngine/cmMesh.cpp
    cmEngine/cmMesh.h
    cmEngine/cmMeshRenderer.cpp
    cmEngine/cmMeshRenderer.h
    cmEngine/cmPipeline.cpp
    cmEngine/cmPipeline.h
    cmEngine/cmPipelineData.cpp
    cmEngine/cmPipelineData.h
    cmEngine/cmPixelShader.cpp
    cmEngine/cmPixelShader.h
    cmEngine/cmRenderComponent.cpp
    cmEngine/cmRenderComponent.h
    cmEngine/cmRenderer.cpp
    cmEngine/cmRenderer.h
    cmEngine/cmRenderState.cpp
    cmEngine/cmRenderState.h
    cmEngine/cmRenderTargetView.cpp
    cmEngine/cmRenderTargetView.h
    cmEngine/cmResourceBase.cpp
    cmEngine/cmResourceBase.h
    cmEngine/cmResourceManager.cpp
    cmEngine/cmResourceManager.h
    cmEngine/cmScene.cpp
    cmEngine/cmScene.h
    cmEngine/cmSceneManager.cpp
    cmEngine/cmSceneManager.h
    cmEngine/cmScript.cpp
    cmEngine/cmScript.h
    cmEngine/cmShader.cpp
    cmEngine/cmShader.h
    cmEngine/cmSprite.cpp
    cmEngine/cmSprite.h
    cmEngine/cmSpriteData.cpp
    cmEngine/cmSpriteData.h
    cmEngine/cmSpriteRenderer.cpp
    cmEngine/cmSpriteRenderer.h
    cmEngine/cmStaticTextBuffer.cpp
    cmEngine/cmStaticTextBuffer.h
    cmEngine/cmTexture.cpp
    cmEngine/cmTexture.h
    cmEngine/cmTimer.cpp
    cmEngine/cmTimer.h
    cmEngine/cmTransform.cpp
    cmEngine/cmTransform.h
    cmEngine/cmType.cpp
    cmEngine/cmType.h
    cmEngine/cmVertexBuffer.cpp
    cmEngine/cmVertexBuffer.h
    cmEngine/cmVertexData.cpp
    cmEngine/cmVertexData.h
    cmEngine/cmVertexShader.cpp
    cmEngine/cmVertexShader.h
    cmEngine/cmViewport.cpp
    cmEngine/cmViewport.h
    cmEngine/cmVoidPopupGUI.cpp
    cmEngine/cmVoidPopupGUI.h
    cmEngine/cmWindow.cpp
    cmEngine/cmWindow.h
    cmEngine/cmWindowsManager.cpp
    cmEngine/cmWindowsManager.h
    cmEngine/EngineInc.h
    cmEngine/EngineModules.h
    cmEngine/Enums.h
    cmEngine/FileDialog.cpp
    cmEngine/FileDialog.h
    cmEngine/framework.h
    cmEngine/ImGuiHelper.cpp
    cmEngine/ImGuiHelper.h
    cmEngine/imguiInc.h
    cmEngine/Macro.h
    cmEngine/OldcmLogger.cpp
    cmEngine/OldcmLogger.h
    cmEngine/OldcmLogGUI.cpp
    cmEngine/OldcmLogGUI.h
    cmEngine/pch.cpp
    cmEngine/pch.h
    cmEngine/resource.h
    cmEngine/Types.h
    cmEngine/UComPtr.cpp
    cmEngine/UComPtr.h
    cmEngine/WindowsStruct.cpp
    cmEngine/WindowsStruct.h
    Libraries/DirectXTex/DirectXTex.h
    Libraries/DirectXTex/DirectXTex.inl
    Libraries/DirectXTK/Audio.h
    Libraries/DirectXTK/BufferHelpers.h
    Libraries/DirectXTK/CommonStates.h
    Libraries/DirectXTK/DDSTextureLoader.h
    Libraries/DirectXTK/DirectXHelpers.h
    Libraries/DirectXTK/Effects.h
    Libraries/DirectXTK/GamePad.h
    Libraries/DirectXTK/GeometricPrimitive.h
    Libraries/DirectXTK/GraphicsMemory.h
    Libraries/DirectXTK/Keyboard.h
    Libraries/DirectXTK/Model.h
    Libraries/DirectXTK/Mouse.h
    Libraries/DirectXTK/PostProcess.h
    Libraries/DirectXTK/PrimitiveBatch.h
    Libraries/DirectXTK/ScreenGrab.h
    Libraries/DirectXTK/SimpleMath.h
    Libraries/DirectXTK/SimpleMath.inl
    Libraries/DirectXTK/SpriteBatch.h
    Libraries/DirectXTK/SpriteFont.h
    Libraries/DirectXTK/VertexTypes.h
    Libraries/DirectXTK/WICTextureLoader.h
    Libraries/DirectXTK/XboxDDSTextureLoader.h
    Sample/x64/Debug/Sample.pch
    Sample/App.cpp
    Sample/App.h
    Sample/main.cpp
    Sample/pch.cpp
    Sample/pch.h
    TestClient/Inter/TestClient.pch
    TestClient/Demo.cpp
    TestClient/Demo.h
    TestClient/DummyScene.cpp
    TestClient/DummyScene.h
    TestClient/DummyScript.cpp
    TestClient/DummyScript.h
    TestClient/Main.cpp
    TestClient/pch.cpp
    TestClient/pch.h
    TestConsole/TestConsole.cpp
        cmEngine/GameEntity.h
        cmEngine/GameEntity.h)
