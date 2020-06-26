namespace K::Memory
{
  template <typename T>
  static inline void
  clear(T& var)
  {
    if (var != nullptr)
    {
      delete var;
      var = nullptr;
    }
  }
}