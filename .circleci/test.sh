#!/bin/bash
set -e
BUILD_DIR=build-$1
cd $BUILD_DIR
echo "Recompile if needed"
make
echo "Starting tests"
mkdir -p $TEST_REPORTS
echo "Saving tests results to $TEST_REPORTS"
GTEST_OUTPUT="xml:$TEST_REPORTS/" CTEST_OUTPUT_ON_FAILURE=TRUE make test
echo "Gathering coverage"
make coverage
cd ..
gcovr -r . --exclude tests
gcovr -r . --exclude tests --html --html-details -o $TEST_REPORTS/coverage.html
