#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<memory>
#include<map>

class House 
{
	int len, wid;
	static std::map<int, std::weak_ptr<House>> cache;

public:
	House()
		:len(0), wid(0) {
	}
	House(int len, int wid)
		:len(len), wid(wid)
	{
	}

	~House()
	{
		std::cout << "destructor" << std::endl;
	}

	void setLen(int length) { len = length; }
	void setWid(int width) { wid = width; }
	int getLen() { return len; }
	int getWid() { return wid; }

	static std::shared_ptr<House> getHouse(int length, int width) {

		std::shared_ptr<House> share_object;
		if (!cache.empty()){
			for (std::map<int, std::weak_ptr<House>>::iterator it = cache.begin(); it != cache.end(); ++it) {
				if (!(it->second.expired())) {
					auto object = it->second.lock();

					if ((object->getLen() == length) && (object->getWid() == width))
					{
						share_object = object; break;
					}

				}
			}

		}
		else
		{
			share_object = std::make_shared<House>(length, width);
			cache.insert(std::pair<int, std::weak_ptr<House>>(cache.size() + 1, std::weak_ptr<House>(share_object)));
		}
		return share_object;
	}
};
