#!/bin/bash
BUILD_DIR=build-$1
cd $BUILD_DIR
echo "Starting tests"
mkdir -p $TEST_REPORTS
echo "Saving tests results to $TEST_REPORTS"
GTEST_OUTPUT="xml:$TEST_REPORTS/" CTEST_OUTPUT_ON_FAILURE=TRUE make test