#pragma once

class Camera : public Object
{
public:
	Camera()
	{
		D3DXMatrixOrthoLH(&projection, App::GetInstance()->screenSize.x, -App::GetInstance()->screenSize.y, 0.f, 1.f);
		D3DXMatrixIdentity(&world);
	}
	virtual ~Camera()
	{}

public:
	Matrix4 projection;
	Matrix4 world;
	Matrix4 view;

public:
	virtual void Update()
	{
		Object::Update();

		view = Matrix4(
			scale.x * cos(rotation), scale.y * sin(rotation), 0.f, 0.f,
			-scale.y * sin(rotation), scale.y * cos(rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			-position.x * scale.x * cos(rotation) + scale.y * sin(rotation), -position.x * scale.y * sin(rotation) - position.y * scale.y * cos(rotation), 0.f, 1.f);
	}

	virtual void Draw()
	{
		Object::Draw();

		SetTransform();
	}

	void SetTransform()
	{
		DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &projection);
		DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &world);
		DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &view);
	}
};

