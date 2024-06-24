#pragma once
#include"../../../../Object/Map/Warp/Gate/BaseGate.h"

class Gate05 :public BaseGate
{
public:

	Gate05() {};
	~Gate05()override {};

	void Init()override;
	void Update()override;
	void OnHit()override;

private:

};
