#pragma once

#include "Camera.h"
#include "Mesh.h"

#define BULLET_RELOAD_TIME		1
#define BULLETS					30

#define EXPLOSION_DEBRISES		240

class CShader;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

private:
	int m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

protected:
	XMFLOAT4X4				m_xmf4x4Transform;
	XMFLOAT4X4				m_xmf4x4World;

	CMesh					*m_pMesh = NULL;

	CShader					*m_pShader = NULL;

public:
	void ReleaseUploadBuffers();

	virtual void SetMesh(CMesh* pMesh);
	virtual void SetShader(CShader* pShader);

	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);

	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4* pxmf4x4World, CMesh* pMesh, CCamera* pCamera);

	//상수 버퍼를 생성한다. 
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	//상수 버퍼의 내용을 갱신한다. 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//게임 객체의 월드 변환 행렬에서 위치 벡터와 방향(x-축, y-축, z-축) 벡터를 반환한다. 
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	
	XMFLOAT4X4	GetWorld() { return m_xmf4x4World; };
	void		SetWorld(XMFLOAT4X4 xmf4x4World) { m_xmf4x4World = xmf4x4World; }

	//게임 객체의 위치를 설정한다. 
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);
	
	//게임 객체를 로컬 x-축, y-축, z-축 방향으로 이동한다.
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT4* pxmf4Quaternion);

	bool IsVisible(CCamera* pCamera = NULL);

	void UpdateBoundingBox();

	// 게임 동작을 위해 추가
public:
	bool						m_bActive = true;

	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox();

	// 충돌된 게임오브젝트의 포인터
	CGameObject					*m_pObjectCollided = NULL;
	DWORD						m_dwDefaultColor = RGB(255, 0, 0);
	DWORD						m_dwColor = RGB(255, 0, 0);

	void SetActive(bool bActive) { m_bActive = bActive; }

	// 계층 구조를 위한 멤버 함수 및 변수 추가
public:
	char		m_pstrFrameName[64];

	CGameObject* m_pParent = NULL;
	CGameObject* m_pChild = NULL;
	CGameObject* m_pSibling = NULL;

	void SetChild(CGameObject* pChild);

	CGameObject* FindFrame(char* pstrFrameName);

	void UpdateTransform(XMFLOAT4X4* pxmf4x4Parent = NULL);

};

class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	virtual ~CRotatingObject();

private:
	XMFLOAT3 m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	float m_fRotationSpeed = 0.0f;

public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis =
			xmf3RotationAxis;
	}
	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);
};

class CBulletObject : public CGameObject
{
public:
	CBulletObject(float fEffectiveRange);
	virtual ~CBulletObject();

public:
	virtual void Animate(float fElapsedTime, XMFLOAT4X4* pxmf4x4Parent = NULL);

	float						m_fBulletEffectiveRange = 50.0f;
	float						m_fMovingDistance = 0.0f;
	XMFLOAT3					m_xmf3FirePosition = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fFireStartTime = 0.f;
	float						m_fElapsedTimeAfterFire = 0.0f;

	XMFLOAT3					m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	float						m_fMovingSpeed = 0.0f;
	float						m_fMovingRange = 0.0f;

	XMFLOAT3					m_xmf3Velocity = XMFLOAT3(0.0f, 0.f, 0.0f);
	XMFLOAT3					m_xmf3Gravity = XMFLOAT3(0.0f, -0.58f, 0.0f);

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingRange(float fRange) { m_fMovingRange = fRange; }

	void SetFirePosition(XMFLOAT3 xmf3FirePosition);
	void Reset();
};

class CExplosiveObject : public CRotatingObject
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();

	bool						m_bBlowingUp = false;

	XMFLOAT4X4					m_pxmf4x4Transforms[EXPLOSION_DEBRISES];
	CRotatingObject		*m_ppParticle[EXPLOSION_DEBRISES];

	float						m_fElapsedTimes = 0.0f;
	float						m_fDuration = 1.0f;
	float						m_fExplosionSpeed = 2.f;
	float						m_fExplosionRotation = 720.0f;

	virtual void Animate(float fElapsedTime, XMFLOAT4X4* pxmf4x4Parent = NULL);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

public:
	static CMesh				*m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES];

	void PrepareExplosion(CMesh* pExplosionMesh);
	void SetExplosionMesh(CMesh* pExplosionMesh);
};