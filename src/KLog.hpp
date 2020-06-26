#ifndef K_EDITOR_KLOG_HPP
#define K_EDITOR_KLOG_HPP

#include <iostream>
#include <cstdarg>

template<typename ...Args>
void klog(Args&&... args)
{
  (std::cerr << ... << args) << std::endl;
}

#endif
