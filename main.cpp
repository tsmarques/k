#include <iostream>
#include <filesystem>

#include <QApplication>

#include <K.hpp>
#include <Options.hpp>
#include <src/KLog.hpp>

K::Result<K::Arguments, std::string>
parseOptions(int argc, char** argv)
{
  K::Options options;

  options
      .add('h', "--help", false, false, "Show usage message")
      .add('v', "--version", false, false, "Show version")
      .add('f', "--files", false, false, "Open given files (separated by space)\n"
                                       "Default value is scratch buffer");

  K::Result<K::Arguments, std::string> ret;
  if (!options.parse(argc, argv))
  {
    ret.setErr("failed to parse arguments");
    return ret;
  }

  K::Arguments args;
  ret.setOk(args);
  return ret;
}

int main(int argc, char** argv)
{
  klog(".. welcome to K\n");
  K::Result<K::Arguments, std::string> ret = parseOptions(argc, argv);

  if (!ret.isOk())
  {
    klog("klog: error: ", ret.getErr());
    return 1;
  }

  // unwrap
  K::Arguments arguments = ret.getOk();

//  m_args.m_curr_dir = fs::current_path();
//  std::cerr <<  m_args.m_curr_dir << std::endl;

  QApplication a(argc, argv);
  K::K w(nullptr, arguments);
  w.show();
  return a.exec();
}
