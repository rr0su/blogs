# Notes — Blog 1: Process Creation Deep Study

This file contains raw working notes, experiment results, and observations before writing the final blog.

---

## 🧪 Experiment 1 — Capturing Clean Baseline Sysmon ID 1

Command:

notepad.exe


Observations:
- Parent: explorer.exe
- CommandLine matches Image
- Integrity: Medium
- StartAddress normal (kernel32 → BaseThreadInitThunk → ntdll)

Questions:
- Does handle inheritance occur? → For Notepad via Explorer = minimal.
- PPID chain stable? → Yes.

---

## 🧪 Experiment 2 — Suspicious Process Creation

Method:

powershell.exe -WindowStyle Hidden -Command notepad


Findings:
- Parent is PowerShell (not explorer).
- WindowStyle Hidden creates unusual STARTUPINFO flags.
- CommandLine mismatches user-visible behavior.

Detection angle:
- Hidden window + non-interactive parent = suspicious.

---

## 🧪 Internals Breakdown Notes

### NtCreateUserProcess
- Creates the process + initial thread object.
- Performs token + image validation.
- Creates section object → mapped into address space.

Key anomaly indicators:
- Image mismatch
- Invalid or unexpected security descriptor
- Token anomalies (low privilege → spawning high integrity)

### CreateProcessInternalW
- Where Windows resolves:
  - PPID
  - Handle inheritance
  - Environment block
  - Working directory

Suspicious:
- Excessive inherited handles
- Unusual PPID spoofing patterns

### Loader (LdrInitialize)
- PE mapping
- Import table resolution
- TLS callbacks execution
- Any missing MZ/PE header → → manual mapping zone

### Thread Init
Normal:
- kernel32.dll!BaseThreadInitThunk
- ntdll.dll!RtlUserThreadStart

Suspicious:
- Non-module start addresses
- Thread start inside heap region
- Thread created before loader fully resolves imports

---

## 🔎 Detection Ideas

- Flag processes where:
  - Parent is inconsistent with user interaction.
  - Command-line shows script-like behavior (hidden/encoded).
  - StartAddress not pointing to valid module.
  - Manual mapping artifacts present.

---

## 📝 To Write in Blog
- “Textbook vs real” comparison table.
- Diagram of full call chain.
- Example Sysmon event fields with explanation.
- Real anomalies vs false positives.

---

## 🚀 Next Steps
- Insert diagrams into `/images`.
- Capture 2 more real-world examples.
- Finalize detection queries.

