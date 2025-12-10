# Performance Benchmark Report

This report presents the complete performance metrics of the project tested on a **2.6 GHz Intel i7 laptop (WSL2 environment)**, including:

- **Matching Core TPS** (matching engine throughput)
- **Match-Only Latency** (pure matching latency)
- **Gateway TPS** (inbound throughput of the gateway)
- **End-to-End RTT** (round-trip latency across the full pipeline)

These benchmark results are summarized in the README.  
This document provides full detailed data.

---

# 1. Matching Core TPS & Match-Only Latency

### Test Command
```
./perf_engine_throughput_latency
```

6 producer threads continuously push orders into 4 matching engine threads.  
The benchmark measures both throughput and latency distribution.

---

## 1.1 Throughput

```
[Producer TPS]       = 1,988,114
[REAL Engine TPS]    =   625,214
[Backlog]            = 1,362,900 msgs
```

### Per-Engine TPS
```
Engine[0] = 156039
Engine[1] = 158074
Engine[2] = 155956
Engine[3] = 155145
```

### Summary
- **Single-engine throughput ≈ 155K TPS**
- **Four-engine total throughput ≈ 625K TPS**

---

## 1.2 Per-Engine Latency

```
Engine[0] samples = 159199
  p50  = 5000 ns
  p95  = 12400 ns
  p99  = 20801 ns
  p999 = 57500 ns
  max  = 2866626 ns

Engine[1] samples = 162063
  p50  = 4901 ns
  p95  = 12100 ns
  p99  = 20100 ns
  p999 = 58201 ns
  max  = 4635143 ns

Engine[2] samples = 160159
  p50  = 5000 ns
  p95  = 12200 ns
  p99  = 20401 ns
  p999 = 59300 ns
  max  = 3241730 ns

Engine[3] samples = 159062
  p50  = 5000 ns
  p95  = 12500 ns
  p99  = 20900 ns
  p999 = 60300 ns
  max  = 3674734 ns
```

---

## 1.3 Overall Latency

```
Global samples = 640483
  p50  = 5000 ns
  p95  = 12300 ns
  p99  = 20600 ns
  p999 = 58900 ns
  max  = 4635143 ns
```

### Latency Summary
- **p50 ≈ 5 μs**
- **p99 ≈ 20 μs**
- **p999 ≈ 50–60 μs**

---

# 2. Gateway TPS (Inbound Read)

### Test Command
```
./perf_gateway_tps
```

### Results
```
[Total Accept] = 8
[Total Read  ] = 123332
[Accept TPS  ] = 1.59983
[Read   TPS  ] = 24663.8
```

---

# 3. End-to-End RTT (Round Trip Time)

### Test Command
```
./perf_rtt
```

### Results (μs)

```
Samples = 20000
p50  = 432.4 us
p95  = 616.9 us
p99  = 724.9 us
p999 = 903.2 us
max  = 2196.3 us
```

---

# 4. Performance Overview

| Metric | Value |
|--------|------------------------------|
| **Matching Core TPS** | ~625,000 orders/sec (4 engines) |
| **Match-Only Latency** | p50 = 5 μs, p99 ≈ 20 μs |
| **Gateway Read TPS** | ~24,600 TPS |
| **End-to-End RTT** | p50 = 0.43 ms |


