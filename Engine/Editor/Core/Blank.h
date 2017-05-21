#pragma once

#include "DX11Base.h"

class CBlank : public CDX11Base
{
public:
	CBlank();
	~CBlank();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update(float dt);
	virtual void Render();
};