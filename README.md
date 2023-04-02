# 1. Game Name : Colorverse
# 2. 오류 해결
## 2-1. 프로젝트 파일이 열리지 않는 경우,
 1) 삭제 : .vs || Binaries || Build || DerivedDataCache || Intermediate || Saved || Colorverse.sln
 2) Coloerverse.uproject 파일에 오른쪽 마우스 클릭 - Generate Visual Studio project files
## 2-2. BP나 기타 파일이 이상한 경우,
 1) Unreal Engine Editor 재시작
 2) 해결이 안 되면, 프로젝트를 삭제하고 새로 Clone
## 2-3. Generate Visual Studio project files 메뉴가 안 보이면,
 1) 해당 uproject 파일의 연결 프로그램을 "C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"로 설정
 2) 위의 방법으로 해결되지 않으면 위 경로의 UnrealVersionSelector.exe를 "C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\Win64"로 복사
 3) 마지막으로 UnrealVersionSelector.exe를 관리자 권한으로 실행
