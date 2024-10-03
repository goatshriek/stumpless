![Stumpless logo](./자원/로고와이름.svg)

**고성능과 다양한 기능을 갖춘 C 언어 로깅 라이브러리입니다.**

[![Linux Builds](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml)
[![Windows Builds](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml)
[![Mac Builds](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/latest/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![Gitter](https://badges.gitter.im/stumpless/community.svg)](https://gitter.im/stumpless/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.1-ff69b4.svg)](https://github.com/goatshriek/stumpless/blob/latest/docs/CODE_OF_CONDUCT.md)  

  
[주요 기능](#주요-기능) |
[빌드 및 설치](#빠른-빌드-및-설치) |
[기본 사용법](#기본-사용법) |
[기여하기](#기여하기)  

[간체 중국어](./l10n/zh-cn/自述.md)
  

[English](./../../README.md)


[한국어](#한국어)  

  
## 주요 특징  
stumpless에는 C 로그를 빠르고 쉽게 만드는 많은 기능이 있습니다:
* Splunk, rsyslog, journald, Windows 이벤트 로그, sqlite 등과 같은
  [다양한 대상](#어디에-로그를-기록할-수-있나요?)에 로그를 기록할 수 있습니다!
* 사용자 요구에 맞는 구조화된 로그와 비구조화된 로그 지원
* Linux, Windows, Mac, FreeBSD, MinGW, MSYS2, Cygwin, DOS 등에서 빌드 가능!
* 스레드 안전성
* 런타임 비용을 전혀 발생시키지 않도록, 컴파일 시 조정하거나 해당 기능을 제거할 수 있습니다.
* 다양 언어로 번역되었습니다. 🇦🇱 🇧🇷 🇧🇬 🇨🇳 🇨🇿 🇩🇪 🇩🇰 🇪🇸 🇫🇷 🇬🇷 🇭🇺 🇮🇳 🇮🇱 🇮🇹
  🇯🇵 🇰🇪 🇰🇷 🇵🇱 🇸🇰 🇱🇰 🇸🇪 🇹🇷 🇺🇸
  ([언어 번역을 추가해 주세요!](https://github.com/goatshriek/stumpless/blob/latest/docs/localization.md))
* 쉽게 접근할 수 있는
  [문서](https://goatshriek.github.io/stumpless/docs/c/latest/index.html),
  [예제](https://github.com/goatshriek/stumpless/tree/latest/docs/examples),
  및 [지원](https://gitter.im/stumpless/community).

### 어디에 로그를 기록할 수 있나요?
이 라이브러리의 주요 목표는 다양한 로그 대상을 위한 일관된 로그 인터페이스를 제공하는 것입니다. 이를 통해 사용자는 이벤트를 정의하고 해당 이벤트가 어디로 전송될지를 쉽게 결정할 수 있습니다. 다른 SDK를 찾거나 데몬 및 플러그인을 추가하여 원하는 위치로 로그를 보내는 작업을 하지 않아도 됩니다. stumpless는 다음에 대한 로그를 기록할 수 있습니다:
* 간단한 문자 버퍼
* 파일 및 스트림
* 유닉스 소켓(예: 로컬 syslog 데몬)
* 네트워크 서버(IPv4 또는 IPv6, TCP 또는 UDP)
* Systemd Journald 서비스
* Sqlite3 데이터베이스
* Windows 이벤트 로그
* 필요한 기타 모든 것에 대한 사용자 정의 함수!

필요한 것이 없나요? 요청 사항과 함께
[이슈](https://github.com/goatshriek/stumpless/issues/new?template=feature_request.md)를 생성해 주시면, 저희의
[로드맵](https://github.com/goatshriek/stumpless/blob/latest/docs/roadmap.md)에 포함하겠습니다!


## 빠른 빌드 및 설치  
Stumpless는 빌드를 위해 cmake와 cmake를 지원하는 빌드 도구 체인(GCC 또는 Visual Studio 등)만 필요합니다. 표준 GNU make 도구 체인을 사용하는 시스템에서는 다음의 단계를 통해 쉽게 설치할 수 있습니다:


```sh
# 소스 트리의 최신 버전 클론
git clone git@github.com:goatshriek/stumpless.git

# 새로운 빌드 디렉토리 생성
mkdir build
cd build

# 새로운 빌드 구성
cmake ../stumpless

# stumpless 빌드 (4개의 스레드 사용 - 원하는 대로 조정 가능)
make -j 4 all

# 라이브러리 설치 (이 작업을 위해 sudo 권한이 필요할 수 있습니다)
sudo make install
```

