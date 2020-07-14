# Severity Level Logging

Severity levels exist in just about every logging API, and serve as a convenient way to categorize log messages at a broad level. The severities in stumpless directly match those specified in the syslog standard ([RFC 5424](https://tools.ietf.org/html/rfc5424)), which are common to most logging libraries regardless of language or platform.


 | Name    | Shorthand | Description                      |
 |---------|-----------|----------------------------------|
 | EMERG   | em        | system is unusable               |
 | ALERT   | a         | action must be taken immediately |
 | CRIT    | c         | critical conditions              |
 | ERR     | er        | error conditions                 |
 | WARNING | w         | warning conditions               |
 | NOTICE  | n         | normal but significant condition |
 | INFO    | i         | informational messages           |
 | DEBUG   | d         | debug-level messages             |
