Choose the library that matches the run-time library you use. If you
choose the wrong type of library, you'll get lots of linker errors.
(In Visual C++, select Project | Settings | C++ | Code Generation and check the field 'Use run-time library').

Library      Run-time library

osc_s.lib    SingleThreaded
osc_m.lib    MultiThreaded
osd_md.lib   MultiThreaded DLL
osc_ds.lib   Debug SingleThreaded
osc_dm.lib   Debug MultiThreaded
osc_dmd.lib  Debug MultiThreaded DLL