#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


fau_timer_module = Extension('_fau_timer',
                           sources=['fau_timer_wrap.c', 'fau_timer.c'],
                           swig_opts=['-fPIC'],
                           )

setup (name = 'fau_timer',
       version = '0.1',
       author      = "Sebastian Schinzel",
       description = """FAU Timer""",
       ext_modules = [fau_timer_module],
       py_modules = ["fau_timer"],
       )
