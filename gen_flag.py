# generate kyber components
from kyber_py.kyber import Kyber512

pk, sk = Kyber512.keygen()

key, c = Kyber512.encaps(pk)

flag = b"flag{i_wish_my_arms_could_handle_all_this_pqc}"

# encrypt with kyber shared key aes256

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

aes_key = key
cipher = AES.new(aes_key, AES.MODE_ECB)

encrypted_flag = cipher.encrypt(pad(flag, 16))


# convert the flags to c arrays

def print_c_array(name, b):
    arr = ','.join(f'0x{x:02X}' for x in b)
    print(f"const uint8_t {name}[{len(b)}] = {{{arr}}};\n")

print_c_array("pk", pk)
print_c_array("ct", c)
print_c_array("flag", encrypted_flag)
