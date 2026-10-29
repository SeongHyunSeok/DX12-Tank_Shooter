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

`C++` · `DirectX 12` · `HLSL` · `DirectXMath` · `DirectXCollision` · `Win32 API`

## 실행 방법

별도의 빌드나 추가 라이브러리 설치 없이 다음 실행 파일을 더블 클릭하면 됩니다.

`Release/Project3.exe`

`Release` 폴더의 `Shaders.hlsl`은 런타임 셰이더 컴파일에 필요하므로 실행 파일과 같은 폴더에
유지해야 합니다. Windows 10/11과 DirectX 12를 지원하는 그래픽 장치 및 드라이버가 필요합니다.

### 소스에서 빌드

`Project3.slnx`를 Visual Studio 2026으로 엽니다.

1. 상단 구성을 `Debug` 또는 `Release`로 선택합니다.
2. 플랫폼을 `x64`로 선택합니다.
3. 솔루션 탐색기에서 `Project3`를 시작 프로젝트로 설정합니다.
4. `F5`를 누르면 빌드 후 실행됩니다. 디버깅 없이 실행하려면 `Ctrl+F5`를 누릅니다.

Visual Studio 2026의 `v145` 도구 집합을 사용합니다. 다른 컴퓨터에서는 Visual Studio Installer에서
**C++를 사용한 데스크톱 개발**을 설치해야 합니다.

빌드 결과는 다음 경로에 생성됩니다.

- Release: `x64/Release/Project3.exe`
- Debug: `x64/Debug/Project3.exe`

빌드된 실행 파일을 Visual Studio 밖에서 직접 실행하려면 저장소 루트의 `Shaders.hlsl`을 실행
파일과 같은 폴더에 복사해야 합니다.

## 조작

- `W`, `S`: 탱크 전진·후진
- `A`, `D`: 탱크 차체 회전
- `←`, `→`: 포탑 좌우 회전
- `↑`, `↓`: 포신 각도 조절
- `Space`: 포탄 발사
