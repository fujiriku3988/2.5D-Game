#pragma once
#include"../../../../Object/Map/Warp/Gate/BaseGate.h"

class Gate04 :public BaseGate
{
public:

	Gate04() {};
	~Gate04()override {};

	void Init()override;
	void Update()override;
	void OnHit()override;

private:

};
