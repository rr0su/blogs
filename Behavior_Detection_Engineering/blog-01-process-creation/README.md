# Blog 1 — What Process Creation Really Looks Like (Real Internals, Not Textbook)

This blog breaks down the **real** Windows process creation path:
`NtCreateUserProcess → CreateProcessInternalW → Loader → Thread Initialization`.

Most public explanations stop at “CreateProcessW → boom, process starts.”  
This blog shows the **actual execution chain**, the handles passed, the inherited attributes, and the telemetry you MUST baseline before doing behavior detection.

---

## 🔥 Goal
Give analysts a **ground-truth model** of process creation so anomalies stand out instantly.

---

## 📌 Core Flow Covered

1. **NtCreateUserProcess**
   - Object Manager checks
   - Token + security descriptor evaluation
   - Section object creation

2. **CreateProcessInternalW**
   - Parameter validation
   - Handle inheritance rules
   - PPID chain resolution
   - StartupInfo processing

3. **Loader Behavior**
   - Image mapping
   - Import resolution
   - TLS callbacks
   - Static vs dynamic loading paths

4. **Thread Initialization**
   - CreateRemoteThread vs RtlCreateUserThread nuances
   - Early thread start behaviors
   - Thread context anomalies

---

## 🕵️ Detection-Relevant Points

- Unexpected parent processes (PPID spoofing / inheritance abuse)
- Suspicious handle flags during creation
- Inconsistent image → command-line → PPID chain
- Loader bypass or manual mapping footprints
- Thread start address anomalies

---

## 🧪 Examples Included

`examples/`
- `sysmon-id1-normal.txt` → Clean baseline sample  
- `sysmon-id1-suspicious.txt` → Injected / spoofed scenarios

---

## 📊 Detection Snippets

`detections/`
- `sigma.yml` → Sigma rule template  
- `kql.txt` → Sentinel / DefLog query  
- `splunk.txt` → SPL query  

---

## 📁 Repository Structure

```code
blog-01-process-creation/
│
├── README.md
├── notes.md
│
├── images/
│ └── process_flow.svg
│
├── examples/
│ ├── sysmon-id1-normal.txt
│ └── sysmon-id1-suspicious.txt
│
└── detections/
├── sigma.yml
├── kql.txt
└── splunk.txt
```


---

## 🛠 How to Use
- Use **notes.md** as the working file while doing hands-on experiments.
- Capture Sysmon logs and drop them in `/examples`.
- Update diagrams in `/images`.
- Keep detection queries in `/detections`.

---

## 📅 Time Required
2 days (assuming Windows internals basics already completed).

---

## 🎯 Why This Matters
Without understanding **real** process creation internals, your detection engineering is just guesswork.  
This blog forces you to build the baseline model every pro analyst relies on.


------

![Process Flow](images/process_flow.svg)
