#pragma once
#include"../../../../Object/Map/Warp/Gate/BaseGate.h"

class Gate02 :public BaseGate
{
public:

	Gate02() {};
	~Gate02()override {};

	void Init()override;
	void Update()override;
	void OnHit()override;

private:

};
