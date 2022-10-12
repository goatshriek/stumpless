SeverityNames=(
  Success=0x0:STUMPLESS_WEL_SEVERITY_SUCCESS
  Informational=0x1:STUMPLESS_WEL_SEVERITY_INFO
  Warning=0x2:STUMPLESS_WEL_SEVERITY_WARNING
  Error=0x3:STUMPLESS_WEL_SEVERITY_ERR
)

FacilityNames=(
  Kernel=0x100:STUMPLESS_WEL_FACILITY_KERN
  User=0x101:STUMPLESS_WEL_FACILITY_USER
  Mail=0x102:STUMPLESS_WEL_FACILITY_MAIL
  Daemon=0x103:STUMPLESS_WEL_FACILITY_DAEMON
  LogAuth=0x104:STUMPLESS_WEL_FACILITY_LOG_AUTH
  Syslog=0x105:STUMPLESS_WEL_FACILITY_SYSLOG
  Lpr=0x106:STUMPLESS_WEL_FACILITY_LPR
  News=0x107:STUMPLESS_WEL_FACILITY_NEWS
  Uucp=0x108:STUMPLESS_WEL_FACILITY_UUCP
  Cron=0x109:STUMPLESS_WEL_FACILITY_CRON
  Auth2=0x10a:STUMPLESS_WEL_FACILITY_AUTH2
  Ftp=0x10b:STUMPLESS_WEL_FACILITY_FTP
  Ntp=0x10c:STUMPLESS_WEL_FACILITY_NTP
  Audit=0x10d:STUMPLESS_WEL_FACILITY_AUDIT
  Alert=0x10e:STUMPLESS_WEL_FACILITY_ALERT
  Cron2=0x10f:STUMPLESS_WEL_FACILITY_CRON2
  Local0=0x110:STUMPLESS_WEL_FACILITY_LOCAL0
  Local1=0x111:STUMPLESS_WEL_FACILITY_LOCAL1
  Local2=0x112:STUMPLESS_WEL_FACILITY_LOCAL2
  Local3=0x113:STUMPLESS_WEL_FACILITY_LOCAL3
  Local4=0x114:STUMPLESS_WEL_FACILITY_LOCAL4
  Local5=0x115:STUMPLESS_WEL_FACILITY_LOCAL5
  Local6=0x116:STUMPLESS_WEL_FACILITY_LOCAL6
  Local7=0x117:STUMPLESS_WEL_FACILITY_LOCAL7
)

LanguageNames=(English=0x0409:MSG00409)

;/* category definitions */

MessageIdTypedef=WORD

MessageId=0x1
SymbolicName=STUMPLESS_WEL_EVENT_EMERGENCY
Language=English
Emergency Event
.

MessageId=0x2
SymbolicName=STUMPLESS_WEL_EVENT_ALERT
Language=English
Alert Event
.

MessageId=0x3
SymbolicName=STUMPLESS_WEL_EVENT_CRITICAL
Language=English
Critical Event
.

MessageId=0x4
SymbolicName=STUMPLESS_WEL_EVENT_ERR
Language=English
Error Event
.

MessageId=0x5
SymbolicName=STUMPLESS_WEL_EVENT_WARNING
Language=English
Warning Event
.

MessageId=0x6
SymbolicName=STUMPLESS_WEL_EVENT_NOTICE
Language=English
Notice Event
.

MessageId=0x7
SymbolicName=STUMPLESS_WEL_EVENT_INFO
Language=English
Informational Event
.

MessageId=0x8
SymbolicName=STUMPLESS_WEL_EVENT_DEBUG
Language=English
Debug Event
.

;/* message definitions */

MessageIdTypedef=DWORD

MessageId=0x11
Severity=Success
Facility=Kernel
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_KERN
Language=English
Kernel Success message: %1
.

MessageId=0x12
Severity=Success
Facility=User
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_USER
Language=English
User Success message: %1
.

MessageId=0x13
Severity=Success
Facility=Mail
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_MAIL
Language=English
Mail Success message: %1
.

MessageId=0x14
Severity=Success
Facility=Daemon
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_DAEMON
Language=English
Daemon Success message: %1
.

MessageId=0x15
Severity=Success
Facility=LogAuth
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOG_AUTH
Language=English
LogAuth Success message: %1
.

MessageId=0x16
Severity=Success
Facility=Syslog
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_SYSLOG
Language=English
Syslog Success message: %1
.

MessageId=0x17
Severity=Success
Facility=Lpr
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LPR
Language=English
Lpr Success message: %1
.

MessageId=0x18
Severity=Success
Facility=News
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_NEWS
Language=English
News Success message: %1
.

MessageId=0x19
Severity=Success
Facility=Uucp
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_UUCP
Language=English
Uucp Success message: %1
.

MessageId=0x1a
Severity=Success
Facility=Cron
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_CRON
Language=English
Cron Success message: %1
.

MessageId=0x1b
Severity=Success
Facility=Auth2
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_AUTH2
Language=English
Auth2 Success message: %1
.

MessageId=0x1c
Severity=Success
Facility=Ftp
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_FTP
Language=English
Ftp Success message: %1
.

MessageId=0x1d
Severity=Success
Facility=Ntp
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_NTP
Language=English
Ntp Success message: %1
.

MessageId=0x1e
Severity=Success
Facility=Audit
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_AUDIT
Language=English
Audit Success message: %1
.

MessageId=0x1f
Severity=Success
Facility=Alert
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_ALERT
Language=English
Alert Success message: %1
.

MessageId=0x20
Severity=Success
Facility=Cron2
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_CRON2
Language=English
Cron2 Success message: %1
.

MessageId=0x21
Severity=Success
Facility=Local0
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL0
Language=English
Local0 Success message: %1
.

MessageId=0x22
Severity=Success
Facility=Local1
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL1
Language=English
Local1 Success message: %1
.

MessageId=0x23
Severity=Success
Facility=Local2
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL2
Language=English
Local2 Success message: %1
.

MessageId=0x24
Severity=Success
Facility=Local3
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL3
Language=English
Local3 Success message: %1
.

MessageId=0x25
Severity=Success
Facility=Local4
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL4
Language=English
Local4 Success message: %1
.

MessageId=0x26
Severity=Success
Facility=Local5
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL5
Language=English
Local5 Success message: %1
.

MessageId=0x27
Severity=Success
Facility=Local6
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL6
Language=English
Local6 Success message: %1
.

MessageId=0x28
Severity=Success
Facility=Local7
SymbolicName=STUMPLESS_WEL_MSG_SUCCESS_LOCAL7
Language=English
Local7 Success message: %1
.

MessageId=0x29
Severity=Error
Facility=Kernel
SymbolicName=STUMPLESS_WEL_MSG_ERR_KERN
Language=English
Kernel Error message: %1
.

MessageId=0x2a
Severity=Error
Facility=User
SymbolicName=STUMPLESS_WEL_MSG_ERR_USER
Language=English
User Error message: %1
.

MessageId=0x2b
Severity=Error
Facility=Mail
SymbolicName=STUMPLESS_WEL_MSG_ERR_MAIL
Language=English
Mail Error message: %1
.

MessageId=0x2c
Severity=Error
Facility=Daemon
SymbolicName=STUMPLESS_WEL_MSG_ERR_DAEMON
Language=English
Daemon Error message: %1
.

MessageId=0x2d
Severity=Error
Facility=LogAuth
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOG_AUTH
Language=English
LogAuth Error message: %1
.

MessageId=0x2e
Severity=Error
Facility=Syslog
SymbolicName=STUMPLESS_WEL_MSG_ERR_SYSLOG
Language=English
Syslog Error message: %1
.

MessageId=0x2f
Severity=Error
Facility=Lpr
SymbolicName=STUMPLESS_WEL_MSG_ERR_LPR
Language=English
Lpr Error message: %1
.

MessageId=0x30
Severity=Error
Facility=News
SymbolicName=STUMPLESS_WEL_MSG_ERR_NEWS
Language=English
News Error message: %1
.

MessageId=0x31
Severity=Error
Facility=Uucp
SymbolicName=STUMPLESS_WEL_MSG_ERR_UUCP
Language=English
Uucp Error message: %1
.

MessageId=0x32
Severity=Error
Facility=Cron
SymbolicName=STUMPLESS_WEL_MSG_ERR_CRON
Language=English
Cron Error message: %1
.

MessageId=0x33
Severity=Error
Facility=Auth2
SymbolicName=STUMPLESS_WEL_MSG_ERR_AUTH2
Language=English
Auth2 Error message: %1
.

MessageId=0x34
Severity=Error
Facility=Ftp
SymbolicName=STUMPLESS_WEL_MSG_ERR_FTP
Language=English
Ftp Error message: %1
.

MessageId=0x35
Severity=Error
Facility=Ntp
SymbolicName=STUMPLESS_WEL_MSG_ERR_NTP
Language=English
Ntp Error message: %1
.

MessageId=0x36
Severity=Error
Facility=Audit
SymbolicName=STUMPLESS_WEL_MSG_ERR_AUDIT
Language=English
Audit Error message: %1
.

MessageId=0x37
Severity=Error
Facility=Alert
SymbolicName=STUMPLESS_WEL_MSG_ERR_ALERT
Language=English
Alert Error message: %1
.

MessageId=0x38
Severity=Error
Facility=Cron2
SymbolicName=STUMPLESS_WEL_MSG_ERR_CRON2
Language=English
Cron2 Error message: %1
.

MessageId=0x39
Severity=Error
Facility=Local0
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL0
Language=English
Local0 Error message: %1
.

MessageId=0x3a
Severity=Error
Facility=Local1
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL1
Language=English
Local1 Error message: %1
.

MessageId=0x3b
Severity=Error
Facility=Local2
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL2
Language=English
Local2 Error message: %1
.

MessageId=0x3c
Severity=Error
Facility=Local3
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL3
Language=English
Local3 Error message: %1
.

MessageId=0x3d
Severity=Error
Facility=Local4
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL4
Language=English
Local4 Error message: %1
.

MessageId=0x3e
Severity=Error
Facility=Local5
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL5
Language=English
Local5 Error message: %1
.

MessageId=0x3f
Severity=Error
Facility=Local6
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL6
Language=English
Local6 Error message: %1
.

MessageId=0x40
Severity=Error
Facility=Local7
SymbolicName=STUMPLESS_WEL_MSG_ERR_LOCAL7
Language=English
Local7 Error message: %1
.

MessageId=0x41
Severity=Warning
Facility=Kernel
SymbolicName=STUMPLESS_WEL_MSG_WARNING_KERN
Language=English
Kernel Warning message: %1
.

MessageId=0x42
Severity=Warning
Facility=User
SymbolicName=STUMPLESS_WEL_MSG_WARNING_USER
Language=English
User Warning message: %1
.

MessageId=0x43
Severity=Warning
Facility=Mail
SymbolicName=STUMPLESS_WEL_MSG_WARNING_MAIL
Language=English
Mail Warning message: %1
.

MessageId=0x44
Severity=Warning
Facility=Daemon
SymbolicName=STUMPLESS_WEL_MSG_WARNING_DAEMON
Language=English
Daemon Warning message: %1
.

MessageId=0x45
Severity=Warning
Facility=LogAuth
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOG_AUTH
Language=English
LogAuth Warning message: %1
.

MessageId=0x46
Severity=Warning
Facility=Syslog
SymbolicName=STUMPLESS_WEL_MSG_WARNING_SYSLOG
Language=English
Syslog Warning message: %1
.

MessageId=0x47
Severity=Warning
Facility=Lpr
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LPR
Language=English
Lpr Warning message: %1
.

MessageId=0x48
Severity=Warning
Facility=News
SymbolicName=STUMPLESS_WEL_MSG_WARNING_NEWS
Language=English
News Warning message: %1
.

MessageId=0x49
Severity=Warning
Facility=Uucp
SymbolicName=STUMPLESS_WEL_MSG_WARNING_UUCP
Language=English
Uucp Warning message: %1
.

MessageId=0x4a
Severity=Warning
Facility=Cron
SymbolicName=STUMPLESS_WEL_MSG_WARNING_CRON
Language=English
Cron Warning message: %1
.

MessageId=0x4b
Severity=Warning
Facility=Auth2
SymbolicName=STUMPLESS_WEL_MSG_WARNING_AUTH2
Language=English
Auth2 Warning message: %1
.

MessageId=0x4c
Severity=Warning
Facility=Ftp
SymbolicName=STUMPLESS_WEL_MSG_WARNING_FTP
Language=English
Ftp Warning message: %1
.

MessageId=0x4d
Severity=Warning
Facility=Ntp
SymbolicName=STUMPLESS_WEL_MSG_WARNING_NTP
Language=English
Ntp Warning message: %1
.

MessageId=0x4e
Severity=Warning
Facility=Audit
SymbolicName=STUMPLESS_WEL_MSG_WARNING_AUDIT
Language=English
Audit Warning message: %1
.

MessageId=0x4f
Severity=Warning
Facility=Alert
SymbolicName=STUMPLESS_WEL_MSG_WARNING_ALERT
Language=English
Alert Warning message: %1
.

MessageId=0x50
Severity=Warning
Facility=Cron2
SymbolicName=STUMPLESS_WEL_MSG_WARNING_CRON2
Language=English
Cron2 Warning message: %1
.

MessageId=0x51
Severity=Warning
Facility=Local0
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL0
Language=English
Local0 Warning message: %1
.

MessageId=0x52
Severity=Warning
Facility=Local1
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL1
Language=English
Local1 Warning message: %1
.

MessageId=0x53
Severity=Warning
Facility=Local2
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL2
Language=English
Local2 Warning message: %1
.

MessageId=0x54
Severity=Warning
Facility=Local3
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL3
Language=English
Local3 Warning message: %1
.

MessageId=0x55
Severity=Warning
Facility=Local4
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL4
Language=English
Local4 Warning message: %1
.

MessageId=0x56
Severity=Warning
Facility=Local5
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL5
Language=English
Local5 Warning message: %1
.

MessageId=0x57
Severity=Warning
Facility=Local6
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL6
Language=English
Local6 Warning message: %1
.

MessageId=0x58
Severity=Warning
Facility=Local7
SymbolicName=STUMPLESS_WEL_MSG_WARNING_LOCAL7
Language=English
Local7 Warning message: %1
.

MessageId=0x59
Severity=Informational
Facility=Kernel
SymbolicName=STUMPLESS_WEL_MSG_INFO_KERN
Language=English
Kernel Informational message: %1
.

MessageId=0x5a
Severity=Informational
Facility=User
SymbolicName=STUMPLESS_WEL_MSG_INFO_USER
Language=English
User Informational message: %1
.

MessageId=0x5b
Severity=Informational
Facility=Mail
SymbolicName=STUMPLESS_WEL_MSG_INFO_MAIL
Language=English
Mail Informational message: %1
.

MessageId=0x5c
Severity=Informational
Facility=Daemon
SymbolicName=STUMPLESS_WEL_MSG_INFO_DAEMON
Language=English
Daemon Informational message: %1
.

MessageId=0x5d
Severity=Informational
Facility=LogAuth
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOG_AUTH
Language=English
LogAuth Informational message: %1
.

MessageId=0x5e
Severity=Informational
Facility=Syslog
SymbolicName=STUMPLESS_WEL_MSG_INFO_SYSLOG
Language=English
Syslog Informational message: %1
.

MessageId=0x5f
Severity=Informational
Facility=Lpr
SymbolicName=STUMPLESS_WEL_MSG_INFO_LPR
Language=English
Lpr Informational message: %1
.

MessageId=0x60
Severity=Informational
Facility=News
SymbolicName=STUMPLESS_WEL_MSG_INFO_NEWS
Language=English
News Informational message: %1
.

MessageId=0x61
Severity=Informational
Facility=Uucp
SymbolicName=STUMPLESS_WEL_MSG_INFO_UUCP
Language=English
Uucp Informational message: %1
.

MessageId=0x62
Severity=Informational
Facility=Cron
SymbolicName=STUMPLESS_WEL_MSG_INFO_CRON
Language=English
Cron Informational message: %1
.

MessageId=0x63
Severity=Informational
Facility=Auth2
SymbolicName=STUMPLESS_WEL_MSG_INFO_AUTH2
Language=English
Auth2 Informational message: %1
.

MessageId=0x64
Severity=Informational
Facility=Ftp
SymbolicName=STUMPLESS_WEL_MSG_INFO_FTP
Language=English
Ftp Informational message: %1
.

MessageId=0x65
Severity=Informational
Facility=Ntp
SymbolicName=STUMPLESS_WEL_MSG_INFO_NTP
Language=English
Ntp Informational message: %1
.

MessageId=0x66
Severity=Informational
Facility=Audit
SymbolicName=STUMPLESS_WEL_MSG_INFO_AUDIT
Language=English
Audit Informational message: %1
.

MessageId=0x67
Severity=Informational
Facility=Alert
SymbolicName=STUMPLESS_WEL_MSG_INFO_ALERT
Language=English
Alert Informational message: %1
.

MessageId=0x68
Severity=Informational
Facility=Cron2
SymbolicName=STUMPLESS_WEL_MSG_INFO_CRON2
Language=English
Cron2 Informational message: %1
.

MessageId=0x69
Severity=Informational
Facility=Local0
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL0
Language=English
Local0 Informational message: %1
.

MessageId=0x6a
Severity=Informational
Facility=Local1
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL1
Language=English
Local1 Informational message: %1
.

MessageId=0x6b
Severity=Informational
Facility=Local2
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL2
Language=English
Local2 Informational message: %1
.

MessageId=0x6c
Severity=Informational
Facility=Local3
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL3
Language=English
Local3 Informational message: %1
.

MessageId=0x6d
Severity=Informational
Facility=Local4
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL4
Language=English
Local4 Informational message: %1
.

MessageId=0x6e
Severity=Informational
Facility=Local5
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL5
Language=English
Local5 Informational message: %1
.

MessageId=0x6f
Severity=Informational
Facility=Local6
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL6
Language=English
Local6 Informational message: %1
.

MessageId=0x70
Severity=Informational
Facility=Local7
SymbolicName=STUMPLESS_WEL_MSG_INFO_LOCAL7
Language=English
Local7 Informational message: %1
.
