﻿//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "Game/SubGame.h"
#include "Game/Data/Model/ModelData.h"
#include "Game/Data/Texture/TextureData.h"
#include "Game/Camera/CameraManager.h"

#include "DebugString.h"

#include "ADX2/ADX2Le.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	// デバッグカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>(width, height);

    m_deviceResources->SetWindow(window, width, height);


	// サブゲームの作成
	SubGame& subGame = SubGame::GetInstace();
	subGame.SetWindow(window);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	
	SubGame& subGame = SubGame::GetInstace();
	subGame.Update(elapsedTime);

	DebugString& debugString = DebugString::GetInstace();
	debugString.Update(timer);

	// デバッグカメラの更新
	m_debugCamera->Update();

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// ビュー行列の作成
	CameraManager& cameraManager = CameraManager::GetInstace();
	m_view = cameraManager.GetView();
	// デバッグビュー
	//m_view = m_debugCamera->GetCameraMatrix();

	// グリッドの床の描画
	//m_gridFloor->Render(context, m_view, m_projection);

	// ここから描画処理を記述する



	m_sprites->Begin(SpriteSortMode_FrontToBack, m_states->NonPremultiplied());

	SubGame& subGame = SubGame::GetInstace();
	subGame.Renderer();

	DebugString& debugString = DebugString::GetInstace();
	debugString.Render();

	m_sprites->End();


	// ここまで

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::DarkBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context =  m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);

	// スプライトフォントの作成
	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

	// グリッドの床の作成
	m_gridFloor = std::make_unique<GridFloor>(device, context, m_states.get(), 10.0f, 10);

	// モデルデータのデバイスを設定する
	ModelData::SetDevice(device);

	// 画像データのデバイスを設定する
	TextureData::SetDevice(device);

	// 音の初期化
	MyLibrary::ADX2Le::GetInstance()->Initialize(L"RajiBato.acf");

	// サブゲームの作成
	SubGame& subGame = SubGame::GetInstace();
	subGame.Initialize(this);

	// 文字のデバッグを作成
	DebugString& debugString = DebugString::GetInstace();
	debugString.Initialize(m_sprites.get(), m_font.get());
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f
	);

	// デバッグカメラにウインドウのサイズ変更を伝える
	m_debugCamera->SetWindowSize(size.right, size.bottom);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.


	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();

	// スプライトフォントの解放
	m_font.reset();

	// グリッドの床の解放
	m_gridFloor.reset();

	// サブゲームの終了処理
	SubGame& subGame = SubGame::GetInstace();
	subGame.Finalize();

	// 音の初期化
	MyLibrary::ADX2Le::GetInstance()->Finalize();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
