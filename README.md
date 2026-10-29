# DX12 Tank Shooter

DirectX 12로 구현한 3D 탱크 슈팅 프로젝트입니다. 탱크를 조작해 지형을 이동하고, 포탄을 발사해 충돌과 폭발 효과를 확인할 수 있습니다.

## 주요 구현 요소

- DirectX 12 렌더링 파이프라인과 HLSL 셰이더
- 탱크 차체·포탑의 계층 구조 및 독립 회전
- 탱크를 추적하는 3인칭 카메라
- 바운딩 박스를 이용한 충돌 판정
- 포탄 오브젝트 풀과 비행 시간 기반 중력 적용
- 폭발 파티클 효과
- 절두체 컬링을 이용한 렌더링 최적화

## 기술 스택

- **Language**: C++
- **Graphics API**: DirectX 12, DXGI
- **Shader**: HLSL
- **Math & Collision**: DirectXMath, DirectXCollision
- **Platform**: Windows, Win32 API
- **Development**: Visual Studio, MSBuild

## 빌드 및 실행

1. Visual Studio에서 `Project3.slnx`를 엽니다.
2. 플랫폼을 `x64`, 구성을 `Debug` 또는 `Release`로 선택합니다.
3. 솔루션을 빌드한 뒤 실행합니다.

## 조작

- `W`, `S`: 탱크 전진·후진
- `A`, `D`: 탱크 차체 회전
- `←`, `→`: 포탑 좌우 회전
- `↑`, `↓`: 포신 각도 조절
- `Space`: 포탄 발사
