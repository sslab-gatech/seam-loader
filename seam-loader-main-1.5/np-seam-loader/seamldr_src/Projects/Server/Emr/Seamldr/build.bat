@echo off
setlocal

:: Check for pseamldr.so and pseamldr.so.consts
if not exist pseamldr.so (
    echo Please build pseamldr.so and pseamldr.so.consts and place them under this directory.
    echo You can build them by running 'build.sh' in 'seam-loader\seam-loader-main-1.5\p-seam-loader' on Ubuntu.
    exit /b 1
)
if not exist pseamldr.so.consts (
    echo Please build pseamldr.so and pseamldr.so.consts and place them under this directory.
    echo You can build them by running 'build.sh' in 'seam-loader\seam-loader-main-1.5\p-seam-loader' on Ubuntu.
    exit /b 1
)

make -f ..\project.mak npseamldr cleanall
git checkout .
make -f ..\project.mak npseamldr

echo NP-SEAMLDR binary built under 'output\ENG_TR_O1\EMR_NP_SEAMLDR_ENG_TR_O1.DBG.bin'.
