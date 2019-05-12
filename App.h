#pragma once

class App : public Singleton<App>
{
public:
	App():
		screenSize(1920.f, 1080.f), mouseClick(false), alreadyMouseClick(false), spr(nullptr), deltaTime(0.f), time(0)
	{}
	virtual ~App()
	{}

public:
	Vec2 screenSize;

	Vec2 mousePosition;
	bool mouseClick;
	bool alreadyMouseClick;

	LPD3DXSPRITE spr;

	float deltaTime;
	double time;

public:

	void Init()
	{
		D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
	}

	void DeviceReset()
	{
		spr->OnResetDevice();
	}

	void DeviceLost()
	{
		spr->OnLostDevice();
	}

	void Release()
	{
		SAFE_RELEASE(spr);
	}
};

