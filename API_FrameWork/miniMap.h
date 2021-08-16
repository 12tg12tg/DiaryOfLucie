#pragma once
#include "gameNode.h"
#include "mapManager.h"
	class miniMap : public gameNode
	{
	private:
		vector<pair<POINT, motherMap*>> _vMinimap;

	public:

		miniMap();
		~miniMap();
		HRESULT init();
		void release();
		void update();
		void render();

	};




