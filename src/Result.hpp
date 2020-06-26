#ifndef BEE_RESULT_HPP
#define BEE_RESULT_HPP

namespace K
{
  template <typename T, typename E>
  class Result
  {
  public:
    Result() :
        success_value(),
        err_value(),
        is_ok(false)
    {  }

    bool
    isOk() const
    {
      return is_ok;
    }

    T
    getOk() const
    {
      return success_value;
    }

    E
    getErr() const
    {
      return err_value;
    }

    void
    setErr(E err)
    {
      err_value = err;
      is_ok = false;
    }

    void
    setOk(T ok)
    {
      success_value = ok;
      is_ok = true;
    }

  private:
    T success_value;
    E err_value;
    bool is_ok;
  };
}

#endif //BEE_RESULT_HPP
