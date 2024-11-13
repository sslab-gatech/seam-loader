set input=%1
make -f ..\project.mak npseamldr cleanall
git checkout .
scp mundo:~/p-seam-loader/bin/debug/pseamldr.so ./
scp mundo:~/p-seam-loader/bin/debug/pseamldr.so.consts ./
make -f ..\project.mak npseamldr
scp output\ENG_TR_O1\EMR_NP_SEAMLDR_ENG_TR_O1.DBG.bin mundo:~/bin/%input%.bin
