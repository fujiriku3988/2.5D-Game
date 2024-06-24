#pragma once
class Camera :public KdGameObject
{
public:
	Camera() {};
	~Camera()override {};

	void Init()override;
	void Update()override;
	void PreDraw();
	void SetTarget(const std::shared_ptr<KdGameObject>& target)
	{
		m_spTarget = target;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z)
		);
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));
	}

private:
	//カメラの回転角度
	Math::Vector3 m_DegAng = Math::Vector3::Zero;

	void UpdateRotateByMouse();

	std::weak_ptr<KdGameObject>m_spTarget;
	std::shared_ptr<KdCamera> m_spCamera = nullptr;

	Math::Matrix m_transMat = Math::Matrix::Identity;
	Math::Matrix m_rotMat = Math::Matrix::Identity;
	Math::Matrix m_rotMatX = Math::Matrix::Identity;

	//カメラ回転用マウス座標
	POINT m_FixMousePos = {};

	Math::Vector3 m_spCamPos;
	Math::Vector3 m_spCamRot;
};

