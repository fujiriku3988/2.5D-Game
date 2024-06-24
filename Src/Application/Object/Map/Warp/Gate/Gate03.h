#pragma once
#include"../../../../Object/Map/Warp/Gate/BaseGate.h"

class Gate03 :public BaseGate
{
public:

	Gate03() {};
	~Gate03()override {};

	void Init()override;
	void Update()override;
	void OnHit()override;

private:

};
