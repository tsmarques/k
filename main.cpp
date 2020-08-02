#include <iostream>
#include <filesystem>

#include <QApplication>

#include <K.hpp>
#include <OptionsParser.hpp>
#include <src/KLog.hpp>

K::Result<K::Options, std::string>
parseOptions(int argc, char** argv)
{
  K::OptionsParser options;

  options
      .add(K::OptionsParser::Entry('h', "--help")
           .isFlag(false)
           .isRequired(false)
           .description("Show usage message"))
      .add(K::OptionsParser::Entry('v', "--version")
           .isFlag(false)
           .isRequired(false)
           .description("Show version"))
      .add(K::OptionsParser::Entry('f', "--files")
           .isFlag(false)
           .isRequired(false)
           .description("Open given files (separated by space)\n"
                        "Default value is scratch buffer"));

  K::Options kargs;
  K::Result<K::Options, std::string> ret;
  if (!options.parse(kargs, argc, argv))
  {
    ret.setErr("failed to parse arguments");
    return ret;
  }

  ret.setOk(kargs);
  return ret;
}

int main(int argc, char** argv)
{
  klog(".. welcome to K\n");
  K::Result<K::Options, std::string> ret = parseOptions(argc, argv);

  if (!ret.isOk())
  {
    klog("klog: error: ", ret.getErr());
    return 1;
  }

  // unwrap
  K::Options arguments = ret.getOk();

  if (arguments.m_help_str.has_value())
  {
    std::cerr << "usage: " << arguments.m_help_str.value() << std::endl;
    return 0;
  }
  else if (arguments.m_version_str.has_value())
  {
    std::cerr << "K: " << arguments.m_version_str.value() << std::endl;
    return 0;
  }

  QApplication a(argc, argv);
  K::K w(nullptr, arguments);
  w.show();
  return a.exec();
}
