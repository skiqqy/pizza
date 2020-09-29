<div align="center">
<img src="assets/header.png"><br>
</div>

The pizza project aims to implement an interpreter for an assembler language.
The spec will be uploaded in a few days, but for now here is an outline of the
project.

## Why

Because it sounds like fun, and is unique.

## Pre Spec/ General plan

* RISC isa.
* Written in C.
* Custom Assembler lang, called slice.
* Either register or stack based (Must still decide).

## Registers

| Register | Details |
| -- | -- |
| R0 | Normally stores the result from an instruction |
| R1 | TODO |
| R2 | TODO |
| R3 | TODO |
| R4 | TODO |
| R5 | TODO |
| R6 | TODO |
| R7 | TODO |
| R8 | TODO |

## Flags

The flags will contain the results from (mostly) logic operations.
See the table below to see what the bits represent.
Note you cannot access the Flags register directly, instead you operate on it
indirectly via the instructions being parsed.

| Bit Mask |    Name     | Abbreviation |   =1    | =0       |
| -------- | ----------  | ------------ | ------- | -------- |
| 0x0001   | Zero Flag   | ZF           | Is Zero | Not Zero |
| 0x0002   | Sign Flag   | SF           | Is Neg  | Is Pos   |
| 0x0004   | Parity Flag | PF           | Is Even | Is Odd   |

[comment]: # (| 0x0000   |           |              |         |          |)

## TODO

- [ ] Design ebnf for `slice` lang.
- [ ] Create a formal spec.
- [ ] Decide on instruction's.
