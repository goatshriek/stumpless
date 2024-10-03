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



