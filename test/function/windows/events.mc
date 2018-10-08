MessageIdTypedef=DWORD

SeverityNames=(
  Success=0x0:SEVERITY_SUCCESS
  Informational=0x1:SEVERITY_INFORMATIONAL
  Warning=0x2:SEVERITY_WARNING
  Error=0x3:SEVERITY_ERROR
)

FacilityNames=(
  Normal=0x256:FACILITY_NORMAL
  EmptyArgument=0x257:FACILITY_EMPTY_ARGUMENT
  MemoryFailure=0x258:FACILITY_MEMORY_FAILURE
)

LanguageNames=(English=0x0409:MSG00409)

; // The following are message definitions.

MessageId=0x1
Severity=Success
Facility=Normal
SymbolicName=MSG_SIMPLE
Language=English
This is a simple log message.
.

MessageId=0x2
Severity=Success
Facility=Normal
SymbolicName=MSG_ONE_INSERTION
Language=English
This is a simple log message with one insertion: %1.
.

MessageId=0x3
Severity=Success
Facility=Normal
SymbolicName=MSG_TWO_INSERTIONS
Language=English
This is a simple log message with two insertions: %1 and %2.
.
