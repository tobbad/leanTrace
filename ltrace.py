# !/usr/bin/env python3



def hash(inData):
    trgt_len = 256
    hash_const = 65599
    res = 0
    for idx in range(trgt_len):
        idx = 256-idx-1
        c = 0
        if len(inData) > idx:
            i = len(inData)-idx-1
            c = ord(inData[i])
        print(idx, chr(c) if c>0 else ".", c)
        res = (res * hash_const + c) % (1<<32)
    return res ^ (res >> 16)
        

if __name__ == "__main__":
    exp_hash=0xf1c6fd7f
    res = hash("funny_bone")
    print("0x%08x %d" %( res, res==exp_hash)
