#pragma once
#include "gameNode.h"

	class miniMap : public gameNode
	{
	private:


	public:

		miniMap();
		~miniMap();
		HRESULT init();
		void release();
		void update();
		void render();

	};




