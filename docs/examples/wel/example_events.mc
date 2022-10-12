MessageIdTypedef=DWORD

SeverityNames=(
  Success=0x0:CUSTOM_SEVERITY_SUCCESS
  Informational=0x1:CUSTOM_SEVERITY_INFORMATIONAL
  Warning=0x2:CUSTOM_SEVERITY_WARNING
  Error=0x3:CUSTOM_SEVERITY_ERROR
)

FacilityNames=(
  Normal=0x100:CUSTOM_FACILITY_NORMAL
)

LanguageNames=(English=0x0409:MSG00409)

; // category definitions

MessageIdTypedef=WORD

MessageId=0x1
SymbolicName=CATEGORY_TREE
Language=English
Tree Indetification Events
.

; // message definitions

MessageIdTypedef=DWORD

MessageId=0x11
Severity=Success
Facility=Normal
SymbolicName=MSG_TREE_IDENTIFIED_BY_CHILD
Language=English
%1 found a %2 tree!.
.
