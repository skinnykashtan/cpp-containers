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

### PushBack
Two overloads. Both grow if `size_ == capacity_`, then start an object's lifetime at `data_ + size_` (placement new, not `operator=`), then `size_++`.
Empty buffer goes to capacity `2`; afterwards `capacity + capacity / 2`.
`PushBack(const T&)` copy-constructs the new element.
`PushBack(T&&)` move-constructs it - `std::move(value)` is required inside the function: the parameter has a name, so it is an lvalue even though its type is `T&&`.
Grow is `ReAlloc`; the third `PushBack` relocates the two live elements, then constructs the new one.<br><br>
Tests:<br>
`PushBack_Fills_Initial_Capacity` - two `int`s, first allocation only (`0 → 2`).<br>
`PushBack_Fills_Int_ReAlloc_Capacity` - third `int` forces `2 → 3`; values survive.
`PushBack_Fills_String_ReAlloc_Capacity` - same grow for `std::string` (still the noexcept-move path).
`ReAlloc_Copies_When_Move_Is_Not_Noexcept` - helper type whose move is not `noexcept`; lvalue `PushBack` so inserts copy; after grow `copyCounter == 5`, `moveCounter == 0` (two extra copies from relocating `obj1`/`obj2`).
`ReAlloc_Moves_When_Move_Is_Noexcept` - same scenario with a `noexcept` move ctor: `copyCounter == 3` (three inserts), `moveCounter == 2` (relocate).

## Array

## Queue

## Deque

## List

## Map

## Hash map