#pragma once

#include "Timer.h"
#include "Shader.h"

class CPlayer;

class CScene
{
public:
	CScene();
	~CScene();

	// 씬에서 마우스와 키보드 메시지를 처리한다.
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void ReleaseUploadBuffers();

	// 그래픽 루트 시그너쳐를 생성한다.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

	void CheckObjectByBulletCollisions();

public:
	CPlayer* m_pPlayer = NULL;

protected:
	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다. 
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	// 루트 시그너쳐를 나타내는 인터페이스 포인터이다.
	/*그래픽스 파이프라인이나 계산 파이프라인에 의해 사용되는 리소스
	(예: 상수 버퍼, 샘플러, 텍스처 등)에 대한 접근 방법을 정의*/ 
	// 간단히 말하면 GPU에게 셰이더에서 어떤 리소스를 어떻게 사용할 것인지 알려주는 설계도
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

