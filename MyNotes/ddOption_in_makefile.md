```bash
dd if=/dev/zero of=xv6.img count=10000

dd if=bootblock of=xv6.img conv=notrunc

dd if=kernel of=xv6.img seek=1 conv=notrunc 
```
the block size for this is around 512 bytes.

## options used during the dd command.

| Part           | Meaning                                                                                |
| -------------- | -------------------------------------------------------------------------------------- |
| `dd`           | Copies data from an input file to an output file, block by block                       |
| `if=/dev/zero` | Specifies `/dev/zero` as the input source; it provides an endless stream of zero bytes |
| `of=xv6.img`   | Specifies `xv6.img` as the output file                                                 |
| `count=10000`  | Copies **10,000 input blocks**                                                         |
| `conv=notrunc` | Prevents `dd` from truncating the existing output file                                 |
| `seek=1`       | Skips **1 output block (512 bytes)** before writing                                    |
| `if=bootblock` | Uses the compiled xv6 boot block as the input                                          |
| `if=kernel`    | Uses the compiled xv6 kernel as the input                                              |


truncating meaning short the file befoe writing overriding that existing file with zeros.

