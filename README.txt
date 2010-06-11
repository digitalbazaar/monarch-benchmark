Apache+PHP and Monarch Benchmarks
---------------------------------

This benchmark suite is used to benchmark Apache and Monarch to see how the
performance profiles look under heavy concurrent load.

The benchmarks require an installation of Apache and a fresh build of 
Monarch to complete. The benchmarks are designed to run in a Unix environment -
Ubuntu, Mac OS X or most other variants. It helps if you run the servers on
one machine and the benchmarks from another machine. A fast network connection
is also required - 100Mbps is recommended, 1Gbps is ideal.

Monarch Benchmark Source Code
-----------------------------

You can get the Monarch Benchmark source code by doing the following commands:

mkdir tmp
git clone git://github.com/digitalbazaar/monarch-benchmark.git
./build-setup

Installing and Running Apache
-----------------------------

Install Apache2 with the prefork MPM Worker. 
Install mod-php5 for Apache2.

cd tmp/monarch-benchmark/apache
./apache-start

Building Monarch
----------------

You can build Monarch from the source code available via Github:

mkdir tmp
git clone git://github.com/digitalbazaar/monarch.git
./build-setup
make
./monarch-run pong

Running the Benchmarks
----------------------

You can run a set of benchmarks by using the bench-url tool in the apache
directory.

cd tmp/monarch-benchmark/apache
./bench-url http://URL_TO_BENCHMARK/

By default, the data will be placed into a directory called testdata. You can 
generate gnuplot graphs by running the following command:

./graph-data testdata

You can view the plots by doing the following:

gnuplot testdata/gnuplot-throughput.plot
gnuplot testdata/gnuplot-latency.plot

To benchmark Apache, do this:

./bench-url http://apache-webserver:8001/pong.php
mv testdata apache-data
./graph-data apache-data
gnuplot apache-data/gnuplot-throughput.plot
gnuplot apache-data/gnuplot-latency.plot

To test Monarch, do this:

./bench-url http://monarch-webserver:19500/data/128
mv testdata monarch-data
./graph-data monarch-data
gnuplot monarch-data/gnuplot-throughput.plot
gnuplot monarch-data/gnuplot-latency.plot

