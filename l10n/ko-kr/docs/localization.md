## 문서 현지화
Stumpless의 일부 문서는 현지화되어 제공됩니다. 이는 온전히 커뮤니티 지원으로
이루어지며, 언어별로 번역된 문서의 분량은 다를 수 있습니다. 특정 언어로 번역된 문서를 확인하기
위해서는 최상위 폴더 내의 `l10n` 폴더를 확인하세요. 해당 폴더에는 번역할 수 있는 언어별로 폴더가
분리되어 있습니다. 언어별로 나누어진 폴더의 내부는 최상위 폴더의 구조를 그대로 따르며 번역본이
없는 문서는 해당 위치에서 제외됩니다. 파일과 폴더의 이름도 현지화할 수 있지만, 필수 사항은 아닙니다.

만약 파일 일부나 전부를 번역해 기여할 경우에는 풀 리퀘스트를 요청해 주세요. 유의미한 분량의
기여만이 반영됩니다. 빈 파일 혹은 적은 문장의 번역을 기여할 경우 반영되지 않을 수 있습니다.

## 라이브러리 현지화
Stumpless는 에러 메시지처럼 사람이 읽기 쉬운 출력물에 대해 다양한 언어를 지원하는 간단한
프레임워크를 제공합니다. 이 구현 방식은 특정 언어별 문자열 정의를 담고 있는 헤더 파일을 사용합니다.
설정을 위하여 간단한 래퍼(Wrapper) 헤더 파일 `private/config/wrapper/locale.h`을 소스 파일에
포함할 수 있습니다. 이 래퍼 헤더 파일은 자동으로 빌드 설정을 확인하여 올바른 로케일을 선택합니다.

## 로케일 헤더
로케일 헤더들은 `private/config/locale`에 위치하며,
[이곳](https://tools.ietf.org/html/rfc5646)에 정의된 IETF 언어 태그를 사용합니다.
예를 들어, 한국어 로케일은 `private/config/locale/ko-kr.h`에 위치합니다.

해당 헤더 파일들은 모두 전처리기를 사용한 동일한 식별자를 사용합니다. 모든 식별자는 `L10N_`를
접두사로 공유하며, 해당 식별자는 컴파일시에 설정된 언어로 변경되어 치환되는 상수 문자열입니다.

이러한 식별자 중 일부는 문자열 상수를 매개변수로 받아 적절한 위치에 삽입하는 함수일 수 있습니다.
예를 들어 `L10N_NULL_ARG_ERROR_MESSAGE` 함수는 NULL 값이 전달된 인자(argument)의 이름을
매개변수로 받아 에러 메시지 안에 삽입합니다. 로케일에 따라 이 값을 메시지의 서로 다른
위치에 배치하거나, 아예 사용하지 않을 수도 있습니다.

## 새로운 구문 추가하기
만약 새로운 에러 메시지나 번역되어야 하는 구문을 추가한다면, 정의된 모든 로케일에
해당 항목을 동일하게 추가해야 합니다. 이는 `en-us` 로케일에 의미 있는 정의가 반드시 포함되어야
하기 때문입니다. 다른 값들은 임시 값(Placeholder)으로 추가되며, 필요한 지식을 가지고 있는
다른 기여자에 의해 번역될 것입니다. 번역되어 있지 않은 구문은 정의 앞에 `// todo translate` 주석을
반드시 추가해야 하며, 구문의 값은 `en-us`의 값과 동일해야 합니다. `scripts/check_l10n.rb` 스크립트는
실행 시 이를 자동으로 확인할 것이며, 실행 시에는 헤더 파일에 대한 통합 검사를 진행합니다.

`scripts/add_l10n_string.rb`는 모든 로케일에 새로운 구문을 빠르게 추가할 수 있는 효율적인
도구입니다. 새로운 구문의 이름과 영어 번역본을 입력하여 실행하면 프로그램이 모든 로케일 헤더에
자동으로 구문을 추가합니다. 아래는 명령어의 예시입니다.
```sh
# 모든 로케일 헤더에 영어 번역문인 "this is a test string"을 가진
# L10N_TEST_STR 심볼이 추가됩니다.
ruby scripts/add_l10n_string.rb TEST_STR this is a test string
```

## 번역할 구문을 검색하기
번역이 필요한 문자열은 현지화 헤더 파일에 `// todo translate` 주석으로 표시되어 있습니다.
이는 Stumpless가 현재 별도의 번역 프레임워크와 연동되어 있지 않음에도 불구하고,
각 로케일별로 번역이 필요한 문자열이 얼마나 되는지 쉽게 파악할 수 있음을 의미합니다.
다음 grep 명령어를 실행하면 번역되지 않은 문자열의 개수를 확인할 수 있습니다
```sh
grep -r -c "// todo translate" include/private/config/locale/

# output looks like this:
# include/private/config/locale/bg-bg.h:12
# include/private/config/locale/cz-cz.h:1
# include/private/config/locale/de-de.h:20
# include/private/config/locale/el-gr.h:0
# include/private/config/locale/en-us.h:0
# include/private/config/locale/es-es.h:2
# include/private/config/locale/fr-fr.h:20
# include/private/config/locale/it-it.h:0
# include/private/config/locale/pl-pl.h:1
# include/private/config/locale/sk-sk.h:17
# include/private/config/locale/sv-se.h:20
```

## 새로운 로케일을 정의하기
라이브러리에 새로운 로케일을 추가하려면 새 헤더 파일을 만들고, 빌드 설정에서 이를 사용할 수 있는지 확인하기만
하면 됩니다. 헤더 추가는 간단합니다. 기존에 있는 헤더를 복사한 뒤(기존 헤더의 언어를 알고 있다면 더 쉽습니다),
정의된 심볼들을 새 로케일에 맞춰 수정하세요. 이때 새 헤더의 이름은 반드시 모두 소문자로 된 유효한 IETF 언어
태그여야 합니다.

헤더를 추가하고 난 후에는 다음 파일들을 업데이트하여 빌드 시스템과 연결해야 합니다.
`tools/cmake/l10n.cmake` 파일, `include/private/config.h.in` 헤더 템플릿, 그리고
로케일 래퍼 헤더 `include/private/config/wrapper/locale.h`을 수정해야 합니다. CMake 스크립트에서,
기존에 작성된 다른 언어들의 패턴을 따라, 로케일을 결정하는 조건문 체인(chain of conditionals)에
`elseif` 블록을 추가하세요. 그 다음, 프라이빗 설정 헤더 템플릿(private config header template)에서,
새로운 로케일을 위한 로케일 식별자를 추가하세요. 이 식별자는 `USE_LOCALE_XXX` 형식을 따라야 합니다.
마지막 부분은 RFC 5646 언어 태그입니다. 이는 모두 대문자이며, 언더바(_)로 띄어쓰기를 대체합니다.
이미 정의된 로케일을 참고하여 작성해주세요. 마지막으로, 로케일 래퍼 헤더에서 CMake 빌드 스크립트와 동일한
순서로 새로운 로케일 구분자에 대해 `#elseif`문을 추가하여 새 헤더를 포함시키면 됩니다.

마지막 단계는 새로운 CI 빌드를 추가하여 당장의 문제나 향후 발생할 수 있는 오류를 방지하는 것입니다.
`.github/workflows/locale.yml` 설정 파일의 빌드 매트릭스(build matrix)에 새 언어용 프로필을
한 줄 추가하기만 하면 되므로 비교적 간단합니다. 모든 작업이 끝나면, 프로젝트 README(Key Features 섹션)에
새 로케일 국기 아이콘을 추가하여 여러분의 기여 결과를 자랑스럽게 표시해 보세요!
