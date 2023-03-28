@rem
@mkdir build
@rem
@cd build
@rem 
@cmake ..
@rem
@cmake --build  . --config Debug
@rem
@copy .\Debug\main.exe ..\
@rem
@cd ..
