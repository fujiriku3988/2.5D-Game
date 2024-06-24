#pragma once
#include"../../../../Object/Map/Warp/Gate/BaseGate.h"

class Gate01 :public BaseGate
{
public:

	Gate01() {};
	~Gate01()override {};

	void Init()override;
	void Update()override;
	void OnHit()override;

private:

};
