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
import tempfile
import shutil
import argparse


VERBOSITY = 1


def log(message, severity=5):
    """Utility function to write a message to stderr if logging is enabled"""
    global VERBOSITY
    if severity < VERBOSITY:
        print(message, file=sys.stderr)


class Demo:
    """
    Demo object for me to prototype the format of a test object on
    """
    def __init__(self):
        self.test = "Moo"
        self.dir = tempfile.mkdtemp(prefix="EmpiricalQOrgTesting")
        self.name = "test test"

    def __enter__(self):
        pass

    def __exit__(self, exc_type, exc_value, traceback):
        if traceback is None:
            log("Cleaning up after test '{}'".format(self.name))
            shutil.rmtree(self.dir)
        else:
            log("ERROR: Problem encountered when executing test", 0)
            log("Traceback follows: {}".format(traceback), 0)


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

    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    if args.debug:
        VERBOSITY = 6
    elif args.set_verbosity:
        VERBOSITY = args.verbosity

    with Demo() as quail:
        pass
