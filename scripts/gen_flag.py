# generate kyber components
from kyber_py.kyber import Kyber512

# bob
# pk = public key
# sk = private (secret) key
public_key, secret_key = Kyber512.keygen()


# alice
# key = shared secret generated (symmetric)
# c = ciphertext that encrypts the shared secret for the owner of sk
shared_key, ct = Kyber512.encaps(public_key)

# bob
# recovering the key from ciphertext (symmetric key)
# _key = Kyber512.decaps(sk, ct)

#now both parties have the same symmetric key exchanged 

# hide pk and sk and encrypted flag(which is encrypted with the shared key we would get during encaps) in binary -> user has to retrieve the pk and sk -> do the encaps to get the c -> use the sk retrieved from the binary and the generated c to decrypt msg -> decrypt msg


# ------------------------------------------------------------------------

flag = b"flag{i_wish_my_arms_could_handle_all_this_pqc}"

# encrypt with kyber shared key aes256ecb (ecb used cuz i dont want iv to make it easier)

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

aes_key = shared_key
cipher = AES.new(aes_key, AES.MODE_ECB)

encrypted_flag = cipher.encrypt(pad(flag, 16))

# ------------------------------------------------------------------------

# convert the flags to c arrays

def print_c_array(name, b):
    arr = ','.join(f'0x{x:02X}' for x in b)
    print(f"const uint8_t {name}[{len(b)}] = {{{arr}}};\n")

print_c_array("pk", public_key)
print_c_array("secret_key", secret_key)
print_c_array("ct", ct)
print_c_array("encrypted_flag", encrypted_flag)
