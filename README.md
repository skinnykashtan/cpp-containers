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
<br><br>
Tests: `Create_Object_With_Default`

### Initializer list
`Vector<T> vector{...}` copies into raw storage with `std::uninitialized_copy_n`. Elements are `const`, so they cannot be moved; `std::uninitialized_move_n` would still copy.
`size_` is set only after the copies succeed. An empty list allocates nothing.
After this ctor, `capacity == size`.
<br><br>
Tests: `Create_Object_With_Initializer_List`.

### ReAlloc
`ReAlloc` is private: it grows the buffer. Callers use `PushBack`, not this function.
If `newCapacity <= capacity_`, it returns.
Otherwise it allocates a larger raw block (`::operator new(newCapacity * sizeof(T))`) and `static_cast`s it to `T*`. That makes pointer arithmetic (`data_ + i`) step by `sizeof(T)`, which placement new / `construct_at` / `uninitialized_*` need. It does not start object lifetime - the allocation is storage, not live objects.
`if constexpr (std::is_nothrow_move_constructible_v<T>)` is a compile-time type trait:
if moving `T` is `noexcept` (a `noexcept` move ctor, or a trivial type), existing elements are **move-constructed** into the new storage with `std::uninitialized_move_n`.
Otherwise they are **copy-constructed** with `std::uninitialized_copy_n` inside `try`.
A throwing copy is cleaned up by the algorithm (prefix in the *new* block); `catch` frees that allocation and rethrows, so the old buffer is unchanged.
Only after that succeeds: `std::destroy_at(data_ + i)` on the old objects (pointer arithmetic, not `data_[i]`), `::operator delete(data_)`, then `data_ = newBlock` and `capacity_ = newCapacity`. `size_` stays the same.

## Array

## Queue

## Deque

## List

## Map

## Hash map