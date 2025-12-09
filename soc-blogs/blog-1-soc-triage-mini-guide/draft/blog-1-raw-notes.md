How SOC Analysts Actually Triage Alerts — A Real-World Mini Guide

Goal of the Blog

Show realistic Tier-1 SOC workflow:
alert → verify → investigate → decide → document → escalate (if needed).

----------


Target Reader

– Beginner SOC students
– Recruiters checking if I understand SOC fundamentals
– Interviewers looking for Tier-1 mindset


-------------


High-Level Flow

What “triage” actually means

How alerts enter the SOC

Severity levels

Step-by-step triage workflow

Common alerts list

One small case-study

When to escalate

Documentation style



---------------


1. What Triaging Actually Means (notes)

Not “solve everything”

First-pass analysis

Validate if alert is real, false positive, or needs escalation

Reduce noise

Provide clean context for Tier-2

Fast + consistent decision-making


--------------------


2. How Alerts Enter SOC (notes)

SIEM (Splunk, Sentinel, QRadar, ELK)

EDR (Defender, CrowdStrike, SentinelOne)

Firewall alerts

Email security (Phishing tools)

Identity platforms (Azure AD, Okta)

Alert contains: timestamp, user, host, detection rule, event data.


------


3. Severity Levels (realistic)

Critical — Active exploitation, malware execution, privilege escalation
High — Suspicious PowerShell, lateral movement indicators
Medium — Failed logons, unusual login location
Low — Noise, repeated benign events, housekeeping alerts


-------------


4. Standard Triage Steps (Tier-1 reality check)
Step 1: Identify

What triggered the alert?

Which rule fired?

What asset? (server, workstation)


Step 2: Investigate (quick checks)

Look at user context

Look at device history

Check frequency of similar alerts

Parse logs (parent process, command-line, network connections)


Step 3: Decide

Noise?

Suspicious but not confirmed malicious?

Confirmed malicious?

Needs escalation? (privileged accounts, lateral movement signs)


Step 4: Document

Summary

What you checked

Why you took decision

Evidence (event IDs, timestamps)


-----------


5. Common Alerts
Suspicious PowerShell

– Encoded commands
– DownloadString
– Parent = WINWORD.exe / EXCEL.exe



Failed Logons

– Repeated failures
– Across many hosts
– From weird geolocation



RDP Brute-Force

– Multiple source IPs
– Repeated Event ID 4625
– Unknown external source



Malware Detection

– EDR quarantined file
– Suspicious executable in temp folder
– User reports popup


-----------


6. Example Case (simple)

Alert: “Suspicious PowerShell Execution”
Log shows:
powershell.exe -enc JAB3AG… (base64)

Tier-1 Actions:

Decode base64

Check parent process → WINWORD.exe

Look for URL in script

Check if user opened phishing email

Decide → escalate to Tier-2


------


7. When to Escalate

Privileged accounts involved

Possible lateral movement

Payload/download detected

Persistence indicators

Command-and-control callbacks

Anything unclear but suspicious


-----


8. Documentation Template

Alert: Suspicious PowerShell
Host: DESKTOP-01
User: non-privileged
Summary: base64 encoded command launched by WINWORD.exe
Checks Performed: parent, cmdline, timeline, user history
Decision: Escalated
Reason: Possible malicious macro execution
Evidence: Event IDs, decoded script snippet
