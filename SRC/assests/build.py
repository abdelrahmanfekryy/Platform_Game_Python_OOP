#set PATH=%PATH%;C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x86
#set INCLUDE=C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um;C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\winrt
#set LIB=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\ucrt\x86;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x86
from cffi import FFI
import os
ffibuilder = FFI()
with open("resorces/functions.h") as f:
    ffibuilder.cdef(f.read())
ffibuilder.set_source("engine",'#include "resorces/functions.h"',sources=["resorces/functions.c"])
ffibuilder.compile()