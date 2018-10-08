MessageIdTypedef=DWORD

SeverityNames=(
  Success=0x0:CUSTOM_SEVERITY_SUCCESS
  Informational=0x1:CUSTOM_SEVERITY_INFORMATIONAL
  Warning=0x2:CUSTOM_SEVERITY_WARNING
  Error=0x3:CUSTOM_SEVERITY_ERROR
)

FacilityNames=(
  Normal=0x256:CUSTOM_FACILITY_NORMAL
)

LanguageNames=(English=0x0409:MSG00409)

MessageId=0x1
SymbolicName=CATEGORY_TEST
Language=English
Test Category
.

MessageId=0x11
Severity=Success
Facility=Normal
SymbolicName=MSG_SIMPLE
Language=English
This is a simple log message.
.

MessageId=0x12
Severity=Success
Facility=Normal
SymbolicName=MSG_ONE_INSERTION
Language=English
This is a simple log message with one insertion: %1.
.

MessageId=0x13
Severity=Success
Facility=Normal
SymbolicName=MSG_TWO_INSERTIONS
Language=English
This is a simple log message with two insertions: %1 and %2.
.
