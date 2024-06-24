#include "Camera.h"

void Camera::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
	m_spCamera->SetProjectionMatrix(60);
	m_spCamPos = { 0.0f,3.5f,-10.0f };
	m_spCamRot = {};
	m_transMat = Math::Matrix::CreateTranslation(m_spCamPos);
	//マウスを画面中央へ固定させる座標値
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
}

void Camera::Update()
{
	//ヌルチェック必須//
	if (!m_spCamera)return;

	//Targetの行列（有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_spTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	UpdateRotateByMouse();

	m_rotMat = GetRotationMatrix();
	m_mWorld =  m_transMat * m_rotMat * _targetMat;
	m_spCamera->SetCameraMatrix(m_mWorld);
}

void Camera::PreDraw()
{
	if (!m_spCamera)return;
	m_spCamera->SetToShader();
}

void Camera::UpdateRotateByMouse()
{
	//①マウスの現在の位置を取得
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	//②画面中央からの差分を算出する
	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	//③カーソルを画面中央に戻す
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//④差分を利用して回転角度を設定する
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	//回転制御X軸
	//m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
	m_DegAng.x = std::clamp(m_DegAng.x, 0.f, 0.f);
}