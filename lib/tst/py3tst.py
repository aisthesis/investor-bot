#!/usr/bin/env python3
import imp

dependencies = ('matplotlib', 'numpy', 'pandas', 'pynance')

def test_pkg(pkg):
    try:
        imp.find_module(pkg)
        print("OK. Package '{0}' found.".format(pkg))
    except ImportError:
        print("\033[91mPackage '{0}' not found. Please install '{0}' on your system.\033[0m".format(pkg))

print("Python 3.x dependencies:")

for pkg in dependencies:
    test_pkg(pkg)

print("Note: Python 3.x dependencies are not needed if you use only Python 2.x\n")
