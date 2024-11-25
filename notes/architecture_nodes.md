- by default nichts an, da speed
- interface "fetch" was dann key-value pairs zurückgibt
  - immer durchiteriert als `vector<unique_ptr<Collector>>`
- selbst http 1.0 "implementieren"
  - just enough um ein valider response zu sein
    - zB immer 200, immer gleicher head
      - aus "Performancegründen"

- for the collectors. maybe replace std::vector with const std::vector&
  - Then they can reuse the buffer since we are singlethreaded
    - document this

- logger should be called SingleThreadedLogger, and explcit notice that no
  locking happens for perf reasons
