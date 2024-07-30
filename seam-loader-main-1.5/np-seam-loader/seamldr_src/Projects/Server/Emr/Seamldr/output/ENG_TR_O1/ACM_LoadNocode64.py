import itpii
itp = itpii.baseaccess(); itp.vp = 0
import acm

eip = itp.threads[itp.vp].state.regs.eip
ACM_Base=acm.SearchACM(eip)
if (ACM_Base!=0):
  itpii.printf("\nLoading ACM symbols ...\n")
  itp.threads[itp.vp].load(r"D:\work\np_seamldr\gnr\po\pr\public\firmware.security.tdx.np-seamldr\seamldr_src\Projects\Server\Emr\Seamldr\output\ENG_TR_O1\EMR_NP_SEAMLDR64_ENG_TR_O1.exe", at=itpii.Address(ACM_Base+0x35000), loadkey = "None", operation=itp.LoadOperations.nocode)
else:
  itpii.printf("\nACM Header not found within 128KB - Failed ACM source loading ...\n")
