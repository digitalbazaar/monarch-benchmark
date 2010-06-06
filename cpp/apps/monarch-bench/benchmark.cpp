/*
 * Copyright (c) 2010 Digital Bazaar, Inc. All rights reserved.
 */
#include "monarch/app/AppFactory.h"
#include "monarch/data/json/JsonWriter.h"

#include <cstdio>

using namespace std;
using namespace monarch::app;
using namespace monarch::config;
using namespace monarch::data::json;
using namespace monarch::modest;
using namespace monarch::net;
using namespace monarch::rt;

#define APP_NAME "monarch.apps.benchmark"

namespace monarch
{
namespace apps
{
namespace benchmark
{

class BenchmarkApp : public App
{
protected:
   /**
    * Options from the command line.
    */
   DynamicObject mOptions;

public:
   BenchmarkApp()
   {
      // set defaults
      mOptions["command"] = "";
      mOptions["port"] = (uint32_t)0;
      mOptions["protocol"] = "TCP";
      mOptions["verbose"] = false;
   };

   virtual ~BenchmarkApp() {};

   virtual DynamicObject getCommandLineSpec(Config& cfg)
   {
      DynamicObject spec;
      spec["help"] =
"PortMap Options\n"
"      --port          The port to use when binding and servicing connections.\n"
"  -v, --verbose       True to be verbose, false not to be.\n"
"                      (default: false)\n"
"\n";

      DynamicObject opt(NULL);

      // create option to set external port
      opt = spec["options"]->append();
      opt["long"] = "--port";
      opt["argError"] = "The port must be an integer > 0.";
      opt["arg"]["target"] = mOptions["port"];

      // create option to set verbose
      opt = spec["options"]->append();
      opt["short"] = "-v";
      opt["long"] = "--verbose";
      opt["argError"] = "Verbose must be true or false.";
      opt["arg"]["target"] = mOptions["verbose"];

      return spec;
   };

   /**
    * Runs the app.
    *
    * @return true if successful, false if an exception occurred.
    */
   virtual bool run()
   {
      printf("Starting Monarch Benchmarking application...");

      return !Exception::isSet();
   };
};

class BenchmarkAppFactory : public AppFactory
{
public:
   BenchmarkAppFactory() : AppFactory(APP_NAME, "1.0")
   {
   }

   virtual ~BenchmarkAppFactory() {}

   virtual App* createApp()
   {
      return new BenchmarkApp();
   }
};

} // end namespace benchmark
} // end namespace apps
} // end namespace monarch

Module* createModestModule()
{
   return new monarch::apps::benchmark::BenchmarkAppFactory();
}

void freeModestModule(Module* m)
{
   delete m;
}
