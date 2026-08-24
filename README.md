# cpp-containers

I'm reimplementing C++ containers from scratch so I actually understand them. Vector, array, queues, maps, hash maps.

As I finish something (or get stuck), I'll write a few notes under its heading. Usually: what it is, how it sits in memory, the complexity that actually matters, and whatever surprised me while implementing it.

## Build and test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Vector

### Default construction
`Vector<T> vector;` - empty, no allocation.
Tests: `Create_Object_With_Default`

### Initializer list
`Vector<T> vector{...}` copies into raw storage with `std::uninitialized_copy_n`. Elements are `const`, so they cannot be moved; `std::uninitialized_move_n` would still copy.
`size_` is set only after the copies succeed. An empty list allocates nothing.
After this ctor, `capacity == size`.
<br><br>
Tests: `Create_Object_With_Initializer_List`.

## Array

## Queue

## Deque

## List

## Map

## Hash map