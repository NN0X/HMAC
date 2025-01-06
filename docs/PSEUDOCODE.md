# Pseudocode for HMAC algorithm

### [Go back to ABOUT](ABOUT.md)

## Pseudocode

```plaintext
function hmac is
    input:
        key:        Bytes    // Array of bytes
        message:    Bytes    // Array of bytes to be hashed
        hashFunc:   Function // The hash function to use (e.g. SHA-1)
        blockSize:  Integer  // The block size of the hash function (e.g. 64 bytes for SHA-1)
        outputSize: Integer  // The output size of the hash function (e.g. 20 bytes for SHA-1)

    // Compute the block sized key
    blockSizedKey = computeBlockSizedKey(key, hash, blockSize)

    opad ← blockSizedKey xor [0x5c blockSize]
    ipad ← blockSizedKey xor [0x36 blockSize]

    return  hash(opad ∥ hash(ipad ∥ message))

function computeBlockSizedKey is
    input:
        key:        Bytes    // Array of bytes
        hash:       Function // The hash function to use (e.g. SHA-1)
        blockSize:  Integer  // The block size of the hash function (e.g. 64 bytes for SHA-1)

    if (length(key) > blockSize) then
        key = hash(key)

    if (length(key) < blockSize) then
        return  Pad(key, blockSize)

    return  key
```
