import cli
from simmod.stc_tools.startup import mem_read

def get_acm_base_address(ptr):
    LookBackBlockCount = (256*1024/1024)  # size=256B, block size 1KB
    DecrementStepSize  = 1024  #1KB aligned

    if ptr == 0:
        print "Bad EIP"
        return
    ptr = ptr&0xfffffc00 # 1KB aligned pointer
    print "\tSearch ACM from 0x%x (1KB aligned pointer)"%ptr
    sign = 0
    while LookBackBlockCount > 0x0:
        sign = mem_read(ptr, 2)._value
        #if sign == 0x0002:
        if (mem_read(ptr+0x10,4)._value == 0x00008086) and (mem_read(ptr+0x4c0,8)._value == 0x18DB46A77FC03AAA):
            print "\t > Found ACM header signature at 0x%x"%ptr
            print r"ACM_32_File = D:\work\np_seamldr\gnr\po\pr\public\firmware.security.tdx.np-seamldr\seamldr_src\Projects\Server\Emr\Seamldr\output\ENG_TR_O1\EMR_NP_SEAMLDR_ENG_TR_O1.exe"
            print "ACM_32_Remap_Address = 0x%x\n" % (ptr - 0x1000)
            print r"ACM_64_File = D:\work\np_seamldr\gnr\po\pr\public\firmware.security.tdx.np-seamldr\seamldr_src\Projects\Server\Emr\Seamldr\output\ENG_TR_O1\EMR_NP_SEAMLDR64_ENG_TR_O1.exe"
            print "ACM_64_Remap_Address = 0x%x\n" % (ptr + 0x35000)
            return ptr
        ptr = ptr - DecrementStepSize
        LookBackBlockCount = LookBackBlockCount - 1
    print "\t > ACM header signature is not found"
    return 0

get_acm_base_address(conf.skybay.mb.cpu0.core[0][0].eip) # search for acm address
