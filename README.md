# Custom C++ vector implememtation

## Push_back benchmark
```
Benchmark: inserting 10000 elements
My vector: << 0 ms
STD vector: << 0 ms

Benchmark: inserting 100000 elements
My vector: << 1 ms
STD vector: << 0 ms

Benchmark: inserting 1000000 elements
My vector: << 8 ms
STD vector: << 7 ms

Benchmark: inserting 10000000 elements
My vector: << 94 ms
STD vector: << 100 ms

Benchmark: inserting 100000000 elements
My vector: << 964 ms
STD vector: << 869 ms
```

## Reallocation benchmark
(This vector is using same growth method as g++ std::vector)
```
Benchmark: reallocations inserting 10000 elements
My vector: << 23
STD vector: << 23

Benchmark: reallocations inserting 100000 elements
My vector: << 29
STD vector: << 29

Benchmark: reallocations inserting 1000000 elements
My vector: << 34
STD vector: << 34

Benchmark: reallocations inserting 10000000 elements
My vector: << 40
STD vector: << 40

Benchmark: reallocations inserting 100000000 elements
My vector: << 46
STD vector: << 46
```
