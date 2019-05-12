#pragma once

class Button : public Sprite
{
public:
	Button(const string& name, function<void()> _fuc):
		Sprite(name), alreadyClick(false), fuc(_fuc)
	{
		normalTex = TextureManager::GetInstance()->LoadTexture(name);
	}
	virtual ~Button()
	{}

public:
	shared_ptr<Texture> normalTex;
	shared_ptr<Texture> pushTex;

	bool alreadyClick;

	function<void()> fuc;

public:
	virtual void Update()
	{
		Sprite::Update();
		
		if(Rect::CollisionPoint(GetRect(), App::GetInstance()->mousePosition))
		{
			if(App::GetInstance()->mouseClick && !alreadyClick)
			{
				if(pushTex != nullptr) { tex = pushTex; }
				alreadyClick = true;
			}
			
			if(!App::GetInstance()->mouseClick && alreadyClick)
			{
				tex = normalTex;
				alreadyClick = false;
				fuc();
			}
		}
	}
};

