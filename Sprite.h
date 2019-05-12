#pragma once

class Sprite : public Object
{
public:
	Sprite():
		Object(), color(0xffffffff)
	{}
	Sprite(const string& name):
		Object(), color(0xffffffff)
	{
		tex = TextureManager::GetInstance()->LoadTexture(name);
	}
	virtual ~Sprite()
	{}

public:
	shared_ptr<Texture> tex;

	Color color;

public:
	virtual void Update() override
	{
		Object::Update();
	}
	
	virtual void Draw() override
	{
		Object::Draw();
		
		if(tex == nullptr) { return; }

		Vec3 center = Vec3(tex->r.right, tex->r.bottom, 0.f);
		center *= 0.5f;

		auto spr = App::GetInstance()->spr;

		if(isNonCamera)
		{
			spr->Begin(D3DXSPRITE_ALPHABLEND);
		}
		else
		{
			spr->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		}

		auto transform = GetTransform();
		spr->SetTransform(&transform);

		spr->Draw(tex->tex, nullptr, &center, nullptr, color);

		spr->End();
	}

	virtual RECT GetRect();
};

