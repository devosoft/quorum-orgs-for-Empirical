#! /usr/bin/env python3

"""
This is a module designed to help me run tests on this Empirical module

This module (will) contain(s) a collection of classes that will test a portion of the functionality
offered by this module. These classes will abstract the configuration and execution of the module,
and verification of the results of the program. This will be done primarily through the use of the
python subprocess module.

This module was written by Jacob Fenton and is Copyright (c) 2016 Michigan State University

Since this is done as a component of the Empirical library it'll share a licence with Empirical

Details can be found at github.com/devosoft/empirical, under doc/license, until I get around to
adding a licence to this project.
"""

import subprocess
import sys
import os
import tempfile
import shutil
import argparse
import queue
import threading
import traceback


VERBOSITY = 1

#TODO: replace with the logging module, which is threadsafe


def log(message, severity=5):
    """Utility function to write a message to stderr if logging is enabled"""
    global VERBOSITY
    if severity < VERBOSITY:
        print(message, file=sys.stderr)


def worker(q, dir, doneq):
    """
    Function that gets threaded

    q: queue object to find the test configurations in
    """
    print("LEMME IN")
    while not q.empty():
        item = q.get()
        print("Item is {}".format(item))

        try:
            args = ["{}/run.out".format(dir)]
            args += item[1]
            print(args)
            p = subprocess.Popen(args, stdout=subprocess.PIPE)
        except Exception as err:
            print("Caught err")
            print(err)
            q.task_done()
            sys.exit(1)
        print("processing item")
        p.wait()
        doneq.put_nowait((item[0], p.stdout.read()))
        print("Item processed")
        q.task_done()
        #TODO: add code to do output verification here


class Demo:
    """
    Demo object for me to prototype the format of a test object on
    """
    def __init__(self, name, source):
        self.executable = source
        self.dir = tempfile.mkdtemp(prefix="EmpiricalQOrgTesting")
        self.name = name
        self.configs = []
        self.queue = queue.Queue()
        self.doneq = queue.Queue()

        # copy the executable into the temp dir
        shutil.copy(source, "{}/run.out".format(self.dir))

    def __enter__(self):
        return self

    def add_test(self, name, args, known_output=None, output_filename=None):
        """
        Utility to add a test to this tester

        name: the name of this test
        config: the list of args to launch the test of the form [-switch1 value1 ...]
        known_output: the filename of the known output for this test to check output against
        output_filename: the expected filename for the output of the test--used with known_output

        Note that all classes share a specific executable, and all tests in a class are run
        in the same folder, so args must be configured to not collide.
        """
        if known_output is not None:
            assert(output_filename is not None and "If known_output is specified, "
                   "output filename must be also")

        print("Putting in queue")
        self.queue.put((name, args, known_output, output_filename))
        print("Put in queue")

    def run_tests(self, threads=1):
        """
        Execute all the configured tests within this module

        Copies the executable into the temporary folder for this module, then launches
        as many tests as threads allowed.
        """
        for i in range(0, threads):
            t = threading.Thread(target=worker(self.queue, self.dir, self.doneq))
            t.start()

        print("Threads launched, waiting to complete")
        self.queue.join()
        print("Queue done, dumping results")

        while not self.doneq.empty():
            item = self.doneq.get()
            print(item)

    def __exit__(self, exc_type, exc_value, tb):
        if tb is None:
            log("Cleaning up after test '{}'".format(self.name))
            shutil.rmtree(self.dir)
        else:
            log("ERROR: Problem encountered when executing test", 0)
            log(exc_value, 0)
            #log("Traceback follows: {}".format(traceback), 0)
            traceback.print_tb(tb)


def get_args():
    """
    Get and process command line arguments
    """

    parser = argparse.ArgumentParser()

    group = parser.add_mutually_exclusive_group()
    group.add_argument("--set-verbosity", help="Set the verbosity to the desired level"
                       ", where higher is louder")
    group.add_argument("--debug", "-v", help="Set the verbosity to the highest level",
                       action="store_true")

    parser.add_argument("--threads", "-t", help="the number of CPU threads to use when running"
                        "tests")

    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    if args.debug:
        VERBOSITY = 6
    elif args.set_verbosity:
        VERBOSITY = args.verbosity

    with Demo("demo_test", "../standard-grid-quorum.out") as quail:
        quail.add_test("demo", [])
        quail.run_tests()
