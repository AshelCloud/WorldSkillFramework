#pragma once

class ObjectList : public Singleton<ObjectList>
{
private:
	vector<shared_ptr<Object>> objects;
	vector<shared_ptr<Object>> entitys;

public:
	ObjectList()
	{}
	virtual ~ObjectList()
	{}

public:
	template<class T>
	shared_ptr<T> AddObject(T* obj, bool isEntity = true)
	{
		auto tmp = shared_ptr<T>(obj);

		if(isEntity)
		{
			entitys.push_back(tmp);
		}
		else
		{
			objects.push_back(tmp);
		}

		return tmp;
	}
	
	void Update()
	{
		for(auto it = objects.begin(); it != objects.end();)
		{
			if((*it)->isRemoved)
			{
				it->reset();
				it = objects.erase(it);
			}
			else
			{
				it++;
			}
		}

		for (auto it = entitys.begin(); it != entitys.end();)
		{
			if ((*it)->isRemoved)
			{
				it->reset();
				it = entitys.erase(it);
			}
			else
			{
				it++;
			}
		}


		for(size_t i = 0; i < objects.size(); i ++)
		{
			objects[i]->Update();
		}

		for (size_t i = 0; i < entitys.size(); i++)
		{
			entitys[i]->Update();
		}
	}

	void Draw()
	{
		sort(objects.begin(), objects.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->zOrder < b->zOrder; } );
		sort(entitys.begin(), entitys.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->position.y < b->position.y; });

		for(size_t i = 0; i < objects.size(); i ++)
		{
			objects[i]->Draw();
		}

		for (size_t i = 0; i < entitys.size(); i++)
		{
			entitys[i]->Draw();
		}
	}

	vector<shared_ptr<Object>> GetObjects(const string& name)
	{
		vector<shared_ptr<Object>> v;

		for(auto obj : objects)
		{
			if(obj->name == name)
			{
				v.push_back(obj);
			}
		}

		for (auto obj : entitys)
		{
			if (obj->name == name)
			{
				v.push_back(obj);
			}
		}

		return v;
	}

	void Release()
	{
		objects.clear();
		entitys.clear();
	}
};

