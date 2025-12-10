# 性能测试报告

本报告展示本项目在 2.6 GHz Intel i7 笔记本电脑（WSL2 环境）上的性能测试结果，包括：

- Matching Core TPS（撮合核心吞吐量）
- Match-Only Latency（纯撮合延迟）
- Gateway TPS（网关层入站吞吐）
- End-to-End RTT（端到端往返延迟）

相关测试结果已用于 README 中的性能摘要。本文件提供完整详细数据。


# 1. Matching Core TPS & Match-Only Latency

测试命令：

```bash
./perf_engine_throughput_latency
```

使用 6 个 producer 线程持续推送订单，测量 4 个撮合引擎线程的吞吐与延迟表现。

---

## 1.1 吞吐量

```
[Producer TPS]       = 1,988,114
[REAL Engine TPS]    =   625,214
[Backlog]            = 1,362,900 msgs
```

### 单引擎吞吐量

```
Engine[0] = 156039
Engine[1] = 158074
Engine[2] = 155956
Engine[3] = 155145
```

### 总结

- **单引擎吞吐 ≈ 155K TPS**  
- **四引擎总吞吐 ≈ 625K TPS**

---

## 1.2 各引擎延迟
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

## 1.3 总体延迟

```
Global samples = 640483
  p50  = 5000 ns
  p95  = 12300 ns
  p99  = 20600 ns
  p999 = 58900 ns
  max  = 4635143 ns
```

**延迟总结：**

- p50 ≈ **5 μs**  
- p99 ≈ **20 μs**  
- p999 ≈ **50–60 μs**


---

# 2. Gateway TPS（Inbound Read）

测试命令：

```bash
./perf_gateway_tps
```

结果：

```
[Total Accept] = 8
[Total Read  ] = 123332
[Accept TPS  ] = 1.59983
[Read   TPS  ] = 24663.8
```

 

---

# 3. End-to-End RTT（Round Trip Time）

测试命令：

```bash
./perf_rtt
```

RTT 结果（单位 μs）：

```
Samples = 20000
p50  = 432.4 us
p95  = 616.9 us
p99  = 724.9 us
p999 = 903.2 us
max  = 2196.3 us
```

---

#  4. 性能总览

| 指标 | 数值 |
|------|------|
| Matching Core TPS | **~625,000 orders/sec（4 引擎）** |
| Match-Only Latency | **p50 = 5 μs，p99 ≈ 20 μs** |
| Gateway Read TPS | **~24,600 TPS** |
| End-to-End RTT | **p50 = 0.43 ms** |

